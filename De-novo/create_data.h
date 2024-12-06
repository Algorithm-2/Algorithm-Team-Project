#ifndef CREATE_DNA_H
#define CREATE_DNA_H

#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <vector>

#define DNA_SEQUENCE "sequence.txt"
#define READS "reads.txt"


void create_data(int n, int l, int p); 
void create_dna(int n); 
void create_read(int l, int p); 

#endif 