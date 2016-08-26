v#include "shell.h"



void setup() {
   Serial.begin(115200);
   SHELL_printHelp();
}

void loop() {
    SHELL_process();
}
