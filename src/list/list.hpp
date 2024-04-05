/**
 * @file list.hpp
 * @author Lorenzo Feng (lorenzo.feng@njust.edu.cn)
 * @brief Base Sorted Node List
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
		while (node != nullptr) {
			auto pre = node->next_;
			delete node;
			node = pre;
		}
		head = nullptr;
	}

	int size() const { return size_; }

	T& operator[](unsigned int i) {
		auto node = head;
		if (i >= size_) {
			throw std::runtime_error("index out of range.");
		}
		for (size_t _ = 0; _ < i; _++) {
			node = node->next_;
		}
		return node->data_;
	}

	void print() {
		auto node = head;
		while (node != nullptr) {
			std::cout << node->data_;
			node = node->next_;
		}
	}

	void push(const T& element) {
		auto node = head;

		if (node == nullptr) {
			head = new Node(element);
			size_ += 1;
			return;
		}

		if (node->data_ > element) {
			head = new Node(element, head);
			size_ += 1;
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

	T pop(unsigned int i = 0) {
		auto node = head;
		if (i >= size_) {
			throw std::runtime_error("index out of range.");
		}

		if (i == 0) {
			head = head->next_;
			size_ -= 1;
			return node->data_;
		}

		for (size_t _ = 0; _ < i - 1; _++) {
			node = node->next_;
		}
		auto data = node->next_->data_;
		node->next_ = node->next_->next_;
		size_ -= 1;
		return data;
	}

	int search(const T& element) {
		if (head == nullptr) {
			return -1;
		}

		auto node = head;
		size_t i = 0;

		while (node != nullptr) {
			if (node->data_ == element) {
				return i;
			}
			node = node->next_;
			i++;
		}
		return -1;
	}
};