
import telebot
bot = telebot.TeleBot('Token')

@bot.message_handler(content_types=['text'])



def get_text_messages(message):
	if message.text == "Привет":
		bot.send_message(message.from_user.id, "Привет, чем я могу тебе помочь?")
	elif message.text == "/help":
		bot.send_message(message.from_user.id, "Напиши привет")
	else:
		bot.send_message(message.from_user.id, "Я тебя не понимаю. Напиши /help.")
		
bot.polling()
#!/usr/bin/python

# This is a simple echo bot using the decorator mechanism.
# It echoes any incoming text messages.