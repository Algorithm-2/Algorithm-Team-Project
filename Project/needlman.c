#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define MAX_LENGTH 200000
#define MATCH 1
#define MISMATCH 0
#define GAP_OPEN -1
#define GAP_EXT -1



void readFile(const char *filename, char *content);
int needlemanWunsch(char *query, char *target);
void measureAccuracy(const char *predicted, const char *target);
void restoreSequence(char *seq1, char *seq2, char *restoredSeq);
int levenshteinDistance(const char *str1, const char *str2);
void ignoreGapsAndMeasureAccuracy(const char *predicted, const char *target);




int execute_needlman() {
	clock_t start, end;
	double time_spent;
	char readSeq[MAX_LENGTH], targetSeq[MAX_LENGTH];
	readFile("read.txt", readSeq);
	readFile("sequence.txt", targetSeq);
	start = clock();
	char restoredSeq[MAX_LENGTH];
	restoreSequence(readSeq, targetSeq, restoredSeq);
	end = clock();
	time_spent = (double)(end - start) / CLOCKS_PER_SEC;
	printf("Execution Time: %.6f seconds\n", time_spent);
	ignoreGapsAndMeasureAccuracy(restoredSeq, targetSeq);
	return time_spent;
}

void readFile(const char *filename, char *content) {
	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		perror("Error opening file");
		exit(1);
	}
	fgets(content, MAX_LENGTH, file);
	fclose(file);
}

int needlemanWunsch(char *query, char *target) {
	int lenQuery = strlen(query);
	int lenTarget = strlen(target);
	int **dp = (int **)malloc((lenQuery + 1) * sizeof(int *));
	for (int i = 0; i <= lenQuery; i++) {
		dp[i] = (int *)malloc((lenTarget + 1) * sizeof(int));
	}
	for (int i = 0; i <= lenQuery; i++) {
		dp[i][0] = i * GAP_EXT;
	}
	for (int j = 0; j <= lenTarget; j++) {
		dp[0][j] = j * GAP_EXT;
	}
	for (int i = 1; i <= lenQuery; i++) {
		for (int j = 1; j <= lenTarget; j++) {
			int matchScore = (query[i - 1] == target[j - 1]) ? MATCH : MISMATCH;
			int scoreDiagonal = dp[i - 1][j - 1] + matchScore;
			int scoreUp = dp[i - 1][j] + GAP_EXT;
			int scoreLeft = dp[i][j - 1] + GAP_EXT;
			dp[i][j] = scoreDiagonal > scoreUp ? scoreDiagonal : scoreUp;
			dp[i][j] = dp[i][j] > scoreLeft ? dp[i][j] : scoreLeft;
		}
	}
	int result = dp[lenQuery][lenTarget];
	for (int i = 0; i <= lenQuery; i++) {
		free(dp[i]);
	}
	free(dp);
	return result;
}

int levenshteinDistance(const char *str1, const char *str2) {
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	int **dp = (int **)malloc((len1 + 1) * sizeof(int *));
	for (int i = 0; i <= len1; i++) {
		dp[i] = (int *)malloc((len2 + 1) * sizeof(int));
	}
	for (int i = 0; i <= len1; i++) dp[i][0] = i;
	for (int j = 0; j <= len2; j++) dp[0][j] = j;
	for (int i = 1; i <= len1; i++) {
		for (int j = 1; j <= len2; j++) {
			int cost = (str1[i - 1] == str2[j - 1]) ? 0 : 1;
			dp[i][j] = fmin(fmin(dp[i - 1][j] + 1, dp[i][j - 1] + 1), dp[i - 1][j - 1] + cost);
		}
	}
	int result = dp[len1][len2];
	for (int i = 0; i <= len1; i++) {
		free(dp[i]);
	}
	free(dp);
	return result;
}

void ignoreGapsAndMeasureAccuracy(const char *predicted, const char *target) {
	int validPredictedCount = 0;
	int validTargetCount = 0;
	int correctCount = 0;
	int lenPredicted = strlen(predicted);
	int lenTarget = strlen(target);
	char paddedPredicted[MAX_LENGTH], paddedTarget[MAX_LENGTH];
	int i = 0, j = 0;
	for (; i < lenPredicted && j < lenTarget; i++, j++) {
		if (predicted[i] != '-') {
			validPredictedCount++;
		}
		if (target[j] != '-') {
			validTargetCount++;
		}
		if (predicted[i] == target[j]) {
			correctCount++;
		}
	}
	double accuracy = (validTargetCount == 0) ? 0 : ((double)correctCount / validTargetCount) * 100;
	printf("Valid Predicted Length: %d\n", validPredictedCount);
	printf("Valid Target Length: %d\n", validTargetCount);
	printf("Correct Matches: %d\n", correctCount);
	printf("Accuracy: %.2f%%\n", accuracy);
}

void restoreSequence(char *seq1, char *seq2, char *restoredSeq) {
	int len1 = strlen(seq1);
	int len2 = strlen(seq2);
	if (len1 + len2 < MAX_LENGTH) {
		strcpy(restoredSeq, seq1);
		strcat(restoredSeq, seq2);
	}
	else {
		strncpy(restoredSeq, seq1, MAX_LENGTH - 1);
		restoredSeq[MAX_LENGTH - 1] = '\0';
	}
}
