#ifndef __MAP_CONFIG_MANAGER_H__
#define __MAP_CONFIG_MANAGER_H__

#include <cstdint>
#include <unordered_map>

#include "MapConfig.h"

class MapConfigManager
{
public:
    static MapConfigManager& Instance();

    bool Init();

    const MapConfig* GetMapConfig(uint32_t mapId) const;

private:
    MapConfigManager() = default;

private:
    std::unordered_map<uint32_t, MapConfig> m_configs;
};


#endif