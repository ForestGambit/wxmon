#include "wxdata.h"
#include "openwx.h"
#include "jsmn.h"

std::string OPENWXURL{ "https://api.openweathermap.org/data/3.0/onecall?lat=34.14&lon=-117.29&exclude=hourly,daily,minutely,alerts&units=imperial&appid=" };

wxdata::wxdata()
{
	OPENWXURL.append(APIKEY);
}

wxdata::~wxdata()
{

}

int wxdata::Refresh()
{
    m_buffer.clear();
    m_temp.clear();
    m_rh.clear();
    
	m_curl = curl_easy_init();
	if (m_curl)
	{
		curl_easy_setopt(m_curl, CURLOPT_URL, OPENWXURL.c_str());
		curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, this->CurlWrite);
		curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &m_buffer);
		CURLcode res = curl_easy_perform(m_curl);
		if (res != CURLE_OK)
		{
			return -10;
		}
		curl_easy_cleanup(m_curl);
	}
	else
	{
		return -11;
	}



	jsmn_parser parser;
	jsmntok_t t[128];
	jsmn_init(&parser);

	auto ret = jsmn_parse(&parser, m_buffer.c_str(), m_buffer.size(), t, sizeof(t));

	if (ret < 0)
	{
        return -20;
	}
	else
	{
		for (int i = 0; i < ret; i++)
		{
			if (t[i].type & JSMN_STRING)
			{
				std::string str;
				str = m_buffer.substr(t[i].start, (t[i].end - t[i].start));
				//std::cout << str << std::endl;

				if (i + 1 < ret)
				{
					if (t[i + 1].type & JSMN_PRIMITIVE)
					{
						std::string str1;
						str1 = m_buffer.substr(t[i + 1].start, (t[i + 1].end - t[i + 1].start));
						if (str == "temp") m_temp = str1;
						if (str == "humidity") m_rh = str1;
					}
				}
			}
		}
		return 0;
	}
 
}

std::string& wxdata::GetBuffer()
{
    return m_buffer;
}

std::string& wxdata::GetTemp()
{
    return m_temp;
}

std::string& wxdata::GetRH()
{
    return m_rh;
}

int wxdata::CurlWrite(char* data, size_t size, size_t nmemb, std::string* writerData)
{
    writerData->append(data, size * nmemb);
    return size*nmemb;
}