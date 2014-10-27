///<------------------------------------------------------------------------------
//< @file:  testcfg.h
//< @brief: ����������
//< ��ͷ�ļ��ɹ����Զ����ɣ������ڱ��ļ������Ķ�
//< @Copyright (c) 2014 tokit.
///<------------------------------------------------------------------------------

#ifndef _testcfg_h_
#define _testcfg_h_

#include <string>

#include <map>
#include <vector>
#include <set>

#include "type.h"

// ����������
struct testcfg_t{
    typedef std::string stringfieldprimary_t; // �ַ�������<<<����>>>
    typedef bool boolfieldprimary_t; // bool������<<<����>>>
    typedef char charfieldprimary_t; // �ַ�����<<<����>>>
    typedef int16 int16fieldprimary_t; // 16λ��������<<<����>>>
    typedef int32 intfieldprimary_t; // 32λ��������<<<����>>>
    typedef int64 int64fieldprimary_t; // 64λ��������<<<����>>>
    typedef uint8 uint8fieldprimary_t; // 8λ�޷�����������<<<����>>>
    typedef uint16 uint16fieldprimary_t; // 16λ�޷�����������<<<����>>>
    typedef uint32 uintfieldprimary_t; // 32λ�޷�����������<<<����>>>
    typedef uint64 uint64fieldprimary_t; // 64λ�޷�����������<<<����>>>
    typedef std::string stringfieldunique_t; // �ַ���Ψһ<<<Ψһ>>>
    typedef bool boolfieldunique_t; // bool��Ψһ<<<Ψһ>>>
    typedef char charfieldunique_t; // �ַ�Ψһ<<<Ψһ>>>
    typedef int16 int16fieldunique_t; // 16λ����Ψһ<<<Ψһ>>>
    typedef int32 intfieldunique_t; // 32λ����Ψһ<<<Ψһ>>>
    typedef int64 int64fieldunique_t; // 64λ����Ψһ<<<Ψһ>>>
    typedef uint8 uint8fieldunique_t; // 8λ�޷�������Ψһ<<<Ψһ>>>
    typedef uint16 uint16fieldunique_t; // 16λ�޷�������Ψһ<<<Ψһ>>>
    typedef uint32 uintfieldunique_t; // 32λ�޷�������Ψһ<<<Ψһ>>>
    typedef uint64 uint64fieldunique_t; // 64λ�޷�������Ψһ<<<Ψһ>>>
    typedef float floatfieldunique_t; // ������Ψһ<<<Ψһ>>>
    typedef double doublefieldunique_t; // ˫���ȸ�����Ψһ<<<Ψһ>>>
    typedef std::vector<std::string> stringfieldarrayvec_t; // �ַ�������<<<����>>>
    typedef std::vector<bool> boolfieldarrayvec_t; // bool������<<<����>>>
    typedef std::vector<char> charfieldarrayvec_t; // �ַ�����<<<����>>>
    typedef std::vector<int16> int16fieldarrayvec_t; // 16λ��������<<<����>>>
    typedef std::vector<int32> intfieldarrayvec_t; // 32λ��������<<<����>>>
    typedef std::vector<int64> int64fieldarrayvec_t; // 64λ��������<<<����>>>
    typedef std::vector<uint8> uint8fieldarrayvec_t; // 8λ�޷�����������<<<����>>>
    typedef std::vector<uint16> uint16fieldarrayvec_t; // 16λ�޷�����������<<<����>>>
    typedef std::vector<uint32> uintfieldarrayvec_t; // 32λ�޷�����������<<<����>>>
    typedef std::vector<uint64> uint64fieldarrayvec_t; // 64λ�޷�����������<<<����>>>
    typedef std::vector<float> floatfieldarrayvec_t; // ����������<<<����>>>
    typedef std::vector<double> doublefieldarrayvec_t; // ˫���ȸ���������<<<����>>>
    typedef std::set<std::string> stringfieldsetset_t; // �ַ�������<<<����>>>
    typedef std::set<bool> boolfieldsetset_t; // bool�ͼ���<<<����>>>
    typedef std::set<char> charfieldsetset_t; // �ַ�����<<<����>>>
    typedef std::set<int16> int16fieldsetset_t; // 16λ��������<<<����>>>
    typedef std::set<int32> intfieldsetset_t; // 32λ��������<<<����>>>
    typedef std::set<int64> int64fieldsetset_t; // 64λ��������<<<����>>>
    typedef std::set<uint8> uint8fieldsetset_t; // 8λ�޷�����������<<<����>>>
    typedef std::set<uint16> uint16fieldsetset_t; // 16λ�޷�����������<<<����>>>
    typedef std::set<uint32> uintfieldsetset_t; // 32λ�޷�����������<<<����>>>
    typedef std::set<uint64> uint64fieldsetset_t; // 64λ�޷�����������<<<����>>>
    typedef std::set<float> floatfieldsetset_t; // ����������<<<����>>>
    typedef std::set<double> doublefieldsetset_t; // ˫���ȸ���������<<<����>>>

