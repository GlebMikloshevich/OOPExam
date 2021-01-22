//
// Created by GLEB on 21.01.2021.
//

#include "HPlayer.h"

HPlayer::HPlayer() {}

HPlayer::HPlayer(int8_t playerNumber) {
    this->playerNumber = playerNumber;
}
HPlayer::~HPlayer(){}

void HPlayer::init(uint8_t playerNumber) {
    this->playerNumber = playerNumber;
}

std::pair<int, int> HPlayer::logTurn() {
    return this->last_turn;
}

void HPlayer::makeTurn(int size, int8_t **field) {
    int r, c;
    std::cout<<"Input row and column.\n";
    std::cin>>r>>c;

    while (r < 0 || c < 0 || r >= size || c >= size || field[r][c] != 0) {
        std::cout<<"This field is out of bound or blocked, input another pair. \n";
        std::cin>>r>>c;
    }
    field[r][c] = this->playerNumber;
    this->last_turn.first = r;
    this->last_turn.second = c;
}