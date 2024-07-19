#pragma once
#include "NormalTask.h"
#include "QuickTask.h"
#include <vector>

using namespace std;

extern ChatType my_chat;

class GeneralQuest
{

	vector<NormalTask> tasks1, tasks2;
	QuickTask quick;
	NormalTask final;
	int p1, p2, p3, p4;

	int task=0;

	vector<ChatType> chats;

	MessageSet final_messages;
	string general_solution="solution";

	Task& getTask() {
		if (task < p1) {
			return tasks1[task];
		}
		if (task < p2) {
			return quick;
		}
		if (task < p3) {
			return tasks2[task - p2];
		}
		return final;
	}
	void specialPerform(string text) {
		if (StringTools::startsWith(text, "-")) {
			general_solution = text.substr(1);
			return;
		}
		if (StringTools::startsWith(text, ".....") && chats.size() >= 5) {
			bot.sendMessage(chats[4], text.substr(5));
			return;
		}
		if (StringTools::startsWith(text, "....") && chats.size() >= 4) {
			bot.sendMessage(chats[3], text.substr(4));
			return;
		}
		if (StringTools::startsWith(text, "...") && chats.size() >= 3) {
			bot.sendMessage(chats[2], text.substr(3));
			return;
		}
		if (StringTools::startsWith(text, "..") && chats.size() >= 2) {
			bot.sendMessage(chats[1], text.substr(2));
			return;
		}
		if (StringTools::startsWith(text, ".") && chats.size()>=1) {
			bot.sendMessage(chats[0], text.substr(1));
			return;
		}
		if (StringTools::startsWith(text, "#")) {
			for (auto chat : chats) {
				bot.sendMessage(chat, text.substr(1));
			}
			return;
		}
		if (text=="Skip") {
			skip();
			return;
		}
	}
	void skip() {
		auto t = getTask().getChat();
		task++;
		if (task < p4) {

			if (task == p2) {
				ChatType tt = chats[chats.size() - 1] == t ? chats[0] : chats[chats.size() - 1];
				getTask().init(tt);
			}
			else 
				getTask().init(t);
		}
	}
	void deinit() {
		bot.sendManyMessages(chats[0], final_messages);
		bot.sendMessage(chats[0], general_solution);
	}

	void checkChat(ChatType chat) {
		auto x = std::find(chats.begin(), chats.end(), chat);
		if (x == chats.end())
			chats.push_back(chat);
	}

public:

	GeneralQuest(const json& obj)
		: final(obj["final"]), quick(obj["quick"]), final_messages(obj["final_messages"]) {
		for (int i = 0; i < obj["items1"].size(); i++) {
			NormalTask t(obj["items1"][i]);
			tasks1.push_back(t);
		}
		for (int i = 0; i < obj["items2"].size(); i++) {
			NormalTask t(obj["items2"][i]);
			tasks2.push_back(t);
		}
		p1 = tasks1.size();
		p2 = p1+1;
		p3 = p2 + tasks2.size();
		p4 = p3 + 1;

	}
	bool perform(ChatType chat_id, string text) {
		if (chat_id == my_chat) {
			specialPerform(text);
		}
		else {
			checkChat(chat_id);
			bool complete = getTask().performResponce(chat_id, text);
			if (complete) {
				skip();
			}
		}
		
		if (task > p4) {
			deinit();
			return true;
		}
		return false;
	}
	void init(ChatType chat_id, string text) {
		if (chat_id == my_chat) {
			specialPerform(text);
			return;
		}
		chats.push_back(chat_id);
		getTask().init(chat_id);
	}
};

