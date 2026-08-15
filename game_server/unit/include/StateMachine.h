#ifndef __STATE_MACHINE_H__
#define __STATE_MACHINE_H__


#include <memory>
#include <map>
#include <string>
#include "UnitState.h"

class Unit;
class StateMachine
{
public:

    explicit StateMachine(Unit* owner)
        : m_owner(owner)
    {
    }

    //设置黑板参数
    void SetBlackbord(const std::string& key, int value)
    {
        m_blackbord[key] = value;
    }

    //读取黑板参数
    bool GetBlackbord(const std::string& key, int & value)
    {
        auto it = m_blackbord.find(key);
        if (it == m_blackbord.end())
        {
            return false;
        }
        
        value = it->second;
        return true;
    }

    void SetGlobalState(std::shared_ptr<UnitState> state)
    {   
        m_globalState = state;
    }

    std::shared_ptr<UnitState> GetCurrState()
    {
        return m_currState;
    }


    void SetState(std::shared_ptr<UnitState> state)
    {
        if (state != nullptr)
        {
            m_currState = state;

            if (m_currState->m_onEnterCallback)
            {
                m_currState->m_onEnterCallback(m_owner);
            }
            
        }
        
    }


    void ChangeState(std::shared_ptr<UnitState> state)
    {
        if (m_currState)
        {
            m_lastState = m_currState;  //保存上一次的状态
            if (m_currState->m_onExitCallback)  //执行退出函数
            {
                m_currState->m_onExitCallback(m_owner);
            }
        }
        
        SetState(state);
    }


    void RevertToLastState()
    {
        if(m_lastState)
        {
            ChangeState(m_lastState);
        }
    }


    void OnTick(int unixtime, int tick)
    {
        if (m_globalState && m_globalState->m_onUpdateCallback)
        {
            m_globalState->m_onUpdateCallback(m_owner, unixtime, tick);
        }

        if (m_currState && m_currState->m_onUpdateCallback)
        {
            m_currState->m_onUpdateCallback(m_owner, unixtime, tick);
        }   
        
    }


    void SendEvent(enum UnitEventType event)
    {
        if (m_currState)
        {
            m_currState->OnEvent(event, m_owner);
        }
    }
private:
    std::shared_ptr<UnitState> m_globalState;   //全局状态
    std::shared_ptr<UnitState> m_lastState;     //上一次的状态
    std::shared_ptr<UnitState> m_currState;     //当前的的状态
    std::map<std::string, int> m_blackbord;     //黑板
    Unit * m_owner;
};











#endif