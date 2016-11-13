enum class PlayerOperationState{
    NONE,
    SHOT,
    WAIT
};

class GameManager{
private:
    GameManager();
    static PlayerOperationState p_OperationState;
public:

    static PlayerOperationState getPlayerOperationState(){
        return p_OperationState;
    }
    
    static void setPlayerOperationState(PlayerOperationState p_Ope){
        p_OperationState = p_Ope;
    }
};