    testcfg_t();

    std::string stringfield; // �ַ���
    bool boolfield; // bool��
    char charfield; // �ַ�
    int16 int16field; // 16λ����
    int32 intfield; // 32λ����
    int64 int64field; // 64λ����
    uint8 uint8field; // 8λ�޷�������
    uint16 uint16field; // 16λ�޷�������
    uint32 uintfield; // 32λ�޷�������
    uint64 uint64field; // 64λ�޷�������
    float floatfield; // ������
    double doublefield; // ˫���ȸ�����
    stringfieldprimary_t stringfieldprimary; // �ַ�������<<<����>>>
    boolfieldprimary_t boolfieldprimary; // bool������<<<����>>>
    charfieldprimary_t charfieldprimary; // �ַ�����<<<����>>>
    int16fieldprimary_t int16fieldprimary; // 16λ��������<<<����>>>
    intfieldprimary_t intfieldprimary; // 32λ��������<<<����>>>
    int64fieldprimary_t int64fieldprimary; // 64λ��������<<<����>>>
    uint8fieldprimary_t uint8fieldprimary; // 8λ�޷�����������<<<����>>>
    uint16fieldprimary_t uint16fieldprimary; // 16λ�޷�����������<<<����>>>
    uintfieldprimary_t uintfieldprimary; // 32λ�޷�����������<<<����>>>
    uint64fieldprimary_t uint64fieldprimary; // 64λ�޷�����������<<<����>>>
    float floatfieldprimary; // ����������
    double doublefieldprimary; // ˫���ȸ���������
    stringfieldunique_t stringfieldunique; // �ַ���Ψһ<<<Ψһ>>>
    boolfieldunique_t boolfieldunique; // bool��Ψһ<<<Ψһ>>>
    charfieldunique_t charfieldunique; // �ַ�Ψһ<<<Ψһ>>>
    int16fieldunique_t int16fieldunique; // 16λ����Ψһ<<<Ψһ>>>
    intfieldunique_t intfieldunique; // 32λ����Ψһ<<<Ψһ>>>
    int64fieldunique_t int64fieldunique; // 64λ����Ψһ<<<Ψһ>>>
    uint8fieldunique_t uint8fieldunique; // 8λ�޷�������Ψһ<<<Ψһ>>>
    uint16fieldunique_t uint16fieldunique; // 16λ�޷�������Ψһ<<<Ψһ>>>
    uintfieldunique_t uintfieldunique; // 32λ�޷�������Ψһ<<<Ψһ>>>
    uint64fieldunique_t uint64fieldunique; // 64λ�޷�������Ψһ<<<Ψһ>>>
    floatfieldunique_t floatfieldunique; // ������Ψһ<<<Ψһ>>>
    doublefieldunique_t doublefieldunique; // ˫���ȸ�����Ψһ<<<Ψһ>>>
    stringfieldarrayvec_t stringfieldarray; // �ַ�������<<<����>>>
    boolfieldarrayvec_t boolfieldarray; // bool������<<<����>>>
    charfieldarrayvec_t charfieldarray; // �ַ�����<<<����>>>
    int16fieldarrayvec_t int16fieldarray; // 16λ��������<<<����>>>
    intfieldarrayvec_t intfieldarray; // 32λ��������<<<����>>>
    int64fieldarrayvec_t int64fieldarray; // 64λ��������<<<����>>>
    uint8fieldarrayvec_t uint8fieldarray; // 8λ�޷�����������<<<����>>>
    uint16fieldarrayvec_t uint16fieldarray; // 16λ�޷�����������<<<����>>>
    uintfieldarrayvec_t uintfieldarray; // 32λ�޷�����������<<<����>>>
    uint64fieldarrayvec_t uint64fieldarray; // 64λ�޷�����������<<<����>>>
    floatfieldarrayvec_t floatfieldarray; // ����������<<<����>>>
    doublefieldarrayvec_t doublefieldarray; // ˫���ȸ���������<<<����>>>
    stringfieldsetset_t stringfieldset; // �ַ�������<<<����>>>
    boolfieldsetset_t boolfieldset; // bool�ͼ���<<<����>>>
    charfieldsetset_t charfieldset; // �ַ�����<<<����>>>
    int16fieldsetset_t int16fieldset; // 16λ��������<<<����>>>
    intfieldsetset_t intfieldset; // 32λ��������<<<����>>>
    int64fieldsetset_t int64fieldset; // 64λ��������<<<����>>>
    uint8fieldsetset_t uint8fieldset; // 8λ�޷�����������<<<����>>>
    uint16fieldsetset_t uint16fieldset; // 16λ�޷�����������<<<����>>>
    uintfieldsetset_t uintfieldset; // 32λ�޷�����������<<<����>>>
    uint64fieldsetset_t uint64fieldset; // 64λ�޷�����������<<<����>>>
    floatfieldsetset_t floatfieldset; // ����������<<<����>>>
    doublefieldsetset_t doublefieldset; // ˫���ȸ���������<<<����>>>
};


