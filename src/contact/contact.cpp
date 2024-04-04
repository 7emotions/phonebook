#include "contact/contact.hpp"

#include <iostream>

std::istream &operator>>(std::istream &is, Contact &contact) {
	is >> contact.name_ >> contact.code_;
	return is;
}

std::ostream &operator<<(std::ostream &os, Contact &contact) {
	os << "Name: " << contact.name_ << "\tCode:" << contact.code_ << std::endl;
	return os;
}