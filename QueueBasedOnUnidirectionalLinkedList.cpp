#include <algorithm>
#include <iostream>
using namespace std;
template <typename T>
struct Node {
	T data;
	Node* next;
	Node(const T& value) : data(value), next(nullptr) {}
};
template <typename T>
class QueueBasedOnUnidirectionalLinkedList {

	Node<T>* head;
	Node<T>* tail;
	unsigned count;
	void initList(const QueueBasedOnUnidirectionalLinkedList& other) {
		head = tail = nullptr;
		count = other.count;
		Clear();
		if (other.head == nullptr) {
			return;
		}
		Node* temp = other.head;
		Node* predPointer, * pointer;
		predPointer = new Node(temp->data);
		head = predPointer;
		temp = temp->next;
		if (temp == nullptr) {
			tail = head;
			return;
		}
		while (temp != nullptr) {
			pointer = new Node(temp->data);
			predPointer->next = pointer;
			predPointer = pointer;
			temp = temp->next;
		}
		tail = pointer;
	}
public:
	class Iterator {
	private:
		Node<T>* current;
	public:
		Iterator(Node<T>* node) : current(node) {}
		Iterator begin() const {
			return Iterator(head);
		}
		Iterator end() const {
			return Iterator(nullptr);
		}
		const Iterator begin() {
			return Iterator(head);
		}
		const Iterator end() {
			return Iterator(nullptr);
		}
	};
	const T& operator[](int index) const {
		Node node = getAt(index);
		return node->data;
	}
	T& operator[](int index) {
		Node<T>* node = getAt(index);
		return node->data;
	}
	void Clear() {
		Node<T>* current = head;
		while (current != nullptr) {
			Node<T>* next = current->next;
			delete current;
			current = next;
		}
		head = tail = nullptr;
		count = 0;
	}
	bool IsEmpty() const {
		return head == nullptr;
	}
	~QueueBasedOnUnidirectionalLinkedList() {
		Clear();
	}
	QueueBasedOnUnidirectionalLinkedList() : head(nullptr), tail(nullptr), count(0) {}
	QueueBasedOnUnidirectionalLinkedList(const QueueBasedOnUnidirectionalLinkedList& other) {
		initList(other);
	}
	QueueBasedOnUnidirectionalLinkedList(QueueBasedOnUnidirectionalLinkedList&& other) {
		if (this == &other) {
			return *this;
		}
		head = std::move(other.head);
		tail = std::move(other.tail);
		count = std::move(other.count);
		other.head = other.tail = nullptr;
		other.count = 0;
	}
	QueueBasedOnUnidirectionalLinkedList(std::initializer_list<T> ilist) : head(nullptr), tail(nullptr), count(0) {
		QueueBasedOnUnidirectionalLinkedList<T> temp;
		for (const T& number : ilist) {
			temp.Push(number);
		}
		std::swap(head, temp.head);
		std::swap(tail, temp.tail);
		std::swap(count, temp.count);

		if (&temp != this) {
			temp.head = nullptr;
			temp.tail = nullptr;
			temp.count = 0;
		}

	}
	Node<T>* getAt(int index) {
		Node<T>* ptr = head;
		int i = 0;
		if (index >= count) {
			return tail;
		}
		for (int i = 0; i < index; i++) {
			ptr = ptr->next;
		}
		return ptr;
	}
	bool Push(const T& element) {
		Node<T>* newNode = new Node<T>(element);
		if (IsEmpty()) {
			head = tail = newNode;
		}
		else {
			tail->next = newNode;
			tail = newNode;
		}
		count++;
		return true;
	}
	bool Pop(T& element) {
		if (IsEmpty()) {
			return false;
		}
		Node<T>* temp = head;
		head = head->next;
		element = temp->data;
		delete temp;

		count--;

		if (IsEmpty()) {
			tail = nullptr;  // Если очередь стала пустой, устанавливаем указатель rear в nullptr
		}

		return true;
	}
	bool Peek(T& element) const {
		if (count == 0) {
			return false;
		}
		element = head->data;
		return true;
	}
	void InsertAt(const T& value, int index) {
		if (index < 0 || index > count) {
			return;
		}

		Node<T>* newNode = new Node<T>(value);

		if (index == 0) {
			// Вставка в начало
			newNode->next = head;
			head = newNode;

			if (tail == nullptr) {
				// Очередь была пуста, обновляем указатель rear
				tail = newNode;
			}
		}
		else {
			Node<T>* current =head;
			Node<T>* prev = nullptr;

			// Перемещаем указатель current до элемента с предыдущим индексом
			for (int i = 0; i < index; i++) {
				prev = current;
				current = current->next;
			}

			// Вставляем новый элемент
			newNode->next = current;
			prev->next = newNode;

			if (current == nullptr) {
				// Вставили в конец, обновляем указатель rear
				tail = newNode;
			}
		}
		count++;
	}
	int RemoveAt(int index) {
		if (index < 0 || index >= count) {
			return false;
		}

		Node<T>* current = head;
		Node<T>* prev = nullptr;

		// Перемещаем указатель current до элемента с заданным индексом
		for (int i = 0; i < index; i++) {
			prev = current;
			current = current->next;
		}
		int ans = current->data;
		// Удаление элемента
		if (prev == nullptr) {
			// Удаляем первый элемент
			head = current->next;
			if (head == nullptr) {
				// Очередь стала пустой, обновляем указатель rear
				tail = nullptr;
			}
		}
		else {
			prev->next = current->next;
			if (current->next == nullptr) {
				// Удаляем последний элемент, обновляем указатель rear
				tail = prev;
			}
		}

		delete current;
		count--;

		return ans;
	}
	unsigned GetSize() {
		return count;
	}
	QueueBasedOnUnidirectionalLinkedList& operator=(const QueueBasedOnUnidirectionalLinkedList& other) {
		if (this == &other) {
			return *this;
		}
		initList(other);
		return *this;
	}
	QueueBasedOnUnidirectionalLinkedList& operator=(QueueBasedOnUnidirectionalLinkedList&& other) {
		if (this == &other) {
			return *this;
		}
		head = std::move(other.head);
		tail = std::move(other.tail);
		count = std::move(other.count);
		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
		return *this;
	}
	QueueBasedOnUnidirectionalLinkedList& operator=(std::initializer_list<int> ilist) {
		QueueBasedOnUnidirectionalLinkedList<T> temp;
		for (const T& number : ilist) {
			temp.PushBack(number);
		}
		swap(head, temp.head);
		swap(tail, temp.tail);
		swap(count, temp.count);

		if (&temp != this) {
			temp.head = nullptr;
			temp.tail = nullptr;
			temp.count = 0;
		}

		return *this;
	}
};

int main() {
	std::initializer_list<int> list = { 1, 5, 6 };
	QueueBasedOnUnidirectionalLinkedList<int> myList = list;
	myList.InsertAt(10, 1);
	cout << myList[1] << endl;
	cout << myList.RemoveAt(1) << endl;
	cout << myList.Push(9) << endl;
	cout << myList[3] << endl;
	return 0;
}