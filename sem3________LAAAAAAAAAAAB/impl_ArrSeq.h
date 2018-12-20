#ifndef _ARR__S__
#define _ARR__S__

using namespace std;
#include <malloc.h>
#include "student.h"
//----------------------------------------------------------ArraySequence-------------------------------------------//
int whatFunc();

template <typename TElement>
int ArraySequence<TElement>::getLength() {
	return currentAmount;
}

template <typename TElement>
void ArraySequence<TElement>::changeCondition(int condition) {
	isEmpty = condition;
}

template <typename TElement>
void ArraySequence<TElement>::Append(TElement item) {
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

		
	}
	changeCondition(0);
}
template <typename TElement>
int ArraySequence<TElement>::getIsEmpty() {
	return isEmpty;
}

template <typename TElement>
ArraySequence<TElement> ArraySequence<TElement>::GetSubSequence(int startIndex, int endIndex) {

	ArraySequence<TElement> result/*(endIndex - startIndex+1)*/;
	result.currentAmount = /*endIndex - startIndex + 1*/0;
	int j = startIndex;
	for (int i = 0; i < endIndex - startIndex + 1; i++) {
		result.Append(currentArr[j]/*, i*/);
		j++;
	}
	result.currentAmount = endIndex - startIndex + 1;
	return result;
}

template <typename TElement>
void ArraySequence<TElement>::Display() {
	if (getIsEmpty() == 0) {
		cout << "Current array sequence:" << endl;
		for (int i = 0; i < getLength(); i++) {
			cout << i + 1 << ") ";
			cout << currentArr[i];
			cout << "\n";
		}
	}
	else
		cout << "It is an empty sequence" << endl;
}

//void ArraySequence<int>::Display() {
//	if (getIsEmpty() == 0) {
//		cout << "Current array sequence:" << endl;
//		for (int i = 0; i < getLength(); i++) {
//			cout << i + 1 << ") ";
//			cout << currentArr[i];
//			cout << "\n";
//		}
//	}
//	else
//		cout << "It is an empty sequence" << endl;
//}
//
//void ArraySequence<double>::Display() {
//	if (getIsEmpty() == 0) {
//		cout << "Current array sequence:" << endl;
//		for (int i = 0; i < getLength(); i++) {
//			cout << i + 1 << ") ";
//			cout << currentArr[i];
//			cout << "\n";
//		}
//	}
//	else
//		cout << "It is an empty sequence" << endl;
//}
//
//void ArraySequence<Student>::Display() {
//	if (getIsEmpty() == 0) {
//		cout << "Current array sequence:" << endl;
//		for (int i = 0; i < getLength(); i++) {
//			cout << i + 1 << ") ";
//			/*cout << currentArr[i];*/
//			cout << currentArr[i].get_name() << " " << currentArr[i].get_age()<<endl;
//			cout << "\n";
//		}
//	}
//	else
//		cout << "It is an empty sequence" << endl;
//}

template <typename TElement>
TElement* ArraySequence<TElement>::GetFirst() {
	//cout << "\n";
	if (getIsEmpty() != 1) {
		/*cout << "The first element is: ";
		cout << currentArr[0];
		cout << "\n";*/
		return currentArr;
	}
	else {
		cout << "You can't get the element from the empty sequence :(" << endl;
		cout << "\n";
		return NULL;
	}
}

template <typename TElement>
TElement* ArraySequence<TElement>::GetLast() {
	//cout << "\n";
	if (getIsEmpty() != 1) {
		/*cout << "The last element is: ";
		cout << currentArr[getLength() - 1];
		cout << "\n";*/
		return currentArr+ getLength() - 1;
	}
	else {
		cout << "You can't get element from the empty sequence" << endl;
		cout << "\n";
		return /*-1*/NULL;
	}
}

template <class TElement>
TElement* ArraySequence<TElement>::Get(int index) {
	//cout << "\n";
	if (getIsEmpty() != 1) {
		/*cout << "The current element is: ";
		cout << currentArr[index - 1] << endl;*/
		return currentArr + index/* - 1*/;
	}
	else {
		cout << "You can't get element from the empty sequence" << endl;
		return /*-1*/NULL;
	}

}

template <typename TElement>
void ArraySequence<TElement>::Prepend(TElement item) {

	if (getLength() == 0) {
		realloc(currentArr, 2);
		currentArr[0] = item;
		currentAmount++;
	}
	else {
		TElement *newArr = new TElement[getLength() + 1];
		for (int i = 1; i < getLength() + 1; i++)
			newArr[i] = currentArr[i - 1];
		newArr[0] = item;
		currentAmount++;

		for (int i = 0; i < getLength(); i++)
			currentArr[i] = newArr[i];
	}
	changeCondition(0);
}

template <typename TElement>
void ArraySequence<TElement>::InsertAt(int index, TElement item) {
	this->currentAmount++;
	TElement *newArray = new TElement[this->currentAmount];
	for (int i = 0; i < index; i++) {
		newArray[i] = currentArr[i];
	}
	newArray[index] = item;
	for (int i = index + 1; i < this->currentAmount; i++) {
		newArray[i] = currentArr[i - 1];
	}
	currentArr = newArray;
}

