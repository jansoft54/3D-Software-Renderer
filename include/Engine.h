#ifndef ENGINE_H
#define ENGINE_H
#include <vector>
#include <SFML/Graphics.hpp>
#include"Entity.h"
#include "Math/Vec3.h"
#include "World.h"
#include "Camera.h"
#include "Rasterizer.h"
#include "SRandom.h"
class Engine
{
    public:
        Engine(sf::RenderWindow&);
        Engine() = default;
       ~Engine() = default;

        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 800;

        void Update(float);
        void handleInput(float);
        void Render();
        void DrawLine(Vec3,Vec3,Vec3);

    private:
        std::vector<Entity> objects;
        sf::RenderWindow& window;
        Vec3 rotation;
        Vec3 transform;
        Camera camera;
        World& world = World::getWorldInstance();
        Rasterizer r;
        SRandom ran;

        float Mx = 0;
        float My = 0;




};

#endif // ENGINE_H
