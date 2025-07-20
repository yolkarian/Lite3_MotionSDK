#include "dr_timer.h"
#include <stdlib.h>

// Include the original C++ header
#include "dr_timer_.h" // Assuming the original DRTimer class is in this header

// Define the DRTimer struct as an opaque type that wraps the C++ DRTimer class
struct DRTimerHandle {
    DRTimer* impl; // Pointer to the actual C++ DRTimer object
};

DRTimerHandle* dr_timer_create(void) {
    DRTimerHandle* timer = (DRTimerHandle*)malloc(sizeof(DRTimerHandle));
    if (!timer) {
        return NULL;
    }
    timer->impl = new ::DRTimer();
    if (!timer->impl) {
        free(timer);
        return NULL;
    }
    return timer;
}

void dr_timer_destroy(DRTimerHandle* timer) {
    if (timer && timer->impl) {
        delete timer->impl;
        timer->impl = NULL;
    }
    free(timer);
}

void dr_timer_init(DRTimerHandle* timer, int ms) {
    if (timer && timer->impl) {
        timer->impl->TimeInit(ms);
    }
}

bool dr_timer_interrupt(DRTimerHandle* timer) {
    if (timer && timer->impl) {
        return timer->impl->TimerInterrupt();
    }
    return false;
}

double dr_timer_get_interval_time(DRTimerHandle* timer, double start_time) {
    if (timer && timer->impl) {
        return timer->impl->GetIntervalTime(start_time);
    }
    return 0.0;
}

double dr_timer_get_current_time(DRTimerHandle* timer) {
    if (timer && timer->impl) {
        return timer->impl->GetCurrentTime();
    }
    return 0.0;
}