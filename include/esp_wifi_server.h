#ifndef SERVER_HPP
#define SERVER_HPP

#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>
#include <LittleFS.h>
#include "settings.h"

const char *ssid = APSSID;
const char *password = APPSK;
const char *host = APHOST;

ESP8266WebServer server(80);
ESP8266HTTPUpdateServer httpUpdater;
File fsUploadFile;

void startServer();
void handleFileList();
void handleFileUpload();
void handleFileDelete();
void handleRoot();
void serverSetup();
void serverLoop();

#endif // SERVER_HPP