// ����������
class testcfgmgr
{
public:
    // ����������
    typedef std::map<std::string, testcfg_t*> testcfgmap;
    typedef std::map<testcfg_t::stringfieldunique_t, testcfg_t*> stringfieldunique2testcfgmap; // �ַ���Ψһ -> testcfg_t
    typedef std::map<testcfg_t::boolfieldunique_t, testcfg_t*> boolfieldunique2testcfgmap; // bool��Ψһ -> testcfg_t
    typedef std::map<testcfg_t::charfieldunique_t, testcfg_t*> charfieldunique2testcfgmap; // �ַ�Ψһ -> testcfg_t
    typedef std::map<testcfg_t::int16fieldunique_t, testcfg_t*> int16fieldunique2testcfgmap; // 16λ����Ψһ -> testcfg_t
    typedef std::map<testcfg_t::intfieldunique_t, testcfg_t*> intfieldunique2testcfgmap; // 32λ����Ψһ -> testcfg_t
    typedef std::map<testcfg_t::int64fieldunique_t, testcfg_t*> int64fieldunique2testcfgmap; // 64λ����Ψһ -> testcfg_t
    typedef std::map<testcfg_t::uint8fieldunique_t, testcfg_t*> uint8fieldunique2testcfgmap; // 8λ�޷�������Ψһ -> testcfg_t
    typedef std::map<testcfg_t::uint16fieldunique_t, testcfg_t*> uint16fieldunique2testcfgmap; // 16λ�޷�������Ψһ -> testcfg_t
    typedef std::map<testcfg_t::uintfieldunique_t, testcfg_t*> uintfieldunique2testcfgmap; // 32λ�޷�������Ψһ -> testcfg_t
    typedef std::map<testcfg_t::uint64fieldunique_t, testcfg_t*> uint64fieldunique2testcfgmap; // 64λ�޷�������Ψһ -> testcfg_t
    typedef std::map<testcfg_t::floatfieldunique_t, testcfg_t*> floatfieldunique2testcfgmap; // ������Ψһ -> testcfg_t
    typedef std::map<testcfg_t::doublefieldunique_t, testcfg_t*> doublefieldunique2testcfgmap; // ˫���ȸ�����Ψһ -> testcfg_t
    typedef std::vector<testcfg_t> testcfgvec;

public:
	testcfgmgr(){}
	~testcfgmgr(){}

	static testcfgmgr& instance(){
		static testcfgmgr static_testcfgmgr;
		return static_testcfgmgr;
	}

private:
    testcfgmgr& operator=(const testcfgmgr&){ static testcfgmgr mgr; return mgr; }
    testcfgmgr (const testcfgmgr&){}

public:
	// @impl ��ȡ������������
	std::string mgr_name(){ return "testcfg"; }

    // ��ȡ����������·��
    std::string get_path(std::string xml){ return "../../xml/" + xml;}

public:
    // �������������
	virtual bool load();

