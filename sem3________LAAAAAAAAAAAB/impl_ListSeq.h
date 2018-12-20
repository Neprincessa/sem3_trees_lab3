#ifndef _LST__S__
#define _LST__S__
using namespace std;

//----------------------------------------------------------ListSequence-------------------------------------------//

template <typename TElement>
void ListSequence<TElement>::Append(TElement item) {

	Node<TElement> *temp = new Node<TElement>;
	temp->Next = NULL;
	temp->data = item;

	if (head != NULL)   //if list is not empty
	{
		amount++;
		temp->Prev = tail;
		tail->Next = temp;
		tail = temp;
	}
	else  //if list is empty
	{
		amount++;
		temp->Prev = NULL;
		head = tail = temp;
	}
	changeCondition(0);
}


template <typename TElement>
void ListSequence<TElement>::Prepend(TElement item) {

	Node<TElement> *temp = new Node<TElement>;
	temp->Prev = NULL;
	temp->data = item;

	if (head != NULL)   //if list is not empty
	{
		amount++;
		temp->Next = head;
		head->Prev = temp;
		head = temp;
	}
	else  //if list is empty
	{
		amount++;
		temp->Prev = NULL;
		head = tail = temp;
	}
	changeCondition(0);
}

template <typename TElement>
void ListSequence<TElement>::Display() {

	Node<TElement> *temp = head;
	int i = 0;
	if (head == NULL)
		cout << "Sequence is empty" << endl;
	else {
		while (temp /*!= NULL*/)
		{
			i++;
			cout << i << ") ";
			cout << temp->data;
			cout << "\n";
			temp = temp->Next;
		}
	}
	cout << "\n";
}

template <typename TElement>
int ListSequence<TElement>::getLength() {
	return this->amount;
}

template <typename TElement>
void ListSequence<TElement>::changeCondition(int state) {
	isEmpty = state;
}


template <typename TElement>
int ListSequence<TElement>::getIsEmpty() {
	return isEmpty;
}

template <typename TElement>
TElement* ListSequence <TElement>::GetFirst() {
	//cout << "\n";
	if (getIsEmpty() != 1) {
		/*cout << "The first element is: ";
		cout << head->data;
		cout << "\n";*/
		return &head->data;
	}
	else {
		cout << "You can't get the element from the emptry sequence" << endl;
		//cout << "\n";
		return 0;
	}
}

template <typename TElement>
TElement* ListSequence<TElement>::GetLast() {
	//	cout << "\n";
	if (getIsEmpty() != 1) {
		/*cout << "The last element is: ";
		cout << tail->data;
		cout << "\n";
		*/return &tail->data;
	}
	else {
		cout << "You can't get the element from the emptry sequence" << endl;
		//2	cout << "\n";
		return 0;
	}
}

template <typename TElement>
TElement* ListSequence<TElement>::Get(int index) {


	if (index < 0 || index > this->amount - 1) {
		return 0;
		//throw Error;/*ExceptionOutOfBounds(index);*/
	}
	if (index == 0) return GetFirst();
	if (index == this->amount - 1) return GetLast();
	else {
		Node<TElement> *temp = new Node<TElement>;
		temp->Next = head->Next;
		while (index - 1) {
			temp->Next = temp->Next->Next;
			index--;
		}
		return &temp->Next->data;
	}
}


template <typename TElement>
void ListSequence<TElement>::InsertAt(int index, TElement item) {

	if (this->isEmpty == 1) this->isEmpty = 0;
	if (index == 0) Prepend(item);
	else if (index == this->amount) Append(item);
	else {
		this->amount++;
		Node<TElement> *temp = new Node<TElement>;
		temp->data = item;
		temp->Next = head->Next;
		temp->Prev = head;
		head->Next = temp;
		if (index != 1) {
			while (index - 1) {
				Node<TElement> *r = temp->Next;
				Node<TElement> *l = temp->Prev;

				l->Next = r;
				r->Prev = l;

				temp->Next = r->Next;
				temp->Prev = r;

				index--;
			}
		}
		if (temp->Next != NULL) {
			temp->Next->Prev = temp;
		}
		temp->Prev->Next = temp;
	}
}

template <typename TElement>
void ListSequence<TElement>::Remove(TElement item) {

	if (head != NULL) {
		int i = 0;
		TElement *forNewList = new TElement[amount - 1];
		Node<TElement> *tmp = new Node<TElement>;
		tmp = head;
		bool flag = false;

		//for head think and tail
		while (tmp && tmp->data != item) {
			forNewList[i] = tmp->data;
			tmp = tmp->Next;
			i++;
		}
		if (tmp)
			tmp = tmp->Next;
		while (tmp) {
			forNewList[i] = tmp->data;
			tmp = tmp->Next;
			i++;
		}

		int tmpAm = amount - 1;
		amount = 0;
		head = tail = NULL;
		for (int i = 0; i< tmpAm; i++)
			Append(forNewList[i]);
	}
	else {
		cout << "You can't remove element from the empty sequence" << endl;
		cout << "\n";
	}
}


template <typename TElement>
int ListSequence<TElement>::chooseFunction() {
	int typeOfFunction = whatFunc();
	return typeOfFunction;
}


template <typename TElement>
ListSequence<TElement> ListSequence<TElement>::GetSubSequence(int startIndex, int endIndex) {

	ListSequence<TElement> resulList;
	resulList.amount = endIndex - startIndex + 1;
	resulList.isEmpty = 0;

	int leftFlag = startIndex;

	int i = 1;

	Node<TElement> *tmp = new Node<TElement>;
	tmp = head;
	while (tmp) {
		if (i >= startIndex && i <= endIndex)
			resulList.Append(tmp->data);
		tmp = tmp->Next;
		i++;
	}

	return resulList;
}

template <typename TElement>
void ListSequence<TElement>::InsertSort() {

	Node<TElement> *t;
	TElement x;
	Node<TElement> curElement;
	t = head->Next;
	while (t) {
		x = t->data;
		curElement.data = t->data;
		Node<TElement> *b = t->Prev;
		while (b != NULL && x < b->data) {
			b->Next->data = b->data;
			b = b->Prev;
		}
		if (b == NULL)
			head->data = curElement.data;
		else
			b->Next->data = curElement.data;
		t = t->Next;
	}
}

template <typename TElement>
TElement* ListSequence<TElement>::getArr() {

	TElement *result = new TElement[amount];
	Node<TElement> *tmp = head;
	int i = 0;
	while (tmp) {
		result[i] = tmp->data;
		tmp = tmp->Next;
		i++;
	}

	return result;
}


template <typename TElement>
void ListSequence<TElement>::RemoveByIndex(int index) {
	Node<TElement> *current = head;
	Node<TElement> *temp = nullptr;
	int i = 0;
	if (index == 0) {
		current = head->Next;
		temp = head;
		head = current;
		//delete temp;
	}
	else if (index == this->getLength() - 1) {
		current = tail->Prev;
		current->Next = NULL;
		temp = tail;
		tail = current;
	}
	else {
		while (current->Next != NULL && i != index) {
			current = current->Next;
			i++;
		}
		current = current->Prev;
		temp = current->Next;
		current->Next = temp->Next;
		temp->Next->Prev = current;
	}
	this->amount--;
	delete temp;
}
#endif // !_LST__S__
