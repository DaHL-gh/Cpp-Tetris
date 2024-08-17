#include <iostream>

#include "board.hpp"

using namespace std;

Board::Board() {
  width = 0;
  height = 0;
  gameboard = new bool *[0];
}

Board::Board(int width, int height) : width(width),
                                      height(height),
                                      gameboard(new bool *[height]) {
  for (int i = 0; i < height; i++) {
    gameboard[i] = new bool[width];
    for (int j = 0; j < width; j++) {
      gameboard[i][j] = 0;
    }
  };
}

Board &Board::operator=(const Board &old) {
  deleteGameboard();
  width = old.width;
  height = old.height;
  createBoard();

  return *this;
}

unsigned int Board::removeLines() {
  int rmLinesCount = 0;

  bool toRemove;
  for (int y = 0; y < height; y++) {

    toRemove = 1;
    for (int x = 0; x < width; x++) {
      if (!gameboard[y][x]) {
        toRemove = 0;
      }
    }

    if (toRemove) {
      rmLinesCount++;

      for (int temp_y = y; temp_y != 0; temp_y--) {
        for (int x = 0; x < width; x++) {
          gameboard[temp_y][x] = gameboard[temp_y - 1][x];
        }
      }
    }
  }

  return rmLinesCount;
}

bool Board::checkCollision(Block *block) {
  int(&blockPos)[2] = *(block->getPos());

  const int(&data)[4][2] = *(block->getBlockData());

  int temp_x, temp_y;
  for (int i = 0; i < 4; i++) {
    temp_x = data[i][0] + blockPos[0];
    temp_y = data[i][1] + blockPos[1];

    // check for board edge collision
    if (!(0 <= temp_y && temp_y < height && 0 <= temp_x && temp_x < width)) {
      return 0;
    }

    // check for fixed block collision
    if (gameboard[temp_y][temp_x]) {
      return 0;
    }
  }

  return 1;
}

void Board::placeBlock(Block *block) {
  int(&blockPos)[2] = *(block->getPos());
  const int(&data)[4][2] = *(block->getBlockData());

  int x, y;
  for (int i = 0; i < 4; i++) {
    x = data[i][0] + blockPos[0];
    y = data[i][1] + blockPos[1];

    // check for board edge collision
    if (0 <= y && y < height && 0 <= x && x < width) {
      gameboard[y][x] = 1;
    }
  }
}

int Board::getWidth() {
  return width;
}

int Board::getHeight() {
  return height;
}

bool **Board::getBoardData() {
  return gameboard;
}

void Board::deleteGameboard() {
  for (int i = 0; i < height; i++) {
    delete[] gameboard[i];
  }
  delete[] gameboard;
}

void Board::createBoard() {
  gameboard = new bool *[height];
  for (int i = 0; i < height; i++) {
    gameboard[i] = new bool[width];
    for (int j = 0; j < width; j++) {
      gameboard[i][j] = 0;
    }
  }
}

void Board::print() {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      cout << gameboard[i][j];
    }
    cout << endl;
  }
}