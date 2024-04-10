/**
 * @file app.hpp
 * @author Lorenzo Feng (lorenzo.feng@njust.edu.cn)
 * @brief IMPL Interface for PhoneBook Application
 * @version 0.1
 * @date 2024-04-05
 *
 *
 */

#include <string>

#include "phonebook/phonebook.hpp"

class PhoneBookApp final {
   public:
	PhoneBookApp();
	~PhoneBookApp() = default;

	/**
	 * @brief Newly add a phonebook named after `bookname`.
	 *
	 * @param bookname name of the new phonebook
	 */
	void NewBook(const std::string& bookname);

	/**
	 * @brief Delete a phonebook from phonebook list. Use `list book` to view
	 * the name of phonebooks.
	 *
	 * @param bookname name of the phonebook to delete
	 * @return PhoneBook phonebook deleted
	 */
	PhoneBook PopBook(const std::string& bookname);

	/**
	 * @brief List all phonebooks.
	 *
	 */
	void ListBook();

	/**
	 * @brief Edit the name of the phonebook.
	 *
	 * @param bookname name to edit
	 * @param alter name to adopt
	 */
	void EditBook(const std::string& bookname, const std::string& alter);

	/**
	 * @brief Newly add a `contact` in phonebook `bookname`.
	 *
	 * @param bookname
	 * @param contact
	 */
	void NewContact(const std::string& bookname, const Contact& contact);

	/**
	 * @brief Delete a contact from phonebook list. Use `list contact
	 * <phonebook>` to view all contacts in phonebook `bookname`.
	 *
	 * @param bookname name of the phonebook
	 * @param name name of the contact
	 * @return Contact contact deleted
	 */
	Contact PopContact(const std::string& bookname, const std::string& name);

	/**
	 * @brief List all contacts in phonebook `bookname`.
	 *
	 * @param bookname
	 */
	void ListContact(const std::string& bookname);

	/**
	 * @brief Edit contact information.
	 *
	 * @param bookname phonebook name
	 * @param contact contact to modify
	 * @param alter contact to adopt
	 */
	void EditContact(const std::string& bookname, const Contact& contact,
					 const Contact& alter);

	/**
	 * @brief Search contact information.
	 *
	 * @param bookname
	 * @param name
	 * @return Contact
	 */
	Contact Search(const std::string& bookname, const std::string& name);

	/**
	 * @brief Import data.
	 *
	 * @param bookname name of phonebook
	 */
	void ExImport(const std::string& bookname);
	/**
	 * @brief Export data.
	 *
	 * @param bookname name of the phonebook to export
	 */
	void ExExport(const std::string& bookname);

   private:
	class Impl;
	Impl* impl_;
};