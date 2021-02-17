#ifndef FUNCTIONTWO_H
#define FUNCTIONTWO_H
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <ctime>
#include <fstream>
using namespace std;

struct PasswordTxt {
	string user_password;
	int count;
};

int ReadByPasswordTxt(PasswordTxt array[]) {
	ifstream readIt("./FunctionOneTxt/password.txt");
	if (readIt.fail()) {
		cout << "该文件没有找到！" << endl;
		cout << "程序已经退出！" << endl;
		exit(1);
	}

	int num = 0;
	while (!readIt.eof()) {
		readIt >> array[num].user_password >> array[num].count;
		num++;
		if (readIt.eof()) break;
	}
	readIt.close();
	return num;
}

void WriteToTxt(PasswordTxt array[] , int size,string txtName) {
	ofstream writeIt;
	writeIt.open(txtName);
	if (writeIt.fail()) {
		cout << "该文件没有找到！" << endl;
		cout << "程序已经退出！" << endl;
		exit(1);
	}
	for (int i = 0; i < size-1; i++) {
		writeIt << array[i].user_password << "\t\t\t" << array[i].count << endl;
	}
	writeIt.close();
}

void InsertSort(PasswordTxt array[] , int size) {	
	for (int i = 1; i < size; i++) {
		PasswordTxt temp;
		temp = array[i];
		int j;
		for (j = i; j >= 0 && (temp.count > array[j - 1].count); j--) {
			array[j] = array[j - 1];
		}
		array[j] = temp;
	}
}

