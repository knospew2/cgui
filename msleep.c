#include "msleep.h"

void msleep(int milliseconds) {
    struct timespec time;
    time.tv_sec = milliseconds / 1000;
    time.tv_nsec = milliseconds * 1000000;
    nanosleep(&time, NULL);
}

