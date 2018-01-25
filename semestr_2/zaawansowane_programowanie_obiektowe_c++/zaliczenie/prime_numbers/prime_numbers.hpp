#ifndef _PRIME_NUMBERS_
#define _PRIME_NUMBERS_

#include <iostream>

unsigned int countLines(std::ifstream &file);
unsigned int jobDiv(const int &nproc, const int &num_lines);
void thread(const std::string &file_name, const unsigned int &algorithm, const unsigned int &begin, const unsigned int &end, std::vector<std::chrono::duration<double>>& ret);

#endif