#!/usr/bin/env python
# -*- coding: utf-8 -*-
# This program is dedicated to the public domain under the CC0 license.

"""
First, a few callback functions are defined. Then, those functions are passed to
the Dispatcher and registered at their respective places.
Then, the bot is started and runs until we press Ctrl-C on the command line.
Usage:
Example of a bot-user conversation using ConversationHandler.
Send /start to initiate the conversation.
Press Ctrl-C on the command line or send a signal to the process to stop the
bot.
"""

import logging
import csv
import psycopg2  # to work with postgrSQL

from telegram import ReplyKeyboardMarkup
from telegram.ext import (Updater, CommandHandler, MessageHandler, Filters,
                          ConversationHandler)
# I use proxy for my bot						  
REQUEST_KWARGS={
    'proxy_url': '...',
	'urllib3_proxy_kwargs': {	    
        'username': '...',
        'password': '...'
    }
}

#@bot.message_handler(content_types=['text'])
# def get_text_messages(message):

# Enable logging
logging.basicConfig(format='%(asctime)s - %(name)s - %(levelname)s - %(message)s',
                    level=logging.INFO)

logger = logging.getLogger(__name__)

CHOOSING, TYPING_REPLY, TYPING_CHOICE = range(3)

reply_keyboard = [['Pizza', 'VOK'],
                  ['Rolls', 'Sets','Something else...'],
                  ['Done']]


# this object is a keyboard, one_time_keyboard hides the keyboard if true
				  
markup = ReplyKeyboardMarkup(reply_keyboard, one_time_keyboard=True)



# 

def facts_to_str(user_data):
    facts = list()  
       
    for key, value in user_data.items():
        facts.append('{} - {}'.format(key, value))
     
    return "\n".join(facts).join(['\n', '\n'])


	# our Greetings after /start

def start(update, context):
    
    update.message.reply_text(
        "Hello! \n I'm from Food Band team. A clever bot that can help you to make a choice! "
        "Why don't you tell me what food you prefer?",
        reply_markup=markup)

    return CHOOSING

# we use it to pass information about ordinary orders
def regular_choice(update, context):
    
    
    # our text field is absolutely the same as database column name
    text = update.message.text
    
    context.user_data['choice'] = text
    update.message.reply_text(
        '{}? The wonderful choice! I imagine how tasty it will be. Please, choose the one you like'.format(text.capitalize()))
	
    
    try:
        conn = psycopg2.connect(dbname='Pizza_bot', user='Kate', password='123456', host='localhost')
    except:
	    print("I am unable to connect to the database")	
    cursor = conn.cursor()
        # Select new order to database    
    try:
        cursor.execute("SELECT product FROM products WHERE product_type = (%s)", [text])
        reply_keyboard_pizza = cursor.fetchall()
		
    except:
	    print("I could not insert into database")
    cursor.close()
    conn.close()
 # I make a keyboard with the types of concrete product and suggest user to choose it
    markup_pizza = ReplyKeyboardMarkup(reply_keyboard_pizza, one_time_keyboard=True)
    update.message.reply_text('Please, choose the one you like',reply_markup=markup_pizza)
	
    return TYPING_REPLY


def custom_choice(update, context):
    update.message.reply_text('Please send me what you want, '
                              'for example "Fresh drinks"')
    text = update.message.text
    context.user_data['choice'] = text
    update.message.reply_text(
        'Our manager will connect with you about this possibility.'.format(text.capitalize()))

    user_data = context.user_data
    print ("custom_choice", user_data)
    return TYPING_REPLY


def received_information(update, context):
    user_data = context.user_data
    text = update.message.text
    category = user_data['choice']
    user_data[category] = text
    print ("custom_choice", user_data)
    del user_data['choice']

    update.message.reply_text("Just so you know, this is what you already told me:"
                              "{}".format(facts_to_str(user_data)),
                              reply_markup=markup)
    return CHOOSING


def done(update, context):
    user_data = context.user_data
	
	# to have user's information
    user = update.message.from_user
    print("user id =",user['id'])
    print("user first_name =",user['first_name'])
	
	#I decided to use message_id as order_id
    order_id = update.message.message_id
    order_date = update.message.date
    order_location = update.message.location
    print ("message_id =", order_id)
    print ("order_date =", order_date)
    print ("order_location =", order_location)
	# write into file this time item = type, user_data[item] - name
    file = open('Band.txt','a')	
    for item in user_data:
        file.write (item + user_data[item] + '\n')
    file.close()
    print("1:", user_data)
