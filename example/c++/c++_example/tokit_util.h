///<------------------------------------------------------------------------------
//< @file:   c++\c++_example\tokit_util.h
//< @author: 
//< @date:   2014��9��27�� 0:2:43
//< @brief:  
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

#ifndef _tokit_util_h_
#define _tokit_util_h_

#include <string>
#include <vector>
#include <set>

#include "type.h"
#include <stdlib.h>

using namespace std;

namespace keyutil
{
    uint64_t Get16161616Key(uint16_t w, uint16_t x, uint16_t y, uint16_t z);

    uint64_t Get161616Key(uint16_t x, uint16_t y, uint16_t z);

    uint64_t Get3232Key(uint32 x, uint32 y);
}

typedef uint64_t Tick;
namespace tickutil
{
    Tick get_tick();

    // ��������ʱ�����ڵĺ����
    uint32_t tick_diff(Tick old_tick);
}

namespace strutil
{
    // �Ƴ����ַ�����ͷ��ĩβ���Ŀո��\t����
    // ����: trim("   start xxx end   ") = "start xxx end"
    string trim(char* str);
    string trim(const string& str);

    // �滻�ַ�����������ַ��������޸�
    // ���磺replace("this is an expmple", "is", "") = "th  an expmple"
    // ����: replace("dbdb", "db", "bd") = "bdbd"
    string& replace(string &str, const char *old, const char* to);
    string& replace(string &str, const char *old, const string& to);

    // ѭ���滻����ÿ���ַ������滻�������滻�����ַ����н����滻
    // ����: replace("dbdb", "db", "bd") = "bbbd"
    // ����: replace("good", "o", "oo") = "���ᵼ����ѭ��"
    string& cycle_replace(string &str, const char *old, const char* to);

    // ���޷���64λ����ת��Ϊ�ַ���
    // ���磺tostr(100123) = "100123"
    string tostr(uint64_t n);

    inline bool str_to_bool(const char* val)
    {
        return (val[0] == '0') ? false : true;
    }

    inline int32_t str_to_int32(const char* val)
    {
        return atoi(val);
    }

    inline uint32_t str_to_uint32(const char* val)
    {
        char *stop_at = NULL;
        return ::strtoul(val, &stop_at, 10);
    }

    inline int64_t str_to_int64(const char* val)
    {
#ifdef WIN32
        return _atoi64(val);
#else
        return strtoll(val, NULL, 10);
#endif        
    }

    inline uint64_t str_to_uint64(const char* val)
    {
#ifdef WIN32
        char *stop_at = NULL;
        return _strtoui64(val, &stop_at, 10);
#else
        return strtoull(val, NULL, 10);
#endif
    }

    inline std::string un_escape_xml(const char* old_str)
    {
        std::string str(old_str);
        replace(str, "&quot;", "\"");

        return str;
    }

    // ���ַ������ݷָ����ָ�Ϊ�ַ�������
    typedef std::vector<std::string> stringvec_t;
    stringvec_t split(const string& src, char cut = ',');
    stringvec_t split(const char* src, char cut = ',');

    typedef std::set<std::string> stringset_t;
    stringset_t split_str_set(const string &src, char cut = ',');

    template <typename T, typename FUNC_T>
    std::vector<T> split_str_to_vec(const string &src, FUNC_T (*cast_func)(const char*), char cut = ',')
    {
        typedef std::vector<T> T_vec;
        T_vec t_vec;

        stringvec_t strvec = split(src, cut);
        for (size_t n = 0; n < strvec.size(); n++){
            const std::string str = strvec[n];
            t_vec.push_back((T)cast_func(str.c_str()));
        }

        return t_vec;
    }

    template <typename T, typename FUNC_T>
    std::set<T> split_str_to_set(const char* src, FUNC_T (*cast_func)(const char*), char cut = ',')
    {
        typedef std::set<T> T_set;
        T_set t_set;

        stringvec_t strvec = split(src, cut);
        for (size_t n = 0; n < strvec.size(); n++){
            const std::string str = strvec[n];
            t_set.insert((T)cast_func(str.c_str()));
        }

        return t_set;
    }
};

using namespace tickutil;
using namespace strutil;

#endif //_tokit_util_h_