///<------------------------------------------------------------------------------
//< @file:   tokit\tokit\cfgdef.h
//< @author: ������
//< @date:   2014��9��25�� 16:35:49
//< @brief:  
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

#ifndef _cfgdef_h_
#define _cfgdef_h_

typedef _Longlong int64_t;

using namespace std;

// ������˵���������������ʼ��
enum excel_row
{
    excel_row_none   = 0,
    
    excel_row_cfg    = 1, // �ļ�������
    excel_row_fields = 4, // �ֶ����Ͷ�����
    excel_row_data   = 8, // ���������
	excel_row_min = 9, // ����Ӧ�м���
};

enum excel_cfg_row
{
    cfg_row_1   = 1, // ���ļ�������ĵ�һ��
    cfg_row_max,     // ����м�������
};

enum excel_cfg_col
{
    cfg_col_none    = 0,
    cfg_col_en_name = 1,
    cfg_col_max_cnt = 2,

    cfg_col_max,
};

enum excel_field_row
{
    field_row_en_name   = 0,
    field_row_data_type = 1,
    field_row_is_unique = 2,
    field_row_max
};

// tokitԭ������
enum enum_tokit_field_type
{
    fieldtype_none   = 0, 
    fieldtype_string = 1,  // �ַ���
    fieldtype_bool   = 2,  // bool����
    fieldtype_int8   = 3,  // ���ֽ�����
    fieldtype_int16  = 4,  // ˫�ֽ�����
    fieldtype_int32  = 5,  // ���ֽ�����
    fieldtype_int64  = 6,  // ���ֽ�����
    fieldtype_uint8  = 7,  // ���ֽ��޷�������
    fieldtype_uint16 = 8,  // ˫�ֽ��޷�������
    fieldtype_uint32 = 9,  // ���ֽ��޷�������
    fieldtype_uint64 = 10, // ���ֽ��޷�������
    fieldtype_float  = 11, // ������
    fieldtype_double = 12, // ˫���ȸ�����
    fieldtype_max,
};

// ����excel������
enum enum_parse_option
{
    parse_option_skip_data = 1, // �������ݽ��������������ö���
    parse_option_read_data = 2, // �������ö��岢��������
};

#endif //_cfgdef_h_