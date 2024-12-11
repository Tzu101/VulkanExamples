#include <iostream>

#include "static_triangle.h"
#include "sierpinski_triangle.h"

int main() {
    try {
        SierpinskiTriangle app{};
        //StaticTriangle app{};
        app.run();
    }
    catch (std::runtime_error err) {
        std::cerr << err.what() << std::endl;
    }
}
