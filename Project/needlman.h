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

// 파일에서 시퀀스를 읽어오는 함수
void readFile(const char *filename, char *content);

// Needleman-Wunsch 알고리즘 구현
int needlemanWunsch(char *query, char *target);

// Levenshtein 거리 계산
int levenshteinDistance(const char *str1, const char *str2);

// 시퀀스를 복원하는 함수
void restoreSequence(char *seq1, char *seq2, char *restoredSeq);

// 갭을 무시한 정확도 측정
void ignoreGapsAndMeasureAccuracy(const char *predicted, const char *target);

// Needleman-Wunsch 실행 함수
int execute_needlman();

#endif // SEQUENCE_UTILS_H
