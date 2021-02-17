#ifndef FUNCTIONFIVE_H
#define FUNCTIONFIVE_H

#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <ctime>
#include <fstream>
using namespace std;

struct UserTxt5 {
	int user_id;
	string user_password;
};

int ReadByUserTxt(UserTxt5 array[]) {
	ifstream readIt("./OriginTxt/user.txt");
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

void WriteToTxt(UserTxt5 array[], int size, string txtName) {
	ofstream writeIt;
	writeIt.open(txtName);
	if (writeIt.fail()) {
		cout << "该文件没有找到！" << endl;
		cout << "程序已经退出！" << endl;
		exit(1);
	}
	for (int i = 0; i < size; i++) {
		writeIt << array[i].user_id << "\t\t\t" << array[i].user_password << endl;
	}
	writeIt.close();
}

void InsertSort5(UserTxt5 array[], int size) {//从小到大排序
	for (int i = 1; i < size; i++) {
		UserTxt5 temp;
		temp = array[i];
		int j;
		for (j = i; j >= 0 && (temp.user_id > array[j - 1].user_id); j--) {
			array[j] = array[j - 1];
		}
		array[j] = temp;
	}
}

void ShellSort5(UserTxt5 array[], int size) {//从小到大排序
	int incrementArray[3] = { 7,3,1 };
	for (int i = 0; i < 3; i++) {
		int increment = incrementArray[i];
		for (int j = increment; j < size; j++) {
			UserTxt5 temp;
			temp = array[j];
			int k;
			for (k = j; k >= increment; k -= increment) {
				if (temp.user_id < array[k - increment].user_id) {
					array[k] = array[k - increment];
				}
				else {
					break;
				}
			}
			array[k] = temp;
		}
	}
}

void BubbleSort5(UserTxt5 array[], int size) {//从小到大排序
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (array[j].user_id > array[j + 1].user_id) {
				UserTxt5 temp;
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
	}
}

bool CompForQuickSort5(UserTxt5 x, UserTxt5 y) {
	return x.user_id < y.user_id;
}

void QuickSort5(UserTxt5 array[], int size) {//从小到大排序
	sort(array, array + size, CompForQuickSort5);
}

void SelectionSort5(UserTxt5 array[], int size) {//从小到大排序
	for (int i = 0; i < size - 1; i++) {
		int maxNum = i;
		for (int j = i + 1; j < size; j++) {
			if (array[j].user_id < array[maxNum].user_id) {
				maxNum = j;
			}
		}
		UserTxt5 temp;
		temp = array[i];
		array[i] = array[maxNum];
		array[maxNum] = temp;
	}
}

//堆排序开始
void DownwardAdjustment5(UserTxt5 array[], int i, int size) {//最大堆的调整
	UserTxt5 temp;
	temp = array[i];
	int child;
	for (int j = i * 2 + 1; j <= size; j = child * 2 + 1) {
		child = j;
		if (child != size && (array[child].user_id < array[child + 1].user_id)) {
			child++;
		}

		if (temp.user_id < array[child].user_id) {
			array[i] = array[child];
			i = child;
		}
		else {
			break;
		}
	}
	array[i] = temp;
}

void HeapSort5(UserTxt5 array[], int size) {//从小到大排序
	for (int i = (size - 1) / 2; i >= 0; i--) {
		DownwardAdjustment5(array, i, size - 1);
	}

	for (int i = size - 1; i >= 1; i--) {
		UserTxt5 temp;
		temp = array[0];
		array[0] = array[i];
		array[i] = temp;
		DownwardAdjustment5(array, 0, i - 1);
	}
}
//堆排序结束

//归并排序开始
void Part5(UserTxt5 temp[], UserTxt5 array[], int low, int high);
void Merge5(UserTxt5 temp[], UserTxt5 array[], int low, int middle, int high);

void Part5(UserTxt5 temp[], UserTxt5 array[], int low, int high) {
	if (low < high) {
		int middle = (low + high) / 2;
		Part5(temp, array, low, middle);
		Part5(temp, array, middle + 1, high);
		Merge5(temp, array, low, middle, high);
	}
}

void Merge5(UserTxt5 temp[], UserTxt5 array[], int low, int middle, int high) {
	int left = low;
	int right = middle + 1;
	int count = 0;
	while (left <= middle && right <= high) {
		if (array[left].user_id <= array[right].user_id) temp[count++] = array[left++];
		else if (array[left].user_id > array[right].user_id) temp[count++] = array[right++];
	}

	while (left <= middle) temp[count++] = array[left++];
	while (right <= high) temp[count++] = array[right++];

	for (int i = 0, k = low; i < count; i++) {
		array[k++] = temp[i];
	}
}

void MergeSort5(UserTxt5 array[], int size) {//从小到大排序
	UserTxt5* temp = new UserTxt5[2000000];
	if (temp != NULL) {
		Part5(temp, array, 0, size - 1);
		delete[] temp;
	}
	else {
		cout << "在 MergeSort 中内存分配失败！" << endl;
	}
}
//归并排序结束

void RadixSort5(UserTxt5 array[], int size) {
	int maxNum = array[0].user_id;
	for (int i = 1; i < size; i++) {
		if (array[i].user_id > maxNum) {
			maxNum = array[i].user_id;
		}
	}

	int count1 = 1;
	UserTxt5* temp = new UserTxt5[size];
	if (temp == NULL) {
		cout << "在 RadixSort 中，不给分配temp临时数组空间！" << endl;
		cout << "程序已停止！" << endl;
		exit(1);
	}

	while (maxNum / count1 > 0) {
		int backet[10] = { 0 };

		for (int i = 0; i < size; i++) {
			backet[array[i].user_id / count1 % 10]++;
		}

		for (int i = 1; i < 10; i++) {
			backet[i] += backet[i - 1];
		}

		for (int i = size - 1; i >= 0; i--) {
			temp[backet[array[i].user_id / count1 % 10] - 1].user_id = array[i].user_id;
			temp[--backet[array[i].user_id / count1 % 10]].user_password = array[i].user_password;
		}

		for (int i = 0; i < size - 1; i++) {
			array[i].user_id = temp[i].user_id;
			array[i].user_password = temp[i].user_password;
		}

		count1 *= 10;
	}

	for (int i = 0, k = size - 1; i < size; i++) {
		array[i].user_id = temp[k - 1].user_id;
		array[i].user_password = temp[k - 1].user_password;
	}

	delete temp;
}


//每个函数的测试
void TestCaseForInsertSort5() {
	UserTxt5* array = new UserTxt5[1500000];
	int size = ReadByUserTxt(array);

	clock_t start = clock();
	InsertSort5(array, size);
	clock_t end = clock();

	UserTxt5* tempArray = new UserTxt5[1500000];

	for (int i = 0; i < size; i++) {
		tempArray[size - i - 1] = array[i];
	}


	WriteToTxt(tempArray, size, "./FunctionFiveTxt/InsertSort.txt");

	double usetime = (double)(end - start) / CLOCKS_PER_SEC;

	cout << endl;
	cout << "The function five Insert Sort need time is : " << usetime << "s" << endl;
	cout << "Insert Sort Success For Function Five" << endl;
	cout << endl;

	delete[] array;
}

void TestCaseForShellSort5() {
	UserTxt5* array = new UserTxt5[1500000];
	int size = ReadByUserTxt(array);

	clock_t start = clock();
	ShellSort5(array, size);
	clock_t end = clock();

	WriteToTxt(array, size, "./FunctionFiveTxt/ShellSort.txt");

	double usetime = (double)(end - start) / CLOCKS_PER_SEC;

	cout << endl;
	cout << "The function five Shell Sort need time is : " << usetime << "s" << endl;
	cout << "Shell Sort Success For Function Five" << endl;
	cout << endl;

	delete[] array;
}

void TestCaseForBubbleSort5() {
	UserTxt5* array = new UserTxt5[1500000];
	int size = ReadByUserTxt(array);

	clock_t start = clock();
	BubbleSort5(array, size);
	clock_t end = clock();

	WriteToTxt(array, size, "./FunctionFiveTxt/BubbleSort.txt");

	double usetime = (double)(end - start) / CLOCKS_PER_SEC;

	cout << endl;
	cout << "The function five Bubble Sort need time is : " << usetime << "s" << endl;
	cout << "Bubble Sort Success For Function Five" << endl;
	cout << endl;

	delete[] array;
}

void TestCaseForQuickSort5() {
	UserTxt5* array = new UserTxt5[1500000];
	int size = ReadByUserTxt(array);

	clock_t start = clock();
	QuickSort5(array, size);
	clock_t end = clock();

	WriteToTxt(array, size, "./FunctionFiveTxt/QuickSort.txt");

	double usetime = (double)(end - start) / CLOCKS_PER_SEC;

	cout << endl;
	cout << "The function five Quick Sort need time is : " << usetime << "s" << endl;
	cout << "Quick Sort Success For Function Five" << endl;
	cout << endl;

	delete[] array;
}

void TestCaseForSelectionSort5() {
	UserTxt5* array = new UserTxt5[1500000];
	int size = ReadByUserTxt(array);

	clock_t start = clock();
	SelectionSort5(array, size);
	clock_t end = clock();

	WriteToTxt(array, size, "./FunctionFiveTxt/SelectionSort.txt");

	double usetime = (double)(end - start) / CLOCKS_PER_SEC;

	cout << endl;
	cout << "The function five Selection Sort need time is : " << usetime << "s" << endl;
	cout << "Selection Sort Success For Function Five" << endl;
	cout << endl;

	delete[] array;
}

void TestCaseForHeapSort5() {
	UserTxt5* array = new UserTxt5[1500000];
	int size = ReadByUserTxt(array);

	clock_t start = clock();
	HeapSort5(array, size);
	clock_t end = clock();

	WriteToTxt(array, size, "./FunctionFiveTxt/HeapSort.txt");

	double usetime = (double)(end - start) / CLOCKS_PER_SEC;

	cout << endl;
	cout << "The function five Heap Sort need time is : " << usetime << "s" << endl;
	cout << "Heap Sort Success For Function Five" << endl;
	cout << endl;

	delete[] array;
}

void TestCaseForMergeSort5() {
	UserTxt5* array = new UserTxt5[1500000];
	int size = ReadByUserTxt(array);

	clock_t start = clock();
	MergeSort5(array, size);
	clock_t end = clock();

	WriteToTxt(array, size, "./FunctionFiveTxt/MergeSort.txt");

	double usetime = (double)(end - start) / CLOCKS_PER_SEC;

	cout << endl;
	cout << "The function five Merge Sort need time is : " << usetime << "s" << endl;
	cout << "Merge Sort Success For Function Five" << endl;
	cout << endl;

	delete[] array;
}

void TestCaseForRadixSort5() {
	UserTxt5* array = new UserTxt5[1500000];
	int size = ReadByUserTxt(array);

	clock_t start = clock();
	RadixSort5(array, size);
	clock_t end = clock();

	WriteToTxt(array, size, "./FunctionFiveTxt/RadixSort.txt");

	double usetime = (double)(end - start) / CLOCKS_PER_SEC;

	cout << endl;
	cout << "The function five Radix Sort need time is : " << usetime << "s" << endl;
	cout << "Radix Sort Success For Function Five" << endl;
	cout << endl;

	delete[] array;
}


//总目录
void TestCaseForFunctionFive() {

	TestCaseForQuickSort5();//

	TestCaseForMergeSort5();//

	TestCaseForHeapSort5();//

	TestCaseForSelectionSort5();//

	TestCaseForShellSort5();//

	TestCaseForInsertSort5();//

	TestCaseForBubbleSort5();//

	//TestCaseForRadixSort5();//

}

#endif
