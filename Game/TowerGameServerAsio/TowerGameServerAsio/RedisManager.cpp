#include "stdafx.h"
#include "RedisManager.h"
#include "UtilHelper.h"
#include <locale>

#pragma warning(disable:4996)

RedisManager::RedisManager()
{
	AddKey = "";
}

RedisManager::~RedisManager()
{
	if (conn != NULL)
	{
		redisFree(conn);
	}
}

bool RedisManager::Connect()
{
	conn = redisConnect(IP.c_str(), port);
	if (conn == NULL)
	{
		return false;
	}
	if (conn != NULL && conn->err)
	{
		return false;
	}
	return true;
}

void RedisManager::SetIP(string InputIP, int InputPort)
{
	IP = InputIP;
	port = InputPort;
}

void RedisManager::Set(string key, string value)
{
	{
		std::lock_guard<std::mutex> lock_guard(m_lock);
		wstring unicode;
		convert_utf8_to_unicode_string(unicode, value.c_str(), value.length());
		reply = (redisReply*)redisCommand(conn, "Set %s %b", key.c_str(), unicode.c_str(), unicode.length() * 2);
		freeReplyObject(reply);
	}
}

void RedisManager::Del(string key)
{
	{
		std::lock_guard<std::mutex> lock_guard(m_lock);
		reply = (redisReply*)redisCommand(conn, "Del %s", key.c_str());
		freeReplyObject(reply);
	}
}

int RedisManager::Exists(string key)
{
	{
		std::lock_guard<std::mutex> lock_guard(m_lock);

		reply = (redisReply*)redisCommand(conn, "Exists %s", key.c_str());

		int value = reply->integer;
		freeReplyObject(reply);
		return value;
	}
}

string RedisManager::Get(string key)
{
	string retValue = "";
	{
		std::lock_guard<std::mutex> lock_guard(m_lock);
		reply = (redisReply*)redisCommand(conn, "Get %s", key.c_str());
		byte* bytearray = new byte[reply->len];
		ZeroMemory(bytearray, sizeof(byte) * reply->len);
		for (int i = 0; i < reply->len; ++i)
		{
			if (reply->str[i] == NULL || reply->str[i] == '\0') continue;
			//retValue += reply->str[i];
			bytearray[i] = reply->str[i];
		}
		wstring retval;
		castChar(bytearray, retval, reply->len);
		retValue = WstringToString(retval);
		freeReplyObject(reply);		
		delete[] bytearray;
	}
	return retValue;
}

void RedisManager::HSet(string key, string field, string value)
{
	{
		std::lock_guard<std::mutex> lock_guard(m_lock);
		wstring unicodefield;
		convert_utf8_to_unicode_string(unicodefield, field.c_str(), field.length());
		
		wstring unicodevalue;
		convert_utf8_to_unicode_string(unicodevalue, value.c_str(), value.length());

		reply = (redisReply*)redisCommand(conn, "HSet %s %b %b", key.c_str(), unicodefield.c_str(), unicodefield.length() * 2, unicodevalue.c_str(), unicodevalue.length() * 2);
		freeReplyObject(reply);
	}
}

void RedisManager::HDel(string key, string field)
{
	{
		std::lock_guard<std::mutex> lock_guard(m_lock);

		wstring unicodefield;
		convert_utf8_to_unicode_string(unicodefield, field.c_str(), field.length());

		reply = (redisReply*)redisCommand(conn, "HDel %s %b", key.c_str(), unicodefield.c_str(), unicodefield.length() * 2);
		freeReplyObject(reply);
	}
}

string RedisManager::HGet(string key, string field)
{
	string retValue = "";
	{
		std::lock_guard<std::mutex> lock_guard(m_lock);

		wstring unicodefield;
		convert_utf8_to_unicode_string(unicodefield, field.c_str(), field.length());
		reply = (redisReply*)redisCommand(conn, "HGet %s %b", key.c_str(), unicodefield.c_str(), unicodefield.length() * 2);
		byte* bytearray = new byte[reply->len];
		ZeroMemory(bytearray, sizeof(byte) * reply->len);
		for (int i = 0; i < reply->len; ++i)
		{
			if (reply->str[i] == NULL || reply->str[i] == '\0')
				continue;
			//retValue += reply->str[i];
			bytearray[i] = reply->str[i];
		}
		wstring retval;
		castChar(bytearray, retval, reply->len);
		retValue = WstringToString(retval);
		freeReplyObject(reply);
		delete[] bytearray;
	}
	return retValue;
}

