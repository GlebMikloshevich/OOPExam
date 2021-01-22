//
// Created by GLEB on 21.01.2021.
//
#include "fstream"
#include "utility"
#include <iostream>
#ifndef OOPEXAM_PLAYER_H
#define OOPEXAM_PLAYER_H


class Player {
private:
    virtual std::pair<int, int> logTurn() = 0;

public:
    virtual ~Player(){};
    virtual void makeTurn(int size, int8_t** field) = 0;
    friend class Game;
};


#endif //OOPEXAM_PLAYER_H
