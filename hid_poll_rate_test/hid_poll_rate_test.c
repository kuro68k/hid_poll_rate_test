// hid_poll_rate_test.cpp : Defines the entry point for the console application.
//

#ifdef WIN32
#include <windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "hidapi.h"

int main()
{
	int res;
	uint8_t buffer[3];
	hid_device *handle;

	res = hid_init();
	handle = hid_open(0x9999, 0x007F, NULL);
	if (handle == NULL)
	{
		printf("Unable to open HID device.\n");
		return 1;
	}

	printf("Reading reports...\n");
	int sample_count = 100;

	LARGE_INTEGER StartTime, EndTime, ElapsedUS;
	LARGE_INTEGER Frequency;

	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&StartTime);

	for (int i = 0; i < sample_count; i++)
	{
		res = hid_read(handle, buffer, sizeof(buffer));
		//printf(".");
	}

	QueryPerformanceCounter(&EndTime);
	ElapsedUS.QuadPart = EndTime.QuadPart - StartTime.QuadPart;
	ElapsedUS.QuadPart *= 1000000;
	ElapsedUS.QuadPart /= Frequency.QuadPart;

	printf("Elapsed time: %ld uS\n", ElapsedUS.QuadPart);
	double ms = ElapsedUS.QuadPart / 1000.0;
	printf("= %.2f mS\n", ms);

	double rate = 1.0 / (ms / sample_count);
	rate *= 1000;
	printf("= %.2f Hz\n", rate);

    return 0;
}

