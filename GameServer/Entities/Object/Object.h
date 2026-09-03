#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <cstdint>
#include "UpdateMask.h"
#include "ObjectGuid.h"
#include "UpdateFields.h"

//对象的抽象基类
class Object
{
public:
    virtual ~Object();

public:
    [[nodiscard]] bool isInWorld() {return m_isInWorld;}

    virtual void addToWorld();
    virtual void removeFromWorld();

    [[nodiscard]] uint32_t getUint32Value(uint16_t index) const;
    void setUint32Value(uint16_t index, uint32_t value);

    [[nodiscard]] float getFloatValue(uint16_t index) const;
    void setFloatValue(uint16_t index, float value);

    //GUID
    [[nodiscard]] ObjectGuid getGuid() const{return getGuidValue(OBJECT_FIELD_GUID);}
    [[nodiscard]] ObjectGuid getGuidValue(uint16_t index) const;

    //对象模版ID
    [[nodiscard]] uint32_t getEntry() const {return getUint32Value(OBJECT_FIELD_ENTRY);};
    void setEntry(uint32_t entry) {setUint32Value(OBJECT_FIELD_ENTRY, entry);}
 
    //设置对象缩放的大小 1.0f = 100%，原始模型大小（默认值） 2.0f = 放大到 2 倍
    [[nodiscard]] float getObjectScale() {return getFloatValue(OBJECT_FIELD_SCALE_X);}
    virtual void setObjectScale(float scale) {setFloatValue(OBJECT_FIELD_SCALE_X, scale);}

    //也是union下面的一个uint32的一个属性
    //GetDynamicFlags() 返回的是一个**"单位当前临时状态"的位集合**：可不可拾取、死没死、灰不灰名、能不能追踪……它既是发给客户端让客户端正确显示的依据，也是服务端逻辑查询状态的依据
    virtual uint32_t getDynamicFlags() const {return 0;}
    bool hasDynamicFlag(uint32_t flag) const {return 0 != (getDynamicFlags() & flag);}
    virtual void setDynamicFlags(uint32_t flag) {replaceAllDynamicFlags(flag | getDynamicFlags());}
    virtual void removeDynamicFlag(uint32_t flag) { replaceAllDynamicFlags(getDynamicFlags() & ~flag); }
    virtual void replaceAllDynamicFlags([[maybe_unused]] uint32_t flag) { }

    [[nodiscard]] TypeID getTypeID() {return m_objectTypeId;}
    //m_objectType是TypeMask位或出来的结果
    [[nodiscard]] bool isType(uint16_t mask) {return mask&m_objectType;}

    //清理字段更新标记 remove=true表示还要从Map中移除这个对象的更新标记
    void clearUpdateMask(bool remove);
    

    virtual void addToObjectUpdate() = 0;
    virtual void removeFromObjectUpdate() = 0;
    //玩家在世界里面 并且是有字段第一次被更新 那么就记录到世界更新队列
    void addToObjectUpdateIfNeeded();

public:
    [[nodiscard]] static ObjectGuid GetGuid(const Object* obj);



protected:
    uint16_t m_objectType;
    TypeID m_objectTypeId;
    uint16_t m_updateFlag;  //管理数据同步的时候 移动/位置的格式

    //这个是一个联合体能够同时写入多种数据 直接分配的是一个数组
    union
    {
        int32_t* m_int32Values;
        uint32_t* m_uint32Values;
        float* m_floatValues;
    };
    

    UpdateMask m_updateMask;
    bool m_objectUpdated;
    uint16_t m_valuesCount;

    uint16_t _fieldNotifyFlags;//管理属性字段是否要强制推送(无论值改没改变)

private:
    [[nodiscard]] bool printIndexError(uint32_t index, bool set) const;
    Object(const Object& o) = delete;
    Object& operator=(const Object& o) =delete;
    Object(Object&& o) = delete;
    Object& operator=(Object&& o) =delete;
private:
    bool m_isInWorld;   //是否在世界里面
};








#endif