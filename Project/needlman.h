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

void readFile(const char *filename, char *content);

int needlemanWunsch(char *query, char *target);

int levenshteinDistance(const char *str1, const char *str2);

void restoreSequence(char *seq1, char *seq2, char *restoredSeq);

void ignoreGapsAndMeasureAccuracy(const char *predicted, const char *target);

void execute_Needlman();

#endif
