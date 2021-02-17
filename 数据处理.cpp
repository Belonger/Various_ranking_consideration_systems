#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <map>
#include <set>
#include <queue>
#include <ctime>
#include "FunctionOne.h"
#include "FunctionTwo.h"
#include "FunctionThree.h"
#include "FunctionFour.h"
#include "FunctionFive.h"
#include "FunctionSix.h"
#include "FunctionSeven.h"
using namespace std;

int main() {
	
	clock_t start = clock();

	TestCaseForFunctionOne();

	TestCaseForFunctionTwo();

	TestCaseForFunctionThree();

	TestCaseForFunctionFour();

	TestCaseForFunctionFive();

	TestCaseForFunctionSix();

	TestCaseForFunctionSeven();

	clock_t end = clock();

	double usetime = (double)(end - start) / CLOCKS_PER_SEC;

	cout << "All time : " << usetime << "s" << endl;
	cout << "Success!" << endl;
	cout << endl;

	return 0;
}