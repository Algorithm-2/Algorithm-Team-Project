#ifndef DNA_GENERATOR_H
#define DNA_GENERATOR_H

#include <string>

// 파일 이름 정의
#define DNA_SEQUENCE "sequence.txt"
#define READS "reads.txt"

// DNA 염기 상수 정의
extern char dna[4];

// 함수 선언
void create_dna(const int N);       // DNA 서열 생성
void create_read(const int L, const int P); // DNA로부터 읽기 조각 생성
void create_seqeunce(const int N, const int L, const int P); // DNA 생성 및 읽기 조각 생성 래퍼 함수

#endif
