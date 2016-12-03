/*
 ゲームの状態を管理
 */

enum class PlayerOperationState{
    NONE,
    SHOT,
    WAIT,
};

enum class PlayerOperationState_Miss{
	NONE,
    FAL,
    GOOD,
    CLEAR,
};

class GameManager{
private:
    GameManager();
    static PlayerOperationState p_OperationState;
    static PlayerOperationState_Miss p_OperationStateMiss;
    
public:

    static PlayerOperationState getPlayerOperationState(){
        return p_OperationState;
    }
    
    static void setPlayerOperationState(PlayerOperationState p_Ope){
        p_OperationState = p_Ope;
    }
    
    static void setPlayerOperationState_Miss(PlayerOperationState_Miss p_Ope){
        p_OperationStateMiss = p_Ope;
    }
    
    static PlayerOperationState_Miss getPlayerOperationState_Miss(){
        return p_OperationStateMiss;
    }
};

