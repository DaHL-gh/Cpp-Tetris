class Block {
public:
  Block();
  Block(unsigned int type, int pos[2]);
  
  Block &operator=(const Block &old);
  
  void debugPrint();

  int (*getBlockData())[4][2];
  void setType(int type);

  int (*getPos())[2];
  void setPos(int newPos[2]);

  void move(int movement[2]);
  void rotateCounterClockwise();
  void rotateClockwise();

private:
  int block_data[4][2];
  int pos[2];
};
