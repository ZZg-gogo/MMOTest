#ifndef __OBJECT_GUID_H__
#define __OBJECT_GUID_H__

#include <cstdint>
#include <type_traits>

// 游戏对象的基础类型 ID
// 一个对象通常只有一个主要 TypeID
enum class TypeID
{
    TYPEID_OBJECT        = 0, // 基础对象

    TYPEID_ITEM          = 1, // 普通物品

    TYPEID_CONTAINER     = 2, // 容器物品，例如背包、箱子等

    TYPEID_UNIT          = 3, // 单位，例如 Creature、Pet、Vehicle 的基础类型

    TYPEID_PLAYER        = 4, // 玩家

    TYPEID_GAMEOBJECT    = 5, // 游戏场景对象，例如门、宝箱、采集物等

    TYPEID_DYNAMICOBJECT = 6, // 动态对象，例如范围技能、持续性区域效果等

    TYPEID_CORPSE        = 7  // 尸体对象
};

// 客户端对象基础类型总数量
#define NUM_CLIENT_OBJECT_TYPES 8


// 游戏对象类型掩码
// 可以通过按位或（|）组合多个类型
enum class TypeMask
{
    TYPEMASK_OBJECT         = 0x0001, // 基础对象类型

    TYPEMASK_ITEM           = 0x0002, // 物品类型

    // 容器类型
    // 0x0006 = 0x0002 | 0x0004
    // Container 本身也是 Item，因此同时拥有 Item 标记
    TYPEMASK_CONTAINER      = 0x0006,

    TYPEMASK_UNIT           = 0x0008, // 单位类型，Creature、Pet、Vehicle 等都属于 Unit

    TYPEMASK_PLAYER         = 0x0010, // 玩家类型，Player 同时也是一种 Unit

    TYPEMASK_GAMEOBJECT     = 0x0020, // 游戏对象类型，例如门、宝箱、采集物等

    TYPEMASK_DYNAMICOBJECT  = 0x0040, // 动态对象类型，例如持续性范围技能对象

    TYPEMASK_CORPSE         = 0x0080, // 尸体类型

    // 可观察者/视野观察者类型集合
    // Player、Unit、DynamicObject 都属于 Seer
    TYPEMASK_SEER =
        TYPEMASK_PLAYER |
        TYPEMASK_UNIT |
        TYPEMASK_DYNAMICOBJECT
};


// GUID 的高位类型
// 用于在对象唯一 GUID 中标识对象所属的 GUID 类型
enum class High16Guid
{
    Item           = 0x4000, // 普通物品 GUID 类型
    Container      = 0x4000, // 容器 GUID 类型，与 Item 使用相同编码

    Player         = 0x0000, // 玩家 GUID 类型

    GameObject     = 0xF110, // 游戏对象 GUID 类型

    // 交通工具类型的 GameObject
    Transport      = 0xF120,

    Unit           = 0xF130, // 普通 Unit / Creature GUID 类型

    Pet            = 0xF140, // 宠物 GUID 类型

    Vehicle        = 0xF150, // 载具 GUID 类型

    DynamicObject  = 0xF100, // 动态对象 GUID 类型

    Corpse         = 0xF101, // 尸体 GUID 类型

    // 移动运输工具 GUID 类型
    // 通常用于特殊的地图/世界运输工具
    Mo_Transport   = 0x1FC0,

    Instance       = 0x1F40, // 副本实例 GUID 类型

    Group          = 0x1F50, // 队伍/小队 GUID 类型
};

//一个对象的GUID 是根据他是否是全局来决定的, 16位类型ID + 24位模版ID + 低24位的counter(如果是全局的话 他是48位)

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

GlobalObjectGuidTraits(High16Guid::Item);
GlobalObjectGuidTraits(High16Guid::Player);

MapObjectGuidTraits(High16Guid::GameObject);
MapObjectGuidTraits(High16Guid::Unit);
MapObjectGuidTraits(High16Guid::Pet);
MapObjectGuidTraits(High16Guid::Vehicle);
MapObjectGuidTraits(High16Guid::DynamicObject);
MapObjectGuidTraits(High16Guid::Corpse);



class ObjectGuid
{
public:
    const static ObjectGuid Empty;
public:
    ObjectGuid() = default;
    explicit ObjectGuid(uint64_t guid) : m_guid(guid){}
    ObjectGuid(High16Guid hi, uint32_t entry, uint32_t counter);
    ObjectGuid(High16Guid hi, uint32_t counter);


public:
    template<High16Guid type>
    static typename std::enable_if<ObjectGuidTraits<type>::Global, ObjectGuid>::type 
        Create(High16Guid hi, uint32_t counter) {return Global(hi, counter);}

    template<High16Guid type>
    static typename std::enable_if<ObjectGuidTraits<type>::MapSpecific, ObjectGuid>::type
        Create(High16Guid hi, uint32_t entry, uint32_t counter) {return MapSpecific(hi, entry, counter);}

    void set(uint64_t guid) {m_guid = guid;}
    void clear() {m_guid = 0;}

    [[nodiscard]] uint64_t getRawGuid() const {return m_guid;}
    [[nodiscard]] High16Guid getHigh() const {return static_cast<High16Guid>(m_guid>>48 & 0x0000FFFF);}
    [[nodiscard]] uint32_t getEntry()const {return hasEntry()? (m_guid>>24)&(0x0000000000FFFFFF) : 0;}
    [[nodiscard]] uint32_t getCounter() const 
    {
        return hasEntry()
                   ? static_cast<uint32_t>(m_guid & (0x0000000000FFFFFF))
                   : static_cast<uint32_t>(m_guid & (0x00000000FFFFFFFF));
    }
    //获取一个类型最大可用的counter
    static uint32_t GetMaxCounter(High16Guid hi)
    {
        return hasEntry(hi)
                   ? static_cast<uint32_t>(0x00FFFFFF)
                   : static_cast<uint32_t>(0xFFFFFFFF);
    }

    [[nodiscard]] uint32_t getMaxCounter(){return GetMaxCounter(getHigh());}
private:
    //创造一个全局的guid
    static ObjectGuid Global(High16Guid hi, uint32_t counter);
    //创建一个和地图相关的guid
    static ObjectGuid MapSpecific(High16Guid hi, uint32_t entry, uint32_t counter);
    //这个guid是否有模版
    static bool hasEntry(High16Guid hi);
    [[nodiscard]] bool hasEntry() const{return hasEntry(getHigh());}
private:
    uint64_t m_guid{0};
};



#endif //__OBJECT_GUID_H__