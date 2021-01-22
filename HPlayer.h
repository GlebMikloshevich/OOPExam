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
    HPlayer(int8_t playerNumber);
    ~HPlayer();

    void init(uint8_t playerNumber);
    void makeTurn(int size, int8_t** field);

    friend class Game;
};


#endif //OOPEXAM_HPLAYER_H
