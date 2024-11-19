#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1000
#define MAX_RESTORED_LENGTH 1000000

int kmp(const char* current_line, const char* next_line) {
	int len1 = strlen(current_line);
	int len2 = strlen(next_line);

	int* lps = (int*)malloc(sizeof(int) * len2);
	int j = 0;
	lps[0] = 0;

	for (int i = 1; i < len2; i++) {
		while (j > 0 && next_line[i] != next_line[j]) {
			j = lps[j - 1];
		}
		if (next_line[i] == next_line[j]) {
			j++;
		}
		lps[i] = j;
	}

	// current_line�� next_line ��
	int i = len1 - len2; // current_line ���κп��� next_line�� �� ����

	j = 0; // next_line�� �� ���� ��ġ
	while (i < len1) { // current_line ������ ��
		if (current_line[i] == next_line[j]) { // ���� ��ġ
			i++;
			j++;
		}
		else {
			if (j > 0) {
				j = lps[j - 1]; // ���� �� LPS ���̺� Ȱ���� ����
			}
			else {
				i++; // j�� 0�̸� ���� ���ڷ� �̵�
			}
		}
	}

	free(lps);
	return j; // ��ġ�� �κ��� ���� ��ȯ
}


void execute_KMP() {
	FILE* file = fopen("read.txt", "r");
	if (!file) {
		perror("Unable to open file");
		exit(1);
	}

	FILE* result_file = fopen("result_kmp.txt", "w");
	if (!result_file) {
		perror("Unable to open result file");
		fclose(file);
		exit(1);
	}

	char current_line[MAX_LINE_LENGTH];
	char next_line[MAX_LINE_LENGTH];
	char restored_dna[MAX_RESTORED_LENGTH] = "";
	int restored_dna_len = 0;

	if (fgets(current_line, sizeof(current_line), file) == NULL) {
		printf("File is empty\n");
		fclose(file);
		fclose(result_file);
		exit(1);
	}

	int len = strlen(current_line);
	if (current_line[len - 1] == '\n') {
		current_line[len - 1] = '\0';
	}

	int i = 0;
	while (current_line[i] != '\0') {
		restored_dna[restored_dna_len] = current_line[i];
		restored_dna_len++;
		i++;
	}
	restored_dna[restored_dna_len] = '\0';

	while (fgets(next_line, sizeof(next_line), file)) {
		len = strlen(next_line);
		if (next_line[len - 1] == '\n') {
			next_line[len - 1] = '\0';
		}

		int overlap_length = kmp(current_line, next_line);

		i = 0;
		while (next_line[overlap_length + i] != '\0') {
			restored_dna[restored_dna_len] = next_line[overlap_length + i];
			restored_dna_len++;
			i++;
		}
		restored_dna[restored_dna_len] = '\0';

		i = 0;
		while (next_line[i] != '\0') {
			current_line[i] = next_line[i];
			i++;
		}
		current_line[i] = '\0';
	}

	fprintf(result_file, "%s", restored_dna);

	fclose(file);
	fclose(result_file);
}

