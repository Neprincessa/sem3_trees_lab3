#include <stdio.h>
#include <string>
#include <vector>
//#include "sequence.h"
//#include "impl_seq.h"



bool checkData(char *ptr) {
	bool isd = true;
	int flag = 0;
	if (*ptr == '-') {
		flag = 1;
		*ptr = *(ptr++);
	}

	while (*ptr)
		if (!isdigit(*ptr++))
		{
			isd = false;
			break;
		}

	if (!isd)
		cout << "Fill in  integer, not a string or a double number" << endl;
	return isd;
}

//--------------------------Exceptions----------------------//
class NoElement : public exception {
public:
	void what() {
		std::cout << "ERROR" << std::endl;
	}
};

class Empty : public exception {
public:
	void what() {
		std::cout << "ERROR" << std::endl;
	}

};

class TroublesWithFibonacci : public exception {
public:
	void what() {
		std::cout << "ERROR" << std::endl;
	}
};
//--------------------------Exceptions----------------------//



//----------------------Binary Search----------------------//

template <typename TElement>
int BasicBinarySearch_Helper(Sequence<TElement>* seq, TElement element, int first, int last, double proportion) {

	if (first > last) {
		throw NoElement();
	}

	if (first == last && first == 0) {
		cout << "elemement index = " << first << endl;
	}
	else {
		int mid = first + (last - first) * proportion;
		TElement tmp = *seq->Get(mid);

		TElement mid_element = *seq->Get(mid);
		if (*seq->Get(first) == element) {
			return first;
		}
		if (mid_element == element) {

			if (mid == first + 1) {
				return mid;
			}
			else return BasicBinarySearch_Helper(seq, element, first, mid + 1, proportion);
		}
		else if (mid_element > element) {
			return BasicBinarySearch_Helper(seq, element, first, mid, proportion);
		}
		else return BasicBinarySearch_Helper(seq, element, mid + 1, last, proportion);
	}
	

}

template <typename TElement>
int BinarySearchBasic(Sequence<TElement>* seq, TElement element) {

	int length = seq->getLength();
	if (length == 0) {
		throw Empty();
	}
	int typeSearch = whatProportionIs();
	MergeSort(seq);
	
	if (typeSearch == 1)
		return BasicBinarySearch_Helper(seq, element, 0, length, double(1) / 2);

	if (typeSearch == 2) 
		return BinarySearchGoldenRatio(seq, element);

	if (typeSearch == 3) {
		cout << "The number of fibonacci number that you whant to get" << endl;
		int n;
		char s[256];
		char *p = s;
		cin >> s;
		while (!checkData(p))
			cin >> s;
		n = atoi(s);
		while (n < 0) {
			cout << "Fill in the positive number" << endl;
			cin >> s;
			n = atoi(s);
		}
		return BinarySearchFibonacciNumber(seq, element, n);
	}
	//return BasicBinarySearch_Helper(seq, element, 0, length, double(1) / 2);
}

template <typename TElement>
int BinarySearchGoldenRatio(Sequence<TElement>* seq, TElement element) {

	int length = seq->getLength();
	if (length == 0) {
		throw Empty();
	}
	MergeSort(seq);
	return BasicBinarySearch_Helper(seq, element, 0, length, double(38) / 100);
}

vector<long int> fib(int n) {
	int a = 1, b = 1, c, i;
	for (i = 2; i <= n; i++)
	{
		c = a + b;
		a = b;
		b = c;
	}
	return { a, b };
}

template <typename TElement>
int BinarySearchFibonacciNumber(Sequence<TElement>* seq, TElement element, int n) {

	if (n <= 1) {
		throw TroublesWithFibonacci();
	}
	int length = seq->getLength();
	if (length == 0) {
		throw Empty();
	}
	MergeSort(seq);
	if (n > seq->getLength())
		n = 2;
	vector<long int> res = fib(n);
	double proportion = double(res[0]) / res[1];
	return BasicBinarySearch_Helper(seq, element, 0, length, proportion);
}

//template <typename TElement>
//int BinarySearchOwnPair(Sequence<TElement>* seq, TElement element, vector<int> pair) {
//
//	int length = seq->getLength();
//	if (length == 0) {
//		throw EmptySequence();
//	}
//	MergeSort(seq);
//	return BasicBinarySearch_Helper(seq, element, 0, length, double(pair[0]) / (pair[0] + pair[1]));
//}
//

// try binary
template <typename TElement>
int Binary_Search(Sequence<TElement> *seq, TElement key) {
	bool flag = false;
	int l = 0; // левая граница
	int r = 9; // правая граница
	int mid;

	while ((l <= r) && (flag != true)) {
		mid = (l + r) / 2; // считываем срединный индекс отрезка [l,r]

		if (seq->Get(mid) == key)
			flag = true; //проверяем ключ со серединным элементом
		if (seq->Get(mid) > key) 
			r = mid - 1; // проверяем, какую часть нужно отбросить
		else 
			l = mid + 1;
	}

	if (flag) 
		cout << "Index of the element " << key << "  in arr is: " << mid << endl;
	else {
		cout << "Sorry. There is no such element :(";
		key = -88;
		//add in main if you need print
	}
	return key;
}


int whatProportionIs() {
	int result;
	cout << "If you whant to use proportions by base way, press 1" << endl;
	cout << "If you whant to use proportions by golden ratio, press 2" << endl;
	cout << "If you whant to use proportions by fibonacci raw, press 3" << endl;

	char s[256];
	char *p = s;
	cin >> s;
	while (!checkData(p))
		cin >> s;
	result = atoi(s);
	while (result < 1 || result > 3) {
		cout << "Fill in the number 1,2 or 3" << endl;
		cin >> s;
		while (!checkData(p))
			cin >> s;
		result = atoi(s);
	}
	return result;
}
