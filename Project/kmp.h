#ifndef KMP_ASSEMBLER_H
#define KMP_ASSEMBLER_H

#define MAX_LINE_LENGTH 1000
#define MAX_RESTORED_LENGTH 1000000

int kmp(const char* current_line, const char* next_line);
void execute_KMP();

#endif
