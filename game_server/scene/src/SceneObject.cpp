#include "SceneObject.h"


SceneObject::SceneObject(uint64_t guid, Scene* scene, uint32_t actorID)
    : m_guid(guid), m_actorConfig(ActorConfigManager::Instance().GetConfig(actorID))
{
    m_scene = scene;
    Reset();
}



SceneObject::~SceneObject()
{
    Reset();
}

bool SceneObject::Reset()   //重置这个对象
{
    //TODO
    return true;
}
