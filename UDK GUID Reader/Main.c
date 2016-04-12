/**
 * Copyright (C) 2016 Jessica James.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * Written by Jessica James <jessica.aj@outlook.com>
 */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdint.h>

int main(int argc, const char **args)
{
	const char *filename;
	FILE *file;
	uint32_t GUID[4];

	if (argc < 2 || strcmp(args[1], "-help") == 0 || strcmp(args[1], "/?") == 0)
	{
		puts("<map name>");
		return 0;
	}

	filename = args[1];

	file = fopen(filename, "rb");
	if (file == NULL)
	{
		puts("ERROR: UNABLE TO OPEN FILE.");
		return 0;
	}

	// seek to string size
	fseek(file, 0x0C, SEEK_CUR);
	
	// read string size (repurpose GUID[0])
	fread(GUID, sizeof(uint32_t), 1, file);

	// seek to GUID
	fseek(file, *GUID + 0x30, SEEK_CUR);

	// read GUID
	if (fread(GUID, sizeof(uint32_t), 4, file) != 4)
	{
		puts("ERROR: UNEXPECTED EOF IN GUID.");
		return 0;
	}

	// cleanup
	fclose(file);

	printf("%.8X%.8X%.8X%.8X\n", GUID[0], GUID[1], GUID[2], GUID[3]);
	return 0;
}
