#ifndef FUNCTIONFOUR_H
#define FUNCTIONFOUR_H

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

struct ElementType1;
struct TreeNode1;
typedef struct TreeNode1* BST1;

struct ElementType1 {
	int use_id;
	string use_password;
};

struct TreeNode1 {
	ElementType1 use_data;
	int count;
	TreeNode1* left;
	TreeNode1* right;
};

BST1 Insert(ElementType1 x, BST1 b) {
	if (b == NULL) {
		b = new TreeNode1();
		b->count = 0;
		b->left = b->right = NULL;
		b->use_data = x;
	}
	else if (x.use_id == b->use_data.use_id) b->count++;
	else if (x.use_id < b->use_data.use_id) b->left = Insert(x, b->left);
	else if (x.use_id > b->use_data.use_id) b->right = Insert(x, b->right);
	return b;
}

BST1 ReadByUserTxt(BST1 b) {
	ifstream readIt("./OriginTxt/user.txt");
	if (readIt.fail()) {
		cout << "该文件没有找到！" << endl;
		cout << "程序已经退出！" << endl;
		exit(1);
	}
	ElementType1 txt;
	while (!readIt.eof()) {
		readIt >> txt.use_id >> txt.use_password;
		b = Insert(txt, b);
		if (readIt.eof()) break;
	}
	readIt.close();
	return b;
}

void GetRandomNum1For2000(long long int array[]) {
	srand(time(NULL));
	for (int i = 0; i < 2000; i++) {
		array[i] = (rand() * rand()) % 1230000;
	}
}

void GetRandomNum1For20(long long int array[]) {
	int i = 0;
	while (i <= 20) {
		long long int num = (rand() * rand()) % 12300000;
		if (num > 1230000 && num <= 12300000) {
			array[i] = num;
			i++;
		}
	}
}

BST1 Find(ElementType1 x, BST1 t) {
	if (t == NULL) {
		return NULL;
	}
	if (x.use_id == t->use_data.use_id) { 
		return t;
	}
	else if (x.use_id < t->use_data.use_id) return Find(x, t->left);
	else if (x.use_id > t->use_data.use_id) return Find(x, t->right);
}

void WriteToTxtIn4(ElementType1* array, int size, string txtName) {
	ofstream writeIt;
	writeIt.open(txtName);
	if (writeIt.fail()) {
		cout << "该文件没有找到！" << endl;
		cout << "程序已经退出！" << endl;
		exit(1);
	}
	for (int i = 0; i < size; i++) {
		writeIt << array[i].use_id << " " << array[i].use_password << endl;
	}
	writeIt.close();
}

double TestCaseFor2000RandomNum1() {
	long long int array[2003];
	ElementType1* arrayToRecord = new ElementType1[4006];

	GetRandomNum1For2000(array);
	
	ElementType1 txt;
	BST1 b;
	b = new TreeNode1();
	b = NULL;
	b = ReadByUserTxt(b);

	TreeNode1* temp;
	int num = 0;

	clock_t start = clock();
	for (int i = 0; i < 2000; i++) {
		txt.use_id = array[i];

		arrayToRecord[num].use_id = array[i];
		arrayToRecord[num++].use_password = "I don't know.";

		temp = Find(txt, b);

		if (temp != NULL) {
			arrayToRecord[num] = temp->use_data;
			num++;
		}
		else {
			arrayToRecord[num].use_id = 111111;
			arrayToRecord[num++].use_password = "Not to find it.";
		}
	}
	clock_t end = clock();
	double useTime = (double)(end - start) / CLOCKS_PER_SEC;

	WriteToTxtIn4(arrayToRecord, 4000, "./FunctionFourTxt/2000RandomNum.txt");

	delete[] arrayToRecord;

	return useTime;
}

double TestCaseFor20RandomNum1() {
	long long int array[23];
	ElementType1* arrayToRecord = new ElementType1[46];

	GetRandomNum1For20(array);

	ElementType1 txt;
	BST1 b;
	b = new TreeNode1();
	b = NULL;
	b = ReadByUserTxt(b);

	TreeNode1* temp;
	int num = 0;

	clock_t start = clock();
	for (int i = 0; i < 20; i++) {
		txt.use_id = array[i];

		arrayToRecord[num].use_id = array[i];
		arrayToRecord[num++].use_password = "I don't know.";

		temp = Find(txt, b);

		if (temp != NULL) {
			arrayToRecord[num] = temp->use_data;
			num++;
		}
		else {
			arrayToRecord[num].use_id = 111111;
			arrayToRecord[num++].use_password = "Not to find it.";
		}
	}
	clock_t end = clock();
	double useTime = (double)(end - start) / CLOCKS_PER_SEC;

	WriteToTxtIn4(arrayToRecord, 20, "./FunctionFourTxt/20RandomNum.txt");

	delete[] arrayToRecord;

	return useTime;
}

//void InOrder(BST1 t) {//测试这棵树
//	if (t) {
//		InOrder(t->left);
//		cout << t->use_data.use_id << " " << t->use_data.use_password << endl;
//		InOrder(t->right);
//	}
//}

void TestCaseForFunctionFour() {
	double time1;
	double time2;
	double useTime;
	time1 = TestCaseFor2000RandomNum1();
	time2 = TestCaseFor20RandomNum1();
	useTime = time1 + time2;

	cout << endl;
	cout << "The function four need time is: " << useTime << "s" << endl;
	cout << endl;

}

#endif