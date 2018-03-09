#pragma once
#include <vector>
#include "Math/Vec3.h"


struct Mesh
{
    std::vector< Vec3> vertices;
    std::vector<std::size_t> indices;


};
