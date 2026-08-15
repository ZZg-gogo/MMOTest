#ifndef __UNITSTATE_H__
#define __UNITSTATE_H__


#include <functional>
#include <map>
#include <string>
#include "UnitStateDefine.h"



class Unit;
typedef std::function<void(Unit*)> UnitStateCallback;
typedef std::function<void(Unit*, int, int)> UnitStateUpdateCallback;
typedef std::map<UnitEventType, UnitStateCallback> UnitEventCallbackMap;

class UnitState
{
public:
    void SetOnEnterCallback(UnitStateCallback callback)
    {
        m_onEnterCallback = callback;
    }
    
    void SetOnExitCallback(UnitStateCallback callback)
    {
        m_onExitCallback = callback;
    }


    void SetOnUpdateCallback(UnitStateUpdateCallback callback)
    {
        m_onUpdateCallback = callback;
    }


    void AddStateCallback(UnitEventType eventType, UnitStateCallback callback)
    {
        m_stateCallbackMap[eventType] = callback;
    }

    void OnEvent(UnitEventType eventType, Unit * unit)
    {

        auto it = m_stateCallbackMap.find(eventType);
        if (it != m_stateCallbackMap.end())
        {
            it->second(unit);
        }
        
    }


    //这个状态的进入回调
    UnitStateCallback m_onEnterCallback;
    //这个状态的退出回调
    UnitStateCallback m_onExitCallback;
    //这个状态的更新回调
    UnitStateUpdateCallback m_onUpdateCallback;
    //当这个状态下 触发某个事件的时候 需要调用的回调函数
    UnitEventCallbackMap m_stateCallbackMap;
};




#endif // !__UNITSTATE_H__