#ifndef RABINKARP_H
#define RABINKARP_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>
#include <ctime>

extern int d;          // 진수
extern int q;      // 모듈러 계산을 위한 소수

int charToValue(char c);
int gethash(const std::string& read);
void execute_RabinKarp(int pattern);
std::vector <std::string> rb_createReadArray();

#endif