#include "PlayerStateManager.h"
#include "UnitState.h"
#include "Unit.h"
#include "Player.h"

void PlayerStateManager::Init()
{

    // 创建 Idle 状态
    auto idleState = std::make_shared<UnitState>();

    idleState->SetOnEnterCallback([](Unit *unit)
                                    {
    auto* player = static_cast<Player*>(unit);

    // 玩家进入 Idle 状态
    player->StopMove(); });

    idleState->SetOnExitCallback([](Unit *unit)
                                    {
                                        auto *player = static_cast<Player *>(unit);

                                        // 玩家离开 Idle 状态
                                    });

    idleState->SetOnUpdateCallback([](Unit *unit, int deltaTime, int nowTime)
                                    {
                                        auto *player = static_cast<Player *>(unit);

                                        // Idle 状态每帧/每次 Update
                                    });

    idleState->AddStateCallback(UnitEventType::MoveRequest, [](Unit *unit)
                                {
    auto* player = static_cast<Player*>(unit);

    // 收到移动事件
    player->Move(); });

    m_states[UnitStateType::Idle] = idleState;

}