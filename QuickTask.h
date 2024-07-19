#pragma once
#include "Task.h"
#include "MessageSet.h"
#include <chrono>

class QuickTask: public Task
{
	MessageSet messages, signs, tips, messages_end;
	int count = 0;
	bool is_began = false;
	clock_t start;
public:
	QuickTask(const json &doc)
		: messages(doc["message"]), signs(doc["signs"]), tips(doc["tips"]), messages_end(doc["message1"])
	{}


	// Inherited via Task
	virtual void init(ChatType chat_id) override;

	virtual bool performResponce(ChatType chat_id, string text) override;

};

