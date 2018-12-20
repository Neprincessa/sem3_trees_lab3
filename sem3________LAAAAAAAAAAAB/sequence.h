#ifndef _TEMPL_IM__
#define _TEMPL_IM__

template <typename TElement>
struct Node
{
	TElement data;
	Node *Next, *Prev;
};

template <typename TElement>
class Sequence {
	int Length;
	int isEmpty;
public:
	Sequence() {
		Length = 0;
		isEmpty = 1;
	}
	virtual int getLength();//amount of elements
	virtual TElement* GetFirst();
	virtual TElement* GetLast();
	virtual void changeCondition(int);
	virtual TElement* Get(int index); //get element by index
	virtual int getIsEmpty(); //feature that it is empty
	virtual void Append(TElement item); // add element at the end of the existing seq
	virtual void Prepend(TElement item); //add element at the begining of the seq
	virtual void InsertAt(int index, TElement item); //insert element in i position
	virtual void Remove(TElement item);
	virtual void Display();
	virtual TElement* getArr();
	virtual int chooseFunction(); // what to do with func
	virtual void RemoveByIndex(int);

	//--------------------------Sorts------------------------------------//
	virtual void InsertSort();
	//	virtual void MergeSort(/*TElement *curArr, int lenD*/);
	virtual void Shell(TElement*, int/*, int*/, int*);
};


template <typename TElement>
class ArraySequence : public Sequence<TElement> {
	int currentAmount;
	int isEmpty;
	TElement *currentArr/* = new TElement[10000]*/; //choose the type - for user interfce
public:
	ArraySequence() {
		currentAmount = 0;
		isEmpty = 1;
	//	currentArr = (TElement*)malloc(/*currentAmount*/1000000 * sizeof(TElement));
		//if (sizeof(TElement) != sizeof(Student))
		/*	for (int i = 0; i < getLength(); i++)
				currentArr[i] = 0;*/
		currentArr = new TElement;
		//else
			//for (int i = 0; i < getLength(); i++) {
			//	Student a;/*
			//	currentArr[i]->name = "";
			//	currentArr[i]->age = 0;
			//	currentArr[i]->flag = 0;*/
			//	currentArr[i] = a;
			//}

	}
	void Append(TElement);
	int getLength();
	void changeCondition(int);
	int getIsEmpty(); //feature that it is empty
	void Display();
	TElement* GetFirst();
	TElement* GetLast();
	TElement* Get(int); //get element by index
	void Prepend(TElement);
	void InsertAt(int, TElement);
	void Remove(TElement);
	ArraySequence<TElement> GetSubSequence(int, int);
	int chooseFunction();
	TElement* getArr();
	void RemoveByIndex(int);
	//------------------------------Sorts---------------------//
	void InsertSort();
	//void MergeSort(/*TElement *curArr, int lenD*/);
	//void merge(int* merged, int lenD, int L[], int lenL, int R[], int lenR);
	//void Shell(TElement*, int, int*);

};


template <typename TElement>
class ListSequence : public Sequence<TElement> {
	int amount;
	int isEmpty;
	Node<TElement> *head;
	Node<TElement> *tail;
public:
	ListSequence() {
		amount = 0;
		isEmpty = 1;
		head = NULL;
		tail = NULL;
	}
	void Append(TElement);
	void Prepend(TElement);
	int getLength();
	int getIsEmpty();
	void changeCondition(int);
	TElement* GetFirst();
	TElement* GetLast();
	TElement* Get(int);
	void InsertAt(int, TElement);
	void Remove(TElement);
	ListSequence<TElement> GetSubSequence(int, int);
	int chooseFunction();
	TElement* getArr();
	void Display();
	void RemoveByIndex(int);
	//----------------------------Sorts-------------------//
	void InsertSort();
	//void MergeSort();
	//void Shell(TElement*, int, int*);

};
template <typename TElement>
Sequence<TElement>* MergeSort(Sequence<TElement>* seq);
#include "merge_sort.h"
#include "impl_seq.h"
#include "impl_ArrSeq.h"
#include "impl_ListSeq.h"
//#include "binary_search.h"
#endif // _TEMPL_IM__

/*
	if (this->currentAmount == 0) {
		this->currentAmount++;
		this->isEmpty = 0;
		currentArr[0] = item;
	}
	else {
		this->currentAmount++;
		TElement *newArray = new TElement[this->currentAmount];
		for (int i = 0; i < this->currentAmount - 1; i++) {
			newArray[i] = currentArr[i];
		}
		newArray[this->currentAmount - 1] = item;
		currentArr = newArray;
		}*/