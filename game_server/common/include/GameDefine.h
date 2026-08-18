#ifndef __GAME_DEFINE_H__
#define __GAME_DEFINE_H__

//存储着游戏内的相关定义

#include <cstdint>

enum class ObjectType : uint32_t
{
    NONE = 0,
    PLAYER = 1,     //玩家
    NPC = 2,        //NPC
    MONSTER = 3,    //怪物
    PET = 4,        //宠物
    MOUNT = 5,      //坐骑
    SUMMON = 6,     //召唤物
};

//玩家当前正在做什么
enum class ActionType : uint32_t
{
    NONE     = 0,  // 无
    IDLE     = 1,  // 待机
    FIXBODY  = 2,  // 定身
    WALK     = 3,  // 行走
    RUN      = 4,  // 跑动
    FLY      = 5,  // 飞行

    SKILL    = 6,  // 技能
    MINE     = 7,  // 采集
    ROLL     = 8,  // 翻滚
    JUMP     = 9,  // 跳跃
    BORN     = 10, // 出生
    DANCE    = 11, // 跳舞

    DEAD     = 12, // 死亡
    WOUND    = 13, // 受击
    BEATBACK = 14, // 击退
    BEATDOWN = 15, // 击倒
    BEATFLY  = 16, // 击飞
};


enum ActionStatus : uint32_t
{
    NONE         = 0,          //无动作
    HURT         = 0x1,        //伤害
    START        = 0x2,        //开始动作
    END          = 0xfffffff,  //技能动作开始
};

//玩家当前有哪些限制或者状态
enum class ObjectStatus : uint32_t   
{
    //数组下标
    NONE          = 0,  //无
    DEAD          = 1,  //死亡
    NOT_MOVE      = 2,  //不能移动
    NOT_CAST      = 3,  //不能放技能
    NOT_BEHURT    = 4,  //不能被攻击
    NOT_BECONTROL = 5,  //无法被控制
    STEALTH       = 6,  //不能被看见
    BLIND         = 7,  //不能看见他人

    COUNT
};



enum class AttrID : uint32_t 
{
    HP            = 0,  //生命值
    MP            = 1,  //魔法值
    HP_MAX        = 2,  //最大生命值
    MP_MAX        = 3,  //最大魔法值
    SPEED         = 4,  //移动速度
    ATTACK        = 5,  //攻击
    ELEMENT       = 6,  //元素伤害
    MAGIC_DEF     = 7,  //魔防
    PHYSIC_DEF    = 8,  //物防
    HIT_RATE      = 9, //命中
    DODGE         = 10, //闪避
    MORE_HURT     = 11, //伤害加深
    LESS_HURT     = 12, //伤害减免
    CRIT_HIT      = 13, //暴击
    CRIT_DEF      = 14, //抗暴
    CRIT_HURT     = 15, //暴伤
    ATTR_NUM      = 16, //属性个数
};


enum class HitShipType : uint32_t
{
    ALL        = 0,      // 全部目标
    FRIEND     = 1,      // 需要目标是友方才能释放
    ENEMY      = 2,      // 需要目标是敌方才能释放
};

//单位之间的关系
enum class Relation : uint32_t
{
    Neutral,
    Friend,
    Enemy,
};

//阵营关系
enum class Camp : uint32_t
{
    None = 0,

    PvePlayer,
    PveEnemy,
    PveNeutral,

    PvpTeam1,
    PvpTeam2,
    PvpTeam3,
    PvpTeam4,
    PvpTeam5,
};



#endif