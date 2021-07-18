#pragma once
#include "stdafx.h"
#include <vector>

namespace UtilHelper
{
	template<typename T>
	static void Padding(std::basic_string<T>& s, typename std::basic_string<T>::size_type n, T c)
	{
		if (n > s.length())
		{
			s.insert(0, n - s.length(), c);
		}
	}

	static std::vector<std::string> split(std::string& s, char delimiter)
	{
		std::vector<std::string> tokens;
		std::string token;
		std::istringstream tokenStream(s);
		while (std::getline(tokenStream, token, delimiter))
		{
			tokens.push_back(token);
		}
		return tokens;
	}

	static std::vector<int> split_int(std::string& s, char delimiter)
	{
		std::vector<int> tokens;
		std::string token;
		std::istringstream tokenStream(s);
		while (std::getline(tokenStream, token, delimiter))
		{
			tokens.push_back(stoi(token));
		}
		return tokens;
	}

	static std::vector<std::wstring> split(std::wstring& s, wchar_t delimiter)
	{
		std::vector<std::wstring> tokens;
		std::wstring token;
		std::wstringstream tokenStream(s);
		while (std::getline(tokenStream, token, delimiter))
		{
			tokens.push_back(token);
		}
		return tokens;
	}

	static std::string makeparam(std::string value1, std::string value2)
	{
		return value1 + "|" + value2;
	}
	static std::string MakeParam(std::vector<std::string> values, char comma)
	{
		std::string value = "";

		for (int i = 0; i < values.size(); i++)
		{
			value += values[i];

			if (i < values.size() - 1)
				value += comma;
		}

		return value;
	}


	static std::string ConvertTimeToString(time_t timeData)
	{
		struct tm pTimeInfo;
		localtime_s(&pTimeInfo, &timeData);

		int year = pTimeInfo.tm_year + 1900;
		int month = pTimeInfo.tm_mon + 1;
		int day = pTimeInfo.tm_mday;
		int hour = pTimeInfo.tm_hour;
		int min = pTimeInfo.tm_min;
		int sec = pTimeInfo.tm_sec;

		std::string timeString = std::to_string(year) + "-" + std::to_string(month) + "-" + std::to_string(day) + " " + std::to_string(hour) + ":" + std::to_string(min) + ":" + std::to_string(sec);
		return timeString;
	}

	static std::string GetDate()
	{
		struct tm pTimeInfo;
		time_t curTime = time(NULL);
		localtime_s(&pTimeInfo, &curTime);

		int year = pTimeInfo.tm_year + 1900;
		int month = pTimeInfo.tm_mon + 1;
		int day = pTimeInfo.tm_mday;

		std::string sMonth = std::to_string(month);
		Padding(sMonth, 2, '0');

		std::string sDay = std::to_string(day);
		Padding(sDay, 2, '0');

		//std::string respawnTime = std::to_string(year) + "-" + std::to_string(month) + "-" + std::to_string(day);
		std::string respawnTime = std::to_string(year) + "-" + sMonth + "-" + sDay;
		
		return respawnTime;
	}

	static std::string GetDate(time_t timeData)
	{
		struct tm pTimeInfo;
		time_t curTime = timeData;
		localtime_s(&pTimeInfo, &curTime);

		int year = pTimeInfo.tm_year + 1900;
		int month = pTimeInfo.tm_mon + 1;
		int day = pTimeInfo.tm_mday;

		std::string sMonth = std::to_string(month);
		Padding(sMonth, 2, '0');

		std::string sDay = std::to_string(day);
		Padding(sDay, 2, '0');

		//std::string respawnTime = std::to_string(year) + "-" + std::to_string(month) + "-" + std::to_string(day);
		std::string respawnTime = std::to_string(year) + "-" + sMonth + "-" + sDay;

		return respawnTime;
	}

	static std::string GetDateTime(time_t timeData)
	{
		struct tm pTimeInfo;
		time_t curTime = timeData;
		localtime_s(&pTimeInfo, &curTime);

		int year = pTimeInfo.tm_year + 1900;
		int month = pTimeInfo.tm_mon + 1;
		int day = pTimeInfo.tm_mday;
		int hour = pTimeInfo.tm_hour;
		int min = pTimeInfo.tm_min;
		int sec = pTimeInfo.tm_sec;

		std::string sMonth = std::to_string(month);
		Padding(sMonth, 2, '0');

		std::string sDay = std::to_string(day);
		Padding(sDay, 2, '0');

		std::string sHour = std::to_string(hour);
		Padding(sHour, 2, '0');

		std::string sMin = std::to_string(min);
		Padding(sMin, 2, '0');

		std::string sSec = std::to_string(sec);
		Padding(sSec, 2, '0');

		
		std::string respawnTime = std::to_string(year) + "-" + sMonth + "-" + sDay + " " + sHour + ":" + sMin + ":" + sSec;

		return respawnTime;
	}

	static int GetRandomNum(int min, int max)
	{
		return rand() % (max + 1 - min) + min;
	}

	static float GetFloatRandomNum(int min, int max)
	{
		return (float)(rand() % (max + 1 - min) + min);
	}	

	//"00:00:00" 형식을 time_t로 (년,월,일 은 현재 시간 기반)
	static time_t stoTime(std::string strValue, int addDay = 0)
	{
		std::vector<std::string> splitdatas = UtilHelper::split(strValue, ':');

		if (splitdatas.size() != 3)
			return NULL;

		tm tm;
		time_t curTime = time(NULL);                // 현재 시간을 받음
		localtime_s(&tm, &curTime);    // 현재 시간을 이쁘게 struct tm에 넣음

		int waitHour = stoi(splitdatas[0]);
		int waitMin = stoi(splitdatas[1]);
		int waitSec = stoi(splitdatas[2]);

		tm.tm_mday += addDay;
		tm.tm_hour = waitHour;
		tm.tm_min = waitMin;
		tm.tm_sec = waitSec;

		return mktime(&tm);
	}

	static std::string DataAddValue(std::string Data, int value, int index, char comma)
	{
		std::vector<std::string> datas = split(Data, comma);

		if (datas.size() <= index)
			return Data;

		datas[index] = std::to_string(stof(datas[index]) + value);

		std::string returnData = "";

		for (int i = 0; i < datas.size(); i++)
		{
			returnData += datas[i];

			if (i < datas.size() - 1)
				returnData += comma;
		}

		return returnData;
	}
}
