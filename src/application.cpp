#if defined(PARTICLE)
#include "application.h"
#else
#include <stdio.h>
#include <stdint.h>
#endif

#include "synth/synth.h"

Synth synth;

void setup() {
	synth.begin();
}

void loop() {}

#if !defined(PARTICLE)
int main(int argc, char **argv) {
	printf("ps-01 starting...\n");
	setup();
	printf("--> running...\n");
}
#endif
