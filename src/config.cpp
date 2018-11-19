#include "config.h"
#include <stdio.h>
#include <list>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <jsoncpp/json/json.h>

Config::Config(){}
Config::Config(const std::string & filename){
    std::ifstream  m_json(filename, std::ifstream::binary);

    m_json >> m_config;
}

Json::Value Config::operator[](std::string const& index){
    return m_config[index];
}

Config::~Config(){}
