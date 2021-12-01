#pragma once 

#include <string>

struct UUID {
    uint8_t data[16];
};

UUID generateUUID();

bool operator==(const UUID& lhs, const UUID& rhs) noexcept;

std::string uuidToHexString(const UUID& uuid, char delim = '-');