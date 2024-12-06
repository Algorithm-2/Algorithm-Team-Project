#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "input.h"
#include "create_data.h"
#include "compare.h"
#include "bruteforce.h"
#include "enhanced_bruteforce.h"
#include "kmp.h"
#include "kmp_lps_reuse.h"
#include "rabinkarp.h"

int main() {
	Info info = input();
	create_data(info.N, info.L, info.P);
	switch (info.toggle)
	{
	case 0:
		d_execute_Bruteforce(info.P); 
		break;
	case 1:
		execute_Bruteforce(info.P);
		break;
	case 2:
		execute_KMP(info.P);
		break;
	case 3:
		r_execute_KMP(info.P);
		break;
	case 4:
		execute_RabinKarp(info.P);
		break;
	}
	compare();
	return 0;
}
