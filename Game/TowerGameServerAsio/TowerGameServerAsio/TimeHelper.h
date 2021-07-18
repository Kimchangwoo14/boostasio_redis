#pragma once
#include <string>
#include <time.h>

namespace TimeHelper
{
	/*
	using namespace chrono;
	auto now = system_clock::now();
	auto timet = std::chrono::system_clock::to_time_t(now);
	std::string sss = TimeHelper::GetDateTimeString(timet);

	auto timePoint = now + 5s;
	auto timet1 = std::chrono::system_clock::to_time_t(timePoint);
	std::string sss1 = TimeHelper::GetDateTimeString(timet1);
	*/


	static std::string	GetDateTimeString(__time64_t ltime)
	{
		char		szTimeBuff[64];
		tm			sTime{};
		if (0 == ::_localtime64_s(&sTime, &ltime))
		{
			sprintf_s(szTimeBuff, "%04d-%02d-%02d %02d:%02d:%02d"
				, sTime.tm_year + 1900
				, sTime.tm_mon + 1
				, sTime.tm_mday
				, sTime.tm_hour
				, sTime.tm_min
				, sTime.tm_sec);
		}
		else
		{
			szTimeBuff[0] = NULL;
		}
		return std::string(szTimeBuff);
	}
}