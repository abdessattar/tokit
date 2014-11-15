///<------------------------------------------------------------------------------
//< @file:   tokit\tokit\cfg.h
//< @author: ������
//< @date:   2014��9��23�� 10:24:53
//< @brief:  �������������ļ����ļ��ṹ
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

#ifndef _cfg_h_
#define _cfg_h_

#include <string>
#include <vector>

#include "cfgdef.h"

typedef _Longlong int64_t;

using namespace std;

// �ֶγ�Ա���������ֶε��ڲ�����
struct field_t
{
    // �ֶ�����
    enum enum_field_attr
    {
        fieldattr_none = 0,   // Ĭ�ϣ��������ֶ�����ͨ��Ա
        fieldattr_n_key = 1,  // ���ֶν��������ֶι�������
        fieldattr_1_key,      // ���ֶε�ֵΨһ
        fieldattr_array,      // ����
        fieldattr_set,        // ����
        fieldattr_max,
    };

    field_t()
        : fieldtype(fieldtype_none)
        , fieldattr(fieldattr_none)
    {
    }

    // �����ֶ����͵�����
    string& get_field_type_name();

    bool is_1_key() const{ return fieldattr_1_key == fieldattr; } // ÿ����¼�б��ֶε�ֵ�Ƿ�Ψһ
    bool is_n_key() const{ return fieldattr_n_key == fieldattr; } // ���ֶ��Ƿ��������ֶι�������
    bool is_array() const{ return fieldattr_array == fieldattr; }
    bool is_set() const{ return fieldattr_set == fieldattr; }

    enum_tokit_field_type fieldtype; // ��������
	string cn_name;         // �����ֶ�����
    string en_name;         // Ӣ���ֶ�����
    string comment;         // ע��
    
    enum_field_attr fieldattr;
};

typedef std::vector<field_t> fieldvec_t;
typedef std::vector<int> keyvec_t;

typedef std::vector<std::string> row_t;
typedef std::vector<row_t> table_t;

// ���ýṹ���壬��excel�ļ��е�һ�����������Ӧ�������˵���������Ľṹ
struct cfg_t
{
    cfg_t()
        : maxcnt(0)
        , row_file_cfg_begin(0)
        , row_fields_begin(0)
        , row_data_begin(0)
    {
    }

    string cn_name;  // ���ö����ļ������ƣ���Ϊ����
    string en_name;  // ���õ����ƣ�����ΪӢ��

    fieldvec_t fields; // ����Ա
    keyvec_t keys;     // ���������б�ĳ���ֶ�����������������������뵽����б�

    size_t maxcnt; // ����м�������

    size_t row_file_cfg_begin; // �ļ�����������ʼ��
    size_t row_fields_begin;   // �ֶζ���������ʼ��
    size_t row_data_begin;     // ��������������ʼ��

    table_t table; // ���ݱ�

    // �����ֶ�����ȡ�ֶ�
    field_t* getfield(const char* fieldname)
    {
        for(size_t n = 0; n < fields.size(); n++){
            field_t &field = fields[n];
            if(field.en_name == fieldname){
                return &field;
            }
        }

        return NULL;
    }
    
    bool only_has_1_row() const { return 1 == maxcnt; }
};

typedef std::vector<cfg_t> cfgvec_t;

// ���ýṹ�������ģ���һ����excel�ļ����Ӧ��������excel�ļ��ڲ�����������Ľṹ
struct cfgbase_t
{
    cfg_t* find_by_en_name(const char* en_name)
    {
        if(NULL == en_name){
            return NULL;
        }

        for(size_t n = 0; n < cfgs.size(); ++n){
            cfg_t &cfg = cfgs[n];

            if(cfg.en_name == en_name){
                return &cfg;
            }
        }

        return NULL;
    }

    
    string filename; // �����õ��ļ���
    cfgvec_t cfgs;   // ���������������
};

namespace cfgtool{
    // �ֶ����͵����� -> ��Ӧö��
	enum_tokit_field_type type_name_2_enum(const char* tokit_type);
}

#endif //_cfg_h_