#ifndef FUNCTIONSIX_H
#define FUNCTIONSIX_H

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <map>
#include <set>
#include <queue>
#include <ctime>
#include <cstdlib>
using namespace std;

struct UserSortTxt {
	int user_id;
	string user_password;
};

int ReadByUserTxt(UserSortTxt array[]) {
	ifstream readIt("./FunctionFiveTxt/HeapSort.txt");
	if (readIt.fail()) {
		cout << "该文件没有找到！" << endl;
		cout << "程序已经退出！" << endl;
		exit(1);
	}

	int num = 0;
	while (!readIt.eof()) {
		readIt >> array[num].user_id >> array[num].user_password;
		num++;
		if (readIt.eof()) break;
	}
	readIt.close();
	return num;
}

void GetRandomNumFor2000In6(long long int array[]) {
	srand(time(NULL));
	for (int i = 0; i < 2000; i++) {
		array[i] = (rand() * rand()) % 1230000;
	}
}

void GetRandomNumFor20In6(long long int array[]) {
	for (int i = 0; i < 20; i++) {
		long long int num = rand() * rand();
		if (num > 1230000) {
			array[i] = num;
		}
	}
}

bool Find(UserSortTxt x, UserSortTxt array[],int size) {
	int low = 0;
	int length = size;
	while (low <= length) {
		int middle = (low + length) / 2;
		if (x.user_id == array[middle].user_id) {
			return true;
		}
		else if (x.user_id < array[middle].user_id) {
			length = middle - 1;
		}
		else if (x.user_id > array[middle].user_id) {
			low = middle + 1;
		}
	}
	return false;
}

double TestCaseFor2000RandomNumIn6() {
	long long int array[2003];
	GetRandomNumFor2000In6(array);

	UserSortTxt* arrayTxt = new UserSortTxt[1500000];
	int size = ReadByUserTxt(arrayTxt);

	UserSortTxt txt;

	clock_t start = clock();
	for (int i = 0; i < 2000; i++) {
		txt.user_id = array[i];
		Find(txt, arrayTxt, size);
	}
	clock_t end = clock();
	double useTime = (double)(end - start) / CLOCKS_PER_SEC;

	return useTime;
}

double TestCaseFor20RandomNumIn6() {
	long long int array[23];
	GetRandomNumFor20In6(array);

	UserSortTxt* arrayTxt = new UserSortTxt[1500000];
	int size = ReadByUserTxt(arrayTxt);

	UserSortTxt txt;

	clock_t start = clock();
	for (int i = 0; i < 20; i++) {
		txt.user_id = array[i];
		Find(txt, arrayTxt, size);
	}
	clock_t end = clock();
	double useTime = (double)(end - start) / CLOCKS_PER_SEC;

	return useTime;

}

void TestCaseForFunctionSix() {
	double time1;
	double time2;
	double useTime;
	time1 = TestCaseFor2000RandomNumIn6();
	time2 = TestCaseFor20RandomNumIn6();
	useTime = time1 + time2;

	cout << endl;
	cout << "The function six need time is : " << useTime << "s" << endl;
	cout << endl;
}

#endif