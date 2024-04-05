/**
 * @file list.hpp
 * @author Lorenzo Feng (lorenzo.feng@njust.edu.cn)
 * @brief 链表功能类
 * @version 0.1
 * @date 2024-04-04
 *
 *
 */

#pragma once

#include <cstddef>
#include <iostream>
#include <stdexcept>

template <typename T>
class NodeList {
   protected:
	struct Node {
		T data_;
		Node* next_;
		Node() { next_ = nullptr; }
		Node(T element, Node* ptr = nullptr) : data_(element), next_(ptr) {}
	}* head;
	std::size_t size_;

   public:
	NodeList() : head(nullptr), size_(0) {}
	~NodeList() {
		auto node = head;
		if (node == nullptr) {
			return;
		}
		while (node->next_ != nullptr) {
			delete node;
			node = node->next_;
		}
		delete node;
	}

	int size() const { return size_; }

	T& operator[](unsigned int i) {
		Node* node = head;
		if (i + 1 >= size_) {
			throw std::runtime_error("index out of range.");
		}
		for (size_t _ = 0; _ < i; _++) {
			node = node->next_;
		}
		return node->data_;
	}

	void print() {
		Node* node = head;
		while (node != nullptr) {
			std::cout << node->data_;
			node = node->next_;
		}
	}

	void push(const T& element) {
		Node* node = head;

		if (node == nullptr) {
			head = new Node(element);
			size_ += 1;
			return;
		}

		if (node->data_ > element) {
			head = new Node(element, head);
			return;
		}

		while (node->next_ != nullptr && node->data_ <= element) {
			node = node->next_;
		}

		if (node->next_ == nullptr) {
			node->next_ = new Node(element);
		} else {
			node->next_ = new Node(element, node->next_);
		}
		size_ += 1;
	}

	void pop(unsigned int i = 0);
};