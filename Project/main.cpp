#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "input.h"
#include "create_data.h"
#include "compare.h"
#include "bruteforce.h"
#include "enhanced_bruteforce.h"
#include "kmp.h"
#include "needlman.h"
#include "rabin.h"

int main() {
	Info info = input();
	create_data(info.N, info.L, info.P);

	execute_Bruteforce(info.P);
	// execute_KMP(info.P);
	// execute_Needlman();
	// execute_Rabin();
	compare();
	return 0;
}