vector<string> RedisManager::HGetAll(string key)
{
	vector<string> retValue = vector<string>();
	{
		std::lock_guard<std::mutex> lock_guard(m_lock);

		wstring unicodefield;
		
		reply = (redisReply*)redisCommand(conn, "HVals %s", key.c_str());

		retValue.push_back("0");

		for (int i = 0; i < reply->elements; ++i)
		{
			string data;
			byte* bytearray = new byte[reply->element[i]->len];
			ZeroMemory(bytearray, sizeof(byte) * reply->element[i]->len);
			for (int j = 0; j < reply->element[i]->len; j++)
			{
				if (reply->element[i]->str[j] == NULL)
					continue;
				//data += reply->element[i]->str[j];
				bytearray[j] = reply->element[i]->str[j];
			}
			wstring retval;
			castChar(bytearray, retval, reply->element[i]->len);
			data = WstringToString(retval);
			delete[] bytearray;
			retValue.push_back(data);
		}

		freeReplyObject(reply);
	}

	//sort(retValue.begin(), retValue.end());
	return retValue;
}

int RedisManager::HExists(string key, string field)
{
	{
		std::lock_guard<std::mutex> lock_guard(m_lock);

		wstring unicodeField;
		convert_utf8_to_unicode_string(unicodeField, field.c_str(), field.length());

		reply = (redisReply*)redisCommand(conn, "HExists %s %b", key.c_str(), unicodeField.c_str(), unicodeField.length() * 2);

		int value = reply->integer;
		freeReplyObject(reply);
		return value;
	}
}

vector<string> RedisManager::ZRevRange(string setId, int min, int max)
{
	vector<string> retValue = vector<string>();
	{
		std::lock_guard<std::mutex> lock_guard(m_lock);

		wstring unicodefield;

		reply = (redisReply*)redisCommand(conn, "ZRevRange %s %d %d", setId.c_str(), min, max);

		retValue.push_back("0");

		for (int i = 0; i < reply->elements; ++i)
		{
			string data;
			for (int j = 0; j < reply->element[i]->len; j++)
			{
				if (reply->element[i]->str[j] == NULL)
					continue;
				data += reply->element[i]->str[j];
			}

			retValue.push_back(data);
		}

		freeReplyObject(reply);
	}

	sort(retValue.begin(), retValue.end());
	return retValue;
}

void RedisManager::ZAdd(string key, int score, string value)
{
	{
		std::lock_guard<std::mutex> lock_guard(m_lock);

		wstring unicodevalue;
		convert_utf8_to_unicode_string(unicodevalue, value.c_str(), value.length());

		reply = (redisReply*)redisCommand(conn, "ZAdd %s %d %b", key.c_str(), score, unicodevalue.c_str(), unicodevalue.length() * 2);
		freeReplyObject(reply);
	}
}

int RedisManager::ZRevRank(string key, string value)
{
	std::string retValue = "";
	{
		std::lock_guard<std::mutex> lock_guard(m_lock);

		wstring unicodevalue;
		convert_utf8_to_unicode_string(unicodevalue, value.c_str(), value.length());

		reply = (redisReply*)redisCommand(conn, "ZRevRank %s %b", key.c_str(), unicodevalue, unicodevalue.length() * 2);
		if (reply == NULL)
			return 0;
		for (int i = 0; i < reply->len; ++i)
		{
			if (reply->str[i] == NULL || reply->str[i] == '\0')
				continue;
			retValue += reply->str[i];
		}

		freeReplyObject(reply);

	}
	return std::stoi(retValue);
}

