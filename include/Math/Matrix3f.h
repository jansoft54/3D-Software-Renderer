#pragma once
#include "Vec3.h"
#include "initializer_list"

class Matrix3f
{
    public:
        Matrix3f();
        Matrix3f(const std::initializer_list<int>);
        virtual ~Matrix3f() = default;
    public:
        Vec3&    Rotate(Vec3&,float,float,float);

        Matrix3f operator* (Matrix3f&);
        Vec3&    operator* (Vec3&);
        float&   operator[](int index);

    private:
         float matrix[9]{0};
};


