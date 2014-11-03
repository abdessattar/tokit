///<------------------------------------------------------------------------------
//< @file:   tokit\tokit\parser.h
//< @author: ������
//< @date:   2014��9��25�� 16:20:22
//< @brief:  
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

#ifndef _parser_h_
#define _parser_h_

class COleSafeArray;
class CWorksheet;

#include "cfg.h"
#include "echoutil.h"

class parser
{
public:
    // ������excel�еĸ����������������������ṹ��
    static bool parse_excel(const string &xlsx, cfgbase_t&, errvec_t &errvec, enum_parse_option parse_option = parse_option_skip_data);

public:
    // ���ڴ洢excel�еĵ�Ԫ�����飬���ڲ�ȡole���뷽ʽʱ��Ч
    static COleSafeArray *g_ole_cell_array;
};

#endif //_parser_h_