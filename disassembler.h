#ifndef CLOWNZ80_DISASSEMBLER_H
#define CLOWNZ80_DISASSEMBLER_H

#include <stddef.h>

#include "clowncommon/clowncommon.h"

typedef unsigned char (*ClownZ80_ReadCallback)(void *user_data);
typedef void (*ClownZ80_PrintCallback)(void *user_data, const char *format, ...);

cc_bool ClownZ80_Disassemble(ClownZ80_ReadCallback read_callback, ClownZ80_PrintCallback print_callback, const void *user_data);

#endif /* CLOWNZ80_DISASSEMBLER_H */
