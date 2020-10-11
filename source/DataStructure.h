#pragma once
#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H
#include <cassert>
#include <iterator>
#include <memory>

// TODO: Give this a good name
template<typename T> class LinkedList {
	/* Type LinkedList<T> is modeled by a finite set of T
	 * Only intended for iteration, not efficient if things will be removed/added often
	 * Constant time insertion, constant time deletion, and linear search
	 * Order does NOT matter
	 * */
	private:
		struct Node {
			T data;
			Node* next;
			Node* prev;
		};
		Node* front;
		Node* last; // past the end iterator
		unsigned int length;
	public:
		class iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
			friend class LinkedList;
			private:
				Node* element;
				Node*& get() {
					return this->element;
				}
			public:
				iterator(Node* current) : element(current) {}
				T& operator->() {
					return this->element->data;
				}
				T& operator*() {
					return this->element->data;
				}
				iterator& operator++() {
					this->element = this->element->next;
					return *this;
				}
				iterator operator++(int) {
					iterator copy(this->element);
					this->operator++();
					return copy;
				}
				iterator& operator--() {
					this->element = this->element->prev;
					return *this;
				}
				iterator operator--(int) {
					iterator copy(this->element);
					this->operator--();
					return copy;
				}
				bool operator!=(const iterator& iter) {
					return this->element != iter.element;
				}
				bool operator==(const iterator& iter) {
					return !(*this != iter);
				}
		};
		LinkedList();
		~LinkedList();
		
		iterator begin() const;
		iterator end() const;
		iterator erase(iterator iter);
		iterator erase(iterator first, iterator last);
		iterator find(const T& data);
		iterator rbegin() const;
		iterator rend() const;
		
		unsigned int size() const;
		void clear();
		void push_back(const T& data);
};

template<typename T> LinkedList<T>::LinkedList() {
	this->clear();
}

template<typename T> LinkedList<T>::~LinkedList() {
	this->clear();
}

template<typename T> unsigned int LinkedList<T>::size() const {
	return this->length;
}

template<typename T> void LinkedList<T>::clear() {
	Node* element = this->front;
	Node* next;
	while (element != this->last) {
		next = element->next;
		delete element;
		element = next;
		this->length--;
	}
	assert(this->length == 0);
	this->last = new Node();
}

template<typename T> typename LinkedList<T>::iterator LinkedList<T>::begin() const {
	return LinkedList<T>::iterator(this->front);
}

template<typename T> typename LinkedList<T>::iterator LinkedList<T>::end() const {
	return LinkedList<T>::iterator(this->last);
}

template<typename T> typename LinkedList<T>::iterator LinkedList<T>::erase(iterator iter) {
	if (iter == this->last) return this->last;
	this->length--;
	Node* die = iter.get();
	if (iter != this->front) {
		die->next->prev = die->prev;
		die->prev->next = die->next;
		delete die;
		return iterator(this->front);
	} else {
		this->front = die->next;
		this->front->prev = NULL;
		delete die;
		return iterator(this->front);
	}
}

template<typename T> typename LinkedList<T>::iterator LinkedList<T>::find(const T& data) const {
	return std::find(this->begin(), this->end(), data);
}

template<typename T> typename LinkedList<T>::iterator LinkedList<T>::erase(iterator first, iterator last) {
	if (first == last) return last;
    this->erase(first++);
	return this->erase(first, last);
}

template<typename T> typename LinkedList<T>::iterator LinkedList<T>::rbegin() const {
	return LinkedList<T>::iterator(this->front);
}

template<typename T> typename LinkedList<T>::iterator LinkedList<T>::rend() const {
	return this->begin();
}

template<typename T> void LinkedList<T>::push_back(const T& data) {
	Node* newest = new Node({data, (this->length) ? this->front : this->last, NULL});
	this->front = newest;
	this->front->next->prev = this->front;
	this->length++;
}
#endif
