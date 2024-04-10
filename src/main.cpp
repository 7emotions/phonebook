#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>

#include <iostream>
#include <regex>
#include <string>

#include "app/app.hpp"

int getFiles(std::vector<std::string> &files, std::string suffix = ".dat") {
	int FileCnt = 0;
	DIR *dirp;
	struct dirent *dp;
	char buff[1024];

	getcwd(buff, 1024);
	std::string path(buff);

	dirp = opendir(path.c_str());

	if (dirp == NULL) {
		std::cout << "Failed to open dir";
		return 0;
	}

	while ((dp = readdir(dirp)) != NULL) {
		std::string curpath(path);
		if (path.back() != '/') {
			curpath += std::string("/") + dp->d_name;
		} else {
			curpath += dp->d_name;
		}

		if (dp->d_type == DT_REG) {
			if (!strrchr(dp->d_name, '.')) {
				continue;
			}
			if (std::string(strrchr(dp->d_name, '.')) == suffix) {
				auto name = std::string(dp->d_name);
				files.push_back(name.substr(0, name.find('.')));
				FileCnt++;
			}
		}
	}
	closedir(dirp);
	return FileCnt;
}

PhoneBookApp app;

bool controller() {
	std::string command;
	std::cout << "App>";
	std::getline(std::cin, command);

	if (command.compare("exit") == 0) {
		return false;
	}

	if (command.compare("help") == 0) {
		std::cout << "Usage: [COMMAND] [ARGUMENT] [VALUE]..." << std::endl
				  << "To manage phonebook information.\n"
				  << "Use `info [COMMAND]` to find out details.\n\n"
				  << "Command:\n"
				  << "\tadd\t"
				  << "to add new a phonebook or contact.\n"
				  << "\tdel\t"
				  << "to delete a phonebook or contact.\n"
				  << "\tlist\t"
				  << "to list data of a phonebook or contacts.\n"
				  << "\tinfo\t"
				  << "to list information about the command.\n"
				  << "\texit\texit app.\n"
				  << "\tsearch\t"
				  << "to search data in phonebook.\n"
				  << "\timport\t"
				  << "to import data from file.\n"
				  << "\texport\t"
				  << "to export data.\n";
		return true;
	}

	std::regex reg("\\s+");
	std::sregex_token_iterator pos(command.begin(), command.end(), reg, -1);
	decltype(pos) end;

	if (pos->str() == "add") {
		if (++pos == end) {
			std::cout << "Missing arguments and values." << std::endl;
			return true;
		}

		auto arg = pos->str();

		if (++pos == end) {
			std::cout << "Missing values." << std::endl;
			return true;
		}
		auto value1 = pos->str();

		if (arg == "book") {
			app.NewBook(value1);
		} else if (arg == "contact") {
			if (++pos == end) {
				std::cout << "Missing name of the contact." << std::endl;
				return true;
			}
			auto value2 = pos->str();
			if (++pos == end) {
				std::cout << "Missing code of the contact." << std::endl;
				return true;
			}
			auto value3 = pos->str();
			app.NewContact(value1, Contact(value2, value3));
		} else {
			std::cout << "Wrong argument for command `add`. Use `info add` to "
						 "find out details."
					  << std::endl;
		}
	} else if (pos->str() == "del") {
		if (++pos == end) {
			std::cout << "Missing arguments and values." << std::endl;
			return true;
		}
		auto arg = pos->str();
		if (++pos == end) {
			std::cout << "Missing values." << std::endl;
			return true;
		}
		auto value1 = pos->str();
		if (arg == "book") {
			app.PopBook(value1);
		} else if (arg == "contact") {
			if (++pos == end) {
				std::cout << "Missing name of the contact." << std::endl;
				return true;
			}
			auto value2 = pos->str();
			app.PopContact(value1, value2);
		} else {
			std::cout << "Wrong argument for command `del`. Use `info del` to "
						 "find out details."
					  << std::endl;
		}
	} else if (pos->str() == "list") {
		if (++pos == end) {
			std::cout << "Missing arguments and values." << std::endl;
			return true;
		}
		auto arg = pos->str();
		if (arg == "book") {
			app.ListBook();
		} else if (arg == "contact") {
			if (++pos == end) {
				std::cout << "Missing values." << std::endl;
				return true;
			}
			auto value1 = pos->str();
			app.ListContact(value1);
		} else {
			std::cout
				<< "Wrong argument for command `list`. Use `info list` to "
				   "find out details."
				<< std::endl;
		}
	} else if (pos->str() == "info") {
		if (++pos == end) {
			std::cout << "Missing argument." << std::endl;
			return true;
		}
		auto arg = pos->str();
		if (arg == "add") {
			std::cout << "Usage: \n\tadd <book|contact> <name1> [name2] [code]"
					  << std::endl
					  << "Options:\n"
					  << "\tbook\t\tAdd new phonebook named after <name1>"
					  << std::endl
					  << "\tcontact\t\tAdd new contact named [name2] with "
						 "[code] to phonebook <name1>"
					  << std::endl;
		} else if (arg == "del") {
			std::cout << "Usage:\n\tdel <book|contact> <name1> [name2]"
					  << std::endl
					  << "Options:\n"
					  << "\tbook\t\tDelete phonebook named <name1>" << std::endl
					  << "\tcontact\t\tDelete contact named [name2] from "
						 "phonebook named <name1>"
					  << std::endl;
		} else if (arg == "list") {
			std::cout
				<< "Usage:\n\tlist <book|contact> [name]" << std::endl
				<< "Options:\n"
				<< "\tbook\t\tList all phonebooks" << std::endl
				<< "\tcontact\t\tList all contacts in phonebook named [name]"
				<< std::endl;
		} else if (arg == "import") {
			std::cout << "Usage:\n\timport [phonebook]" << std::endl
					  << "Arguments:\n"
					  << "\t[phonebook]\t\tname of phonebook to import. "
					  << std::endl;
		} else if (arg == "export") {
			std::cout << "Usage:\n\texport [phonebook]" << std::endl
					  << "Arguments:\n"
					  << "\t[phonebook]\t\tname of phonebook to export. Use "
						 "`list book` to check all phonebooks"
					  << std::endl;
		} else if (arg == "search") {
			std::cout << "Usage:\n\tsearch <phonebook> <name>" << std::endl;
			std::cout << "Arguments:\n"
					  << "\t[phonebook]\tname of phonebook to search. Use "
						 "`list book` to check all phonebooks"
					  << std::endl
					  << "\t[name]\t\tname of contact to search. " << std::endl;
		} else {
			std::cout << "Command not found. Use `help` to find out more"
					  << std::endl;
		}
	} else if (pos->str() == "search") {
		if (++pos == end) {
			std::cout << "Missing values." << std::endl;
			return true;
		}
		auto value1 = pos->str();
		if (++pos == end) {
			std::cout << "Missing values." << std::endl;
			return true;
		}
		auto value2 = pos->str();

		app.Search(value1, value2);
	} else if (pos->str() == "import") {
		if (++pos == end) {
			std::cout << "Missing argument." << std::endl;
			return true;
		}
		auto arg = pos->str();

		app.ExImport(arg);
	} else if (pos->str() == "export") {
		if (++pos == end) {
			std::cout << "Missing argument." << std::endl;
			return true;
		}
		auto arg = pos->str();
		app.ExExport(arg);
	} else {
		std::cout << "Command not found. Use `help` to find out more"
				  << std::endl;
	}

	return true;
}

