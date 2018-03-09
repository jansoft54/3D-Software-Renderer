#include "Entity.h"
#include <iostream>

 Entity::Entity(float x,float y,float z)
:origin(x,y,z)
,startorigin(x,y,z)
{
    //ctor

}

void Entity::addFace(std::initializer_list< Vec3> initlist)
{
    std::vector<Vec3> vec;
    vec.insert(vec.end(),initlist.begin(),initlist.end());
    if(vec.size() != 3)
        throw 404;
    if( mesh.vertices.size() != 0)
    {
        for(auto& vertex: vec)
        {
            bool vertex_inList = false;
            for(unsigned i = 0; i < mesh.indices.size();++i)
            {
                if(vertex.equals(mesh.vertices[mesh.indices[i]]))
                {
                    mesh.indices.push_back(mesh.indices[i]);
                    vertex_inList = true;
                    break;
                }
            }
            if(!vertex_inList)
            {
            //No matching Vertex found
                mesh.vertices.push_back(vertex);
                mesh.indices.push_back(mesh.vertices.size()-1);
            }
        }

    }else
    {
        mesh.vertices.insert(mesh.vertices.end(),vec.begin(),vec.end());
        mesh.indices.push_back(0);mesh.indices.push_back(1);mesh.indices.push_back(2);
    }
}
Mesh& Entity::getMesh()
{

    return mesh;
}
