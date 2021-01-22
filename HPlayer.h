//
// Created by GLEB on 21.01.2021.
//
#include "Player.h"
#ifndef OOPEXAM_HPLAYER_H
#define OOPEXAM_HPLAYER_H


class HPlayer : public Player {
private:
    int playerNumber = 1;
    std::pair <int, int> last_turn;
    std::pair<int, int> logTurn();

public:
    HPlayer();
    HPlayer(int playerNumber);
    ~HPlayer();
    void makeTurn(int size, int** field);

    friend class Game;
};


#endif //OOPEXAM_HPLAYER_H
