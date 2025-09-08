#ifndef WEBHANDLERS_H
#define WEBHANDLERS_H

#include <WebServer.h>

extern WebServer server;
extern const char INDEX_HTML[] PROGMEM;

void handleRoot();
void handleForward();
void handleBackward();
void handleLeft();
void handleRight();
void handleStop();
void handleSpeed();
void handleNotFound();

#endif
