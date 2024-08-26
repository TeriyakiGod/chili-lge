#ifndef SERVER_HPP
#define SERVER_HPP

#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>
#include <LittleFS.h>
#include "settings.h"

extern const char *ssid;
extern const char *password;
extern const char *host;

extern ESP8266WebServer server;
extern ESP8266HTTPUpdateServer httpUpdater;
extern File fsUploadFile;

void startServer();
void handleFileList();
void handleFileUpload();
void handleFileDelete();
void handleRoot();
void serverSetup();
void serverLoop();

#endif // SERVER_HPP
