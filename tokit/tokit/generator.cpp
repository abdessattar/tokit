///<------------------------------------------------------------------------------
//< @file:   tokit\tokit\generator.cpp
//< @author: ������
//< @date:   2014��9��25�� 14:46:17
//< @brief:  
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

#include "generator.h"
#include "parser.h"
#include "file_util.h"

bool generator::parse_excel(enum_parse_option parse_option /* = parse_option_ignore_data */)
{
    /*
    if(false == fileutil::exist(m_excel)){
        ECHO_ERR("����: �Ҳ���excel�ṹ�����ļ�<%s>", m_excel.c_str());
        return false;
    }


    if (!parser::parse_excel(m_excel, m_cfgbase, m_errvec, parse_option)){
        ECHO_ERR("���󣺽���<%s>�ļ�ʧ��", m_excel.c_str());
        echo_errs();
        return false;
    }
    */
    return true;
}

void generator::echo_errs()
{
    echoutil::echo_errvec(m_errvec);
    m_errvec.clear();
}
