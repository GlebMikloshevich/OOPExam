//
// Created by GLEB on 21.01.2021.
//

#include "Game.h"

Game::Game(int size, int cellsToWin) {
    this->init(size, cellsToWin);
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

    this->file = fopen("C:\\Users\\GLEB\\CLionProjects\\OOPExam\\log.txt", "w");

    if (!file) {
        std::cerr<<"file open error\n";
        throw GameException();
    }

    //this->player1 = new HPlayer();
    this->player1 = new AIPlayer(this->size, this->cellsToWin, 1);
    this->player2 = new AIPlayer(this->size, this->cellsToWin, 2);
    //this->player2 = new HPlayer(2);
    this->gameLoop();
}

void Game::printField(){
    for (int i = 0; i < this->size; i++){
        for (int j = 0; j < this->size; j++) {
            //TODO make grid with numbers around
            switch (this->field[i][j]) {
                case 0:
                    std::cout<<'.';
                    break;
                case 1:
                    //std::cout<<"\033[1;31mX \033[0m";
                    std::cout<<'X';
                    break;
                case 2:
                    std::cout<<'0';
                    //std::cout<<"\033[1;33m0 \033[0m";
                    break;
                default:
                    throw GameException();
                    exit(1);
                    break;
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
        fwrite("player one won ", sizeof("player one won"), 1, this->file);
        return true;
    } else if (winner == 2) {
        std::cout<<"player two won!";
        fwrite("player two won ", sizeof("player two won"), 1, this->file);
        return true;
    } else if (winner == -1) {
        std::cout<<"draw";
        fwrite("draw ", sizeof("draw"), 1, this->file);
        return true;
    }


    fwrite("next turn ", sizeof("next turn"), 1, this->file);
    return false;

}

void Game::gameLoop() {
    std::pair<int, int> coords;

    //loop

    /* player one */
    while(true) {
        std::cout<<"--- Player one turn ---\n";
        player1->makeTurn(this->size, this->field);
        coords = player1->logTurn();

        fwrite("player one", sizeof("player one"), 1, this->file);
        fwrite(&coords.first, sizeof(int), 1, this->file);
        fwrite(" ", sizeof(char), 1, this->file);
        fwrite(&coords.second, sizeof(int), 1, this->file);
        fwrite("\n", sizeof(char), 1, this->file);
        this->printField();

        if (this->printCheckWinner())
            break;
        /* player two */
        std::cout<<"--- Player two turn ---\n";
        player2->makeTurn(this->size, this->field);
        coords = player2->logTurn();

        fwrite("player two", sizeof("player two"), 1, this->file);
        fwrite(&(coords.first), sizeof(int), 1, this->file);
        fwrite(" ", sizeof(char), 1, this->file);
        fwrite(&coords.second, sizeof(int), 1, this->file);
        fwrite("\n", sizeof(char), 1, this->file);
        this->printField();

        if (this->printCheckWinner())
            break;
    }

}