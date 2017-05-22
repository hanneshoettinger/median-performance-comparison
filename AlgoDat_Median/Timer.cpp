#pragma once
#include "stdafx.h"
#include "Timer.h"
#include <stdio.h>

TimerFunc::TimerFunc()
{
}

TimerFunc::~TimerFunc()
{
}

void TimerFunc::startTimer()
{
	// get ticks per second
	QueryPerformanceFrequency(&frequency);

	// start timer
	QueryPerformanceCounter(&t1);
}

void TimerFunc::stopTimer(char select)
{
	// stop timer
	QueryPerformanceCounter(&t2);

	// compute the elapsed time
	elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;

	int milliseconds = (int)(elapsedTime) % 1000;
	int seconds = (int)(elapsedTime / 1000) % 60;
	int minutes = (int)(elapsedTime / (1000 * 60)) % 60;
	int hours = (int)(elapsedTime / (1000 * 60 * 60)) % 24;

	printf("%.2d:%.2d:%.2d.%.3d; ", hours, minutes, seconds, milliseconds);

	time temp;
	temp.hours = hours;
	temp.minutes = minutes;
	temp.seconds = seconds;
	temp.milliseconds = milliseconds;

	switch (select)
	{
		case 'n':
			Timesnth.push_back(temp);
			break;
		case 'r':
			Timesrand.push_back(temp);
			break;
		case 'm':
			Timesmedian.push_back(temp);
			break;
		case 'q':
			Timesqs.push_back(temp);
			break;
	}
	elapsedTime = 0;
}
void TimerFunc::saveTimes(const char* filename)
{
	using namespace std;
	
	time avergaer;
	time avergaen;
	time avergaeq;
	time avergaem;
	
	avergaem = calculateTimeAverage(Timesmedian);
	avergaen = calculateTimeAverage(Timesnth);
	avergaeq = calculateTimeAverage(Timesqs);
	avergaer = calculateTimeAverage(Timesrand);

	FILE * pFile;

	fopen_s(&pFile,filename,"w");
	fprintf(pFile, "Time-Format: hh:mm:ss.ms\n");
	fprintf(pFile, "Average nth-Element: %.2d:%.2d:%.2d.%.3d\n", avergaen.hours, avergaen.minutes, avergaen.seconds, avergaen.milliseconds);
	fprintf(pFile, "Average Quicksort: %.2d:%.2d:%.2d.%.3d\n", avergaeq.hours, avergaeq.minutes, avergaeq.seconds, avergaeq.milliseconds);
	fprintf(pFile, "Average random Pivot: %.2d:%.2d:%.2d.%.3d\n", avergaer.hours, avergaer.minutes, avergaer.seconds, avergaer.milliseconds);
	fprintf(pFile, "Average Median of Medians: %.2d:%.2d:%.2d.%.3d\n ", avergaem.hours, avergaem.minutes, avergaem.seconds, avergaem.milliseconds);
	fclose(pFile);
}
time TimerFunc::calculateTimeAverage(std::vector<time> times)
{
	time temp;
	for (time n : times)
	{
		temp = temp + n;
	}
	return temp / (times.size() - 1);
}