int main(int argc, char **argv) {
	std::cout << "PhoneBookApp Bash, version 0.0.1-release." << std::endl
			  << "Author:Lorenzo Feng(lorenzo.feng@njust.edu.cn)" << std::endl
			  << "Type `help` to get more details.\n\n"
			  << R"(
 ___________________
< Hey! Who are you!?>
 -------------------
                       \                    ^    /^
                        \                  / \  // \
                         \   |\___/|      /   \//  .\
                          \  /O  O  \__  /    //  | \ \           *----*
                            /     /  \/_/    //   |  \  \          \   |
                            @___@`    \/_   //    |   \   \         \/\ \
                           0/0/|       \/_ //     |    \    \         \  \
                       0/0/0/0/|        \///      |     \     \       |  |
                    0/0/0/0/0/_|_ /   (  //       |      \     _\     |  /
                 0/0/0/0/0/0/`/,_ _ _/  ) ; -.    |    _ _\.-~       /   /
                             ,-}        _      *-.|.-~-.           .~    ~
            \     \__/        `/\      /                 ~-. _ .-~      /
             \____(oo)           *.   }            {                   /
             (    (--)          .----~-.\        \-`                 .~
             //__\\  \__ Moo!   ///.----..<        \             _ -~
            //    \\               ///-._ _ _ _ _ _ _{^ - - - - ~)"
			  << std::endl
			  << std::endl;

	std::vector<std::string> files;

	getFiles(files);

	for (auto file : files) {
		app.ExImport(file);
	}

	while (controller()) {
	}
	return 0;
}