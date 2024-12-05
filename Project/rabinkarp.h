#ifndef RABINKARP_H
#define RABINKARP_H
#include <string>

extern int d;          // 진수
extern int q;      // 모듈러 계산을 위한 소수

int charToValue(char c);
int gethash(const std::string& read);
void execute_RabinKarp(int pattern);
void createReadArray();

#endif