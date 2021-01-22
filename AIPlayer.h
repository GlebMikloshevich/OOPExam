//
// Created by GLEB on 21.01.2021.
//
#include "Player.h"
#ifndef OOPEXAM_AIPLAYER_H
#define OOPEXAM_AIPLAYER_H


class AIPlayer : public Player{
    int size;
    int** weights;
    int8_t playerNumber;
    int cellsToWin;

    std::pair <int, int> last_turn;
    std::pair<int, int> logTurn();
    void makeTurn(int size, int8_t** field);
    void updateWeights(int8_t** field);
    bool oneTurnWin(int8_t** field, int8_t player);

public:
    AIPlayer();
    AIPlayer(int size, int cellsToWin);
    AIPlayer(int size, int cellsToWin, int8_t playerNumber);
    ~AIPlayer();
    void init(int size, int cellsToWin,  int8_t playerNumber);

    friend class Game;
};


#endif //OOPEXAM_AIPLAYER_H
