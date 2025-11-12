/* os_tasks.c - using OSA mutex (mutex_t) to protect LED HAL */

#include "Cpu.h"
#include "Events.h"
#include "os_tasks.h"

#include "FreeRTOS.h"
#include "task.h"

#include "ledrgb_hal.h"
#include "fsl_debug_console.h"

#ifndef pdMS_TO_TICKS
#define pdMS_TO_TICKS(ms) ((TickType_t)((((TickType_t)(ms) * (TickType_t)configTICK_RATE_HZ) + 500u) / 1000u))
#endif

/* Use the same mutex object declared in main.c */
extern mutex_t ledMutex;

/* small wrappers for readability */
static inline void led_mutex_lock(void)
{
    /* block forever until we get the mutex */
    (void)OSA_MutexLock(&ledMutex, OSA_WAIT_FOREVER);
}
static inline void led_mutex_unlock(void)
{
    (void)OSA_MutexUnlock(&ledMutex);
}

/* Task1 */
void Task1_task(os_task_param_t task_init_data)
{
    typedef enum { STATE_RED_ON, STATE_RED_OFF } fsm1_state_t;
    fsm1_state_t currentState = STATE_RED_ON;

    ledrgb_init();

#ifdef PEX_USE_RTOS
    while (1) {
#endif
        switch (currentState) {
            case STATE_RED_ON:
                led_mutex_lock();
                ledrgb_setRedLed();
                led_mutex_unlock();

                vTaskDelay(pdMS_TO_TICKS(500));

                currentState = STATE_RED_OFF;
                break;

            case STATE_RED_OFF:
                led_mutex_lock();
                ledrgb_clearRedLed();
                led_mutex_unlock();

                vTaskDelay(pdMS_TO_TICKS(500));
                currentState = STATE_RED_ON;
                break;

            default:
                currentState = STATE_RED_ON;
                break;
        }
#ifdef PEX_USE_RTOS
    }
#endif
}

/* Task2 */
void Task2_task(os_task_param_t task_init_data)
{
    typedef enum { STATE_GREEN_ON, STATE_GREEN_OFF } fsm2_state_t;
    fsm2_state_t currentState = STATE_GREEN_ON;

    ledrgb_init();

#ifdef PEX_USE_RTOS
    while (1) {
#endif
        switch (currentState) {
            case STATE_GREEN_ON:
                led_mutex_lock();
                ledrgb_setGreenLed();
                led_mutex_unlock();

                vTaskDelay(pdMS_TO_TICKS(300));
                currentState = STATE_GREEN_OFF;
                break;

            case STATE_GREEN_OFF:
                led_mutex_lock();
                ledrgb_clearGreenLed();
                led_mutex_unlock();

                vTaskDelay(pdMS_TO_TICKS(300));
                currentState = STATE_GREEN_ON;
                break;

            default:
                currentState = STATE_GREEN_ON;
                break;
        }
#ifdef PEX_USE_RTOS
    }
#endif
}
