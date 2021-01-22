//
// Created by GLEB on 21.01.2021.
//

#include "Game.h"
std::string output;
Game::Game(int size, int cellsToWin) {
    this->init(size, cellsToWin);
}

Game::~Game() {
    delete this->player1;
    delete this->player2;


    for (int i = 0; i < this->size; i++) {
        delete this->field[i];
    }
    delete [] field;
}

void Game::init(int size, int cellsToWin) {
    this->size = size;
    this->cellsToWin = cellsToWin;

    this->field = new int* [size];
    for (int i = 0; i < size; i++){
        this->field[i] = new int[size];
        for (int j = 0; j < size; j++)
            this->field[i][j] = 0;
    }

    this->file.open(this->path, std::ios::out);

    if (!file) {
        std::cerr<<"file open error\n";
        throw GameException();
    }


    //this->player1 = new HPlayer(1);
    this->player1 = new AIPlayer(this->size, this->cellsToWin, 1);
    this->player2 = new HPlayer(2);
    //this->player2 = new AIPlayer(this->size, this->cellsToWin, 2);

    this->gameLoop();
}

void Game::printField(){
    for (int i = 0; i < this->size; i++){
        for (int j = 0; j < this->size; j++) {
            switch (this->field[i][j]) {
                case 0:
                    std::cout<<'.';
                    break;
                case 1:
                    std::cout<<'X';
                    break;
                case 2:
                    std::cout<<'0';
                    break;
                default:
                    throw GameException();
            }
            if (j != this->size-1)
                std::cout<<' ';
        }
        std::cout<<'\n';
    }
}

int Game::getWinner() {
    int vi[4] = {1, 1, 1, 0};
    int vj[4] = {1, -1, 0, 1};
    int fullness = 0;
    // - size?
    for (int i = 0; i < this->size; i++) {
        for (int j = 0; j < this->size; j++) {
            if (this->field[i][j] == 0)
                continue;
            fullness++;

            for (int k = 0; k < 4; k++) {
                int cur_vi = vi[k];
                int cur_vj = vj[k];
                int cur_i = i;
                int cur_j = j;
                int row_length = 0;

                //идем в четыре стороны и проверяем победу.
                while (row_length < this->cellsToWin) {
                    if (cur_i < 0 || cur_j < 0 || cur_i >= this->size || cur_j >= this->size)
                        break;

                    if (this->field[cur_i][cur_j] != this->field[i][j])
                        break;
                    row_length++;
                    cur_i += cur_vi;
                    cur_j += cur_vj;
                }

                if (row_length == this->cellsToWin)
                    return this->field[i][j];
            }
        }
    }

    if (fullness == this->size*this->size)
        return -1; //поле закончилось
    return 0;
}

bool Game::printCheckWinner() {
    int winner = this->getWinner();

    if (winner == 1) {
        std::cout<<"player one won!";
        this->file<<"player one won";
        return true;
    } else if (winner == 2) {
        std::cout<<"player two won!";
        this->file<<"player two won";
        return true;
    } else if (winner == -1) {
        std::cout<<"draw";
        this->file<<"draw";
        return true;
    }

    return false;

}

void Game::gameLoop() {
    std::pair<int, int> coords;

    //loop
    while(true) {
        std::cout<<"-----------------------\n|   Player one turn   |\n-----------------------\n";
        player1->makeTurn(this->size, this->field);
        coords = player1->logTurn();

        this->file<<"Player one "<<coords.first<<' '<<coords.second<<'\n';
        this->printField();

        if (this->printCheckWinner())
            break;
        /* player two */
        std::cout<<"-----------------------\n|   Player two turn   |\n-----------------------\n";
        player2->makeTurn(this->size, this->field);
        coords = player2->logTurn();

        this->file<<"Player two "<<coords.first<<' '<<coords.second<<'\n';
        this->printField();

        if (this->printCheckWinner())
            break;
    }
    this->file.close();

}