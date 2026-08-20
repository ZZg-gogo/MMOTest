#ifndef __ACTOR_CONFIG_H__
#define __ACTOR_CONFIG_H__

#include <array>
#include <cstdint>
#include <string>
#include <unordered_map>

#include "GameDefine.h"

// ============================================================
// Actor配置
//
// 描述一个角色/怪物模板的静态数据。
// 例如：1001 = Knight
// ============================================================

struct ActorConfig
{
    uint32_t actorId = 0;

    std::string name;

    uint32_t level = 1;

    float radius = 0.5f;

    ObjectType objectType = ObjectType::NONE;
    Camp camp = Camp::None;

    //单位的基础属性
    std::array<int32_t, static_cast<size_t>(AttrID::COUNT)> attrs{};
};

// ============================================================
// Actor配置管理器
// ============================================================

class ActorConfigManager
{
public:
    static ActorConfigManager &Instance()
    {
        static ActorConfigManager instance;
        return instance;
    }

    // 禁止复制
    ActorConfigManager(const ActorConfigManager &) = delete;
    ActorConfigManager &operator=(const ActorConfigManager &) = delete;

public:
    // 初始化所有 Actor 配置
    void Init()
    {
        m_configs.clear();

        // ====================================================
        // 1001 Knight
        // ====================================================
        {
            ActorConfig config;

            config.actorId = 1001;
            config.name = "Knight";
            config.level = 1;
            config.radius = 0.6f;

            config.objectType = ObjectType::PLAYER;
            config.camp = Camp::PvePlayer;

            config.attrs[static_cast<size_t>(AttrID::HP)] = 1000;
            config.attrs[static_cast<size_t>(AttrID::MP)] = 300;

            config.attrs[static_cast<size_t>(AttrID::HP_MAX)] = 1000;
            config.attrs[static_cast<size_t>(AttrID::MP_MAX)] = 300;

            config.attrs[static_cast<size_t>(AttrID::SPEED)] = 320;
            config.attrs[static_cast<size_t>(AttrID::ATTACK)] = 120;
            config.attrs[static_cast<size_t>(AttrID::ELEMENT)] = 30;

            config.attrs[static_cast<size_t>(AttrID::MAGIC_DEF)] = 40;
            config.attrs[static_cast<size_t>(AttrID::PHYSIC_DEF)] = 80;

            config.attrs[static_cast<size_t>(AttrID::HIT_RATE)] = 100;
            config.attrs[static_cast<size_t>(AttrID::DODGE)] = 50;

            config.attrs[static_cast<size_t>(AttrID::MORE_HURT)] = 0;
            config.attrs[static_cast<size_t>(AttrID::LESS_HURT)] = 10;

            config.attrs[static_cast<size_t>(AttrID::CRIT_HIT)] = 10;
            config.attrs[static_cast<size_t>(AttrID::CRIT_DEF)] = 10;
            config.attrs[static_cast<size_t>(AttrID::CRIT_HURT)] = 150;

            m_configs.emplace(config.actorId, std::move(config));
        }

        // ====================================================
        // 1002 Assassin
        // ====================================================
        {
            ActorConfig config;

            config.actorId = 1002;
            config.name = "Assassin";
            config.level = 1;
            config.radius = 0.45f;

            config.objectType = ObjectType::PLAYER;
            config.camp = Camp::PvePlayer;

            config.attrs[static_cast<size_t>(AttrID::HP)] = 700;
            config.attrs[static_cast<size_t>(AttrID::MP)] = 400;

            config.attrs[static_cast<size_t>(AttrID::HP_MAX)] = 700;
            config.attrs[static_cast<size_t>(AttrID::MP_MAX)] = 400;

            config.attrs[static_cast<size_t>(AttrID::SPEED)] = 420;
            config.attrs[static_cast<size_t>(AttrID::ATTACK)] = 150;
            config.attrs[static_cast<size_t>(AttrID::ELEMENT)] = 20;

            config.attrs[static_cast<size_t>(AttrID::MAGIC_DEF)] = 30;
            config.attrs[static_cast<size_t>(AttrID::PHYSIC_DEF)] = 40;

            config.attrs[static_cast<size_t>(AttrID::HIT_RATE)] = 120;
            config.attrs[static_cast<size_t>(AttrID::DODGE)] = 100;

            config.attrs[static_cast<size_t>(AttrID::MORE_HURT)] = 0;
            config.attrs[static_cast<size_t>(AttrID::LESS_HURT)] = 5;

            config.attrs[static_cast<size_t>(AttrID::CRIT_HIT)] = 30;
            config.attrs[static_cast<size_t>(AttrID::CRIT_DEF)] = 5;
            config.attrs[static_cast<size_t>(AttrID::CRIT_HURT)] = 200;

            m_configs.emplace(config.actorId, std::move(config));
        }

        // ====================================================
        // 1003 Mage
        // ====================================================
        {
            ActorConfig config;

            config.actorId = 1003;
            config.name = "Mage";
            config.level = 1;
            config.radius = 0.5f;

            config.objectType = ObjectType::PLAYER;
            config.camp = Camp::PvePlayer;

            config.attrs[static_cast<size_t>(AttrID::HP)] = 650;
            config.attrs[static_cast<size_t>(AttrID::MP)] = 800;

            config.attrs[static_cast<size_t>(AttrID::HP_MAX)] = 650;
            config.attrs[static_cast<size_t>(AttrID::MP_MAX)] = 800;

            config.attrs[static_cast<size_t>(AttrID::SPEED)] = 300;
            config.attrs[static_cast<size_t>(AttrID::ATTACK)] = 50;
            config.attrs[static_cast<size_t>(AttrID::ELEMENT)] = 160;

            config.attrs[static_cast<size_t>(AttrID::MAGIC_DEF)] = 70;
            config.attrs[static_cast<size_t>(AttrID::PHYSIC_DEF)] = 30;

            config.attrs[static_cast<size_t>(AttrID::HIT_RATE)] = 100;
            config.attrs[static_cast<size_t>(AttrID::DODGE)] = 50;

            config.attrs[static_cast<size_t>(AttrID::MORE_HURT)] = 0;
            config.attrs[static_cast<size_t>(AttrID::LESS_HURT)] = 5;

            config.attrs[static_cast<size_t>(AttrID::CRIT_HIT)] = 15;
            config.attrs[static_cast<size_t>(AttrID::CRIT_DEF)] = 10;
            config.attrs[static_cast<size_t>(AttrID::CRIT_HURT)] = 180;

            m_configs.emplace(config.actorId, std::move(config));
        }

        // ====================================================
        // 2001 Goblin
        // ====================================================
        {
            ActorConfig config;

            config.actorId = 2001;
            config.name = "Goblin";
            config.level = 1;
            config.radius = 0.5f;

            config.objectType = ObjectType::MONSTER;
            config.camp = Camp::PveEnemy;

            config.attrs[static_cast<size_t>(AttrID::HP)] = 500;
            config.attrs[static_cast<size_t>(AttrID::MP)] = 100;

            config.attrs[static_cast<size_t>(AttrID::HP_MAX)] = 500;
            config.attrs[static_cast<size_t>(AttrID::MP_MAX)] = 100;

            config.attrs[static_cast<size_t>(AttrID::SPEED)] = 250;
            config.attrs[static_cast<size_t>(AttrID::ATTACK)] = 60;
            config.attrs[static_cast<size_t>(AttrID::ELEMENT)] = 0;

            config.attrs[static_cast<size_t>(AttrID::MAGIC_DEF)] = 20;
            config.attrs[static_cast<size_t>(AttrID::PHYSIC_DEF)] = 30;

            config.attrs[static_cast<size_t>(AttrID::HIT_RATE)] = 80;
            config.attrs[static_cast<size_t>(AttrID::DODGE)] = 20;

            config.attrs[static_cast<size_t>(AttrID::MORE_HURT)] = 0;
            config.attrs[static_cast<size_t>(AttrID::LESS_HURT)] = 0;

            config.attrs[static_cast<size_t>(AttrID::CRIT_HIT)] = 5;
            config.attrs[static_cast<size_t>(AttrID::CRIT_DEF)] = 0;
            config.attrs[static_cast<size_t>(AttrID::CRIT_HURT)] = 150;

            m_configs.emplace(config.actorId, std::move(config));
        }
    }

    // 根据ActorID查询配置
    const ActorConfig *GetConfig(uint32_t actorId) const
    {
        auto it = m_configs.find(actorId);

        if (it == m_configs.end())
        {
            return nullptr;
        }

        return &it->second;
    }

private:
    ActorConfigManager() {Init();}

private:
    std::unordered_map<uint32_t, ActorConfig> m_configs;
};

#endif