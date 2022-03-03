#include "tools.h"

std::string Tools::array2string(std::vector<int> &writableArray, char delimiter){
  std::string stringValue = "";
  for(int walker = 0; walker<writableArray.size(); walker++){
    if(stringValue != "")stringValue+=delimiter;
    stringValue.append(std::to_string(writableArray[walker]));
  }
  return stringValue;
}
std::vector<int> Tools::string2array(std::string &s, char delimiter){
  std::vector<int> tokens;
  std::string token;
  std::istringstream tokenStream(s);
  while (std::getline(tokenStream, token, delimiter)){
    tokens.push_back(std::stoi(token));
  }
  return tokens;
}
void Tools::array_insert_end(std::vector<int> &array, int maxsize, int value){
  for(int walker = 1; (walker<maxsize); walker++){
    array[walker-1] = array[walker];
  }
  if(array.size()<maxsize)array.push_back(value);
  else array[maxsize-1] = value;
}
int Tools::rand_between(int min, int max){
  int size = max - min;
  return min+rand()%size;
}
void Tools::init_rand(){
  srand(time(NULL));
}
void Tools::printVectorInt(std::string name, std::vector<int> &array){
  std::cout << "Name: " << name << std::endl;
  std::cout << "Size: " << array.size() << std::endl;
  for(int walker = 0; walker<array.size(); walker++){
    std::cout << array[walker] << ", ";
  }
  std::cout << std::endl;
}
double Tools::midinote2freq(int midinote){
  double freq = pow(2.0, ((midinote-69)/12.))*440.0;
  return freq;
}
int Tools::keymidi(char input){
  switch (input){
    case 'a': // c
      return 0;
    case 'w': // cis
      return 1;
    case 's': // d
      return 2;
    case 'e': // dis
      return 3;
    case 'd': // e
      return 4;
    case 'f': // f
      return 5;
    case 't': // fis
      return 6;
    case 'g': // g
      return 7;
    case 'y': // gis
      return 8;
    case 'h': // a
      return 9;
    case 'u': // ais
      return 10;
    case 'j': // b
      return 11;
    case 'k': // c
      return 12;
    case 'o': // cis
      return 12+1;
    case 'l': // d
      return 12+2;
    case 'p': // dis
      return 12+3;
    case ';': // e
      return 12+4;
    case '\'': // f
      return 12+5;
  }
  return -1;
}
