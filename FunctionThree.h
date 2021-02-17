#ifndef FUNCTIONTHREE_H
#define FUNCTIONTHREE_H

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

struct ListNode;
struct UserTxt;
typedef struct ListNode* List;

struct UserTxt {
	long long int user_id;
	string user_password;
};

struct ListNode {
	UserTxt data;
	ListNode* next;
};

List Init(List& l) {//用头插法
	l = new ListNode();
	if (l == NULL) return NULL;
	l->next = NULL;
	return l;
}

bool Insert(UserTxt x, List l) {
	List newL = new ListNode();
	if (newL == NULL) return false;
	newL->data = x;
	newL->next = l->next;
	l->next = newL;
	return true;
}

void ReadByUserTxt(List& l) {
	ifstream readIt("./OriginTxt/user.txt");
	if (readIt.fail()) {
		cout << "该文件没有找到！" << endl;
		cout << "程序已经退出！" << endl;
		exit(1);
	}
	UserTxt txt;
	while (!readIt.eof()) {
		readIt >> txt.user_id >> txt.user_password;
		Insert(txt, l);
		if (readIt.eof()) break;
		
	}
	readIt.close();
}

void GetRandomNumFor2000(long long int array[]) {
	srand(time(NULL));
	for (int i = 0; i < 2000; i++) {
		array[i] = (rand() * rand()) % 1230000;
	}
}

void GetRandomNumFor20(long long int array[]) {
	int i = 0;
	while (i <= 20) {
		long long int num = (rand() * rand()) % 12300000;
		if (num > 1230000 && num <= 12300000) {
			array[i] = num;
			i++;
		}
	}
}

List Find(UserTxt x, const List l) {
	List temp = new ListNode();
	if (temp == NULL) {
		cout << "在 FunctionThree 中的find()函数不给temp分配临时内存空间！" << endl;
		return NULL;
	}
	temp = l->next;
	while(temp!=NULL){
		if (temp->data.user_id == x.user_id) {
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}

List GetThisList(List l) {
	ReadByUserTxt(l);//需要看看是否读进去了!!!
	return l;
}

void WriteToTxtIn3(UserTxt* array, int size, string txtName) {
	ofstream writeIt;
	writeIt.open(txtName);
	if (writeIt.fail()) {
		cout << "该文件没有找到！" << endl;
		cout << "程序已经退出！" << endl;
		exit(1);
	}
	for (int i = 0; i < size; i++) {
		writeIt << array[i].user_id << " " << array[i].user_password << endl;
	}
	writeIt.close();
}

double TestCaseFor2000RandomNum() {
	long long int array[2003];
	UserTxt* arrayToRecord = new UserTxt[4006];
	
	GetRandomNumFor2000(array);
	
	UserTxt txt;
	List l;
	l = Init(l);
	l = GetThisList(l);

	List temp;
	int num = 0;

	clock_t start = clock();
	for (int i = 0; i < 2000; i++) {
		txt.user_id = array[i];
		
		arrayToRecord[num].user_id = array[i];
		arrayToRecord[num++].user_password = "I don't know.";
		
		temp = Find(txt, l);
		
		if (temp != NULL) {
			arrayToRecord[num] = temp->data;
			num++;
		}
		else {
			arrayToRecord[num].user_id = 111111;
			arrayToRecord[num++].user_password = "Not to find it.";
		}
	}
	clock_t end = clock();
	double useTime = (double)(end - start) / CLOCKS_PER_SEC;

	WriteToTxtIn3(arrayToRecord, 4000, "./FunctionThreeTxt/2000RandomNum.txt");

	delete[] arrayToRecord;

	return useTime;
}

double TestCaseFor20RandomNum() {
	long long int array[23];
	GetRandomNumFor20(array);
	UserTxt* arrayToRecord = new UserTxt[46];


	UserTxt txt;
	List l;
	l = Init(l);
	l = GetThisList(l);

	List temp;
	int num = 0;

	clock_t start = clock();
	for (int i = 0; i < 20; i++) {
		txt.user_id = array[i];
		
		arrayToRecord[num].user_id = array[i];
		arrayToRecord[num++].user_password = "I don't know!";

		temp = Find(txt, l);

		if (temp != NULL) {
			arrayToRecord[num] = temp->data;
			num++;
		}
		else {
			arrayToRecord[num].user_id = 111111;
			arrayToRecord[num++].user_password = "not to find it!";
		}
	}
	clock_t end = clock();
	double useTime = (double)(end - start) / CLOCKS_PER_SEC;

	WriteToTxtIn3(arrayToRecord, 40, "./FunctionThreeTxt/20RandomNum.txt");

	delete[] arrayToRecord;

	return useTime;

}

void TestCaseForFunctionThree() {
	double time1;
	double time2;
	double useTime;
	time1 = TestCaseFor2000RandomNum();
	time2 = TestCaseFor20RandomNum();
	useTime = time1 + time2;

	cout << endl;
	cout << "The function three need time is: " << useTime << "s" << endl;
	cout << endl;
}

#endif