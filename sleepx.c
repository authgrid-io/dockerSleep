// sleepx.c - sleep forever (default) or for N seconds; accepts "sleep 3600" style.
#define _GNU_SOURCE
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>   // <-- needed for strcmp
#include <time.h>
#include <unistd.h>

static void sleep_forever(void) {
    for (;;) pause();  // waits for signals, near-zero CPU
}

int main(int argc, char **argv) {
    // Support "sleep 3600" style
    if (argc > 1 && argv[1] && argv[1][0] != '\0' && strcmp(argv[1], "sleep") == 0) {
        argv++; argc--;
    }

    if (argc < 2) {   // default: sleep forever
        sleep_forever();
        return 0;
    }

    char *end = NULL;
    long long secs = strtoll(argv[1], &end, 10);
    if (end && *end == '\0' && secs >= 0) {
        struct timespec req = {.tv_sec = (time_t)secs, .tv_nsec = 0};
        while (nanosleep(&req, &req) == -1 && errno == EINTR) { }
        return 0;
    }

    fprintf(stderr, "Invalid argument: %s (use integer seconds or no args for infinity)\n", argv[1]);
    return 2;
}