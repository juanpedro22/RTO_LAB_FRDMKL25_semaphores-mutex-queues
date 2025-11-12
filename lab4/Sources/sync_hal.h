/* sync_hal.h - Cabeçalho de sincronização para LED HAL
 *
 * Inclui FreeRTOS.h antes de semphr.h para evitar o erro de ordem de includes.
 */

#ifndef SYNC_HAL_H
#define SYNC_HAL_H

/* FreeRTOS.h deve aparecer ANTES de semphr.h e queue.h */
#include "FreeRTOS.h"

#ifdef USE_MUTEX
  #include "fsl_os_abstraction.h" /* mutex_t e OSA prototypes */
  extern mutex_t ledMutex;
  void led_lock(void);
  void led_unlock(void);
#else
  #include "semphr.h"            /* depende de FreeRTOS.h estar incluído antes */
  extern SemaphoreHandle_t ledSema;
  void led_signal(void); /* para Task1 -> Task2 (give) */
  void led_wait(void);   /* para Task2 -> espera (take) */
#endif /* USE_MUTEX */

#endif /* SYNC_HAL_H */
