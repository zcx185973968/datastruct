#ifndef LINKEDLIST_HH_
#define LINKEDLIST_HH_

template<typename T>
class LinkedList {
private:
	class Node {
	public:
		T val;
		Node* next;
		Node* prev;
		Node(const T& v, Node* next, Node* prev)
			: val(v), next(next), prev(prev) {}
	};
	Node* head;
public:
	LinkedList() {
		head = nullptr;
	}
	~LinkedList() {
#if 0
		// ILLEGAL: You cannot refer to memory after deletion
		for (Node* p = head; p != nullptr; p = p->next)
			delete p;
#endif

		Node* q;
		for (Node* p = head; p!= nullptr; p=q) {
			q = p->next; 
			delete p;
		}
		// or
#if 0
		for (Node* p = head; p!= nullptr; ) {
			Node* q = p;
			p = p->next; 
			delete q;
		}
#endif
	}
	//copy constructor
	LinkedList(const LinkedList& orig) {
#if 0
		//BAAAAAAD
		for (int i = 0; i < orig.size(); i++)
			addEnd(orig.get(i));
#endif







		
		if (orig.head == nullptr) {
			head = nullptr;
			return;
		}
		head = new Node(orig.head->val, nullptr, nullptr);
		
		Node*q = head;
		for (Node* p = orig.head->next; p!= nullptr; p = p->next) {
			q->next = new Node(p->val, nullptr, q);
      q = q->next;
		}
	}
	void addStart(const T& v) { //O(1)
		if (head == nullptr) {
			head = new Node(v, head, nullptr);
			return;
		}
		head = new Node(v, head, nullptr);
		head->next->prev = head;
	}
	
	void addEnd(const T& v) {
		if (head == nullptr) {
			head = new Node(v, nullptr, nullptr);
			return;
		}
		Node* p;
    for (p = head; p->next != nullptr; p = p->next)
			;
    p->next = new Node(v, nullptr, p);		
	}
	void add(const T&  v) { addStart(v); }
  void insert(const T& v, int pos) {
		Node* p = head;
		for (int i = 0; i < pos; i++)
			p = p->next;
		Node* temp = new Node(v, p->next, p);
		p->next = temp; // break the link with the node before us
		temp->next->prev = temp;
	}
	class Iterator {
	private:
		Node* p;
	public:
		Iterator(Node* p) : p(p) {}
		Iterator(const LinkedList<T>& list) {
			p = list.head;
		}
		bool notEnd() const {
			return p != nullptr; 
		}
		void operator++() {
			p = p->next;
		}
		void operator--() {
			p = p->prev;
		}
		T val() const {
			return p->val;
		}
	};
	Iterator end() const {
		if (head == nullptr) {
			return Iterator(nullptr);
		}
		Node* p = head;
		for ( ; p->next != nullptr; p = p->next)
			;
    return Iterator(p);
	}

};

#endif
