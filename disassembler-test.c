#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "clowncommon/clowncommon.h"

#include "disassembler.h"

static cc_bool FileToBuffer(const char* const file_path, unsigned char** const file_buffer, size_t* const file_size)
{
	cc_bool success = cc_false;
	FILE* const file = fopen(file_path, "rb");

	if (file == NULL)
	{
		fprintf(stderr, "Could not open file '%s'.", file_path);
	}
	else
	{
		fseek(file, 0, SEEK_END);
		*file_size = ftell(file);
		rewind(file);
		*file_buffer = (unsigned char*)malloc(*file_size);

		if (*file_buffer == NULL)
		{
			fprintf(stderr, "Could not allocate buffer for file '%s'.", file_path);
		}
		else
		{
			fread(*file_buffer, 1, *file_size, file);
			success = cc_true;
		}

		fclose(file);
	}

	return success;
}

static void PrintCallback(void* const user_data, const char* const format, ...)
{
	va_list args;

	(void)user_data;

	va_start(args, format);
	vfprintf(stdout, format, args);
	va_end(args);
}

int main(const int argc, char** const argv)
{
	unsigned char *file_buffer;
	size_t file_size;
	long index = 0;
	size_t bytes_read;

	FileToBuffer(argv[1], &file_buffer, &file_size);

	sscanf(argv[2], "%X", &index);

	while (ClownZ80_Disassemble(&file_buffer[index], &bytes_read, PrintCallback, NULL))
		index += bytes_read;

	free(file_buffer);

	return EXIT_SUCCESS;
}
