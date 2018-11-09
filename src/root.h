#ifndef Root_H
#define Root_H

#include <list>
#include <jsoncpp/json/json.h>

class Root
{
public:
	Root();
	Root(const std::string &filename);
	~Root();
	Json::Value operator[](std::string const& index);
    Json::Value m_root;

};

#endif