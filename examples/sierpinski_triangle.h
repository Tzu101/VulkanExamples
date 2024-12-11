#pragma once

#include "static_triangle.h"

#include <vector>

class SierpinskiTriangle: public StaticTriangle {
public:
    SierpinskiTriangle();

private:
    void load_sierpinski_model();

   static constexpr int SIERPINSKI_DEPTH = 7;
};
