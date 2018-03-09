#include "World.h"
#include "Entity.h"
#include <iostream>


World& World::getWorldInstance()
{
    static World w;
    return w;
}
void World::addEntityToWorld(Entity& e)
{
    objects.push_back(e);
}
void World::TransformWorld(Vec3& vec)
{

    for (auto& object: objects)
    {

        Vec3 & origin = object.origin;
        for(auto i = object.getMesh().vertices.begin(),end = object.getMesh().vertices.end(); i!=end; ++i)
        {
            *i += vec;

        }
        origin += vec;
    }
        vec.x = 0;
        vec.y = 0;
        vec.z = 0;


}
void World::RotateObjects(Vec3& vec)
{

    float xa = vec.x ;
    float ya = vec.y;
    float za = vec.z;

    for(auto& object: objects)
    {
        Vec3& origin = object.origin;
        for(auto i = object.getMesh().vertices.begin(),end = object.getMesh().vertices.end(); i!=end; ++i)
        {
            if(xa != 0 || ya != 0 || za != 0)
            {


                (*i) -= {2.5,0,-2.5};
                (*i) -= origin;
                matrix.Rotate(*i,xa,ya,za);
                (*i) += {2.5,0,-2.5};
                (*i) += origin;
                vec.x = 0;
                vec.y = 0;
                vec.z = 0;
            }

        }

    }
}
void World::RotateWorld(float x, float y,Vec3& cameraPos)
{

    for(auto& object: objects)
    {
      Vec3& origin = object.origin;
        for(auto i = object.getMesh().vertices.begin(),end = object.getMesh().vertices.end(); i!=end; ++i)
        {
            if(x != 0 || y != 0)
            {

                (*i) -= {cameraPos.x,0,cameraPos.z};
                (*i) -= origin;
                matrix.Rotate(*i,x,y,0);
                (*i) += origin;
                (*i) += {cameraPos.x,0,cameraPos.z};
            }
        }
    }
}
void World::GenerateWorld()
{
    //Generate Terrain
  Entity e(0,0,0);
  Entity e2(0,0,0);
    //Cube
  e.addFace({{-0,-0,-0},{1,0,0},{0,1,0}}); e.addFace({{1,0,0},{1,1,0},{0,1,0}});
 e.addFace({{0,0,1},{1,0,1},{0,1,1}});     e.addFace({{1,0,1},{1,1,1},{0,1,1}});
  e.addFace({{0,0,0},{0,0,1},{0,1,1}});   e.addFace({{0,0,0},{0,1,1},{0,1,0}});
  e.addFace({{1,0,0},{1,0,1},{1,1,1}});      e.addFace({{1,0,0},{1,1,1},{1,1,0}});
  e.addFace({{0,1,0},{1,1,0},{0,1,0}});    e.addFace({{0,1,0},{1,1,0},{1,1,1}});
  e.addFace({{0,0,0},{1,0,0},{0,0,0}}); e.addFace({{0,0,0},{1,0,0},{1,0,1}});


/* e2.addFace({{-4,-4,-4},{-5,-4,-4},{-4,-5,-4}}); e2.addFace({{-5,-4,-4},{-5,-5,-4},{-4,-5,-4}});
  e2.addFace({{-4,-4,-5},{-5,-4,-5},{-4,-5,-5}});     e2.addFace({{-5,-4,-5},{-5,-5,-5},{-4,-5,-5}});
  e2.addFace({{-4,-4,-4},{-4,-4,-5},{-4,-5,-5}});   e2.addFace({{-4,-4,-4},{-4,-5,-5},{-4,-5,-4}});
  e2.addFace({{-5,-4,-4},{-5,-4,-5},{-5,-5,-5}});      e2.addFace({{-5,-4,-4},{-5,-5,-5},{-5,-5,-4}});
  e2.addFace({{-4,-5,-4},{-5,-5,-4},{-4,-5,-4}});    e2.addFace({{-4,-5,-4},{-5,-5,-4},{-5,-5,-5}});
  e2.addFace({{-4,-4,-4},{-5,-4,-4},{-4,-4,-4}}); e2.addFace({{-4,-4,-4},{-5,-4,-4},{-5,-4,-5}});
  */

  objects.push_back(e);
  //objects.push_back(e2);


}
void World::GenerateTerrain(float width,float quadcount,const Vec3& start)
{
    float facesize = width / quadcount ;
    Entity terrain(0,0,0);

     for(float i = 0; i < quadcount; ++i)
        for(float j = 0; j < quadcount; ++j)
        {
            terrain.addFace({{facesize * j,-1,-facesize * i},  {facesize * (j + 1) ,-1,-facesize * i},      {facesize * (j + 1) ,-1,-facesize * (i + 1) }});
            terrain.addFace({{facesize * j,-1,-facesize * i},  {facesize * (j + 1) ,-1,-facesize * (i+1) } ,{facesize * j,-1,-facesize * (i + 1)}});
        }



    objects.push_back(terrain);


}
std::vector<Entity>& World::getObjects()
{
    return objects;
}
