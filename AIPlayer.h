//
// Created by GLEB on 21.01.2021.
//
#include "Player.h"
#ifndef OOPEXAM_AIPLAYER_H
#define OOPEXAM_AIPLAYER_H


class AIPlayer : public Player{
    int size;
    int** weights;
    int playerNumber;
    int cellsToWin;

    std::pair <int, int> last_turn;
    std::pair<int, int> logTurn();
    void makeTurn(int size, int** field);
    void updateWeights(int** field);

public:
    AIPlayer();
    AIPlayer(int size, int cellsToWin);
    AIPlayer(int size, int cellsToWin, int playerNumber);
    ~AIPlayer();
    void init(int size, int cellsToWin,  int playerNumber);

    friend class Game;
};


#endif //OOPEXAM_AIPLAYER_H
