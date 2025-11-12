/* os_tasks.c - com DbgConsole_Printf para timestamps */

#include "Cpu.h"
#include "Events.h"
#include "os_tasks.h"

/* FreeRTOS headers */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* HAL for LEDs */
#include "ledrgb_hal.h"

/* Debug console */
#include "fsl_debug_console.h"

/* Fallback pdMS_TO_TICKS se não definido */
#ifndef pdMS_TO_TICKS
#define pdMS_TO_TICKS(ms) ((TickType_t)((((TickType_t)(ms) * (TickType_t)configTICK_RATE_HZ) + 500u) / 1000u))
#endif

/* Semáforo definido em main.c */
extern SemaphoreHandle_t ledSema;

/*
 * Task1: pisca LED vermelho e dá semáforo para Task2, com log
 */
void Task1_task(os_task_param_t task_init_data)
{
    typedef enum {
        STATE_RED_ON,
        STATE_RED_OFF
    } fsm1_state_t;

    fsm1_state_t currentState = STATE_RED_ON;

    /* Inicializa hardware (idempotente) */
    ledrgb_init();

#ifdef PEX_USE_RTOS
    while (1) {
#endif
        switch (currentState) {
            case STATE_RED_ON:
                ledrgb_setRedLed();

                vTaskDelay(pdMS_TO_TICKS(500));

                /* Transição e sinalização */
                currentState = STATE_RED_OFF;
                (void)xSemaphoreGive(ledSema);
                break;

            case STATE_RED_OFF:
                ledrgb_clearRedLed();

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

/*
 * Task2: espera semáforo e pisca LED verde por um ciclo, com log
 */
void Task2_task(os_task_param_t task_init_data)
{
    typedef enum {
        STATE_GREEN_ON,
        STATE_GREEN_OFF
    } fsm2_state_t;

    fsm2_state_t currentState = STATE_GREEN_ON;

    /* Inicializa hardware (idempotente) */
    ledrgb_init();

#ifdef PEX_USE_RTOS
    while (1) {
#endif
        /* Bloqueia até receber sinal de Task1 */
        if (xSemaphoreTake(ledSema, portMAX_DELAY) == pdTRUE) {
            switch (currentState) {
                case STATE_GREEN_ON:
                    ledrgb_setGreenLed();
                    vTaskDelay(pdMS_TO_TICKS(300));
                    currentState = STATE_GREEN_OFF;
                    break;

                case STATE_GREEN_OFF:
                    ledrgb_clearGreenLed();
                    vTaskDelay(pdMS_TO_TICKS(300));
                    currentState = STATE_GREEN_ON;
                    break;

                default:
                    currentState = STATE_GREEN_ON;
                    break;
            }
            /* Não repostamos aqui; Task1 controla os posts. */
        } else {
            /* Não esperado com portMAX_DELAY */
        }
#ifdef PEX_USE_RTOS
    }
#endif
}
