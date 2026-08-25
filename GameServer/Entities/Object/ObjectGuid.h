#ifndef __OBJECT_GUID_H__
#define __OBJECT_GUID_H__

#include <cstdint>

enum class High16Guid : uint16_t
{
    Item           = 0x4000,  // 物品
    Player         = 0x0000,  // 玩家
    GameObject     = 0xF110,  // 游戏对象
    Unit           = 0xF130,  // 生物
    Pet            = 0xF140,  // 宠物
    Vehicle        = 0xF150,  // 载具
    DynamicObject  = 0xF100,  // 动态对象
    Corpse         = 0xF101,  // 尸体
};

//一个对象的GUID 是根据他是否是全局来决定的, 16位类型ID + 24位地图ID(全局对象没有) + 低24位的counter(如果是全局的话 他是48位)

//非类型模版参数 
template<High16Guid high>
struct ObjectGuidTraits
{
    static const bool Global = false;    //构造GUID的时候是否是一个全局对象
    static const bool MapSpecific = false;      //构造GUID的时候是否是一个Map对象
};

#define GlobalObjectGuidTraits(highGuid) \
    template<> struct ObjectGuidTraits<highGuid> \
    {\
        static const bool Global = true;    \
         static const bool MapSpecific = false;     \
    }


#define MapObjectGuidTraits(highGuid) \
    template<> struct ObjectGuidTraits<highGuid> \
    {\
        static const bool Global = false;    \
        static const bool MapSpecific = true;     \
    }



#endif //__OBJECT_GUID_H__