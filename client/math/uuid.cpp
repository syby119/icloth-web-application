#include <cstdio>
#include <chrono>
#include <limits>
#include <random>
#include <cstring>
#include <sstream>

#include "uuid.h"

struct UUIDNode {
    uint8_t nodeID[6];
};

struct UUIDState {
    uint64_t timestamp;
    UUIDNode  node;
    uint16_t clockSequence;
};


/* read UUID generator state from non-volatile store */
bool readState(uint64_t& timestamp, UUIDNode& node, uint16_t& clockSequence) {
    static bool inited = false;

    bool success = true;
    /* only need to read state once per boot */
    if (!inited) {
        UUIDState state;

        FILE *fp = fopen("uuid_state.txt", "rb");
        if (!fp || fread(&state, sizeof(UUIDState), 1, fp) != 1) {
            success = false;
        }
        fclose(fp);

        if (success) {
            timestamp = state.timestamp;
            node = state.node;
            clockSequence = state.clockSequence;
            inited = true;
        }
    }

    return success;
}

/* save UUID generator state back to non-volatile storage */
bool writeState(uint64_t timestamp, UUIDNode node, uint16_t clockSequence) {
    static bool inited = false;
    static uint64_t nextSaveTime;

    bool success = true;
    if (!inited) {
        nextSaveTime = timestamp;
        inited = true;
    }

    // always save state to volatile shared state
    UUIDState state = { timestamp, node, clockSequence };
    if (timestamp >= nextSaveTime) {
        FILE* fp = fopen("uuid_state.txt", "wb");
        if (!fp || fwrite(&state, sizeof(UUIDState), 1, fp) != 1) {
            success = false;
        }
        fclose(fp);

        // schedule next save for 10 seconds from now
        nextSaveTime = timestamp + (10 * 10'000'000);
    }

    return success;
}

/* get time as 60-bit 100ns ticks since UUID epoch */
static uint64_t getSystemTime() {
    using Clock = std::chrono::system_clock;
    using DurationUnit = std::ratio<1, 10'000'000>;
    using Duration = std::chrono::duration<uint64_t, DurationUnit>;
    
    static Clock::time_point lastTimeStamp = Clock::now();
    static uint64_t tick = 0;
    constexpr uint64_t resolution = DurationUnit::den / Clock::period::den;

    Clock::time_point now;
    while (true) {
        now = Clock::now();
        // time point since last clock reading changed
        if (now != lastTimeStamp) {
            tick = 0;
            lastTimeStamp = now;
            break;
        }
        // time elapsed is less than resolution
        if (tick < resolution - 1) {
            ++tick;
            break;
        }
    }

    // ticks since January 1, 1970 to now (100ns)
    uint64_t t1 = std::chrono::duration_cast<Duration>(now.time_since_epoch()).count();
    // ticks since October 15, 1582 to January 1, 1970 (100ns)
    constexpr uint64_t t2 = 0x01B21DD213814000ULL;
    
    return t1 + t2 + tick;
}

/* system dependent call to get IEEE node ID(e.g Network card MAC address).
   This sample implementation generates a random node ID. */
static UUIDNode getNodeIdentifier() {
    static bool inited = false;
    static UUIDNode savedNode = { { 0, 0, 0, 0, 0, 0 } };

    if (!inited) {
        FILE* fp = fopen("uuid_nodeid.txt", "rb");
        if (fp) {
            fread(&savedNode, sizeof(UUIDNode), 1, fp);
            fclose(fp);
        } else {
            uint64_t t = std::chrono::steady_clock::now().time_since_epoch().count();
            uint32_t seed = ((t >> 32) ^ t) & 0xFFFFFFFF;
            std::default_random_engine e { seed };
            std::uniform_int_distribution<uint64_t> d {
                0, std::numeric_limits<uint64_t>::max() };
            uint64_t id = d(e);
            memcpy(&savedNode, &id, sizeof(UUIDNode));

            fp = fopen("uuid_nodeid.txt", "wb");
            if (fp) {
                fwrite(&savedNode, sizeof(UUIDNode), 1, fp);
                fclose(fp);
            }
        }
    }

    return savedNode;
}

/* generate a crypto-quality random number. This sample doesn't do that */
static uint16_t getTrueRandom() {
    uint64_t t = std::chrono::steady_clock::now().time_since_epoch().count();
    uint32_t seed = ((t >> 32) ^ t) & 0xFFFFFFFF;
    std::default_random_engine e { seed };

    std::uniform_int_distribution<uint16_t> d {
        0, std::numeric_limits<uint16_t>::max() };

    return d(e);
}

/* Construct a version 1 uuid with the information we've gathered
   plus a few constants. */
static UUID formatUUID(uint64_t timestamp, UUIDNode node, uint16_t clockSequence) {
    UUID uuid;

    uint32_t timeLow = timestamp & 0xFFFFFFFF;
    uint16_t timeMid = (timestamp >> 32) & 0xFFFF;
    uint16_t timeHighAndVersion = (timestamp >> 48) & 0x0FFF;
    timeHighAndVersion |= (1 << 12);
    
    uint8_t clockSequenceLow = clockSequence & 0xFF;
    uint8_t clockSequenceHighAndReserved = (clockSequence & 0x3F00) >> 8;
    clockSequenceHighAndReserved |= 0x80;

    memcpy(uuid.data + 0, &timeLow, sizeof(timeLow));
    memcpy(uuid.data + 4, &timeMid, sizeof(timeMid));
    memcpy(uuid.data + 6, &timeHighAndVersion, sizeof(timeHighAndVersion));
    memcpy(uuid.data + 8, &clockSequenceHighAndReserved, sizeof(clockSequenceHighAndReserved));
    memcpy(uuid.data + 9, &clockSequenceLow, sizeof(clockSequenceLow));
    memcpy(uuid.data + 10, &node, sizeof(node));

    return uuid;
}

UUID generateUUID() {
    uint64_t timestamp = getSystemTime();
    UUIDNode node = getNodeIdentifier();

    uint64_t lastTimestamp;
    UUIDNode lastNode;
    uint16_t clockSequence;
    bool success = readState(lastTimestamp, lastNode, clockSequence);

    if (!success || memcmp(&node, &lastNode, sizeof(UUIDNode))) {
        clockSequence = getTrueRandom();
    } else if (timestamp < lastTimestamp){
        ++clockSequence;
    }

    writeState(timestamp, node, clockSequence);

    return formatUUID(timestamp, node, clockSequence);
}

bool operator==(const UUID& lhs, const UUID& rhs) noexcept {
    for (int i = 0; i < 16; ++i) {
        if (lhs.data[i] != rhs.data[i]) {
            return false;
        }
    }

    return true;
}

std::string uuidToHexString(const UUID& uuid, char delim) {
    std::string result;
    const int ranges[] = { 0, 4, 6, 8, 10, 16 };
    const int n = sizeof(ranges) / sizeof(int);
    for (int i = 1; i < n; ++i) {
        for (int j = ranges[i - 1]; j < ranges[i]; ++j) {
            std::stringstream hexstream;
            hexstream << std::hex << static_cast<int>(uuid.data[j]);
            std::string str = hexstream.str();
            if (str.length() < 2) {
                result += "0";
            }
            result += str;
        }

        if (i < n - 1) {
            result += delim;
        }
    }

    return result;
}