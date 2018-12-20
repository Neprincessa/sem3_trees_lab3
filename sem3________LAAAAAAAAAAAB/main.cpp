#include <iostream>
#include <cstdlib>
#include "sequence.h"
#include "merge_sort.h"
#include "binary_search.h"
#include "BTree.h"
#include <random>
#include <chrono>

using namespace std;

//=======================TestsImplication========================// 
bool Test_Insert() {
	BTree<int> myBtree(2, NULL);
	myBtree.insert(1);
	myBtree.insert(2);
	myBtree.insert(3);
	myBtree.insert(4);
	if ((myBtree.search(4)).index)
	{
		return true;
	}
	else {
		return false;
	}

}

bool Test_Remove() {
	BTree<int> myBtree(2, NULL);
	myBtree.insert(1);
	myBtree.insert(2);
	myBtree.insert(3);
	myBtree.remove(3);
	if (myBtree.getRootLength() == 2) {
		return true;
	}
	else {
		return false;
	}

}

bool Test_Binary() {
	ArraySequence<int> myArray;
	myArray.Append(1);
	myArray.Append(2);
	myArray.Append(3);
	if (BinarySearchBasic(&myArray, 2)) {
		return true;
	}
	else {
		return false;
	}
}
//=======================TestsImplication========================// 

//USE THIS FUNC! 

//----------------------------CheckData------------------------//
template <class NUMBER, class STREAM>
int get_flow(NUMBER &num, STREAM &flow) {
	flow >> num;
	while (!flow.good())
	{
		cout << "repeat: ";
		flow.clear();
		flow.ignore(numeric_limits <streamsize>::max(), '\n');
		flow >> num;
	}
	return num;
}
//----------------------------CheckData------------------------//


