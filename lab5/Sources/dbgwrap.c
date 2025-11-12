/* dbgwrap.c - wrapper minimal para satisfazer o símbolo DbgConsole_Printf
   Chama vprintf, então o envio depende do retarget do printf (geralmente o PE/jlink/SDK faz o redirecionamento).
*/

#include <stdarg.h>
#include <stdio.h>

int DbgConsole_Printf(const char *fmt, ...)
{
    int ret;
    va_list args;
    va_start(args, fmt);
    ret = vprintf(fmt, args); /* vprintf usa implementação de printf do newlib (retarget necessário) */
    va_end(args);
    return ret;
}
