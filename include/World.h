#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include "Math/Vec3.h"
#include "Entity.h"
#include "Math/Matrix3f.h"

class World
{
    private:
        std::vector<Entity> objects;
        Matrix3f matrix;

    public:
        World() = default;
        World(const World&) = delete;
        static World& getWorldInstance();
        void addEntityToWorld(Entity&);
        void TransformWorld(Vec3&);

        void RotateWorld(float,float,Vec3&);
        void RotateObjects(Vec3&);

        void GenerateWorld();
        void GenerateTerrain(float, float, const Vec3&);

        std::vector<Entity>& getObjects();





};

#endif // WORLD_H
