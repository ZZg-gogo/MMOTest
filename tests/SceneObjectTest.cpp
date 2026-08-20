#include "Scene.h"
#include "SceneObject.h"

#include <iostream>


int main(int argc, const char ** argv)
{

    SceneObject obj1{9527, nullptr, 2001};


    std::cout<<"obj name = "<<obj1.m_actorConfig->name<<'\n';

    return 0;
}