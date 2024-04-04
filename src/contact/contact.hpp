/**
 * @file contact.hpp
 * @author Lorenzo Feng (lorenzo.feng@njust.edu.cn)
 * @brief Description class for contacts
 * @version 0.1
 * @date 2024-04-04
 *
 *
 */

#pragma once

#include <string>

class Contact {
   public:
	explicit Contact();
	/**
	 * @brief Construct a new Contact object
	 *
	 * @param name Name of Contact
	 * @param code Number Code
	 */
	explicit Contact(std::string name, std::string code)
		: name_(name), code_(code) {}

	inline bool operator>=(Contact &contact) {
		return this->name_ >= contact.name_;
	}
	inline bool operator>(Contact &contact) {
		return this->name_ > contact.name_;
	}
	inline bool operator<(Contact &contact) {
		return this->name_ < contact.name_;
	}
	inline bool operator<=(Contact &contact) {
		return this->name_ <= contact.name_;
	}
	inline bool operator==(Contact &contact) {
		return this->name_ == contact.name_;
	}

	friend std::istream &operator>>(std::istream &is, Contact &contact);
	friend std::ostream &operator<<(std::ostream &os, Contact &contact);

   private:
	std::string name_;
	std::string code_;
};
