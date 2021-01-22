//
// Created by GLEB on 21.01.2021.
//
#include "fstream"
#include "HPlayer.h"
#include "AIPlayer.h"
#include <string>
#include <stdio.h>

#ifndef OOPEXAM_GAME_H
#define OOPEXAM_GAME_H

class GameException{};
class Game {
private:
    int size;
    int cellsToWin = 3;
    int** field; //in fact, we don't need int here. 2 bits is enough
    FILE* file;

    //char* path = "C:\\Users\\GLEB\\CLionProjects\\OOPExam\\log.txt";

    Player* player1;
    Player* player2;
    void printField();
    int getWinner(); // -1 - gameIsOver, 0 - no one, 1 - player 1, 2 - player 2
    bool printCheckWinner();
    void gameLoop();
public:

    Game();
    Game(int size, int cellsToWin);
    void init(int size, int cellsToWin);
    //TODO destructor field, file, path, player1/2



};


#endif //OOPEXAM_GAME_H
