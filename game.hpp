#include "board.hpp"

#ifdef BLOCK_HPP
#include "block.hpp"
#endif

class Game {
public:
  Game();

  void run();

private:
  bool running = 1;
  unsigned int score = 0;

  Board board;
  Block next_block;
  Block current_block;

  void handle_user_input();
  void tryMove(int move[2]);
  void hardDrop();
  void gameTick();
  void placeBlock();
  void draw();
};