template <typename TElement>
void ArraySequence<TElement>::Remove(TElement item) {

	int i = 0;
	int j = 0;
	bool flag = false;

	if (getIsEmpty() == 1)
		cout << "You can't remove element from empty sequence" << endl;
	else {
		TElement *newArr = new TElement[getLength() - 1];
		while (i<getLength()) {
			if (currentArr[i] != item) {
				newArr[j] = currentArr[i];
				j++;
			}
			if (currentArr[i] == item)
				flag = true;
			i++;
		}
		if (flag == false)
			cout << "The element to remove hasn't been found" << endl;
		else
		{
			currentAmount--;
			for (int i = 0; i < getLength(); i++)
				currentArr[i] = newArr[i];
		}
	}
}

template <typename TElement>
int ArraySequence<TElement>::chooseFunction() {
	int typeOfFunction = whatFunc();
	return typeOfFunction;
}

template <typename TElement>
void ArraySequence<TElement>::InsertSort() {

	TElement temp; // временная переменная для хранения значения элемента сортируемого массива
	int	item; // индекс предыдущего элемента
	for (int counter = 1; counter < currentAmount; counter++)
	{
		TElement a = currentArr[counter];
		temp = currentArr[counter]; // инициализируем временную переменную текущим значением элемента массива
		item = counter - 1; // запоминаем индекс предыдущего элемента массива
		while (item >= 0 && currentArr[item] > temp) // пока индекс не равен 0 и предыдущий элемент массива больше текущего
		{
			currentArr[item + 1] = currentArr[item]; // перестановка элементов массива
			currentArr[item] = temp;
			item--;
		}
	}
}

template <typename TElement>
TElement* ArraySequence<TElement>::getArr() {
	return currentArr;
}

template <typename TElement>
void ArraySequence<TElement>::RemoveByIndex(int index) {
	this->currentAmount--;
	TElement *newArray = new TElement[this->currentAmount];
	for (int j = 0; j < index; j++) {
		newArray[j] = currentArr[j];
	}
	for (int k = index; k < this->currentAmount; k++) {
		newArray[k] = currentArr[k + 1];
	}
	currentArr = newArray;
}


