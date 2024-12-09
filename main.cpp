#include <iostream>

#include "sierpinski_triangle.h"

int main() {
    try {
        SierpinskiTriangle app{};
        app.run();
    }
    catch (std::runtime_error err) {
        std::cerr << err.what() << std::endl;
    }
}
