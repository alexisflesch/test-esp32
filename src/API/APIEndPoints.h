#ifndef APIENDPOINTS_H
#define APIENDPOINTS_H

#include <ESPAsyncWebServer.h>

extern AsyncWebServer server; // Declare server as extern

void setupApiEndpoints(AsyncWebServer &server);

#endif