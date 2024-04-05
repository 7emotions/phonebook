/**
 * @file app.hpp
 * @author Lorenzo Feng (lorenzo.feng@njust.edu.cn)
 * @brief 电话簿应用业务接口类
 * @version 0.1
 * @date 2024-04-05
 *
 *
 */

#include <string>

#include "phonebook/phonebook.hpp"

class PhoneBookApp {
   public:
	PhoneBookApp();
	~PhoneBookApp() = default;

	void NewBook(const std::string& bookname);
	PhoneBook PopBook(const std::string& bookname);
	void LstBook();

	void NewContact(const std::string& bookname, const Contact& contact);
	Contact PopContact(const std::string& bookname, const std::string& name);
	void LstContact(const std::string& bookname);

	void ExImport(const std::string& path);
	void ExExport(const std::string& bookname);

   private:
	class Impl;
	Impl* impl_;
};