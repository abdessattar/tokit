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

%structs%

// %cfg_member%
class %mgr%
{
public:
%typedefs%

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

    // ��ȡxml�ļ�·��
    std::string get_path(std::string xml){ return "../../xml/" + xml;}

public:
    // ����%cfg_member%
	virtual bool load();

    // ���%cfg_member%
    virtual void clear();

public:
%load_funcs%

public:
%clear_funcs%

public:
%get_funcs%

public:
%members%
};

#endif // _%cfg%_h_
