#pragma once
#ifndef SEQUENCE_UTILS_H
#define SEQUENCE_UTILS_H

#define MAX_LENGTH 200000
#define MATCH 1
#define MISMATCH 0
#define GAP_OPEN -1
#define GAP_EXT -1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

// ���Ͽ��� �������� �о���� �Լ�
void readFile(const char *filename, char *content);

// Needleman-Wunsch �˰��� ����
int needlemanWunsch(char *query, char *target);

// Levenshtein �Ÿ� ���
int levenshteinDistance(const char *str1, const char *str2);

// �������� �����ϴ� �Լ�
void restoreSequence(char *seq1, char *seq2, char *restoredSeq);

// ���� ������ ��Ȯ�� ����
void ignoreGapsAndMeasureAccuracy(const char *predicted, const char *target);

// Needleman-Wunsch ���� �Լ�
int execute_needlman();

#endif // SEQUENCE_UTILS_H
