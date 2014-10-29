///<------------------------------------------------------------------------------
//< @file:   language\xml\xml_generator.cpp
//< @author: ������
//< @date:   2014��9��25�� 15:49:16
//< @brief:  
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

#include "xml_generator.h"

#include <fstream>
#include <iostream>

#include "cfg.h"
#include "file_util.h"
#include "str_util.h"
#include "echoutil.h"
#include "parser.h"
#include "tickutil.h"

namespace xmlutil{
    void escape_xml(const string &str)
    {
        strutil::replace(const_cast<std::string&>(str), "\"", "&quot;");
    }

    void get_xml_text(const cfg_t &cfg, std::string &xml_text)
    {
        const fieldvec_t &fields = cfg.fields;
        const table_t &table = cfg.table;

        xml_text = "<" + cfg.en_name + " xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">\n";
        xml_text.reserve(cfg.table.size() * fields.size() * 15);

        string row_text;
        for(size_t r = 0; r < cfg.table.size(); r++){
            const row_t &row = table[r];

            row_text = "    <row";
            for(size_t c = 0; c < fields.size(); c++){
                escape_xml(row[c]);
                row_text += " " + cfg.fields[c].en_name + "=\"" + row[c] + "\"";
            }
            row_text += "/>\n";
            xml_text += row_text;
        }

        xml_text += "</" + cfg.en_name + ">";
    }
};

bool xml_generator::generate()
{
    if(false == fileutil::exist(m_xml_dir)){
        ECHO_ERR("����: <%s>·��������", m_xml_dir.c_str());
        return false;
    }

    return save_as_xml();
}

bool xml_generator::save_as_xml()
{
    //Tick tick_now = tickutil::get_tick();

    size_t n_cfg = m_cfgbase.cfgs.size();
    for(size_t n = 0; n < n_cfg; ++n){
        const cfg_t &cfg = m_cfgbase.cfgs[n];
        const string xml = m_xml_dir + "\\" + strip_ext(strip_dir(cfg.en_name)) + ".xml";

        string xml_text;        
        xmlutil::get_xml_text(cfg, xml_text);
        
        ofstream o(xml);
        o << xml_text;

        ECHO_OK("����[%s] -> [%s]�ɹ�", cfg.cn_name.c_str(), xml.c_str());
    }

//     uint32_t passed_ms = tickutil::tick_diff(tick_now);
//     double passed_sec = (double)passed_ms / 1000;
//     ECHO_WARN("����xml���, ����ʱ<%0.3f>��", passed_sec);
    return true;
}
