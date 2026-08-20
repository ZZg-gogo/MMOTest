#ifndef __MAP_OBJECT_H__
#define __MAP_OBJECT_H__



class Scene;

class MapObject
{
public:
    MapObject() : m_scene(nullptr) {}
    virtual ~MapObject() = default;

public:

    Scene * GetScene() noexcept {return m_scene;}
    void SetScene(Scene* scene) {m_scene = scene;}

public:
    Scene * m_scene;    //这个单位所属的场景
};




#endif