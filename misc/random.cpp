#include <random>

#include "random.hpp"

using namespace std;

random_device rd;
mt19937 gen(rd());

int randint(int min, int max) {
  uniform_int_distribution<> dist(min, max - 1);
  
  return dist(gen);
}

int randint(int max) {
  uniform_int_distribution<> dist(0, max - 1);
  
  return dist(gen);
}