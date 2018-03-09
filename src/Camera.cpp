#include "Camera.h"
#include <iostream>
Camera::Camera()
:pos(0,0,3)
,world(World::getWorldInstance())
,rotation(0,0,0)
{
    //ctor
}

void Camera::Transform(Vec3& vec)
{

   if(vec.x != 0 || vec.y != 0|| vec.z != 0)
   {
    pos -= vec;
    world.TransformWorld(vec);

   }

}
void Camera::Rotate(float x,float y)
{
    if(x != 0 || y != 0)
        world.RotateWorld(x,y,pos);
}
Camera::~Camera()
{
    //dtor
}
