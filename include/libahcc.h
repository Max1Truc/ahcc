#ifndef H_LIB_AHCC
#define H_LIB_AHCC

#include <iostream>
#include <fstream>
#include <string>
#include <set>

int compress(std::ifstream &input, std::ofstream &output);

int uncompress(std::ifstream &input, std::ofstream &output);

#endif