int main() {

	char s[256];
	char *p = s;
	string surnames[28] = { "afirst", "bfirst","cfirst", "dfirst", "efirst", "ffirst", "gfirst", "hfirst", "ifirst", "jfirst", "kfirst", "lfirst","mfirst", "nfirst", "ofirst","pfirst","qfirst","rfirst","sfirst","tfirst", "ufirst", "vfirst", "wfirst","xfirst", "zfirst" };
	//add what type of data user whants to work
	//int tmp;
	//cout << "Try beautiful func" << endl;
	//cin >> tmp;
	//cout << get_flow(tmp, cin);

	//бинарный поиск 
	/*ArraySequence<int> myArr;
	try
	{
		cout << "Binary search for arr: " << BinarySearchBasic(&myArr, 8102) + 1 << endl;
	}
	catch (NoElement a)
	{
		a.what();
	}
	catch (Empty a)
	{
		a.what();
	}*/
	
	/*myArr.Append(58);
	myArr.Prepend(877);
	cout<<myArr.Get(1);*/
	//for (int i = 0; i < 20; i++) {
	//	srand(i * 5631);
	//	std::random_device rd;
	//	std::mt19937_64 gen(rd());
	//	int tmpEl = rand() % 10000 + 1;
	//	myArr.Append(tmpEl);
	//}
	//cout << "Sorted sequence" << endl;
	//MergeSort(&myArr);
	//myArr.Display();
	//cout<<"Binary search for arr: "<<BinarySearchBasic(&myArr, 8102)+1<<endl;

	////--------Realization for list------------//
	//ListSequence<int> myList;
	//for (int i = 0; i < 20; i++) {
	//	srand(i * 7777777);
	//	std::random_device rd;
	//	std::mt19937_64 gen(rd());
	//	int tmpEl = rand() % 10000 + 1;
	//	myList.Append(tmpEl);
	//}

	//cout << "LIST" << endl;
	//MergeSort(&myList);
	//cout << "Binary search for list: " << BinarySearchBasic(&myList, 15)+1<<endl;
	//
	////-------------------Btree--------------------//
	//BTree<int> tree(2, NULL);
	//tree.insert(5);
	//tree.insert(88);
	//tree.insert(4);
	//tree.insert(6);
	//tree.insert(32);
	//tree.traverse();
	//cout << "\n";
	//cout<<"root length"<<tree.getRootLength()<<endl;
	//tree.remove(5);
	//tree.traverse();
	//cout << "\n";


	////--------Student--------//
	//cout << "fill in what category do you want to find" << endl;
	//int flag;
	///*cout << "1 - age; 2 - name" << endl;
	//cin >> s;
	//while (!checkData(p))
	//	cin >> s;
	//flag = atoi(s);
	//while (flag < 1 || flag > 2) {
	//	cout << "Fill in 1 or 2" << endl;
	//	cin >> s;
	//	while (!checkData(p))
	//		cin >> s;
	//	flag = atoi(p);
	//}*/
	////cin >> flag;
	//
	//ArraySequence <Student> *studentArr = new ArraySequence<Student>;

	//cout << "Fill in the amount of people" << endl;
	//int amount;
	////cin >> s;
	//cin >> amount; // add check

	//for (int i = 0; i < amount; i++) {
	//	Student myStudent;
	//	myStudent.name = "Elon Musk";
	//	myStudent.age = rand() % 20 + 15;
	//	studentArr->Append(myStudent);
	//}

	//cout << "STUDENT" << endl;	
	//srand(3);
	//Student myStudentToSearch;
	//myStudentToSearch =*studentArr->Get(rand() % amount);
	//cout<<"To search: "<< myStudentToSearch << endl;
	//MergeSort(studentArr);
	//studentArr->Display();

	//cout<<BinarySearchBasic(studentArr, myStudentToSearch)+1<<endl;


	//-------------------------------Tests---------------------------------//

	cout << "work with student" << endl;
	Student myStudentTest;
	myStudentTest.age = 65;
	myStudentTest.name = "feffd";
	myStudentTest.flag = 2;
	cout << myStudentTest;
	cout << "TESTS" << endl;
	if (Test_Insert())
		cout << "Insert in BTree works successfully  " << endl;
	else
		cout << "Insert in BTree doesn't work. Plak:(" << endl;

	if (Test_Binary())
		cout << "Binary search in BTree works successfully  " << endl;
	else
		cout << "Binary search in BTree doesn't work. Plak:(" << endl;

	if (Test_Remove())
		cout << "Remove in BTree works successfully  " << endl;
	else
		cout << "Remove in BTree doesn't work. Plak:(" << endl;
	//-------------------------------Tests---------------------------------//


	//-------------------------------Time---------------------------------//
	
	//-----------------BinarySearchStudent_ArrSequence-------------------//
	cout << "\n" << "ArraySequence" << endl;

	ArraySequence<Student>* studentArr = new ArraySequence<Student>;
	cout << "length ->> ";
	int length;
	length = get_flow(length, cin);
	while (length < 0) {
		cout << "Fill in positive number" << endl;
		length = get_flow(length, cin);
	}

	cout << "atribute (1-name,2-age)->> ";
	int flag;
	flag = get_flow(flag, cin);
	while (flag< 1 || flag > 2 ) {
		cout << "Fill in 1 or 2" << endl;
		flag = get_flow(flag, cin);
	}

	for (int i = 0; i < length; i++) {
		Student myStudent;
		myStudent.name = "Ivan Ivanov"+surnames[i % 28];
		srand(i * 5631);
		std::random_device rd;
		std::mt19937_64 gen(rd());
		myStudent.age = rand() % 10000 + 1;
		myStudent.flag = flag;
		studentArr->Append(myStudent);
	}

	Student myStudentToSearch;
	cout << "Student to search" << endl;
	srand(3);
	std::random_device rd;
	std::mt19937_64 gen(rd());
	myStudentToSearch = *studentArr->Get(rand() % length);
	cout << myStudentToSearch;
	MergeSort(studentArr);
	cout << "\n";
	cout << "Sequence" << endl;
	studentArr->Display();
	auto begin = chrono::high_resolution_clock::now();

	try
	{
		BinarySearchBasic(studentArr, myStudentToSearch);
	}
	catch (NoElement a)
	{
		a.what();
	}
	catch (Empty a)
	{
		a.what();
	}

	auto end = chrono::high_resolution_clock::now();
	cout << "binary search time: " << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() / 10 << " ns" << endl;
	//-----------------BinarySearchStudent_ArrSequence-------------------//


	//-----------------BinarySearchStudent_ListSequence-------------------//
	cout <<"\n"<< "ListSequence" << endl;

	ListSequence<Student>* studentList = new ListSequence<Student>;
	//cout << "length ->> ";
	/*int amount;
	cin >> amount;
	cout << "atribute (1-name,2-age)->> ";
	int secondFlag;
	cin >> secondFlag;*/

	for (int i = 0; i < length; i++) {
		Student myStudent;
		myStudent.name = "Ivan Ivanov" + surnames[i % 28];
		srand(i * 5631);
		std::random_device rd;
		std::mt19937_64 gen(rd());
		myStudent.age = rand() % 10000 + 1;
		myStudent.flag = flag;
		studentList->Append(myStudent);
	}

	Student StudentToSearch;
	cout << "Student to search" << endl;
	srand(3);
	StudentToSearch = *studentList->Get(rand() % length);
	cout << StudentToSearch;
	MergeSort(studentList);
	cout << "\n";
	cout << "Sequence" << endl;
	studentList->Display();
	begin = chrono::high_resolution_clock::now();

	try
	{
		BinarySearchBasic(studentList, StudentToSearch);
	}
	catch (NoElement a)
	{
		a.what();
	}
	catch (Empty a)
	{
		a.what();
	}
	end = chrono::high_resolution_clock::now();

	cout << "binary search time: " << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() / 10 << " ns" << endl;
	//-----------------BinarySearchStudent_ListSequence-------------------//

	//-----------------BinarySearchStudent_BTree-------------------//
	BTreeBuilder<Student> myBuilder(3);
	BTree<Student> myTree = myBuilder.build(studentArr, length, flag);
	cout << "BTree" << endl;
	myTree.traverse();
	cout << "\n";
	cout << "Student" << endl;
	cout << myStudentToSearch;
	cout << "\n";
	begin = chrono::high_resolution_clock::now();

	try
	{
		myTree.search(myStudentToSearch);
	}
	catch (NoElement a)
	{
		a.what();
	}

	end = chrono::high_resolution_clock::now();
	cout << "binary search time: " << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() / 10 << " ns" << endl;
	//-----------------BinarySearchStudent_BTree-------------------//

	//-------------------------------Time---------------------------------//

	

	system("pause");
	return 0;
}
