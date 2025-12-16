#ifndef CLOWNZ80_DISASSEMBLER_H
#define CLOWNZ80_DISASSEMBLER_H

#include <stddef.h>

#include "clowncommon/clowncommon.h"

typedef void (*ClownZ80_PrintCallback)(void *user_data, const char *format, ...);

cc_bool ClownZ80_Disassemble(const unsigned char *machine_code, size_t *bytes_read, ClownZ80_PrintCallback print_callback, const void *user_data);

#endif /* CLOWNZ80_DISASSEMBLER_H */
