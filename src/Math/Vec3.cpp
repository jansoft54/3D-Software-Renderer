#include "Math/Matrix3f.h"


Vec3 Vec3::crossProduct(const Vec3& one , const Vec3& two)
{
 return {one.y * two.z - one.z * two.y
        ,one.z * two.x - one.x * two.z
        ,one.x * two.y - one.y * two.x};
}
float Vec3::dotProduct(const Vec3& one , const Vec3& two)
{
 return one.x * two.x + one.y * two.y + one.z * two.z;
}
Vec3::Vec3(float x , float y ,float z)
: z(z), x(x), y(y)
{
}

Vec3& Vec3::operator+=(const Vec3& vec)
{
    x += vec.x;
    y += vec.y;
    z += vec.z;

    return *this;
}
Vec3 Vec3::operator+(const Vec3& vec)
{
    x += vec.x;
    y += vec.y;
    z += vec.z;

    return {x + vec.x, y + vec.y , z + vec.z};
}

Vec3& Vec3::operator*=(float x)
{
    x *= x;
    y *= x;
    z *= x;

    return *this;
}
Vec3& Vec3::operator-=(const Vec3& vec)
{
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;

    return *this;
}
Vec3 Vec3::operator- (const Vec3& vec)
{

    return {x - vec.x, y - vec.y , z - vec.z};
}
bool Vec3::equals(Vec3& vec)
{
    return this->x == vec.x && this->y == vec.y && this->z == vec.z;
}
