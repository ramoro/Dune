#ifndef Config_H
#define Config_H

#include <list>
#include <jsoncpp/json/json.h>

class Config
{
public:
	Config();
	Config(const std::string &filename);
	~Config();
	Json::Value operator[](std::string const& index);
    Json::Value m_config;

};

#endif