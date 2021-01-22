//
// Created by GLEB on 21.01.2021.
//
#include "Player.h"
#ifndef OOPEXAM_HPLAYER_H
#define OOPEXAM_HPLAYER_H


class HPlayer : public Player {
public:
    int playerNumber = 1;
    std::pair <int, int> last_turn;

    HPlayer();
    HPlayer(int playerNumber);
    std::pair<int, int> logTurn();
    void makeTurn(int size, int** field);

    friend class Game;
};


#endif //OOPEXAM_HPLAYER_H
