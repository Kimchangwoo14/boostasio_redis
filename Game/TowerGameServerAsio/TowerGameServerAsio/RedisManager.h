#pragma once
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <hiredis.h>
#include <string>
#include "hiredispp.h"
#include <mutex>
//#pragma commnet (lib, "hiredis.lib")
//#pragma commnet (lib, "Win32_Interop.lib")

using namespace std;

class RedisManager
{
public:
	RedisManager();
	~RedisManager();
	int				loop = 0;
	bool			Connect();
	void			SetIP(string InputIP, int InputPort);
	void			Set(string key, string value);
	string			Get(string key);
	void			Del(string key);
	int				Exists(string key);

	void			HSet(string key, string field, string value);
	void			HDel(string key, string field);
	string			HGet(string key, string field);
	vector<string>  HGetAll(string key);
	int				HExists(string key, string field);
	vector<string>	ZRevRange(string setId, int min, int max);
	void			ZAdd(string key, int score, string value);
	int				ZRevRank(string key, string value);
	double			ZScore(string key, string value);

	void			join(const vector<string>& v, char c, string& s);
	void			join(const vector<wstring>& v, char c, wstring& s);
	string			WstringToString(std::wstring const& str);
	bool			castChar(byte _buffer[], wstring &value, int len);
	string			AddKey = "";

	std::map<string, vector<string>>	GetTemplateData(string key, int keyIndex);
	std::map<string, vector<string>>	GetMapData(string mapIndex);
private:
	string			IP = "";
	int				port;
	redisContext	*conn = NULL;
	redisReply		*reply = NULL;
	mutex			m_lock;
	DWORD convert_unicode_to_utf8_string(
		__out std::string& utf8,
		__in const wchar_t* unicode,
		__in const size_t unicode_size
	);
	DWORD convert_utf8_to_unicode_string(
		__out std::wstring& unicode,
		__in const char* utf8,
		__in const size_t utf8_size
	);

	DWORD convert_ansi_to_unicode_string(
		__out std::wstring& unicode,
		__in const char* ansi,
		__in const size_t ansi_size
	);
	DWORD convert_unicode_to_ansi_string(
		__out std::string& ansi,
		__in const wchar_t* unicode,
		__in const size_t unicode_size
	);

};