#include "MapConfigManager.h"

MapConfigManager& MapConfigManager::Instance()
{
    static MapConfigManager instance;
    return instance;
}

bool MapConfigManager::Init()
{
    m_configs.clear();

    //==========================================================
    // Map 1：新手村
    // PVE
    //==========================================================
    {
        MapConfig config;

        config.mapId = 1;
        config.name = "BeginnerVillage";

        config.width = 100.0f;
        config.height = 100.0f;

        // 玩家出生点
        config.spawnPoints.push_back({
            ObjectType::PLAYER,
            0,
            Camp::PvePlayer,
            Vec2(10.0, 50.0)
        });

        // 怪物
        config.spawnPoints.push_back({
            ObjectType::MONSTER,
            10001,
            Camp::PveEnemy,
            Vec2(50.0, 50.0)
        });

        config.spawnPoints.push_back({
            ObjectType::MONSTER,
            10002,
            Camp::PveEnemy,
            Vec2(60.0, 50.0)
        });

        m_configs.emplace(config.mapId, std::move(config));
    }

    //==========================================================
    // Map 2：竞技场
    // PVP
    //==========================================================
    {
        MapConfig config;

        config.mapId = 2;
        config.name = "Arena";

        config.width = 100.0f;
        config.height = 100.0f;

        // Team 1
        config.spawnPoints.push_back({
            ObjectType::PLAYER,
            0,
            Camp::PvpTeam1,
            Vec2(20.0, 50.0)
        });

        // Team 2
        config.spawnPoints.push_back({
            ObjectType::PLAYER,
            0,
            Camp::PvpTeam2,
            Vec2(80.0, 50.0)
        });

        m_configs.emplace(config.mapId, std::move(config));
    }

    return true;
}

const MapConfig*
MapConfigManager::GetMapConfig(uint32_t mapId) const
{
    auto it = m_configs.find(mapId);

    if (it == m_configs.end())
    {
        return nullptr;
    }

    return &it->second;
}