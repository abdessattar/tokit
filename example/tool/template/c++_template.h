///<------------------------------------------------------------------------------
//< @file:  %cfg%.h
//< @brief: %cfg_member%
//< ��ͷ�ļ��ɹ����Զ����ɣ������ڱ��ļ������Ķ�
//< @Copyright (c) 2014 tokit.
///<------------------------------------------------------------------------------

#ifndef _%cfg%_h_
#define _%cfg%_h_

#include <string>

#include <map>
#include <vector>
#include <set>

#include "type.h"

%structs_part%

// %cfg_member%
class %mgr%
{
public:
%mgr_typedefs_part%

public:
	%mgr%(){}
	~%mgr%(){}

	static %mgr%& instance(){
		static %mgr% static_%mgr%;
		return static_%mgr%;
	}

private:
    %mgr%& operator=(const %mgr%&){ static %mgr% mgr; return mgr; }
    %mgr% (const %mgr%&){}

public:
	// @impl ��ȡ������������
	std::string mgr_name(){ return "%cfg%"; }

    // ��ȡ����������·��
    std::string get_path(std::string xml){ return "../../xml/" + xml;}

public:
    // ����%cfg_member%
	virtual bool load();

    // ���%cfg_member%
    virtual void clear();

// ���뷽��
public:
%mgr_load_funcs_part%

// ��շ���
public:
%mgr_clear_funcs_part%

// ���ҷ���
public:
%mgr_find_funcs_part%

// ��ȡ��Ա����
public:
%mgr_get_funcs_part%

// ��Ա������
public:
%mgr_members_part%
};

#endif // _%cfg%_h_
