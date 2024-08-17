#include <iostream>

#include "block.hpp"

using namespace std;

const int revL[4][2] = {{0, 0}, {1, 0}, {-1, 0}, {1, 1}};
const int L[4][2] = {{0, 0}, {1, 0}, {-1, 0}, {1, -1}};
const int cube[4][2] = {{0, 0}, {1, 0}, {0, 1}, {1, 1}};
const int tri[4][2] = {{0, 0}, {1, 0}, {0, 1}, {0, -1}};
const int Z[4][2] = {{0, 0}, {1, 0}, {0, 1}, {-1, 1}};
const int revZ[4][2] = {{0, 0}, {-1, 0}, {0, 1}, {1, 1}};
const int stick[4][2] = {{0, 0}, {-1, 0}, {1, 0}, {2, 0}};

const int (*blocks_data[7])[4][2] = {&revL, &L, &cube, &tri, &Z, &revZ, &stick};

Block::Block() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 2; j++) {
      block_data[i][j] = 0;
    }
  }
  
  pos[0] = 0;
  pos[1] = 0;
}

Block::Block(unsigned int type, int pos[2]) {
//  cout << "block" << endl;
  setType(type);
  setPos(pos);
//  cout << "endblock" << endl;
}

Block &Block::operator=(const Block &old) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 2; j++) {
      block_data[i][j] = old.block_data[i][j];
    }
  }
  
  for (int i = 0; i < 2; i++) {
    pos[i] = old.pos[i];
  }
  
  return *this;
}

int (*Block::getBlockData())[4][2] {
  return &block_data;
}

void Block::setType(int type) {
//  cout << "settingtype " << type << endl;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 2; j++) {
      block_data[i][j] = (*blocks_data[type])[i][j];
    }
  }
}

int (*Block::getPos())[2] {
  return &pos;
}

void Block::setPos(int newPos[2]) {
  for (int i = 0; i < 2; i++) {
    pos[i] = newPos[i];
  }
}

void Block::move(int movement[2]) {
  for (int i = 0; i < 2; i++) {
    pos[i] += movement[i];
  }
}

void Block::rotateCounterClockwise() {
  for (int i = 0; i < 4; i++) {
    int temp_x = block_data[i][0];
    int temp_y = block_data[i][1];

    block_data[i][0] = -temp_y;
    block_data[i][1] = temp_x;
  }
}

void Block::rotateClockwise() {
  for (int i = 0; i < 4; i++) {
    int temp_x = block_data[i][0];
    int temp_y = block_data[i][1];

    block_data[i][0] = temp_y;
    block_data[i][1] = -temp_x;
  }
}

void Block::debugPrint() {
  cout << "pos: ";
  for (int i = 0; i < 2; i++) {
    cout << pos[i];
    if (i <= 0) {
      cout << ", ";
    } else {
      cout << endl;
    }
  }

  cout << "data:" << endl;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 2; j++) {
      cout << block_data[i][j];
      if (j <= 0) {
        cout << ", ";
      }
    }
    cout << endl;
  }
}
