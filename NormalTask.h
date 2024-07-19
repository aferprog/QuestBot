#pragma once
#include "BotAdapter.h"
#include "MessageSet.h"
#include "Task.h"

extern BotAdapter bot;

class NormalTask: public Task
{
	MessageSet first_msgs;
	MessageSet tips;
	string password;

public:
	NormalTask(const json& obj)
		: first_msgs(obj["message"]), tips(obj["tips"]), password(obj["password"]) {
	}
	virtual void init(ChatType chat_id) override{
		chat = chat_id;
		bot.sendManyMessages(chat_id, first_msgs);
	}
	virtual bool performResponce(ChatType chat_id, string text) override{
		if (!checkPassword(text, password)) {
			bot.sendMessage(chat_id, tips.next());
			return false;
		}
		return true;
	}
};