double RedisManager::ZScore(string key, string value)
{
	std::string retValue = "";
	{
		std::lock_guard<std::mutex> lock_guard(m_lock);

		wstring unicodevalue;
		convert_utf8_to_unicode_string(unicodevalue, value.c_str(), value.length());

		reply = (redisReply*)redisCommand(conn, "ZScore %s %b", key.c_str(), unicodevalue, unicodevalue.length() * 2);
		if (reply == NULL)
			return 0;
		for (int i = 0; i < reply->len; ++i)
		{
			if (reply->str[i] == NULL || reply->str[i] == '\0')
				continue;
			retValue += reply->str[i];
		}

		freeReplyObject(reply);

	}
	return std::stod(retValue);
}

std::map<string, vector<string>> RedisManager::GetTemplateData(string key, int keyIndex)
{
	vector<string> templateDatas = HGetAll(key);

	std::map<string, vector<string>> templateMap;

	for (int i = 0; i < templateDatas.size(); i++)
	{
		string templateData = templateDatas[i];

		if (templateData == "" || templateData == "0")
			continue;

		vector<string> datas = UtilHelper::split(templateData, ',');

		templateMap.insert({ datas[keyIndex], datas });
	}

	return templateMap;
}

std::map<string, vector<string>> RedisManager::GetMapData(string mapIndex)
{
	std::map<string, vector<string>> retValue;
	{
		//std::lock_guard<std::mutex> lock_guard(m_lock);

		string hashID = "os_map";
		string key = hashID + mapIndex;

		vector<string> mapData = HGetAll(key);

		for (int i = 0; i < mapData.size(); i++)
		{			
			string data = mapData[i];

			if (data == "")
				continue;

			vector<string> datas = UtilHelper::split(data, L',');

			if (datas.size() < 3)
				continue;

			string mapKey = datas[0];

			auto check = retValue.find(mapKey);

			if (check == retValue.end())
				retValue.insert({ mapKey, datas });
		}
	}

	return retValue;
}

DWORD RedisManager::convert_unicode_to_utf8_string(
	__out std::string& utf8,
	__in const wchar_t* unicode,
	__in const size_t unicode_size
) {
	DWORD error = 0;
	do {
		if ((nullptr == unicode) || (0 == unicode_size)) {
			error = ERROR_INVALID_PARAMETER;
			break;
		}
		utf8.clear();
		//
		// getting required cch.
		//
		int required_cch = ::WideCharToMultiByte(
			CP_UTF8,
			WC_ERR_INVALID_CHARS,
			unicode, static_cast<int>(unicode_size),
			nullptr, 0,
			nullptr, nullptr
		);
		if (0 == required_cch) {
			error = ::GetLastError();
			break;
		}
		//
		// allocate.
		//
		utf8.resize(required_cch);
		//
		// convert.
		//
		if (0 == ::WideCharToMultiByte(
			CP_UTF8,
			WC_ERR_INVALID_CHARS,
			unicode, static_cast<int>(unicode_size),
			const_cast<char*>(utf8.c_str()), static_cast<int>(utf8.size()),
			nullptr, nullptr
		)) {
			error = ::GetLastError();
			break;
		}
	} while (false);
	return error;
}

DWORD RedisManager::convert_utf8_to_unicode_string(
	__out std::wstring& unicode,
	__in const char* utf8,
	__in const size_t utf8_size
) {
	DWORD error = 0;
	do {
		if ((nullptr == utf8) || (0 == utf8_size)) {
			error = ERROR_INVALID_PARAMETER;
			break;
		}
		unicode.clear();
		//
		// getting required cch.
		//
		int required_cch = ::MultiByteToWideChar(
			CP_UTF8,
			MB_ERR_INVALID_CHARS,
			utf8, static_cast<int>(utf8_size),
			nullptr, 0
		);
		if (0 == required_cch) {
			error = ::GetLastError();
			break;
		}
		//
		// allocate.
		//
		unicode.resize(required_cch);
		//
		// convert.
		//
		if (0 == ::MultiByteToWideChar(
			CP_UTF8,
			MB_ERR_INVALID_CHARS,
			utf8, static_cast<int>(utf8_size),
			const_cast<wchar_t*>(unicode.c_str()), static_cast<int>(unicode.size())
		)) {
			error = ::GetLastError();
			break;
		}
	} while (false);
	return error;
}

