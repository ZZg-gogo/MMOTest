#ifndef __PLAYER_STATE_MANAGER_H__
#define __PLAYER_STATE_MANAGER_H__


#include <memory>
#include <string>
#include <unordered_map>
#include "UnitStateDefine.h"


class UnitState;

class PlayerStateManager
{
public:
    static PlayerStateManager& Instance()
    {
        static PlayerStateManager instance;
        return instance;
    }

    void Init();

    std::shared_ptr<UnitState> GetState(UnitStateType stateType)
    {
        auto it = m_states.find(stateType);

        if (it != m_states.end())
        {
            return it->second;
        }

        return nullptr;
    }

private:
    PlayerStateManager() = default;
    ~PlayerStateManager() = default;

    PlayerStateManager(const PlayerStateManager&) = delete;
    PlayerStateManager& operator=(const PlayerStateManager&) = delete;

private:
    std::unordered_map<UnitStateType, std::shared_ptr<UnitState>> m_states;
};





#endif 