//template <typename TElement>
//int ArraySequence<TElement>::getLength() {
//	return currentAmount;
//}
//
//template <typename TElement>
//void ArraySequence<TElement>::changeCondition(int condition) {
//	isEmpty = condition;
//}
//
//template <typename TElement>
//void ArraySequence<TElement>::Append(TElement item) {
//	//if (getLength() == 0) {
//	////	realloc(currentArr, 2 * sizeof(TElement));
//	//	currentArr[0] = item;
//	//	currentAmount++;
//	//}
//	//else {
//
//	//	TElement *newArr = new TElement[getLength() + 1];
//	//	for (int i = 0; i < getLength(); i++)
//	//		newArr[i] = currentArr[i];
//	//	newArr[getLength()] = item;
//
//	//	TElement a = newArr[getLength()];
//	//	currentAmount++;
//
//	//	/*cout << "Check 1" << endl;
//	//	for (int i = 0; i < currentAmount-1; i++)
//	//	cout << i + 1 << ") " << currentArr[i] << endl;*/
//
//	//	//realloc(currentArr, (currentAmount + 2) * sizeof(TElement));
//
//	//	for (int i = 0; i < getLength(); i++)
//	//		currentArr[i] = newArr[i];
//
//	//	/*cout << "Check 2" << endl;
//	//	for (int i = 0; i < currentAmount; i++)
//	//	cout << i + 1 << ") " << currentArr[i] << endl;
//	//	*/
//	//}
//
//	if (this->currentAmount == 0) {
//		this->currentAmount++;
//		this->isEmpty = 0;
//		currentArr[0] = item;
//	}
//	else {
//		this->currentAmount++;
//		TElement *newArray = new TElement[this->currentAmount];
//		for (int i = 0; i < this->currentAmount - 1; i++) {
//			newArray[i] = currentArr[i];
//		}
//		newArray[this->currentAmount - 1] = item;
//		currentArr = newArray;
//	}
//	changeCondition(0);
//}
//
//template <typename TElement>
//int ArraySequence<TElement>::getIsEmpty() {
//	return isEmpty;
//}
//
//template <typename TElement>
//ArraySequence<TElement> ArraySequence<TElement>::GetSubSequence(int startIndex, int endIndex) {
//
//	ArraySequence<TElement> result/*(endIndex - startIndex+1)*/;
//	result.currentAmount = /*endIndex - startIndex + 1*/0;
//	int j = startIndex;
//	for (int i = 0; i < endIndex - startIndex + 1; i++) {
//		result.Append(currentArr[j]/*, i*/);
//		j++;
//	}
//	result.currentAmount = endIndex - startIndex + 1;
//	return result;
//}
//
//template <typename TElement>
//void ArraySequence<TElement>::Display() {
//	if (getIsEmpty() == 0) {
//		cout << "Current array sequence:" << endl;
//		for (int i = 0; i < getLength(); i++) {
//			cout << i + 1 << ") ";
//			cout << currentArr[i];
//			cout << "\n";
//		}
//	}
//	else
//		cout << "It is an empty sequence" << endl;
//}
//
//
////template <typename TElement>
////TElement ArraySequence<TElement>::GetFirst() {
////	//cout << "\n";
////	if (getIsEmpty() != 1) {
////		/*cout << "The first element is: ";
////		cout << currentArr[0];
////		cout << "\n";*/
////		return currentArr[0];
////	}
////	else {
////		cout << "You can't get the element from the empty sequence :(" << endl;
////		cout << "\n";
////		TElement  a = -1;
////		return a;
////	}
////}
//
//template <typename TElement>
//TElement ArraySequence<TElement>::GetLast() {
//	//cout << "\n";
//	if (getIsEmpty() != 1) {
//		/*cout << "The last element is: ";
//		cout << currentArr[getLength() - 1];
//		cout << "\n";*/
//		return currentArr[getLength() - 1];
//	}
//	else {
//		cout << "You can't get element from the empty sequence" << endl;
//		cout << "\n";
//		int a;
//		a =-1;
//		return /*-1*/a;
//	}
//}
//
//
//template <class TElement>
//TElement ArraySequence<TElement>::Get(int index) {
//	//cout << "\n";
//	if (getIsEmpty() != 1) {
//		/*cout << "The current element is: ";
//		cout << currentArr[index - 1] << endl;*/
//		return currentArr[index/* - 1*/];
//	}
//	else {
//		cout << "You can't get element from the empty sequence" << endl;
//		int a = -1;
//		return /*-1*/a;
//	}
//}
//
//template <typename TElement>
//void ArraySequence<TElement>::Prepend(TElement item) {
//
//	if (getLength() == 0) {
//		//realloc(currentArr, 2);
//		currentArr[0] = item;
//		currentAmount++;
//	}
//	else {
//		TElement *newArr = new TElement[getLength() + 1];
//		for (int i = 1; i < getLength() + 1; i++)
//			newArr[i] = currentArr[i - 1];
//		newArr[0] = item;
//		currentAmount++;
//
//		for (int i = 0; i < getLength(); i++)
//			currentArr[i] = newArr[i];
//	}
//	changeCondition(0);
//}
//
//template <typename TElement>
//void ArraySequence<TElement>::InsertAt(int index, TElement item) {
//	this->currentAmount++;
//	TElement *newArray = new TElement[this->currentAmount];
//	for (int i = 0; i < index; i++) {
//		newArray[i] = currentArr[i];
//	}
//	newArray[index] = item;
//	for (int i = index + 1; i < this->currentAmount; i++) {
//		newArray[i] = currentArr[i - 1];
//	}
//	currentArr = newArray;
//}
//
//template <typename TElement>
//void ArraySequence<TElement>::Remove(TElement item) {
//
//	int i = 0;
//	int j = 0;
//	bool flag = false;
//
//	if (getIsEmpty() == 1)
//		cout << "You can't remove element from empty sequence" << endl;
//	else {
//		TElement *newArr = new TElement[getLength() - 1];
//		while (i<getLength()) {
//			if (currentArr[i] != item) {
//				newArr[j] = currentArr[i];
//				j++;
//			}
//			if (currentArr[i] == item)
//				flag = true;
//			i++;
//		}
//		if (flag == false)
//			cout << "The element to remove hasn't been found" << endl;
//		else
//		{
//			currentAmount--;
//			for (int i = 0; i < getLength(); i++)
//				currentArr[i] = newArr[i];
//		}
//	}
//}
//
//template <typename TElement>
//int ArraySequence<TElement>::chooseFunction() {
//	int typeOfFunction = whatFunc();
//	return typeOfFunction;
//}
//
//template <typename TElement>
//void ArraySequence<TElement>::InsertSort() {
//
//	TElement temp; // временная переменная для хранения значения элемента сортируемого массива
//	int	item; // индекс предыдущего элемента
//	for (int counter = 1; counter < currentAmount; counter++)
//	{
//		TElement a = currentArr[counter];
//		temp = currentArr[counter]; // инициализируем временную переменную текущим значением элемента массива
//		item = counter - 1; // запоминаем индекс предыдущего элемента массива
//		while (item >= 0 && currentArr[item] > temp) // пока индекс не равен 0 и предыдущий элемент массива больше текущего
//		{
//			currentArr[item + 1] = currentArr[item]; // перестановка элементов массива
//			currentArr[item] = temp;
//			item--;
//		}
//	}
//}
//
//template <typename TElement>
//TElement* ArraySequence<TElement>::getArr() {
//	return currentArr;
//}
//
//template <typename TElement>
//void ArraySequence<TElement>::RemoveByIndex(int index) {
//	this->currentAmount--;
//	TElement *newArray = new TElement[this->currentAmount];
//	for (int j = 0; j < index; j++) {
//		newArray[j] = currentArr[j];
//	}
//	for (int k = index; k < this->currentAmount; k++) {
//		newArray[k] = currentArr[k + 1];
//	}
//	currentArr = newArray;
//}

#endif // !_ARR__S__

