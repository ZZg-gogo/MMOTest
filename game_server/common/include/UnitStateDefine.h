#ifndef __UNIT_STATE_DEFINE_H__
#define __UNIT_STATE_DEFINE_H__


enum class UnitStateType
{
    None,

    Idle,       // 空闲
    Move,       // 移动
    Attack,     // 攻击
    Dead,       // 死亡
};


enum class UnitEventType
{
    None,

    MoveRequest,    // 请求移动
    StopRequest,    // 请求停止
    AttackRequest,  // 请求攻击

    AttackEnd,      // 攻击结束
    Die,            // 死亡事件
};


#endif // !__UNIT_STATE_DEFINE_H__