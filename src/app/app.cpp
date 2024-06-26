#include "app/app.hpp"

#include <fstream>

class PhoneBookApp::Impl : public NodeList<PhoneBook> {
   public:
	Impl() : NodeList<PhoneBook>() {}

	void NewBook(const std::string& bookname) { push(PhoneBook(bookname)); }

	PhoneBook PopBook(const std::string& bookname) {
		auto index = search(PhoneBook(bookname));
		if (index == -1) {
			std::cout << "No such phonebook." << std::endl;
			return PhoneBook("");
		}
		return pop(index);
	}

	void ListBook() {
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
		auto index = search(PhoneBook(bookname));
		if (index == -1) {
			std::cout << "No such phonebook." << std::endl;
			return Contact();
		}

		auto node = head;
		for (int _ = 0; _ < index; _++) {
			node = node->next_;
		}
		index = node->data_.search(Contact(name));

		if (index == -1) {
			std::cout << "No such contact." << std::endl;
			return Contact();
		}
		return node->data_.pop(index);
	}

	void ListContact(const std::string& bookname) {
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

		std::cout << "Contacts in Phonebook [" << bookname
				  << "] Mumber:" << node->data_.size() << "\n";
		node->data_.print();
	}

	Contact Search(const std::string& bookname, const std::string& name) {
		auto node = head;

		if (node == nullptr) {
			std::cout << "There`s no phonebook." << std::endl;
			return Contact();
		}

		while (node != nullptr) {
			if (node->data_.getName() == bookname) {
				break;
			}
			node = node->next_;
		}

		if (node == nullptr) {
			std::cout << "There`s no phonebook named " << bookname << std::endl;
			return Contact();
		}

		auto index = node->data_.search(Contact(name));
		std::cout << node->data_[index];
		return node->data_[index];
	}

	void ExImport(const std::string& bookname) {
		std::ifstream in(bookname + ".dat", std::ios::binary);
		if (!in.is_open()) {
			std::cout << "Failed to read data." << std::endl;
			throw std::runtime_error("Failed to read data.");
		}

		if (search(PhoneBook(bookname)) == -1) {
			NewBook(bookname);
		}

		auto buffer = new char[1024];
		while (true) {
			if (!in.getline(buffer, 1024)) {
				break;
			}
			std::string name(buffer);
			in.getline(buffer, 1024);
			std::string code(buffer);

			NewContact(bookname, Contact(name, code));
		}
	}

	void ExExport(const std::string& bookname) {
		std::ofstream out(bookname + ".dat", std::ios::binary);
		if (!out.is_open()) {
			std::cout << "Failed to save data." << std::endl;
			throw std::runtime_error("Failed to save data.");
		}

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

		for (size_t i = 0; i < node->data_.size(); i++) {
			auto data = node->data_[i];

			out << data.getName() << "\n" << data.getCode() << "\n";
		}
		out.close();
	}
};

PhoneBookApp::PhoneBookApp() { impl_ = new PhoneBookApp::Impl(); }

void PhoneBookApp::NewBook(const std::string& bookname) {
	return impl_->NewBook(bookname);
}
PhoneBook PhoneBookApp::PopBook(const std::string& bookname) {
	return impl_->PopBook(bookname);
}
void PhoneBookApp::ListBook() { return impl_->ListBook(); }

void PhoneBookApp::NewContact(const std::string& bookname,
							  const Contact& contact) {
	return impl_->NewContact(bookname, contact);
}
Contact PhoneBookApp::PopContact(const std::string& bookname,
								 const std::string& name) {
	return impl_->PopContact(bookname, name);
}
void PhoneBookApp::ListContact(const std::string& bookname) {
	return impl_->ListContact(bookname);
}

void PhoneBookApp::ExImport(const std::string& path) {
	return impl_->ExImport(path);
}
void PhoneBookApp::ExExport(const std::string& bookname) {
	return impl_->ExExport(bookname);
}

Contact PhoneBookApp::Search(const std::string& bookname,
							 const std::string& name) {
	return impl_->Search(bookname, name);
}