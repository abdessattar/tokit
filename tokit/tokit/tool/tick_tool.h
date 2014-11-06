///<------------------------------------------------------------------------------
//< @file:   tick_tool.h
//< @author: ������
//< @date:   2014��9��20�� 11:46:18
//< @brief:  
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

#ifndef _ticktool_h_
#define _ticktool_h_

#include "type.h"

typedef uint64 Tick;
namespace ticktool
{
    Tick get_tick();

    // ��������ʱ�����ڵĺ����
    uint32_t tick_diff(Tick old_tick);
}

class tick_t
{
public:
    tick_t()
    {
        start_tick();
    }

    void start_tick()
    {
        m_tick = ticktool::get_tick();
    }

    // ������
    double end_tick();

private:
    Tick m_tick;
};

#endif //_ticktool_h_