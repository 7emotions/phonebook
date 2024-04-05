#include "app/app.hpp"

class PhoneBookApp::Impl : public NodeList<PhoneBook> {
   public:
	Impl() : NodeList<PhoneBook>() {}

	void NewBook(const std::string& bookname) { push(PhoneBook(bookname)); }
	PhoneBook PopBook(const std::string& bookname) { return PhoneBook(""); }
	void LstBook() {
		std::cout << "PhoneBook List:" << std::endl;
		print();
	}

	void NewContact(const std::string& bookname, const Contact& contact) {
		auto node = head;

		if (node == nullptr) {
			std::cout << "There`s no phonebook." << std::endl;
			return;
		}

		while (node != nullptr) {
			if (node->data_.getName() == bookname) {
				break;
			}
			node = node->next_;
		}

		if (node == nullptr) {
			std::cout << "There`s no phonebook named " << bookname << std::endl;
			return;
		}

		node->data_.push(contact);
	}

	Contact PopContact(const std::string& bookname, const std::string& name) {
		return Contact();
	}

	void LstContact(const std::string& bookname) {
		auto node = head;

		if (node == nullptr) {
			std::cout << "There`s no phonebook." << std::endl;
			return;
		}

		while (node != nullptr) {
			if (node->data_.getName() == bookname) {
				break;
			}
			node = node->next_;
		}

		if (node == nullptr) {
			std::cout << "There`s no phonebook named " << bookname << std::endl;
			return;
		}

		std::cout << "Contacts in Phonebook[" << bookname << "]\n";
		node->data_.print();
	}

	void ExImport(const std::string& path) {}
	void ExExport(const std::string& bookname) {}
};

PhoneBookApp::PhoneBookApp() { impl_ = new PhoneBookApp::Impl(); }

void PhoneBookApp::NewBook(const std::string& bookname) {
	return impl_->NewBook(bookname);
}
PhoneBook PhoneBookApp::PopBook(const std::string& bookname) {
	return impl_->PopBook(bookname);
}
void PhoneBookApp::LstBook() { return impl_->LstBook(); }

void PhoneBookApp::NewContact(const std::string& bookname,
							  const Contact& contact) {
	return impl_->NewContact(bookname, contact);
}
Contact PhoneBookApp::PopContact(const std::string& bookname,
								 const std::string& name) {
	return impl_->PopContact(bookname, name);
}
void PhoneBookApp::LstContact(const std::string& bookname) {
	return impl_->LstContact(bookname);
}

void PhoneBookApp::ExImport(const std::string& path) {
	return impl_->ExImport(path);
}
void PhoneBookApp::ExExport(const std::string& bookname) {
	return impl_->ExExport(bookname);
}