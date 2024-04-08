#include "contact/contact.hpp"

#include <iostream>

std::ostream &operator<<(std::ostream &os, Contact &contact) {
	os << "Name: " << contact.name_ << "\tCode:" << contact.code_ << std::endl;
	return os;
}