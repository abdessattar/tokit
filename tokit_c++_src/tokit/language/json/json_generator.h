///<------------------------------------------------------------------------------
//< @file:   language\json\json_generator.h
//< @author: hongkunan
//< @date:   2014��11��6�� 15:51:25
//< @brief:  
//< Copyright (c) 2014 heihuo. All rights reserved.
///<------------------------------------------------------------------------------

#ifndef _json_generator_h_
#define _json_generator_h_

#include <string>
#include "generator.h"

using std::string;

class json_generator : public generator
{
public:
    json_generator(cfgbase_t &cfgbase, const string &json_dir)
        : generator(cfgbase)
        , m_json_dir(json_dir)
    {
    }

public:
    // @impl
    virtual bool generate();

private:
    // ��excel�и���������������Ӧ��json�ļ�
    bool save_as_json();

private:
    std::string m_json_dir;
};

#endif //_json_generator_h_