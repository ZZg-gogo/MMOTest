#include "Object.h"
#include <Logger.h>


void Object::addToWorld()
{
    if (m_isInWorld)
    {
        return;
    }

    m_isInWorld = true;
    clearUpdateMask(false);
}


void Object::removeFromWorld()
{
    if (!m_isInWorld)
    {
        return;
    }

    m_isInWorld = false;
    clearUpdateMask(true);
}

//清理字段更新标记 remove=true表示还要从Map中移除这个对象的更新标记
void Object::clearUpdateMask(bool remove)
{
    m_updateMask.clear();
    if (m_objectUpdated)
    {

        if (remove)
        {
            removeFromObjectUpdate();
        }
        m_objectUpdated  = false;
    }
}




uint32_t Object::getUint32Value(uint16_t index) const
{
    if (index == m_valuesCount)
    {
        printIndexError(index, false);
        return 0;
    }
    

    return m_uint32Values[index];
}


void Object::setUint32Value(uint16_t index, uint32_t value)
{
    if (index == m_valuesCount)
    {
        printIndexError(index, true);
        return;
    }

    if (m_uint32Values[index] != value)
    {
        m_uint32Values[index] = value;
        m_updateMask.setBit(index);
        addToObjectUpdateIfNeeded();
    }
    
}

float Object::getFloatValue(uint16_t index) const
{
    if (index == m_valuesCount)
    {
        printIndexError(index, false);
        return 0.0;
    }

    return m_floatValues[index];
}


void Object::setFloatValue(uint16_t index, float value)
{
    if (index == m_valuesCount)
    {
        printIndexError(index, false);
        return;
    }

    if (m_floatValues[index] != value)
    {
        m_floatValues[index] = value;
        m_updateMask.setBit(index);
        addToObjectUpdateIfNeeded();
    }
    
}


ObjectGuid Object::getGuidValue(uint16_t index) const
{
    return ObjectGuid{(*(uint64_t*)(&m_uint32Values[index]))};
}



ObjectGuid GetGuid(const Object* obj)
{
    return obj->getGuid();
}

//玩家在世界里面 并且是有字段第一次被更新 那么就记录到世界更新队列
void Object::addToObjectUpdateIfNeeded()
{
    if (m_isInWorld && !m_objectUpdated)
    {
        addToObjectUpdate();
        m_objectUpdated = true;
    }
    
}

bool Object::printIndexError(uint32_t index, bool set) const
{
    LOGGER_ERROR("Object::PrintIndexError index={} m_valuesCount={} m_objectType={} set={}", index, m_valuesCount, m_objectType, set);
    return false;
}
