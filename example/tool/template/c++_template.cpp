///<------------------------------------------------------------------------------
//< @file:  %cfg%.cpp
//< @brief: %cfg_member%
//< ��ͷ�ļ��ɹ����Զ����ɣ������ڱ��ļ������Ķ�
//< @Copyright (c) 2014 tokit.
///<------------------------------------------------------------------------------

#include "%cfg%.h"

#include <iostream>
#include <string.h>
#include <rapidxml_utils.hpp>
#include "tokit_util.h"

%structs_ctor%

void %mgr%::clear()
{
%clear_stmt%
}

bool %mgr%::load()
{
	bool is_succ = true;
%load_stmt%
	return is_succ;
}

%mgr_load_funcs_part%

%mgr_clear_funcs_part%

%mgr_find_funcs_part%