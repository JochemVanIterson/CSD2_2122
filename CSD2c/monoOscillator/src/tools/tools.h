#ifndef _TOOLS_H_
#define _TOOLS_H_

#include <iostream>
#include <map>
#include <iomanip>
#include <string>
#include <random>
#include <sstream>
#include <cmath>

class Tools{
public:
  Tools();
  ~Tools();

  static std::string array2string(std::vector<int> &writableArray, char delimiter);
  static std::vector<int> string2array(std::string &s, char delimiter);
  static void array_insert_end(std::vector<int> &array, int maxsize, int value);
  static void init_rand();
  static int rand_between(int min, int max);
  static void printVectorInt(std::string name, std::vector<int> &array);
  static double midinote2freq(int midinote);
  static int keymidi(char input);
};

#endif
