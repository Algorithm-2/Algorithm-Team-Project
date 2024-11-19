#ifndef RABINKARP_H
#define RABINKARP_H

#include <vector>
#include <string>

extern int d;
extern int pattern;
extern int q;

int charToValue(char c);
int gethash(const std::string& read);
double calculateMatchRate(const std::string& original, const std::string& reconstructed);
bool allVisited(std::vector<bool>& visited);
void execute_Rabin();

#endif
