///<------------------------------------------------------------------------------
//< @file:  dotaequipcfg.h
//< @brief: dotaװ����, dotaӢ�۱�
//< ��ͷ�ļ��ɹ����Զ����ɣ������ڱ��ļ������Ķ�
//< @Copyright (c) 2014 tokit.
///<------------------------------------------------------------------------------

#ifndef _dotaequipcfg_h_
#define _dotaequipcfg_h_

#include <string>

#include <map>
#include <vector>
#include <set>

#include "type.h"

// dotaװ����
struct dotaequipcfg_t{
    typedef uint32 id_t; // ��ƷID<<<Ψһ>>>
    typedef std::string name_t; // ��Ʒ����<<<Ψһ>>>
    typedef std::vector<uint32> bornlistvec_t; // �ϳ��б�<<<����>>>
    typedef std::vector<uint8> bornnumvec_t; // �ϳ�����<<<����>>>

    dotaequipcfg_t();

    id_t id; // ��ƷID<<<Ψһ>>>
    name_t name; // ��Ʒ����<<<Ψһ>>>
    std::string desc; // ����
    uint32 price; // �۳��۸�
    bool isdrop; // �Ƿ���������
    int32 attack; // ������
    bornlistvec_t bornlist; // �ϳ��б�<<<����>>>
    bornnumvec_t bornnum; // �ϳ�����<<<����>>>
};

// dotaӢ�۱�
struct dotaherocfg_t{
    typedef uint32 id_t; // Ӣ��ID<<<Ψһ>>>
    typedef std::string name_t; // Ӣ������<<<Ψһ>>>

    dotaherocfg_t();

    id_t id; // Ӣ��ID<<<Ψһ>>>
    name_t name; // Ӣ������<<<Ψһ>>>
    double strength; // ����
    double agile; // ����
    double intelligense; // ����
};


// dotaװ����, dotaӢ�۱�
class dotaequipcfgmgr
{
public:
    // dotaװ����
    typedef std::map<dotaequipcfg_t::id_t, dotaequipcfg_t*> id2dotaequipcfgmap; // ��ƷID -> dotaequipcfg_t
    typedef std::map<dotaequipcfg_t::name_t, dotaequipcfg_t*> name2dotaequipcfgmap; // ��Ʒ���� -> dotaequipcfg_t
    typedef std::vector<dotaequipcfg_t> dotaequipcfgvec;

    // dotaӢ�۱�
    typedef std::map<dotaherocfg_t::id_t, dotaherocfg_t*> id2dotaherocfgmap; // Ӣ��ID -> dotaherocfg_t
    typedef std::map<dotaherocfg_t::name_t, dotaherocfg_t*> name2dotaherocfgmap; // Ӣ������ -> dotaherocfg_t
    typedef std::vector<dotaherocfg_t> dotaherocfgvec;

public:
	dotaequipcfgmgr(){}
	~dotaequipcfgmgr(){}

	static dotaequipcfgmgr& instance(){
		static dotaequipcfgmgr static_dotaequipcfgmgr;
		return static_dotaequipcfgmgr;
	}

private:
    dotaequipcfgmgr& operator=(const dotaequipcfgmgr&){ static dotaequipcfgmgr mgr; return mgr; }
    dotaequipcfgmgr (const dotaequipcfgmgr&){}

public:
	// @impl ��ȡ������������
	std::string mgr_name(){ return "dotaequipcfg"; }

    // ��ȡ����������·��
    std::string get_path(std::string xml){ return "../../xml/" + xml;}

public:
    // ����dotaװ����, dotaӢ�۱�
	virtual bool load();

    // ���dotaװ����, dotaӢ�۱�
    virtual void clear();

// ���뷽��
public:
    bool load_dotaequipcfg();
    bool load_dotaherocfg();

// ��շ���
public:
    void clear_dotaequipcfg();
    void clear_dotaherocfg();

// ���ҷ���
public:
    // dotaװ����
    dotaequipcfg_t* get_dotaequipcfg_by_id(dotaequipcfg_t::id_t id);
    dotaequipcfg_t* get_dotaequipcfg_by_name(const char* name);

    // dotaӢ�۱�
    dotaherocfg_t* get_dotaherocfg_by_id(dotaherocfg_t::id_t id);
    dotaherocfg_t* get_dotaherocfg_by_name(const char* name);

// ��ȡ��Ա����
public:
    // dotaװ����
    const id2dotaequipcfgmap& get_id2dotaequipcfgmap(){ return m_id2dotaequipcfgmap; }
    const name2dotaequipcfgmap& get_name2dotaequipcfgmap(){ return m_name2dotaequipcfgmap; }
    const dotaequipcfgvec& get_dotaequipcfgvec(){ return m_dotaequipcfgvec; }

    // dotaӢ�۱�
    const id2dotaherocfgmap& get_id2dotaherocfgmap(){ return m_id2dotaherocfgmap; }
    const name2dotaherocfgmap& get_name2dotaherocfgmap(){ return m_name2dotaherocfgmap; }
    const dotaherocfgvec& get_dotaherocfgvec(){ return m_dotaherocfgvec; }

// ��Ա������
public:
    // dotaװ����
    id2dotaequipcfgmap m_id2dotaequipcfgmap;
    name2dotaequipcfgmap m_name2dotaequipcfgmap;
    dotaequipcfgvec m_dotaequipcfgvec;

    // dotaӢ�۱�
    id2dotaherocfgmap m_id2dotaherocfgmap;
    name2dotaherocfgmap m_name2dotaherocfgmap;
    dotaherocfgvec m_dotaherocfgvec;
};

#endif // _dotaequipcfg_h_