DWORD RedisManager::convert_ansi_to_unicode_string(
	__out std::wstring& unicode,
	__in const char* ansi,
	__in const size_t ansi_size
) {
	DWORD error = 0;
	do {
		if ((nullptr == ansi) || (0 == ansi_size)) {
			error = ERROR_INVALID_PARAMETER;
			break;
		}
		unicode.clear();
		//
		// getting required cch.
		//
		int required_cch = ::MultiByteToWideChar(
			CP_ACP,
			0,
			ansi, static_cast<int>(ansi_size),
			nullptr, 0
		);
		if (0 == required_cch) {
			error = ::GetLastError();
			break;
		}
		unicode.resize(required_cch);
		//
		// convert.
		//
		if (0 == ::MultiByteToWideChar(
			CP_ACP,
			0,
			ansi, static_cast<int>(ansi_size),
			const_cast<wchar_t*>(unicode.c_str()), static_cast<int>(unicode.size())
		)) {
			error = ::GetLastError();
			break;
		}
	} while (false);
	return error;
}

DWORD RedisManager::convert_unicode_to_ansi_string(
	__out std::string& ansi,
	__in const wchar_t* unicode,
	__in const size_t unicode_size
) {
	DWORD error = 0;
	do {
		if ((nullptr == unicode) || (0 == unicode_size)) {
			error = ERROR_INVALID_PARAMETER;
			break;
		}
		ansi.clear();
		//
		// getting required cch.
		//
		int required_cch = ::WideCharToMultiByte(
			CP_ACP,
			0,
			unicode, static_cast<int>(unicode_size),
			nullptr, 0,
			nullptr, nullptr
		);
		if (0 == required_cch) {
			error = ::GetLastError();
			break;
		}
		//
		// allocate.
		//
		ansi.resize(required_cch);
		//
		// convert.
		//
		if (0 == ::WideCharToMultiByte(
			CP_ACP,
			0,
			unicode, static_cast<int>(unicode_size),
			const_cast<char*>(ansi.c_str()), static_cast<int>(ansi.size()),
			nullptr, nullptr
		)) {
			error = ::GetLastError();
			break;
		}
	} while (false);
	return error;
}

void RedisManager::join(const vector<string>& v, char c, string& s) {

	s.clear();

	for (vector<string>::const_iterator p = v.begin();
		p != v.end(); ++p) {
		s += *p;
		if (p != v.end() - 1)
			s += c;
	}
}

void RedisManager::join(const vector<wstring>& v, char c, wstring& s) {

	s.clear();

	for (vector<wstring>::const_iterator p = v.begin();
		p != v.end(); ++p) {
		s += *p;
		if (p != v.end() - 1)
			s += c;
	}
}

string RedisManager::WstringToString(std::wstring const& str)
{
	std::locale loc("Korean");
	typedef std::codecvt<wchar_t, char, std::mbstate_t> codecvt_t;

	std::codecvt<wchar_t, char, std::mbstate_t> const& codecvt = std::use_facet<codecvt_t>(loc);

	std::mbstate_t state = std::mbstate_t();

	std::vector<char> buff((str.size() + 1) * codecvt.max_length());

	wchar_t const* in_next = str.c_str();

	char* out_next = &buff[0];

	codecvt_t::result r = codecvt.out(state, str.c_str(), str.c_str() + str.size(), in_next, &buff[0], &buff[0] + buff.size(), out_next);

	return std::string(&buff[0]);
}

bool RedisManager::castChar(byte _buffer[], wstring &value, int len)
{
	wchar_t* EncodeArr = new wchar_t[len];
	ZeroMemory(EncodeArr, sizeof(wchar_t) * len);
	memcpy_s(EncodeArr, len, _buffer, len);
	std::wstring wstr(EncodeArr);
	value = wstr;
	delete[] EncodeArr;
	return true;
}