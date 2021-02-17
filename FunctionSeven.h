#ifndef FUNCTIONSEVEN_H
#define FUNCTIONSEVEN_H

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

struct Node;
struct SevenTxt;
typedef struct Node* position;
struct HashTable;
typedef struct HashTable* HashT;
struct ElementTypes;

struct ElementTypes {
	string user_password;
	int count;
};

struct Node {
	ElementTypes key;
	position next;
};

struct HashTable {
	int tableSize;
	position* array;
};

int Hash(ElementTypes x, HashT h) {
	int sum = 0;
	int size = x.user_password.length();
	for (int i = 0; i < size; i++) {
		sum += int(x.user_password[i]);
	}
	return sum % h->tableSize;
}

HashT Init(int size, HashT& h) {
	h = new HashTable();
	if (h == NULL) return NULL;
	h->tableSize = size;
	h->array = new position[size];
	if (h->array == NULL) {
		delete h;
		return NULL;
	}
	for (int i = 0; i < h->tableSize; i++) {
		h->array[i] = new Node();
		if (h->array[i] == NULL) {
			for (int j = 0; j < i; j++)
				delete h->array[j];
			delete h->array;
			delete h;
			return NULL;
		}
		h->array[i]->next = NULL;
	}
	return h;
}

position FindInHashTable(ElementTypes x, HashT h) {
	position p = h->array[Hash(x, h)];
	p = p->next;
	while (p != NULL && p->key.user_password != x.user_password) p = p->next;
	return p;
}

bool Insert(ElementTypes x, HashT h) {
	position p = FindInHashTable(x, h);
	if (p == NULL) {
		position newNode = new Node();
		if (newNode == NULL) return false;
		newNode->key = x;
		newNode->next = h->array[Hash(x, h)]->next;
		h->array[Hash(x, h)]->next = newNode;
		return true;
	}
	return false;
}

void ReadByPasswordTxtIn7(HashT h) {
	ifstream readIt("./FunctionTwoTxt/HeapSort.txt");
	if (readIt.fail()) {
		cout << "该文件没有找到！" << endl;
		cout << "程序已经退出！" << endl;
		exit(1);
	}

	ElementTypes a;

	while (!readIt.eof()) {
		readIt >> a.user_password >> a.count;
		Insert(a, h);
		if (readIt.eof()) break;
	}
	readIt.close();
}

ElementTypes* GetTruePassword() {
	ifstream readIt("./FunctionTwoTxt/HeapSort.txt");
	if (readIt.fail()) {
		cout << "该文件没有找到！" << endl;
		cout << "程序已经退出！" << endl;
		exit(1);
	}

	ElementTypes* truePassword = new ElementTypes[23];
	int sum = 0;
	ElementTypes temp;


	while (!readIt.eof()&&sum<20) {
		readIt >> temp.user_password >> temp.count;
		truePassword[sum++] = temp;
		if (readIt.eof()) break;
	}

	return truePassword;
}

ElementTypes* GetFalsePassword() {
	ifstream readIt("./FunctionTwoTxt/HeapSort.txt");
	if (readIt.fail()) {
		cout << "该文件没有找到！" << endl;
		cout << "程序已经退出！" << endl;
		exit(1);
	}

	ElementTypes* falsePassword = new ElementTypes[23];
	int sum = 0;
	ElementTypes temp;

	while (!readIt.eof() && sum < 20) {
		readIt >> temp.user_password >> temp.count;
		temp.user_password += (temp.user_password + "adsdaf5as13d");
		falsePassword[sum].user_password = temp.user_password;
		falsePassword[sum++].count = 0;
		if (readIt.eof()) break;
	}

	return falsePassword;
}

void WriteToTxtIn7(ElementTypes* array, int size, string txtName) {
	ofstream writeIt;
	writeIt.open(txtName);
	if (writeIt.fail()) {
		cout << "该文件没有找到！" << endl;
		cout << "程序已经退出！" << endl;
		exit(1);
	}
	for (int i = 0; i < size; i++) {
		writeIt << array[i].user_password << "     " << array[i].count << endl;
	}
	writeIt.close();
}

double TestCaseForTruePassword(HashT h) {
	ElementTypes* truePassword;
	ElementTypes* arrayToRecordForTruePassword = new ElementTypes[40];

	truePassword = GetTruePassword();

	position temp;
	int num = 0;

	clock_t start = clock();
	for (int i = 0; i < 20; i++) {
		temp = FindInHashTable(truePassword[i], h);
		arrayToRecordForTruePassword[num++] = truePassword[i];
		if (temp != NULL) {
			arrayToRecordForTruePassword[num++] = temp->key;
		}
		else {
			arrayToRecordForTruePassword[num].user_password = truePassword[i].user_password;
			arrayToRecordForTruePassword[num++].count = 0;
		}
	}
	clock_t end = clock();
	double useTime = (double)(end - start) / CLOCKS_PER_SEC;

	WriteToTxtIn7(arrayToRecordForTruePassword, 40, "./FunctionSevenTxt/truePassword.txt");

	return useTime;
}

double TestCaseForFalsePassword(HashT h) {
	ElementTypes* falsePassword;
	ElementTypes* arrayToRecordForFalsePassword = new ElementTypes[40];

	falsePassword = GetFalsePassword(); 

	position temp;
	int num = 0;

	clock_t start = clock();
	for (int i = 0; i < 20; i++) {
		temp = FindInHashTable(falsePassword[i], h);
		arrayToRecordForFalsePassword[num++] = falsePassword[i];
		if (temp != NULL) {
			arrayToRecordForFalsePassword[num++] = temp->key;
		}
		else {
			arrayToRecordForFalsePassword[num].user_password = falsePassword[i].user_password;
			arrayToRecordForFalsePassword[num++].count = 0;
		}
	}
	clock_t end = clock();
	double useTime = (double)(end - start) / CLOCKS_PER_SEC;

	WriteToTxtIn7(arrayToRecordForFalsePassword, 40, "./FunctionSevenTxt/falsePassword.txt");

	return useTime;
}

void TestCaseForFunctionSeven() {
	HashT h;
	h = Init(100, h);
	ReadByPasswordTxtIn7(h);

	double time1;
	double time2;
	double sumTime;

	time1 = TestCaseForTruePassword(h);
	time2 = TestCaseForFalsePassword(h);

	sumTime = time1 + time2;

	cout << "The function seven need time is: " << sumTime << endl;
}

#endif