# My integration with database
    try:
        conn = psycopg2.connect(dbname='Pizza_bot', user='Kate', password='123456', host='localhost')
    except:
	    print("I am unable to connect to the database")
	
    cursor = conn.cursor()
    for item in user_data:
        print("item", item)
        if item == 'Something else...':
            try:
                cursor.execute('INSERT INTO order_details (product_type, product, order_id, price) VALUES (%s, %s, %s, %s)', ["Something else...", user_data[item], order_id, 0])
                conn.commit()
                print("I insert into order_details", item, user_data[item], order_id)
            except:
	            print("I could not insert into database order_details 1")
			    
	
# Insert new order to database    
    sum = 0    
    try:
        for item in user_data:            
            if item == "Pizza" or item == "VOK" or item == "Rolls" or item == "Sets":
                cursor.execute("SELECT price FROM products WHERE product=(%s)", [user_data[item]])
                prod = cursor.fetchone()
                price = prod [0]
                sum = sum + price
             #print ("price", price)
                cursor.execute('INSERT INTO order_details (product_type, product, order_id, price) VALUES (%s, %s, %s, %s)', [item, user_data[item], order_id, price])
                conn.commit()
    except:
	    print("I could not insert into database 2")
    try:
	# insert order into orders table
        cursor.execute('INSERT INTO orders (user_id, order_id, check_sum, payment_method, order_date) VALUES (%s, %s, %s, %s, %s)', [user['id'], order_id, sum, 0, order_date])
        print ("INSERT INTO orders - Sucess") 
	# insert user into orders table if we have no this user. We have a list of turples
        list_id = []
        cursor.execute("SELECT id from users")
        list_id = cursor.fetchall()
        
        check_id = 1
        for item in list_id:  # I use loop to detect if we have this user in our users table
            if item[0] == user['id']:
                check_id = 0
                break				
        if check_id != 0:
            cursor.execute('INSERT INTO users (id, name, location) VALUES (%s, %s, %s)', [user['id'], user['first_name'], order_location])
        print ("INSERT INTO users - Sucess") 
        conn.commit()
    except:
	    print("I could not insert into database 3")
   
    cursor.execute("SELECT * FROM orders WHERE user_id = (%s) AND order_id = (%s) AND order_date = (%s)", [user['id'], order_id,order_date])
    rows = cursor.fetchall()
    row = rows[0]
    print("row", row)
    

    cursor.close()
    conn.close()
    print("context.user_data", context.user_data)
    if 'choice' in user_data:
        del user_data['choice']

    update.message.reply_text("So, your order is next:"
                              "{}".format(facts_to_str(user_data)))
    
    str(sum)
    update.message.reply_text("Summary for: ""{}".format(sum))
    
    update.message.reply_text("Until next time! Type /start to make a new order")
    user_data.clear()
    order_id = 0
    return ConversationHandler.END


def error(update, context):
    """Log Errors caused by Updates."""
    logger.warning('Update "%s" caused error "%s"', update, context.error)


def main():
    # Create the Updater and pass it your bot's token.
    # Make sure to set use_context=True to use the new context based callbacks
    # Post version 12 this will no longer be necessary
    updater = Updater("...", use_context=True)
    
    # Get the dispatcher to register handlers
    dp = updater.dispatcher

    # Add conversation handler with the states CHOOSING, TYPING_CHOICE and TYPING_REPLY
    conv_handler = ConversationHandler(
        
        entry_points=[CommandHandler('start', start)],
		

        states={
            CHOOSING: [MessageHandler(Filters.regex('^(Pizza|VOK|Rolls|Sets)$'),
                                      regular_choice),
                       MessageHandler(Filters.regex('^Something else...$'),
                                      custom_choice)
                       ],

            TYPING_CHOICE: [MessageHandler(Filters.text,
                                           regular_choice)
                            ],

            TYPING_REPLY: [MessageHandler(Filters.text,
                                          received_information),
                           ],
        },

        fallbacks=[MessageHandler(Filters.regex('^Done$'), done)]
    )

    dp.add_handler(conv_handler)

    # log all errors
    dp.add_error_handler(error)

    # Start the Bot
    updater.start_polling()

    # Run the bot until you press Ctrl-C or the process receives SIGINT,
    # SIGTERM or SIGABRT. This should be used most of the time, since
    # start_polling() is non-blocking and will stop the bot gracefully.
    print ("To make an order, please enter '/start' ")
    updater.idle()


if __name__ == '__main__':
    main()