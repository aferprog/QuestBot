#include "QuickTask.h"

extern BotAdapter bot;

void QuickTask::init(ChatType chat_id)
{
    chat = chat_id;
    bot.sendManyMessages(chat_id, messages);
}

bool QuickTask::performResponce(ChatType chat_id, string text)
{
    constexpr double t = 12000;
    if (is_began) {
        double duration = (static_cast<double>(clock() - start) / CLOCKS_PER_SEC) * 1000.0;
        count++;

        if (duration > t) {
            if (count == 25 || count == 26) {
                bot.sendManyMessages(chat, messages_end);
                return true;
            }
            bot.sendMessage(chat, std::to_string(count));
            bot.sendMessage(chat, tips.next());
            
            is_began = false;
        }
    }
    else {
        if (chat_id != chat)
            return false;
        is_began = true;
        count = 0;
        bot.SleepMilliseconds(bot.getRandomNumber(500, 2000));
        bot.sendMessage(chat, signs.next());
        start = clock();
    }
    return false;
}
