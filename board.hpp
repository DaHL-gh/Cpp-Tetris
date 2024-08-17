#include "block.hpp"

class Board {
public:
  Board();
  Board(int width, int height);

  Board &operator=(const Board &old);
  
  unsigned int removeLines();
  bool checkCollision(Block *block);
  void placeBlock(Block *block);

  int getWidth();
  int getHeight();
  bool **getBoardData();
  
  void print();


private:
  int width;
  int height;
  bool **gameboard;

  void deleteGameboard();
  void createBoard();
};