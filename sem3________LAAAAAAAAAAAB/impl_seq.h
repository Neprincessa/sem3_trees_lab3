#ifndef _TEML__T__
#define _TEML__T__
using namespace std;

//----------------------------------------------------------Sequence-------------------------------------------------------//
template <typename TElement>
int Sequence<TElement>::getLength() {
	return Length;
}

template <typename TElement>
void Sequence<TElement>::Append(TElement a) {
	TElement b = a;
}

template <typename TElement>
void Sequence<TElement>::changeCondition(int condition) {
	isEmpty = condition;
}

template <typename TElement>
int Sequence<TElement>::getIsEmpty() {
	return isEmpty;
}

template <typename TElement>
TElement* Sequence<TElement>::GetFirst() {
	cout << "The first element is: ";
	return 0;
}

template <typename TElement>
TElement* Sequence<TElement>::GetLast() {
	cout << "The last element is: ";
	return 0;
}

template <typename TElement>
TElement* Sequence<TElement>::Get(int index) {
	cout << "The current element is: ";
	return 0;
}

template <typename TElement>
void Sequence<TElement>::Prepend(TElement item) {
	TElement b = item;
}

template <typename TElement>
void Sequence<TElement>::Remove(TElement item) {
	cout << "Delete element" << endl;
}

template <typename TElement>
void Sequence<TElement>::InsertAt(int index, TElement item) {
	cout << "Insert element" << endl;
}

template <typename TElement>
int Sequence<TElement>::chooseFunction() {
	return 0;
}


template <typename TElement>
void Sequence<TElement>::Display() {
	cout << "The sequence is:" << endl;
}

template <typename TElement>
void Sequence<TElement>::InsertSort() {
	cout << "This is insert sort: " << endl;
}

template <typename TElement>
void Sequence<TElement>::Shell(TElement* arr, int size, int *len) {
	cout << "This is shell sort" << endl;
}

template <typename TElement>
TElement* Sequence<TElement>::getArr() {
	TElement *arr = new TElement[18];
	return arr;
}

template <typename TElement>
void Sequence <TElement>::RemoveByIndex(int a) {
	cout << "AAAAAAAAAAAA" << endl;
}
#endif // !_TEML__T__
