#include <iostream>
#include <cstdlib>
#include "client.h"

int main() {
	try {
		Client app;
		app.run();
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		exit(EXIT_FAILURE);
	} catch (...) {
		std::cerr << "Unknown exception" << std::endl;
		exit(EXIT_FAILURE);
	}

	return 0;
}