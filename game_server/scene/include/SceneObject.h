#ifndef __SCENE_OBJECT_H__
#define __SCENE_OBJECT_H__


#include <cstdint>
#include <array>

#include "MapObject.h"
#include "GameDefine.h"
#include "Vec2.h"
#include "ActorConfig.h"


class SceneObject : public MapObject
{

public:
    //全局唯一ID, 在哪个场景里面, 角色ID
    SceneObject(uint64_t guid, Scene* scene, uint32_t actorID);
    ~SceneObject();


public:
    bool OnUpdate(uint64_t tick);   //每帧更新驱动单位
    bool MakeEnterInfo(ObjectEnterInfo& info);           //组装进入消息
    bool MakeUpdateInfo(ObjectUpdateInfo& info);        //组装更新消息
    bool Reset();   //重置这个对象

//以下为对象的操作方法
public:
    uint32_t GetHp();
    //设置当前的位置和朝向
    bool SetPos(float x, float y, float rotation);
    Vec2 GetPos() const;
    float GetFaceTo();  //获得朝向

public: //单位基础信息
    uint64_t m_guid;        //全局唯一ID
    uint32_t m_actorID;     //角色ID
    const ActorConfig * m_actorConfig;    //角色的基础配置
    uint32_t m_level;       //角色等级
    enum ObjectType m_objectType;   //对象类型
    enum Camp m_camp;       //当前的阵营
    enum ActionType m_actionID; //当前的动作ID
    Vec2 m_pos;             //当前的位置
    float m_rotation;       //当前的朝向
    std::array<uint32_t, static_cast<std::size_t>(ObjectStatus::COUNT)> m_status{}; //当前的状态

    std::array<int32_t, static_cast<std::size_t>(AttrID::COUNT)> m_attrsRate{}; //当前的属性改变的万分比
    std::array<int32_t, static_cast<std::size_t>(AttrID::COUNT)> m_attrs{}; //当前的属性
    uint64_t m_lastMoveTick;    //最后一次移动的时间
};






#endif