    // ��ղ���������
    virtual void clear();

// ���뷽��
public:
    bool load_testcfg();

// ��շ���
public:
    void clear_testcfg();

// ���ҷ���
public:
    // ����������
    testcfg_t* get_testcfg(const char* stringfieldprimary, testcfg_t::boolfieldprimary_t boolfieldprimary, testcfg_t::charfieldprimary_t charfieldprimary, testcfg_t::int16fieldprimary_t int16fieldprimary, testcfg_t::intfieldprimary_t intfieldprimary, testcfg_t::int64fieldprimary_t int64fieldprimary, testcfg_t::uint8fieldprimary_t uint8fieldprimary, testcfg_t::uint16fieldprimary_t uint16fieldprimary, testcfg_t::uintfieldprimary_t uintfieldprimary, testcfg_t::uint64fieldprimary_t uint64fieldprimary);
    testcfg_t* get_testcfg_by_stringfieldunique(const char* stringfieldunique);
    testcfg_t* get_testcfg_by_boolfieldunique(testcfg_t::boolfieldunique_t boolfieldunique);
    testcfg_t* get_testcfg_by_charfieldunique(testcfg_t::charfieldunique_t charfieldunique);
    testcfg_t* get_testcfg_by_int16fieldunique(testcfg_t::int16fieldunique_t int16fieldunique);
    testcfg_t* get_testcfg_by_intfieldunique(testcfg_t::intfieldunique_t intfieldunique);
    testcfg_t* get_testcfg_by_int64fieldunique(testcfg_t::int64fieldunique_t int64fieldunique);
    testcfg_t* get_testcfg_by_uint8fieldunique(testcfg_t::uint8fieldunique_t uint8fieldunique);
    testcfg_t* get_testcfg_by_uint16fieldunique(testcfg_t::uint16fieldunique_t uint16fieldunique);
    testcfg_t* get_testcfg_by_uintfieldunique(testcfg_t::uintfieldunique_t uintfieldunique);
    testcfg_t* get_testcfg_by_uint64fieldunique(testcfg_t::uint64fieldunique_t uint64fieldunique);
    testcfg_t* get_testcfg_by_floatfieldunique(testcfg_t::floatfieldunique_t floatfieldunique);
    testcfg_t* get_testcfg_by_doublefieldunique(testcfg_t::doublefieldunique_t doublefieldunique);

// ��ȡ��Ա����
public:
    // ����������
    const testcfgmap& get_testcfgmap(){ return m_testcfgmap; }
    const stringfieldunique2testcfgmap& get_stringfieldunique2testcfgmap(){ return m_stringfieldunique2testcfgmap; }
    const boolfieldunique2testcfgmap& get_boolfieldunique2testcfgmap(){ return m_boolfieldunique2testcfgmap; }
    const charfieldunique2testcfgmap& get_charfieldunique2testcfgmap(){ return m_charfieldunique2testcfgmap; }
    const int16fieldunique2testcfgmap& get_int16fieldunique2testcfgmap(){ return m_int16fieldunique2testcfgmap; }
    const intfieldunique2testcfgmap& get_intfieldunique2testcfgmap(){ return m_intfieldunique2testcfgmap; }
    const int64fieldunique2testcfgmap& get_int64fieldunique2testcfgmap(){ return m_int64fieldunique2testcfgmap; }
    const uint8fieldunique2testcfgmap& get_uint8fieldunique2testcfgmap(){ return m_uint8fieldunique2testcfgmap; }
    const uint16fieldunique2testcfgmap& get_uint16fieldunique2testcfgmap(){ return m_uint16fieldunique2testcfgmap; }
    const uintfieldunique2testcfgmap& get_uintfieldunique2testcfgmap(){ return m_uintfieldunique2testcfgmap; }
    const uint64fieldunique2testcfgmap& get_uint64fieldunique2testcfgmap(){ return m_uint64fieldunique2testcfgmap; }
    const floatfieldunique2testcfgmap& get_floatfieldunique2testcfgmap(){ return m_floatfieldunique2testcfgmap; }
    const doublefieldunique2testcfgmap& get_doublefieldunique2testcfgmap(){ return m_doublefieldunique2testcfgmap; }
    const testcfgvec& get_testcfgvec(){ return m_testcfgvec; }

// ��Ա������
public:
    // ����������
    testcfgmap m_testcfgmap;
    stringfieldunique2testcfgmap m_stringfieldunique2testcfgmap;
    boolfieldunique2testcfgmap m_boolfieldunique2testcfgmap;
    charfieldunique2testcfgmap m_charfieldunique2testcfgmap;
    int16fieldunique2testcfgmap m_int16fieldunique2testcfgmap;
    intfieldunique2testcfgmap m_intfieldunique2testcfgmap;
    int64fieldunique2testcfgmap m_int64fieldunique2testcfgmap;
    uint8fieldunique2testcfgmap m_uint8fieldunique2testcfgmap;
    uint16fieldunique2testcfgmap m_uint16fieldunique2testcfgmap;
    uintfieldunique2testcfgmap m_uintfieldunique2testcfgmap;
    uint64fieldunique2testcfgmap m_uint64fieldunique2testcfgmap;
    floatfieldunique2testcfgmap m_floatfieldunique2testcfgmap;
    doublefieldunique2testcfgmap m_doublefieldunique2testcfgmap;
    testcfgvec m_testcfgvec;
};

#endif // _testcfg_h_
