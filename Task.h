#pragma once
#include "BotAdapter.h"
#include <algorithm>

using ChatType = int64_t;
using namespace std;

class Task
{
protected:
	static bool checkPassword(string input, string passwords) {
		std::transform(input.begin(), input.end(), input.begin(), ::tolower);
		std::transform(passwords.begin(), passwords.end(), passwords.begin(), ::tolower);

		std::istringstream iss(passwords);

		std::string token;
		while (std::getline(iss, token, '/')) {
			std::cout << token << std::endl;
			if (token == input)
				return true;
		}
		
		return false;
	}

	ChatType chat=0;

public:

	ChatType getChat() {
		return chat;
	}

	virtual void init(ChatType chat_id) = 0;
	virtual bool performResponce(ChatType chat_id, string text) = 0;
};

