#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <string>
#include <vector>
#include "JsonFunctions.h"
#include "BotAdapter.h"

#include "GeneralQuest.h"


ChatType my_chat = 479799067;
BotAdapter bot;

int main() {


    json doc = json::parse(Different::ReadFileToString("Quest.json"));

    string token = "1368992915:AAGQ_pMBwlWy7_HwKxpfAthFe9i78hKkI5Y";
    printf("Token: %s\n", token.c_str());

    bot.init(token);
    GeneralQuest gq(doc);

    bool flag=false;

    string deny = doc["if_closed"];
    bool is_open = true;
    bot().getEvents().onAnyMessage([&gq, &flag, &deny, &is_open](Message::Ptr message) {
        // return;
        printf("User wrote: %s\n", message->text.c_str());

        if (message->chat->id == my_chat && message->text == "Gate") {
            is_open = !is_open;
            return;
        }

        if (!is_open) {
            bot.sendMessage(message->chat->id, deny);
            return;
        }
        
        if (StringTools::startsWith(message->text, "/start") && !flag) {
            gq.init(message->chat->id, message->text);
            flag = true;
            return;
        }
        
        gq.perform(message->chat->id, message->text);
    });


    try {
        printf("Bot username: %s\n", bot.getBot().getApi().getMe()->username.c_str());
        bot.getBot().getApi().deleteWebhook();

        TgLongPoll longPoll(bot.getBot());
        while (true) {
            printf("Long poll started\n");
            longPoll.start();
        }
    }
    catch (exception& e) {
        printf("error: %s\n", e.what());
    }

    return 0;
}