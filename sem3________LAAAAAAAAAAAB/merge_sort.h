#ifndef __MERGE__T__
#define __MERGE__T__

#include <iostream>
//#include "templ.h"

template <typename TElement>
void MergeSequences(Sequence<TElement>* arr, int left, int middle, int right) {
	int i, j, k;
	int n1 = middle - left + 1;
	int n2 = right - middle;


	ListSequence<TElement>* LeftArr = new ListSequence<TElement>;
	ListSequence<TElement>* RightArr = new ListSequence<TElement>;

	for (i = 0; i < n1; i++) {
		LeftArr->InsertAt(i, *arr->Get(left + i));
	}
	for (j = 0; j < n2; j++) {
		RightArr->InsertAt(j, *arr->Get(middle + j + 1));
	}

	i = 0; // начальный индекс первой подпоследовательности
	j = 0; // начальный индекс второй подпоследовательности
	k = left; // начальный индекс итоговой подпоследовательности

	while (i < n1 && j < n2) {
		if (*LeftArr->Get(i) <= *RightArr->Get(j)) {
			arr->RemoveByIndex(k);
			arr->InsertAt(k, *LeftArr->Get(i));
			i++;
		}
		else {
			arr->RemoveByIndex(k);
			arr->InsertAt(k, *RightArr->Get(j));
			j++;
		}
		k++;
	}
	while (i < n1) {
		arr->RemoveByIndex(k);
		arr->InsertAt(k, *LeftArr->Get(i));
		i++;
		k++;
	}
	while (j < n2) {
		arr->RemoveByIndex(k);
		arr->InsertAt(k, *RightArr->Get(j));
		j++;
		k++;
	}
}


template <typename TElement>
void MergeSort_Helper(Sequence<TElement>* seq, int left, int right) {
	if (left < right) {
		int middle = left + (right - left) / 2;
		MergeSort_Helper(seq, left, middle);
		MergeSort_Helper(seq, middle + 1, right);
		MergeSequences(seq, left, middle, right);
	}
}

template <typename TElement>
Sequence<TElement>* MergeSort(Sequence<TElement>* seq) {
	MergeSort_Helper(seq, 0, seq->getLength() - 1);
	return seq;
}


#endif // !__MERGE__T__
