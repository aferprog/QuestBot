#pragma once
#include "JsonFunctions.h"

using namespace std;
using json = nlohmann::json;

class MessageSet
{
	string last="";
	queue<string> msgs;
public:
	MessageSet(const json& json_arr) {
		msgs = Different::jsonToQueue(json_arr);
	}
	void add(string text) {
		msgs.push(text);
	}
	string next() {
		if (msgs.size() > 0)
		{
			last = msgs.front();
			msgs.pop();
			return last;
		}
		else
			return last;
	}
	queue<string>& getSource() {
		if (!msgs.empty())
			last = msgs.back();
		return msgs;
	}
};