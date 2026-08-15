#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Unit.h"

class StateMachine;

class Player : public Unit
{
public:
    Player();
    void StopMove();
    void Move();


private:
    StateMachine * m_stateMachine;
};


#endif // !__PLAYER_H__