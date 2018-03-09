#ifndef RASTERIZER_H
#define RASTERIZER_H
#include "Math/Vec3.h"
#include <limits>
#include <SFML/Graphics.hpp>


class Rasterizer
{
    public:
        Rasterizer(sf::RenderWindow& window);
        virtual ~Rasterizer() = default;
        void DrawTriangle(const Vec3*v1, const Vec3*v2, const Vec3* v3, const sf::Color& c);
    private:
        void fillFlatTopTriangle(const Vec3*v1, const Vec3*v2, const Vec3* v3, const sf::Color& c);
        void fillFlatBottomTriangle(const Vec3*v1, const Vec3*v2, const Vec3* v3, const sf::Color& c);
        void PutPixel(int x,int y,sf::Uint8 r, sf::Uint8 g,sf::Uint8 b);
    private:
        sf::Uint8* pixels ;
        sf::Sprite* sprite;
        sf::RenderWindow& window;
        sf::Texture texture;
        int* depth_buffer;
};


#endif // RASTERIZER_H
