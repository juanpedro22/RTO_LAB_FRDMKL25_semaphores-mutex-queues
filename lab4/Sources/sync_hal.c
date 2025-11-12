/* sync_hal.c - Implementação das wrappers de sincronização.
 *
 * Compile este arquivo junto com main.c e os_tasks.c.
 */

#include "FreeRTOS.h"   /* garante tipos como TickType_t, BaseType_t */
#include "task.h"       /* pode ser útil se usar API de tarefas */
#include "sync_hal.h"

#ifdef USE_MUTEX

/* Mutex (OSA) mode */
mutex_t ledMutex; /* instância definida aqui */

void led_lock(void)
{
    (void)OSA_MutexLock(&ledMutex, OSA_WAIT_FOREVER);
}

void led_unlock(void)
{
    (void)OSA_MutexUnlock(&ledMutex);
}

#else

/* Semaphore (FreeRTOS) mode */
SemaphoreHandle_t ledSema = NULL; /* instância definida aqui */

void led_signal(void)
{
    /* Damos o semáforo (ignorar retorno para simplicidade) */
    (void)xSemaphoreGive(ledSema);
}

void led_wait(void)
{
    (void)xSemaphoreTake(ledSema, portMAX_DELAY);
}

#endif /* USE_MUTEX */
