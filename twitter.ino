#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <TwitterWebAPI.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <iostream>
#include <ctime>
#include <string>

using namespace std;

const char *ntp_server = "0.fr.pool.ntp.org";
int timezone = +2; // EU Central timezone +02:00 HRS

// Wifi info
const char* ssid = "my wifi ssid";
const char* password = "my wifi password";

// Token twitter
static char const consumer_key[] = "EUsirQhYkrDs9zgAcBMEnDa4L";
static char const consumer_sec[] = "5NgCEsoL58gFKNzmQEHTeMz2eMbtYzK54faRwFjC151yRctyou";
static char const accesstoken[] = "01247123818251984898-i6dGtl1Xvsk71q2guXpurALsommiaT";
static char const accesstoken_sec[] = "MOvIb42kE0kyiOzc1jJcQnZf7lyKb6O4bR8suBteUHmwl";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, ntp_server, timezone * 3600, 1000 * 60);  // NTP server pool, offset (in seconds), update interval (in milliseconds)
TwitterClient tcr(timeClient, consumer_key, consumer_sec, accesstoken, accesstoken_sec);

tcr.startNTP(); // Start NTP connection with Twitter's API

void setup_wifi() {
  delay(10);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() { }

void loop() {
  if (true) // TODO: if letterbox is open
    time_t now = time(0);
    tm *ltm = localtime(&now);

    int hours = timezone + ltm->tm_hour;
    int minutes = ltm->tm_min;
    string time = to_string(hours) + "h" + (minutes < 10 ? "0" + to_string(minutes) : to_string(minutes));

    string twitter_post_msg = "@FraigneauLucas tu as reçu une lettre à: " + time + " ouvre la vite!";
    tcr.tweet(twitter_post_msg);
}