#if defined(PARTICLE)
#include "application.h"
#else
#include <stdio.h>
#include <sys/signal.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

#endif

#include "synth/synth.h"

Synth synth;

void setup() {
	synth.begin();
}

void loop() {}

#if !defined(PARTICLE)
void exit_handler(int s){
    printf("(i) exiting\n");
    exit(1);

}

int main(int argc, char **argv) {
	printf("\033[1;31m~~~ ps-01 synthesizer ~~~\033[0m\n\n");
	setup();
	printf("(i) running...\n");

    // Stopping on Ctrl+C
    struct sigaction sigIntHandler;

    sigIntHandler.sa_handler = exit_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;

    sigaction(SIGINT, &sigIntHandler, NULL);

    pause();

    return 0;
}
#endif
