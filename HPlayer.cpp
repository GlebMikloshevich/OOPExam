//
// Created by GLEB on 21.01.2021.
//

#include "HPlayer.h"

HPlayer::HPlayer() {}

HPlayer::HPlayer(int playerNumber) {
    this->playerNumber = playerNumber;
}
HPlayer::~HPlayer(){}

std::pair<int, int> HPlayer::logTurn() {
    return this->last_turn;
}

void HPlayer::makeTurn(int size, int **field) {
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