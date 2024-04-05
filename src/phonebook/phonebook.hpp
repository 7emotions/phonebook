/**
 * @file phonebook.hpp
 * @author Lorenzo Feng (lorenzo.feng@njust.edu.cn)
 * @brief PhoneBook Descriptor
 * @version 0.1
 * @date 2024-04-05
 *
 *
 */

#include <string>

#include "contact/contact.hpp"
#include "list/list.hpp"

class PhoneBook : public NodeList<Contact> {
   public:
	explicit PhoneBook(const std::string &bookname)
		: NodeList<Contact>(), bookname_(bookname) {}

	inline bool operator>=(const PhoneBook &phonebook) {
		return this->bookname_ >= phonebook.bookname_;
	}
	inline bool operator>(const PhoneBook &phonebook) {
		return this->bookname_ > phonebook.bookname_;
	}
	inline bool operator<(const PhoneBook &phonebook) {
		return this->bookname_ < phonebook.bookname_;
	}
	inline bool operator<=(const PhoneBook &phonebook) {
		return this->bookname_ <= phonebook.bookname_;
	}
	inline bool operator==(const PhoneBook &phonebook) {
		return this->bookname_ == phonebook.bookname_;
	}

	const std::string getName() const { return bookname_; }

	friend std::ostream &operator<<(std::ostream &os, PhoneBook &phonebook) {
		os << "Name: " << phonebook.bookname_ << "\tMembers:" << phonebook.size_
		   << std::endl;
		return os;
	}

   private:
	const std::string bookname_;
};