#ifndef __MAP_CONFIG_H__
#define __MAP_CONFIG_H__

#include <cstdint>
#include <vector>
#include "Vec2.h"
#include "GameDefine.h"


struct SpawnPoint
{
    ObjectType objectType;
    uint32_t templateId;
    Camp camp;
    Vec2 position;
};

struct MapConfig
{
    uint32_t mapId;
    const char* name;

    float width;
    float height;

    std::vector<SpawnPoint> spawnPoints;
};



#endif