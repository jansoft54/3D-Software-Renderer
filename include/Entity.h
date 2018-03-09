#pragma once
#include "Mesh.h"
#include <initializer_list>


class Entity
{
    public:
        Entity(float,float,float);
        virtual ~Entity() = default ;
    public:
        Mesh& getMesh();
        Vec3 origin;
        Vec3 startorigin;
        void addFace(std::initializer_list<Vec3>);

    public:
        float alphaX = 0;
        float alphaY = 0;
        float alphaZ = 0;
        Mesh mesh;

};

