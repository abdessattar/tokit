///<------------------------------------------------------------------------------
//< @file:  dotaequipcfg.h
//< @brief: dotaװ����, dotaӢ�۱�, dota���ܱ�, dota�����
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

    std::string print() const;

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

    std::string print() const;

    id_t id; // Ӣ��ID<<<Ψһ>>>
    name_t name; // Ӣ������<<<Ψһ>>>
    double strength; // ����
    double agile; // ����
    double intelligense; // ����
};

// dota���ܱ�
struct dotaskillcfg_t{
    typedef uint32 id_t; // Ӣ��ID<<<Ψһ>>>
    typedef std::string name_t; // Ӣ������<<<Ψһ>>>

    dotaskillcfg_t();

    std::string print() const;

    id_t id; // Ӣ��ID<<<Ψһ>>>
    name_t name; // Ӣ������<<<Ψһ>>>
    double strength; // ����
    double agile; // ����
    double intelligense; // ����
};

// dota�����
struct dotamonstercfg_t{
    typedef uint32 id_t; // Ӣ��ID<<<Ψһ>>>
    typedef std::string name_t; // Ӣ������<<<Ψһ>>>

    dotamonstercfg_t();

    std::string print() const;

    id_t id; // Ӣ��ID<<<Ψһ>>>
    name_t name; // Ӣ������<<<Ψһ>>>
    double strength; // ����
    double agile; // ����
    double intelligense; // ����
};


// dotaװ����, dotaӢ�۱�, dota���ܱ�, dota�����
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

    // dota���ܱ�
    typedef std::map<dotaskillcfg_t::id_t, dotaskillcfg_t*> id2dotaskillcfgmap; // Ӣ��ID -> dotaskillcfg_t
    typedef std::map<dotaskillcfg_t::name_t, dotaskillcfg_t*> name2dotaskillcfgmap; // Ӣ������ -> dotaskillcfg_t
    typedef std::vector<dotaskillcfg_t> dotaskillcfgvec;

    // dota�����
    typedef std::map<dotamonstercfg_t::id_t, dotamonstercfg_t*> id2dotamonstercfgmap; // Ӣ��ID -> dotamonstercfg_t
    typedef std::map<dotamonstercfg_t::name_t, dotamonstercfg_t*> name2dotamonstercfgmap; // Ӣ������ -> dotamonstercfg_t
    typedef std::vector<dotamonstercfg_t> dotamonstercfgvec;

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

    // ��ȡxml�ļ�·��
    std::string get_path(std::string xml){ return "../../xml/" + xml;}

public:
    // ����dotaװ����, dotaӢ�۱�, dota���ܱ�, dota�����
	virtual bool load();

    // ���dotaװ����, dotaӢ�۱�, dota���ܱ�, dota�����
    virtual void clear();

public:
    bool load_dotaequipcfg();
    bool load_dotaherocfg();
    bool load_dotaskillcfg();
    bool load_dotamonstercfg();

public:
    void clear_dotaequipcfg();
    void clear_dotaherocfg();
    void clear_dotaskillcfg();
    void clear_dotamonstercfg();

public:
    // dotaװ����
    const dotaequipcfg_t* get_dotaequipcfg_by_id(dotaequipcfg_t::id_t id);
    const dotaequipcfg_t* get_dotaequipcfg_by_name(const char* name);
    const id2dotaequipcfgmap& get_id2dotaequipcfgmap(){ return m_id2dotaequipcfgmap; }
    const name2dotaequipcfgmap& get_name2dotaequipcfgmap(){ return m_name2dotaequipcfgmap; }
    const dotaequipcfgvec& get_dotaequipcfgvec(){ return m_dotaequipcfgvec; }

    // dotaӢ�۱�
    const dotaherocfg_t* get_dotaherocfg_by_id(dotaherocfg_t::id_t id);
    const dotaherocfg_t* get_dotaherocfg_by_name(const char* name);
    const id2dotaherocfgmap& get_id2dotaherocfgmap(){ return m_id2dotaherocfgmap; }
    const name2dotaherocfgmap& get_name2dotaherocfgmap(){ return m_name2dotaherocfgmap; }
    const dotaherocfgvec& get_dotaherocfgvec(){ return m_dotaherocfgvec; }

    // dota���ܱ�
    const dotaskillcfg_t* get_dotaskillcfg_by_id(dotaskillcfg_t::id_t id);
    const dotaskillcfg_t* get_dotaskillcfg_by_name(const char* name);
    const id2dotaskillcfgmap& get_id2dotaskillcfgmap(){ return m_id2dotaskillcfgmap; }
    const name2dotaskillcfgmap& get_name2dotaskillcfgmap(){ return m_name2dotaskillcfgmap; }
    const dotaskillcfgvec& get_dotaskillcfgvec(){ return m_dotaskillcfgvec; }

    // dota�����
    const dotamonstercfg_t* get_dotamonstercfg_by_id(dotamonstercfg_t::id_t id);
    const dotamonstercfg_t* get_dotamonstercfg_by_name(const char* name);
    const id2dotamonstercfgmap& get_id2dotamonstercfgmap(){ return m_id2dotamonstercfgmap; }
    const name2dotamonstercfgmap& get_name2dotamonstercfgmap(){ return m_name2dotamonstercfgmap; }
    const dotamonstercfgvec& get_dotamonstercfgvec(){ return m_dotamonstercfgvec; }

public:
    // dotaװ����
    id2dotaequipcfgmap m_id2dotaequipcfgmap; // ��ƷID -> dotaequipcfg
    name2dotaequipcfgmap m_name2dotaequipcfgmap; // ��Ʒ���� -> dotaequipcfg
    dotaequipcfgvec m_dotaequipcfgvec;

    // dotaӢ�۱�
    id2dotaherocfgmap m_id2dotaherocfgmap; // Ӣ��ID -> dotaherocfg
    name2dotaherocfgmap m_name2dotaherocfgmap; // Ӣ������ -> dotaherocfg
    dotaherocfgvec m_dotaherocfgvec;

    // dota���ܱ�
    id2dotaskillcfgmap m_id2dotaskillcfgmap; // Ӣ��ID -> dotaskillcfg
    name2dotaskillcfgmap m_name2dotaskillcfgmap; // Ӣ������ -> dotaskillcfg
    dotaskillcfgvec m_dotaskillcfgvec;

    // dota�����
    id2dotamonstercfgmap m_id2dotamonstercfgmap; // Ӣ��ID -> dotamonstercfg
    name2dotamonstercfgmap m_name2dotamonstercfgmap; // Ӣ������ -> dotamonstercfg
    dotamonstercfgvec m_dotamonstercfgvec;
};

#endif // _dotaequipcfg_h_
