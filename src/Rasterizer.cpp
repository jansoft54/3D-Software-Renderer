#include "Rasterizer.h"
#include <iostream>
#include <cmath>
#include <cstring>
#include "Engine.h"
Rasterizer::Rasterizer(sf::RenderWindow& win)
:pixels(new sf::Uint8[Engine::WIDTH*Engine::WIDTH *4])
,window(win)
,depth_buffer(new int[800*800]{std::numeric_limits<int>::infinity()})
{
    texture.create(Engine::WIDTH,Engine::WIDTH);
    sprite = new sf::Sprite(texture);
}


void Rasterizer::DrawTriangle( const Vec3*v1, const Vec3*v2, const Vec3* v3, const sf::Color& c)
{
    if(v2->y < v1->y) std::swap(v1,v2);
    if(v3->y < v1->y) std::swap(v1,v3);
    if(v3->y < v2->y) std::swap(v2,v3);

 //std::cout << v1->y << " " << v2->y <<" " << v3->y<<std::endl;
    if(v1->y == v2->y)
    {
        if(v2->x < v1->x) std::swap(v1,v2);
        fillFlatTopTriangle(v1,v2,v3,c);

    }
    else if(v2->y == v3->y)
    {
        if(v3->x < v2->x) std::swap(v2,v3);
        fillFlatBottomTriangle(v1,v2,v3,c);
    }
    else
    {
//        const float a = (v2->y - v1->y) / (v3->y - v1->y);
        Vec3 v4{v1->x + ((v2->y - v1->y) / (v3->y - v1->y)) * (v3->x - v1->x),v2->y,0};
        if(v2->x < v4.x) // right major
        {
            fillFlatBottomTriangle(v1,v2,&v4,c);
            fillFlatTopTriangle(v2,&v4,v3,c);
        }
        else //left major
        {
            fillFlatBottomTriangle(v1,&v4,v2,c);
            fillFlatTopTriangle(&v4,v2,v3,c);
        }

    }

    texture.update(pixels);
    window.draw(*sprite);
    std::memset(pixels,0,Engine::WIDTH* Engine::WIDTH*4 * sizeof(sf::Uint8));

}

void Rasterizer::fillFlatBottomTriangle( const  Vec3* v1,const Vec3* v2 , const Vec3* v3, const sf::Color& c)
{
    float inslope1 = ((v2->x - v1->x)) / ((v2->y - v1->y));
    float inslope2 = ((v3->x - v1->x)) / ((v3->y - v1->y));

    const int yStart = ceil(v1->y - 0.5f);
    const int yEnd = ceil(v3->y - 0.5f);

    for(int y = yStart; y < yEnd; y++) // Scan Lining
    {
        const float px1 = inslope1 * ( y + 0.5f - v1->y) + v1->x;
        const float px2 = inslope2 * ( y + 0.5f - v1->y) + v1->x;

        const int xStart  = ceil(px1 - 0.5f);
        const int xEnd  = ceil(px2 - 0.5f);


        for( int x = xStart,s = 0; x < xEnd; x++)
        {
             if(x > 0 &&  x < Engine::WIDTH && y > 0 && y < Engine::HEIGHT )
             {
                PutPixel(x,y,c.r,c.g,c.b);
                s = 1;
             }
            else if (s) break;
        }

    }

}
void Rasterizer::fillFlatTopTriangle(const  Vec3* v1, const Vec3* v2 , const Vec3* v3, const sf::Color& c)
{

    float inslope1 = (v3->x - v1->x) / (v3->y - v1->y);
    float inslope2 = (v3->x - v2->x) / (v3->y - v2->y);

    const int yStart = ceil(v1->y - 0.5f);
    const int yEnd = ceil(v3->y - 0.5f);

    for(int y = yStart; y < yEnd; y++) // Scan Lining
    {
        const float px1 = inslope1 * ( y + 0.5f - v1->y) + v1->x;
        const float px2 = inslope2 * ( y + 0.5f - v2->y) + v2->x;

        const int xStart  = ceil(px1 - 0.5f);
        const int xEnd  = ceil(px2 - 0.5f);
        for(int x = xStart,s = 0; x < xEnd; x++)
        {
             if(x > 0 &&  x < Engine::WIDTH && y > 0 && y < Engine::HEIGHT )
             {
                PutPixel(x,y,c.r,c.g,c.b);
                s = 1;
             }
            else if (s) break;
        }
    }
}

void Rasterizer::PutPixel(int x,int y,sf::Uint8 r, sf::Uint8 g,sf::Uint8 b)
{
    pixels[x * 4 + (y) * Engine::WIDTH * 4] = r;
    pixels[x * 4 + (y) * Engine::WIDTH * 4 + 1] = g;
    pixels[x * 4 + (y) * Engine::WIDTH * 4 + 2] = b;
    pixels[x * 4 + (y) * Engine::WIDTH * 4 + 3] = 255;
}

