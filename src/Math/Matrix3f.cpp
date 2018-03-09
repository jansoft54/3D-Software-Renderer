#include "Matrix3f.h"
#include <iostream>
#include <cstring>
#include <math.h>
#define PI 3.14159265
#define rad(x)(x * PI/180)



Matrix3f::Matrix3f()
{

   Identity();

}
Matrix3f::Matrix3f(const std::initializer_list<int> values)
{
    if(values.size() != 9)
        return;
   std::copy(values.begin(),values.end(),matrix);
}

Matrix3f Matrix3f::operator*( Matrix3f& matrix)
{
    Matrix3f result;
    for(int j = 0; j<3; ++j)
    {
        for(int k = 0; k <3; ++k)
        {
            for(int i = 0; i<3;++i)
            {
                result[i + j * 3] +=  this->matrix[i + j * 3] * matrix[3 * i + k];
            }
        }
    }
    return result;
}
Vec3& Matrix3f::operator*( Vec3& vec)
{
    Vec3 result(0,0,0);
    result.x = vec.x * matrix[0 + 0 * 3] + vec.y * matrix[1 + 0 * 3] + vec.z * matrix[2 + 0 * 3];
    result.y = vec.x * matrix[0 + 1 * 3] + vec.y * matrix[1 + 1 * 3] + vec.z * matrix[2 + 1 * 3];
    result.z = vec.x * matrix[0 + 2 * 3] + vec.y * matrix[1 + 2 * 3] + vec.z * matrix[2 + 2 * 3];
    vec = result;
    return vec;
}
float& Matrix3f::operator[]( int index)
{
    return matrix[index];
}
Vec3& Matrix3f::Rotate( Vec3& pos,float xdiff , float ydiff,float zdiff )
{
    Matrix3f xRotation;
    Matrix3f yRotation;
    Matrix3f zRotation;

    xRotation[0 + 0 * 3] = 1;                xRotation[1 + 0 * 3] = 0;                xRotation[2 + 0 * 3] = 0;
    xRotation[0 + 1 * 3] = 0;                xRotation[1 + 1 * 3] = cos(rad(xdiff));  xRotation[2 + 1 * 3] = -sin(rad(xdiff));
    xRotation[0 + 2 * 3] = 0;                xRotation[1 + 2 * 3] = sin(rad(xdiff));  xRotation[2 + 2 * 3] =  cos(rad(xdiff));

    yRotation[0 + 0 * 3] = cos(rad(ydiff));  yRotation[1 + 0 * 3] = 0;                yRotation[2 + 0 * 3] = sin(rad(ydiff));
    yRotation[0 + 1 * 3] = 0;                yRotation[1 + 1 * 3] = 1;                yRotation[2 + 1 * 3] = 0;
    yRotation[0 + 2 * 3] =-sin(rad(ydiff));  yRotation[1 + 2 * 3] = 0;                yRotation[2 + 2 * 3] = cos(rad(ydiff));

    zRotation[0 + 0 * 3] = cos(rad(zdiff));  zRotation[1 + 0 * 3] = -sin(rad(zdiff)); zRotation[2 + 0 * 3] = 0;
    zRotation[0 + 1 * 3] = sin(rad(zdiff));  zRotation[1 + 1 * 3] =  cos(rad(zdiff)); zRotation[2 + 1 * 3] = 0;
    zRotation[0 + 2 * 3] = 0;                zRotation[1 + 2 * 3] = 0;                zRotation[2 + 2 * 3] = 1;

    xRotation * pos; yRotation * pos; zRotation * pos;
    Restore();
    return pos;
}
void Matrix3f::Identity()
{
    this->matrix[0 + 0 * 3] = 1;
    this->matrix[1 + 1 * 3] = 1;
    this->matrix[2 + 2 * 3] = 1;

}
void Matrix3f::Restore()
{
    std::memset(this->matrix,0,9 * sizeof(int));
    Identity();


}
