#include "root.h"
#include <stdio.h>
#include <list>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <jsoncpp/json/json.h>

Root::Root(const std::string & filename){
    std::ifstream  m_json(filename, std::ifstream::binary);

    m_json >> m_root;    
}

Json::Value Root::operator[](std::string const& index){
    return m_root[index];
}

Root::~Root(){}
