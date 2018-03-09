#ifndef CAMERA_H
#define CAMERA_H
#include "Math/Vec3.h"
#include "World.h"

class Camera
{
    public:
        Camera();
        virtual ~Camera();
    public:
        void Transform(Vec3&);
        void Rotate(float,float);
        Vec3 pos;

    private:
        World& world;
        Vec3 rotation;
      //  Vec3 origin;
};

#endif // CAMERA_H
