#ifndef FUNCTIONONE_H
#define FUNCTIONONE_H

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <map>
#include <set>
#include <queue>
#include <ctime>
using namespace std;

struct ElementType;
struct TreeNode;
typedef struct TreeNode* BST;

struct ElementType {
	int use_id;
	string use_password;
};

struct TreeNode {
	ElementType use_data;
	int count;
	TreeNode* left;
	TreeNode* right;
};

BST Insert(ElementType x, BST b) {
	if (b == NULL) {
		b = new TreeNode();
		b->count = 0;
		b->left = b->right = NULL;
		b->use_data = x;
	}
	else if (x.use_password == b->use_data.use_password) b->count++;
	else if (x.use_password < b->use_data.use_password) b->left = Insert(x, b->left);
	else if (x.use_password > b->use_data.use_password) b->right = Insert(x, b->right);
	return b;
}

BST ReadByUserTxt(BST b) {
	ifstream readIt("./OriginTxt/user.txt");
	if (readIt.fail()) {
		cout << "该文件没有找到！" << endl;
		cout << "程序已经退出！" << endl;
		exit(1);
	}
	ElementType txt;
	while (!readIt.eof()) {
		readIt >> txt.use_id >> txt.use_password;
		b = Insert(txt, b);
		if (readIt.eof()) break;
	}
	readIt.close();
	return b;
}

void WriteToPasswordTxt() {
	BST b;
	b = new TreeNode();
	b = NULL;
	b = ReadByUserTxt(b);

	ofstream writeIt;
	writeIt.open("./FunctionOneTxt/password.txt");
	if (writeIt.fail()) {
		cout << "该文件没有找到！" << endl;
		cout << "程序已经退出！" << endl;
		exit(1);
	}

	queue<BST> que;
	BST temp = new TreeNode();
	temp = b;

	que.push(temp);
	while (temp) {
		if (temp->left) que.push(temp->left);
		if (temp->right) que.push(temp->right);
		//写入password.txt中
		writeIt << temp->use_data.use_password << "\t\t\t" << temp->count << endl;
		que.pop();
		if (que.empty()) return;
		temp = que.front();
	}

	writeIt.close();
}

void TestCaseForFunctionOne() {
	clock_t start = clock();
	WriteToPasswordTxt();
	clock_t end = clock();
	double useTime = (double)(end - start) / CLOCKS_PER_SEC;

	cout << "The function one need time is: " << useTime << "s" << endl;
	cout << endl;
}

#endif