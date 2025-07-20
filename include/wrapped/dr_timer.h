#ifndef DR_TIMER_WRAPPED_H_
#define DR_TIMER_WRAPPED_H_

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/// @brief Opaque handle to the timer object
typedef struct DRTimerHandle DRTimerHandle;

/// @brief Creates a new timer instance.
/// @return Pointer to the timer instance, or NULL on failure.
DRTimerHandle* dr_timer_create(void);

/// @brief Destroys a timer instance and frees resources.
/// @param timer Pointer to the timer instance.
void dr_timer_destroy(DRTimerHandle* timer);

/// @brief Initializes the timer with a specified interval in milliseconds.
/// @param timer Pointer to the timer instance.
/// @param ms The interval of the timer in milliseconds.
void dr_timer_init(DRTimerHandle* timer, int ms);

/// @brief Handles timer interrupt events.
/// @param timer Pointer to the timer instance.
/// @return True if an interrupt occurred, false otherwise.
bool dr_timer_interrupt(DRTimerHandle* timer);

/// @brief Calculates the current time relative to a given start time.
/// @param timer Pointer to the timer instance.
/// @param start_time The start time to calculate the relative time from.
/// @return The relative time from the given start time in seconds.
double dr_timer_get_interval_time(DRTimerHandle* timer, double start_time);

/// @brief Gets the current system time in seconds.
/// @param timer Pointer to the timer instance.
/// @return The current system time in seconds.
double dr_timer_get_current_time(DRTimerHandle* timer);

#ifdef __cplusplus
}
#endif

#endif /* DR_TIMER_H_ */