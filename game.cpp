#include "game.hpp"

#include <conio.h>
#include <vcruntime_typeinfo.h>

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <thread>

#include "misc/random.hpp"

using namespace std;

Game::Game() {
  board = Board(10, 20);

  int pos[2] = {board.getWidth() / 2, 0};
  current_block = Block(randint(7), pos);
  next_block = Block(randint(7), pos);
}

void Game::run() {
  auto last_frame_time = chrono::system_clock::now();
  auto refresh_time = chrono::milliseconds(500);

  while (running) {
    handle_user_input();

    auto scince_last_frame = chrono::system_clock::now() - last_frame_time;
    if (scince_last_frame > refresh_time) {
      gameTick();

      last_frame_time += refresh_time;
    }
  }
};

void Game::tryMove(int move[2]) {
  current_block.move(move);

  move[0] = -move[0];
  move[1] = -move[1];

  if (!board.checkCollision(&current_block)) {
    current_block.move(move);
  }
}

void Game::handle_user_input() {
  if (_kbhit()) {
    char c = _getch();

    int move[2];

    switch (c) {
      case 'W':
      case 'w':
        move[0] = 0;
        move[1] = -1;
        tryMove(move);
        break;
      case 'A':
      case 'a':
        move[0] = -1;
        move[1] = 0;
        tryMove(move);
        break;
      case 'S':
      case 's':
        move[0] = 0;
        move[1] = 1;
        tryMove(move);
        break;
      case 'D':
      case 'd':
        move[0] = 1;
        move[1] = 0;
        tryMove(move);
        break;
      case ' ':
        current_block.rotateClockwise();
        if (!board.checkCollision(&current_block)) {
          current_block.rotateCounterClockwise();
        }
        break;
      case 13:
        hardDrop();
        break;
    }

    draw();
  }
}

void Game::placeBlock() {
  board.placeBlock(&current_block);
  int rmLineCount = board.removeLines();

  switch (rmLineCount) {
    case 1:
      score += 100;
    case 2:
      score += 200;
    case 3:
      score += 200;
    case 4:
      score += 300;
  }

  current_block = next_block;
  int pos[2] = {5, 0};
  next_block = Block(randint(7), pos);
}

void Game::hardDrop() {
  int move[2] = {0, 1};

  while (board.checkCollision(&current_block)) {
    current_block.move(move);
    score += 2;
  }

  move[0] = -move[0];
  move[1] = -move[1];

  current_block.move(move);
  placeBlock();
}

void Game::gameTick() {
  int move[2] = {0, 1};

  current_block.move(move);

  move[0] = -move[0];
  move[1] = -move[1];

  if (!board.checkCollision(&current_block)) {
    current_block.move(move);
    placeBlock();
  }

  draw();
}

void Game::draw() {
  int board_width = board.getWidth();
  int board_height = board.getHeight();
  bool **board_data = board.getBoardData();

  int current_block_data[4][2];
  int(*block_data)[4][2] = current_block.getBlockData();
  int(*pos)[2] = current_block.getPos();
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 2; j++) {
      current_block_data[i][j] = (*block_data)[i][j] + (*pos)[j];
    }
  }

  system(
<<<<<<< HEAD
      "cls");
=======
      "cl"
      "s");
>>>>>>> 530fca984de8f2466e45df9eb04f839f7e370ef8

  cout << "+";
  for (int i = 0; i < board_width; i++) {
    cout << "--";
  }
  cout << "+" << endl;

  bool is_curr_block = 0;
  for (int y = 0; y < board_height; y++) {
    cout << "|";
    for (int x = 0; x < board_width; x++) {
      is_curr_block = 0;
      for (int k = 0; k < 4; k++) {
        if (current_block_data[k][0] == x && current_block_data[k][1] == y) {
          is_curr_block = 1;
        }
      }

      if (board_data[y][x]) {
        cout << "[]";
      } else if (is_curr_block) {
        cout << "{}";
      } else {
        cout << "  ";
        cout << "  ";
      }
    }
    cout << "|" << endl;
  }

  cout << "+";
  for (int i = 0; i < board_width; i++) {
    cout << "--";
  }
  cout << "+" << endl;

<<<<<<< HEAD
  cout << "score: "
=======
  cout << "s"
          "c"
          "o"
          "r"
          "e"
          ":"
          " "
>>>>>>> 530fca984de8f2466e45df9eb04f839f7e370ef8
       << score << endl;
}