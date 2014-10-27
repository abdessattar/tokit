///<------------------------------------------------------------------------------
//< @file:   tickutil.h
//< @author: ������
//< @date:   2014��9��20�� 11:46:18
//< @brief:  
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

#ifndef _tickutil_h_
#define _tickutil_h_

#include "type.h"

typedef uint64_t Tick;
namespace tickutil
{
    Tick get_tick();

    // ��������ʱ�����ڵĺ����
    uint32_t tick_diff(Tick old_tick);
}

#endif //_tickutil_h_