#ifndef DNA_GENERATOR_H
#define DNA_GENERATOR_H

#include <string>

// ���� �̸� ����
#define DNA_SEQUENCE "sequence.txt"
#define READS "reads.txt"

// DNA ���� ��� ����
extern char dna[4];

// �Լ� ����
void create_dna(const int N);       // DNA ���� ����
void create_read(const int L, const int P); // DNA�κ��� �б� ���� ����
void create_seqeunce(const int N, const int L, const int P); // DNA ���� �� �б� ���� ���� ���� �Լ�

#endif
