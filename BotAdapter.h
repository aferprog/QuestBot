#pragma once
#include <tgbot/tgbot.h>
#include <string>
#include "MessageSet.h"
#include <random>

using namespace std;
using namespace TgBot;

using ChatType  = int64_t;

class BotAdapter
{
	Bot* bot;
public:
	BotAdapter() = default;
	BotAdapter(string token){
		bot = new Bot(token);
	}

	int getRandomNumber(int min, int max) {
		// Создайте генератор случайных чисел
		std::random_device rd;
		std::mt19937 gen(rd()); // Используйте Mersenne Twister engine (MT19937)

		// Создайте распределение
		std::uniform_int_distribution<int> distribution(min, max);

		// Генерируйте случайное число и верните его
		return distribution(gen);
	}

	Bot& getBot() {
		return *bot;
	}
	Bot& operator()() {
		return *bot;
	}

	void init(string token) {
		bot = new Bot(token);
	}

	void sendMessage(ChatType chat_id, string text) {
		bot->getApi().sendMessage(chat_id, text, false, 0);
	}
	void SleepMilliseconds(int milliseconds) {
		std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
	}
	void sendManyMessages(ChatType chat_id, MessageSet &msg) {
		while (!msg.getSource().empty()) {
			SleepMilliseconds(1000);
			sendMessage(chat_id, msg.getSource().front());
			msg.getSource().pop();
		}
	}

};

// BotAdapter bot;