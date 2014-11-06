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
#include "file_tool.h"
#include "str_tool.h"
#include "echo_tool.h"
#include "tick_tool.h"

#include "parser.h"

namespace xmltool{
    // ת��:
    //     1. ���� -> &quot;
    void escape_xml(string &str)
    {
        strtool::replace(str, "\"", "&quot;");
    }

    // ������ƴ�ӳ�xml��ʽ
    void slice_xml_text(const cfg_t &cfg, std::string &xml_text)
    {
        const fieldvec_t &fields = cfg.fields;
        table_t &table = *(const_cast<table_t*>(&cfg.table));

        xml_text = "<" + cfg.en_name + " xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">\n";
        xml_text.reserve(cfg.table.size() * fields.size() * 15);

        string row_text;
        for(size_t r = 0; r < cfg.table.size(); r++){
            row_t &row = table[r];

            // ������ƴ�ӳ�����<row a="a1" b="b1" c="c1"....>��xml�ı�
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
    if(false == filetool::exist(m_xml_dir)){
        ECHO_ERR("����: <%s>·��������", m_xml_dir.c_str());
        return false;
    }

    return save_as_xml();
}

bool xml_generator::save_as_xml()
{

    // ��excel�и������������ݵ�������Ӧ��xml�ļ���
    size_t n_cfg = m_cfgbase.cfgs.size();
    for(size_t n = 0; n < n_cfg; ++n){
        const cfg_t &cfg = m_cfgbase.cfgs[n];
        const string xml = m_xml_dir + "\\" + strip_ext(strip_dir(cfg.en_name)) + ".xml";

        string xml_text;        
        xmltool::slice_xml_text(cfg, xml_text);

        ofstream o(xml);
        o << xml_text;
        ECHO_OK("����[%s] -> [%s]�ɹ�", cfg.cn_name.c_str(), xml.c_str());
    }

    return true;
}
