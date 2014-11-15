///<------------------------------------------------------------------------------
//< @file:   language\c++\c++_generator.h
//< @author: ������
//< @date:   2014��9��25�� 15:43:10
//< @brief:  
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

#ifndef _cpp_generator_h_
#define _cpp_generator_h_

#include <string>
#include "generator.h"

using std::string;

struct cfgbase_t;
struct cfg_t;
struct field_t;

namespace cpptool{
    enum enum_get_c_field_option{
        gcfo_with_namespace = 0,    // ָ��������
        gcfo_without_namespace = 1, // ��ָ��������
    };

    string get_field_c_typedef_type(const cfg_t&, const field_t&, enum_get_c_field_option c_type = gcfo_with_namespace); // ��ȡ�����ֶε�c++��typedef���ͣ�����map��vec���������͵��ֶΣ�Ҳ������typedef���������
    string get_field_c_type(const field_t&); // ��ȡ�����ֶε�c++�����ͣ�����map��vector���������͵��ֶΣ����������⴦��
    string get_field_parameter_c_type(const cfg_t&, const field_t&); // ��ȡ���������е����ֶε���������int id��const char* name��
    string get_n_key_map_name(const cfg_t&); // ��ȡ���map�������map��key���ɶ��������϶��ɵģ�
    string get_1_key_map_name(const cfg_t&, const field_t&); // ��ȡ����map��
    string get_vec_name(const cfg_t&); // ��ȡ����vector������
    string get_mgr_name(const cfgbase_t&); // ��ȡ���ù�����������
    string get_comment(const cfg_t&); // ��ȡ���õ�ע��
    string get_cfg_type_name(const cfg_t &cfg); // ��ȡ���ýṹ�������

    string get_load_func_declare(const cfg_t&);// ��ȡ���뷽������
    string get_clear_func_name(const cfg_t&);// ��ȡ��շ�������
    string get_clear_func_declare(const cfg_t&);// ��ȡ��շ�������
    string get_n_key_find_func_declare(const cfg_t&); // ��ȡ���ݶ����ֵ�������õķ�������
    string get_1_key_find_func_declare_list(const cfg_t&); // ��ȡ����1����ֵ�������õķ��������б�
    string get_1_key_find_func_declare(const cfg_t&, const field_t&); // ��ȡ����1����ֵ�������õķ�������
    string get_member_comment_list(const cfgbase_t &cfgbase); // ��ȡ���Ա��ע��
}

namespace cpptool{
    // ��excel�ļ��е�ÿ���������Ӧ���ɵ��ı���ƴ������
    typedef string (gen_func_t)(const cfg_t&);
    string splice(const cfgbase_t &cfgbase, gen_func_t func, const char* splice_token = "\n");

    // ���磺void %mgr%::clear() -> void clear()
    string clear_scope(const cfg_t&, gen_func_t func, const char* prefix = "", const char* postfix = "");
}

class cpp_generator : public generator
{
public:
    cpp_generator(cfgbase_t &cfgbase, const string &to_dir, const string &h_templet, const string &cpp_templet)
        : generator(cfgbase)
        , m_h_templet_path(h_templet)
        , m_cpp_templet_path(cpp_templet)
        , m_to_dir(to_dir)
    {
    }

public:
    // @impl
    virtual bool generate();

public:
    // tokitԭ������ -> c++����
    static string& raw_type_2_c_type(enum_tokit_field_type);

private:
    bool gen_h_file(const string &h_file);
	bool gen_cpp_file(const string &cpp_file);

private:
    std::string m_h_templet_path;   /* ��������.h��ģ���ļ� */
    std::string m_cpp_templet_path; /* ��������.cpp��ģ���ļ� */
    std::string m_to_dir;
};

#endif //_cpp_generator_h_