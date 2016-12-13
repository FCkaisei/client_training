#include <iostream>
#include <GLUT/GLUT.h>
#ifndef __GAMEMANAGER_H_INCLUDED__
#define __GAMEMANAGER_H_INCLUDED__


class GameManager{
public:
    extern PlayerOperationState getPlayerOperationState();
    extern void setPlayerOperationState(PlayerOperationState p_Ope);
    extern void setPlayerOperationState_Miss(PlayerOperationState_Miss p_Ope);
    extern PlayerOperationState_Miss getPlayerOperationState_Miss();
    extern void CheckAllGameState();
}

#endif
