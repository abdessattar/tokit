///<------------------------------------------------------------------------------
//< @file:   language\xml\xml_generator.h
//< @author: ������
//< @date:   2014��9��25�� 15:49:5
//< @brief:  ����xml����
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

#ifndef _xml_generator_h_
#define _xml_generator_h_

#include <string>
#include "generator.h"

using std::string;

class xml_generator : public generator
{
public:
    xml_generator(cfgbase_t &cfgbase, const string &xml_dir)
        : generator(cfgbase)
        , m_xml_dir(xml_dir)
    {
    }

public:
    // @impl
    virtual bool generate();

private:
    // ��excel�и���������������Ӧ��xml�ļ�
    bool save_as_xml();

private:
    std::string m_xml_dir;
};

#endif //_xml_generator_h_