#include "MyBot.h"
#include <dpp/dpp.h>

/* Be sure to place your token in the line below.
 * Follow steps here to get a token:
 * https://dpp.dev/creating-a-bot-application.html
 * When you invite the bot, be sure to invite it with the
 * scopes 'bot' and 'applications.commands', e.g.
 * https://discord.com/oauth2/authorize?client_id=940762342495518720&scope=bot+applications.commands&permissions=139586816064
 */
const std::string    BOT_TOKEN = "YOUR TOKEN";

const dpp::snowflake source_channel_id = 11111111111; // Change to your source channels ID. This will be the channel that messages get copied from

const std::vector<dpp::snowflake> target_channel_ids = { 1111111111 }; //Add your target channels. These will be the channels the messages get copied too.


int main() {
	/* Create the bot, but with our intents so we can use messages. */
	dpp::cluster bot(BOT_TOKEN, dpp::i_default_intents | dpp::i_message_content);

	bot.on_log(dpp::utility::cout_logger());

	bot.on_message_create([&bot](const dpp::message_create_t& event) {
		if (event.msg.channel_id == source_channel_id)
		{
			std::cout << "Message source: " << event.msg.channel_id << std::endl;

			for (const auto& target_channel_id : target_channel_ids)
			{
				dpp::message msg(target_channel_id, event.msg.content);
				bot.message_create(msg);
			}
		}
		});

	bot.start(dpp::st_wait);

	return 0;
}