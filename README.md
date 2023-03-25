
# AutoMuster

To send a text message in C, you'll need to use an SMS gateway API since C doesn't have built-in support for sending text messages. I'll provide an example using the Twilio API. First, sign up for a Twilio account and obtain your API credentials (Account SID, Auth Token, and phone number).

Install the libcurl library (to make HTTP requests) and libjson-c (to parse JSON data). On Ubuntu, you can use:

    `sudo apt-get install libcurl4-openssl-dev libjson-c-dev`

**Compile the code**

    gcc -o send_sms send_sms.c -lcurl -ljson-c

**Run the compiled binary**

    ./send_sms

This program will keep running and check the time every 10 seconds. When the time reaches 7:30 AM, it will send the "alive" message to the specified recipient's phone number using the Twilio API. After sending the message, the program will wait for a minute before checking the time again to prevent multiple messages from being sent at the same time.

Please note that this example assumes you have a working internet connection and you have set the correct API credentials and phone numbers in the code. Also, make sure to replace the placeholders with your actual Twilio Account SID, Auth Token, Twilio phone number, and the recipient's phone number.


