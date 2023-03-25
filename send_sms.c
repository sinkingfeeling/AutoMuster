#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <json-c/json.h>
#include <time.h>

// Replace these with your Twilio Account SID, Auth Token, and phone number
#define ACCOUNT_SID "your_account_sid"
#define AUTH_TOKEN "your_auth_token"
#define TWILIO_PHONE_NUMBER "your_twilio_phone_number"

// Receiver phone number
#define TO_PHONE_NUMBER "receiver_phone_number"

void send_sms(const char *to, const char *from, const char *body) {
    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        char url[256];
        snprintf(url, sizeof(url), "https://api.twilio.com/2010-04-01/Accounts/%s/Messages.json", ACCOUNT_SID);

        char auth_header[128];
        snprintf(auth_header, sizeof(auth_header), "Authorization: Basic %s", AUTH_TOKEN);

        char payload[512];
        snprintf(payload, sizeof(payload), "To=%s&From=%s&Body=%s", to, from, body);

        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, auth_header);
        headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload);
        curl_easy_setopt(curl, CURLOPT_USERPWD, ACCOUNT_SID ":" AUTH_TOKEN);
        curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "SMS sending failed: %s\n", curl_easy_strerror(res));
        } else {
            printf("SMS sent successfully.\n");
        }

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }

    curl_global_cleanup();
}

int main() {
    time_t raw_time;
    struct tm *time_info;

    while (1) {
        time(&raw_time);
        time_info = localtime(&raw_time);

        // Check if it's 7:30 AM
        if (time_info->tm_hour == 7 && time_info->tm_min == 30) {
            send_sms(TO_PHONE_NUMBER, TWILIO_PHONE_NUMBER, "alive");
            sleep(60); // Wait a minute to avoid multiple messages
        }
        sleep(10); // Check time every 10 seconds
    }

    return 0;
}
