#ifndef RABINKARP_H
#define RABINKARP_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>
#include <ctime>

extern int d;          // ����
extern int q;      // ��ⷯ ����� ���� �Ҽ�

int charToValue(char c);
int gethash(const std::string& read);
void execute_RabinKarp(int pattern);
std::vector <std::string> rb_createReadArray();

#endif