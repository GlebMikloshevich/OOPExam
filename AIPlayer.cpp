//
// Created by GLEB on 21.01.2021.
//

#include "AIPlayer.h"

const int vi[4] = {1, 1, 1, 0};
const int vj[4] = {1, -1, 0, 1};

AIPlayer::AIPlayer(int size, int cellsToWin) {
    this->init(size, cellsToWin, 2);
}

AIPlayer::AIPlayer(int size, int cellsToWin, int playerNumber) {
    this->init(size, cellsToWin, playerNumber);
}

void AIPlayer::init(int size, int cellsToWin, int playerNumber) {
    this->size = size;
    this->weights = new int* [size];
    for (int i = 0; i < size; i++) {
        this->weights[i] = new int[size];
        for (int j = 0; j < size; j++)
            this->weights[i][j] = 0;
    }
    this->cellsToWin = cellsToWin;
    this->playerNumber = playerNumber;
}

std::pair<int, int> AIPlayer::logTurn() {
    return this->last_turn;
}

void AIPlayer::makeTurn(int size, int **field) {
    this->updateWeights(field);
    /*
    for (int i = 0; i < this->size; i++) {
        for (int j = 0; j < this->size; j++) {
            std::cout<<this->weights[i][j]<<' ';
        }
        std::cout<<'\n';
    }
     */

    int a = 1;
    //TODO Gleb, do something!
    std::pair <int, int> cur_turn (0, 0);
    int cur_weight = this->weights[0][0];
    for (int i = 0; i < this->size; i++) {
        for (int j = 0; j < this->size; j++) {
            if (this->weights[i][j] > cur_weight) {
                cur_weight = this->weights[i][j];
                cur_turn.first = i;
                cur_turn.second = j;
            }
        }
    }
    //std::cout<<"player number "<<this->playerNumber<<'\n';
    field[cur_turn.first][cur_turn.second] = this->playerNumber;
    this->last_turn = cur_turn;
    //std::cout<<"AI turn is "<<cur_turn.first<<' '<<cur_turn.second<<'\n';
}

void AIPlayer::updateWeights(int** field) {
    this->weights[size/2][size/2] = 1;
    for (int i = 0; i < this->size; i++) {
        for (int j = 0; j < this->size; j++) {
            if (field[i][j] != 0) {
                this->weights[i][j] = -1;
                continue;
            }
            for (int k = 0; k < 4; k++) {
                int cur_vi = vi[k];
                int cur_vj = vj[k];
                int cur_i = i;
                int cur_j = j;

                int cur_weight = 0;
                int free_tiles = 0;
                //идем в четыре стороны и проверяем победу.
                if (field[i][j] == 2){
                    cur_weight++ ;
                    free_tiles++ ;
                } else if (field[i][j] == 0) {
                    free_tiles++;
                } else continue;

                for (int t = 0; t < cellsToWin-1; t++){
                    //hard code
                    cur_i += cur_vi;
                    cur_j += cur_vj;

                    if (cur_i < 0 || cur_j <0 || cur_i >= this->size || cur_j >= this->size)
                        break;

                    if (field[cur_i][cur_j] == 2){ //TODO switch case
                        cur_weight++ ;
                        free_tiles++ ;
                    } else if (field[cur_i][cur_j] == 0){
                        free_tiles++;
                    } else break;
                }

                cur_vi = -vi[k]; //reversed
                cur_vj = -vj[k];
                cur_i = i;
                cur_j = j;
                for (int t = 0; t < cellsToWin-1; t++){
                    //hard code
                    cur_i += cur_vi;
                    cur_j += cur_vj;

                    if (cur_i < 0 || cur_j < 0 || cur_i >= this->size || cur_j >= this->size)
                        break;
                    if (field[cur_i][cur_j] == 2){
                        cur_weight++ ;
                        free_tiles++ ;

                    } else if (field[cur_i][cur_j] == 0){
                        free_tiles++;
                    } else break;


                }
                if (cur_weight >= this->weights[i][j]) {
                    if (free_tiles == this->cellsToWin)
                        this->weights[i][j] = cur_weight;
                    if (free_tiles > this->cellsToWin)
                        this->weights[i][j] = cur_weight + 1;
                }

                if (this->weights[this->size/2][this->size/2] == 0) //first turn check
                    this->weights[this->size/2][this->size/2]++;
            }
        }
    }
}