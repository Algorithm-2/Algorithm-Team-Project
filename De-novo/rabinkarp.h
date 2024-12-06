#ifndef RABINKARP_H
#define RABINKARP_H
#include <string>

extern int d;          // ����
extern int q;      // ��ⷯ ����� ���� �Ҽ�

int charToValue(char c);
int gethash(const std::string& read);
void execute_RabinKarp(int pattern);
void createReadArray();

#endif