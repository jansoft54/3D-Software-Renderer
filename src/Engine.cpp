#include "Engine.h"
#include "Math/Matrix3f.h"
#include <iostream>
#include "SRandom.h"
constexpr int cameraoffset_z=2;


Engine::Engine(sf::RenderWindow& window )
:window(window)
,rotation(0,0,0)
,transform(0,0,0)
,r(window)
,ran(SRandom::getRandom())
{
    world.GenerateWorld();
    world.GenerateTerrain(30,50,{0,0,0});
}

void Engine::Update(float dt)
{

    handleInput(dt);

    camera.Transform(transform);
    camera.Rotate(rotation.x,rotation.y);
    rotation.y = 0;
    Render();
}
void Engine::handleInput(float dt)
{
     sf::Event event;
    while(window.pollEvent(event))

        if(event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            window.close();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        transform.x  = 5 * dt;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        transform.x = -5 *dt;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        transform.z = 5 * dt;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        transform.z = -5 *dt;


    rotation.y = (sf::Mouse::getPosition().x - Mx)  * dt * 70;
    Mx = sf::Mouse::getPosition().x;
    My = sf::Mouse::getPosition().y ;

}

void Engine::Render()
{
    for(auto& object : world.getObjects())
        for(auto i = object.getMesh().indices.begin(),
            end = object.getMesh().indices.end();
            i != end ; std::advance(i,3) )
            {
                Vec3& v1 = object.getMesh().vertices[*i];
                Vec3& v2 = object.getMesh().vertices[*std::next(i)];
                Vec3& v3 = object.getMesh().vertices[*std::next(i,2)];

                //if(Vec3::dotProduct(Vec3::crossProduct(v2 - v1, v3 - v1), v1 - Vec3(0,0,0)) <0)
                    DrawLine(v1,v2,v3);
            }
}
void Engine::DrawLine(Vec3 vec1,Vec3 vec2,Vec3 vec3)
{
    sf::VertexArray varray(sf::Triangles,3);


    float x1 = (vec1.x /(cameraoffset_z-vec1.z*0.5) +1) * WIDTH/2  ;
    float y1 = (-vec1.y/(cameraoffset_z-vec1.z*0.5) +1) * WIDTH/2 ;

    float x2 = (vec2.x /(cameraoffset_z-vec2.z*0.5) +1) * WIDTH/2  ;
    float y2 = (-vec2.y/(cameraoffset_z-vec2.z*0.5) +1) * WIDTH/2 ;

    float x3 = (vec3.x /(cameraoffset_z-vec3.z*0.5) +1) * WIDTH/2  ;
    float y3 = (-vec3.y/(cameraoffset_z-vec3.z*0.5) +1) * WIDTH/2 ;

    if(vec2.z < 3.5f && vec3.z < 3.5f && vec1.z < 3.5f)
    {
       varray[0].position = {x2 ,y2};  varray[0].color = sf::Color::Red;
        varray[1].position = {x3 ,y3};  varray[1].color = sf::Color::Green;
        varray[2].position = {x1 ,y1};  varray[2].color = sf::Color::Blue;

        window.draw(varray);


       /* Vec3 v1 {x1,y1,0};
        Vec3 v2 {x2,y2,0};
        Vec3 v3 {x3,y3,0};

        r.DrawTriangle(&v1,&v2,&v3, sf::Color(100,100,100));
        r.DrawTriangle(&v1,&v2,&v3, sf::Color(200,200,200));
        */

    }

}