void ShellSort(PasswordTxt array[] , int size) {
	int incrementArray[4] = { 7,5,3,1 };
	for (int i = 0; i < 4; i++) {
		int increment = incrementArray[i];
		for (int j = increment; j < size; j++) {
			PasswordTxt temp;
			temp = array[j];
			int k;
			for (k = j; k >= increment; k -= increment) {
				if (temp.count > array[k-increment].count) {
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

void BubbleSort(PasswordTxt array[], int size) {
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (array[j].count < array[j + 1].count) {
				PasswordTxt temp;
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
	}
}

bool CompForQuickSort(PasswordTxt x, PasswordTxt y) {
	return x.count > y.count;
}

void QuickSort(PasswordTxt array[], int size) {
	sort(array, array + size, CompForQuickSort);
}

void SelectionSort(PasswordTxt array[], int size) {
	for (int i = 0; i < size - 1; i++) {
		int maxNum = i;
		for (int j = i + 1; j < size; j++) {
			if (array[j].count > array[maxNum].count) {
				maxNum = j;
			}
		}
		PasswordTxt temp;
		temp = array[i];
		array[i] = array[maxNum];
		array[maxNum] = temp;
	}
}

//堆排序开始
void DownwardAdjustment(PasswordTxt array[], int i, int size) {
	PasswordTxt temp;
	temp = array[i];
	int child;
	for (int j = i * 2 + 1; j <= size; j = child * 2 + 1) {
		child = j;
		if (child != size && (array[child].count > array[child+1].count)) {
			child++;
		}

		if (temp.count > array[child].count) {
			array[i] = array[child];
			i = child;
		}
		else {
			break;
		}
	}
	array[i] = temp;
}

void HeapSort(PasswordTxt array[], int size) {
	for (int i = (size - 1) / 2; i >= 0; i--) {
		DownwardAdjustment(array, i, size-1);
	}

	for (int i = size-1; i >= 1; i--) {
		PasswordTxt temp;
		temp = array[0];
		array[0] = array[i];
		array[i] = temp;
		DownwardAdjustment(array, 0, i - 1);
	}
}
//堆排序结束

//归并排序开始
void Part(PasswordTxt temp[], PasswordTxt array[], int low, int high);
void Merge(PasswordTxt temp[], PasswordTxt array[], int low, int middle, int high);

void Part(PasswordTxt temp[], PasswordTxt array[], int low, int high) {
	if (low < high) {
		int middle = (low + high) / 2;
		Part(temp, array, low, middle);
		Part(temp, array, middle + 1, high);
		Merge(temp, array, low, middle, high);
	}
}

void Merge(PasswordTxt temp[], PasswordTxt array[], int low, int middle, int high) {
	int left = low;
	int right = middle + 1;
	int count = 0;
	while (left <= middle && right <= high) {
		if (array[left].count >= array[right].count) temp[count++] = array[left++];
		else if (array[left].count < array[right].count) temp[count++] = array[right++];
	}

	while (left <= middle) temp[count++] = array[left++];
	while (right <= high) temp[count++] = array[right++];

	for (int i = 0, k = low; i < count; i++) {
		array[k++] = temp[i];
	}
}

void MergeSort(PasswordTxt array[], int size) {
	PasswordTxt* temp = new PasswordTxt[1000000];
	if (temp != NULL) {
		Part(temp, array, 0, size - 1);
		delete[] temp;
	}
	else {
		cout << "在 MergeSort 中内存分配失败！" << endl;
	}
}
//归并排序结束

void RadixSort(PasswordTxt array[], int size) {
	PasswordTxt maxNum = array[0];
	for (int i = 1; i < size; i++) {
		if (array[i].count > maxNum.count) {
			maxNum = array[i];
		}
	}

	int count1 = 1;
	PasswordTxt* temp = new PasswordTxt[size+1];
	if (temp == NULL) {
		cout << "在 RadixSort 中，不给分配temp临时数组空间！" << endl;
		cout << "程序已停止！" << endl;
		exit(1);
	}

	while (maxNum.count / count1 > 0) {
		PasswordTxt backet[10];
		for (int i = 0; i < 10; i++) {
			backet[i].count = 0;
			backet[i].user_password = "000";
		}

		for (int i = 0; i < size; i++) {
			backet[array[i].count / count1 % 10].count++;
		}

		for (int i = 1; i < 10; i++) {
			backet[i].count += backet[i - 1].count;
		}

		for (int i = size - 1; i >= 0; i--) {
			temp[backet[array[i].count / count1 % 10].count - 1].user_password = array[i].user_password;
			temp[backet[array[i].count / count1 % 10].count - 1].count = array[i].count;
			--backet[array[i].count / count1 % 10].count;
		}

		for (int i = 0; i < size - 1; i++) {
			/*array[i].user_password = temp[i].user_password;
			array[i].count = temp[i].count;*/
			array[i] = temp[i];
		}

		count1 *= 10;
	}
	
	for (int i = 0, k = size - 1; i < size; i++) {
		/*array[i].count = temp[k-1].count;
		array[i].user_password = temp[k-1].user_password;*/
		array[i] = temp[k - 1];
	}
}

//每个函数的测试
void TestCaseForInsertSort() {
	PasswordTxt* array = new PasswordTxt[1000000];
	int size = ReadByPasswordTxt(array);

	clock_t start = clock();
	InsertSort(array, size);
	clock_t end = clock();
	
	WriteToTxt(array, size, "./FunctionTwoTxt/InsertSort.txt");

	double usetime = (double)(end - start) / CLOCKS_PER_SEC;

	cout << endl;
	cout << "The function two Insert Sort need time is : " << usetime << "s" << endl;
	cout << "Insert Sort Success For Function Two" << endl;
	cout << endl;

	delete[] array;
}

void TestCaseForShellSort() {
	PasswordTxt* array = new PasswordTxt[1000000];
	int size = ReadByPasswordTxt(array);

	clock_t start = clock();
	ShellSort(array, size);
	clock_t end = clock();

	WriteToTxt(array, size, "./FunctionTwoTxt/ShellSort.txt");

	double usetime = (double)(end - start) / CLOCKS_PER_SEC;

	cout << endl;
	cout << "The function two Shell Sort need time is : " << usetime << "s" << endl;
	cout << "Shell Sort Success For Function Two" << endl;
	cout << endl;

	delete[] array;
}

void TestCaseForBubbleSort() {
	PasswordTxt* array = new PasswordTxt[1000000];
	int size = ReadByPasswordTxt(array);

	clock_t start = clock();
	BubbleSort(array, size);
	clock_t end = clock();

	WriteToTxt(array, size, "./FunctionTwoTxt/BubbleSort.txt");

	double usetime = (double)(end - start) / CLOCKS_PER_SEC;

	cout << endl;
	cout << "The function two Bubble Sort need time is : " << usetime << "s" << endl;
	cout << "Bubble Sort Success For Function Two" << endl;
	cout << endl;

	delete[] array;
}

void TestCaseForQuickSort() {
	PasswordTxt* array = new PasswordTxt[1000000];
	int size = ReadByPasswordTxt(array);

	clock_t start = clock();
	QuickSort(array, size);
	clock_t end = clock();

	WriteToTxt(array, size, "./FunctionTwoTxt/QuickSort.txt");

	double usetime = (double)(end - start) / CLOCKS_PER_SEC;

	cout << endl;
	cout << "The function two Quick Sort need time is : " << usetime << "s" << endl;
	cout << "Quick Sort Success For Function Two" << endl;
	cout << endl;

	delete[] array;
}

void TestCaseForSelectionSort() {
	PasswordTxt* array = new PasswordTxt[1000000];
	int size = ReadByPasswordTxt(array);

	clock_t start = clock();
	SelectionSort(array, size);
	clock_t end = clock();

	WriteToTxt(array, size, "./FunctionTwoTxt/SelectionSort.txt");

	double usetime = (double)(end - start) / CLOCKS_PER_SEC;

	cout << endl;
	cout << "The function two Selection Sort need time is : " << usetime << "s" << endl;
	cout << "Selection Sort Success For Function Two" << endl;
	cout << endl;

	delete[] array;
}

void TestCaseForHeapSort() {
	PasswordTxt* array = new PasswordTxt[1000000];
	int size = ReadByPasswordTxt(array);

	clock_t start = clock();
	HeapSort(array, size);
	clock_t end = clock();

	WriteToTxt(array, size, "./FunctionTwoTxt/HeapSort.txt");

	double usetime = (double)(end - start) / CLOCKS_PER_SEC;

	cout << endl;
	cout << "The function two Heap Sort need time is : " << usetime << "s" << endl;
	cout << "Heap Sort Success For Function Two" << endl;
	cout << endl;

	delete[] array;
}

void TestCaseForMergeSort() {
	PasswordTxt* array = new PasswordTxt[1000000];
	int size = ReadByPasswordTxt(array);

	clock_t start = clock();
	MergeSort(array, size);
	clock_t end = clock();

	WriteToTxt(array, size, "./FunctionTwoTxt/MergeSort.txt");

	double usetime = (double)(end - start) / CLOCKS_PER_SEC;

	cout << endl;
	cout << "The function two Merge Sort need time is : " << usetime << "s" << endl;
	cout << "Merge Sort Success For Function Two" << endl;
	cout << endl;

	delete[] array;
}

void TestCaseForRadixSort() {
	PasswordTxt* array = new PasswordTxt[1000000];
	int size = ReadByPasswordTxt(array);

	clock_t start = clock();
	RadixSort(array, size);
	clock_t end = clock();

	WriteToTxt(array, size, "./FunctionTwoTxt/RadixSort.txt");

	double usetime = (double)(end - start) / CLOCKS_PER_SEC;

	cout << endl;
	cout << "The function two Radix Sort need time is : " << usetime << "s" << endl;
	cout << "Radix Sort Success For Function Two" << endl;
	cout << endl;

	delete[] array;
}

void PrintForOneToTwenty() {
	ifstream readIt("./FunctionTwoTxt/QuickSort.txt");
	if (readIt.fail()) {
		cout << "该文件没有找到！" << endl;
		cout << "程序已经退出！" << endl;
		exit(1);
	}

	PasswordTxt* temp = new PasswordTxt[25];
	int count = 0;

	cout << "前二十的密码和次数为：" << endl;
	while (!readIt.eof()) {
		readIt >> temp[count].user_password >> temp[count].count;
		cout << temp[count].user_password << " " << temp[count].count << endl;
		count++;
		if (readIt.eof() || count == 20) break;
	}
	readIt.close();
	
	cout << endl;
}

//总目录
void TestCaseForFunctionTwo() {

	TestCaseForShellSort();//24s
	
	TestCaseForQuickSort();//2.15s
	
	TestCaseForSelectionSort();//2.6s

	TestCaseForHeapSort();//0.62s

	TestCaseForMergeSort();//1.9s

	TestCaseForInsertSort();//173s

	TestCaseForBubbleSort();//1100s

	//TestCaseForRadixSort();

	PrintForOneToTwenty();
}

#endif