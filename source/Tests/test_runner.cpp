#include "Tests/GameTestSuite.h"
#include <iostream>

int main() {
    try {
        Nauvoo::GameTestSuite suite;
        suite.RunAllTests();
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "TEST SUITE ERROR: " << e.what() << std::endl;
        return 1;
    }
}
