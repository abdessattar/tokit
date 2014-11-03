///<------------------------------------------------------------------------------
//< @file:   tokit\tokit\parser.cpp
//< @author: ������
//< @date:   2014��9��25�� 16:20:30
//< @brief:  
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

#include "parser.h"

#include <algorithm>
#include <fstream>
#include <iostream>

#include <libxl.h>

#include "excel/CApplication.h"  
#include "excel/CRange.h"  
#include "excel/CWorkbook.h"  
#include "excel/CWorkbooks.h"  
#include "excel/CWorksheet.h"
#include "excel/CWorksheets.h"

#include "excel_util.h"
#include "str_util.h"
#include "echoutil.h"
#include "tickutil.h"
#include "file_util.h"

using namespace excelutil;
using namespace libxl;

COleSafeArray* parser::g_ole_cell_array = NULL;


namespace parseutil
{
    // �����������������ʼ��
    bool parse_each_region_begin_row(libxl::Sheet &sheet, int row_cnt, cfg_t &cfg, errvec_t& errvec)
    {
        // 1. �ӿ��п�ʼ�����ҵ��ļ�����������ʼ��
        for(int row = excel_row_cfg; row < row_cnt; row++){
            if (!is_cell_empty(sheet, row, 1)){
                cfg.row_file_cfg_begin = row;
                break;
            }
        }

        if (0 == cfg.row_file_cfg_begin){
            errvec.push_back(getmsg("����δ<%s>�����ļ�Ӣ����", cfg.cn_name.c_str()));
            return false;
        }

        // 2. ���ļ���������ʼ���������������ҵ��ֶζ���������ʼ��
        for(int row = cfg.row_file_cfg_begin + cfg_row_max; row < row_cnt; row++){
            if (!is_cell_empty(sheet, row, 1)){
                cfg.row_fields_begin = row;
                break;
            }
        }

        if (0 == cfg.row_fields_begin){
            errvec.push_back(getmsg("����δ��<%s>�����ҵ��ֶζ���", cfg.cn_name.c_str()));
            return false;
        }

        // 3. ���ֶζ�������ʼ�����������ҵ�����������ʼ��
        for(int row = cfg.row_fields_begin + field_row_max + 1; row < row_cnt; row++){
            if (!is_cell_empty(sheet, row, 1)){
                cfg.row_data_begin = row;
                break;
            }
        }

        if (0 == cfg.row_data_begin){
            errvec.push_back(getmsg("����δ��<%s>�����ҵ�����", cfg.cn_name.c_str()));
            return false;
        }

        return true;
    }

    // �����ļ�������
	bool parse_cfg(libxl::Sheet &sheet, int row_cnt, cfg_t &cfg, errvec_t& errvec)
	{
        if (0 == cfg.row_file_cfg_begin){
            return false;
        }

        // �ļ�����
		cfg.en_name = get_cell_str(sheet, cfg.row_file_cfg_begin + cfg_row_1, cfg_col_en_name);

        // �����������
		cfg.maxcnt  = get_cell_int(sheet, cfg.row_file_cfg_begin + cfg_row_1, cfg_col_max_cnt);

        if (cfg.en_name.empty()){
            errvec.push_back(getmsg("����<%s>ʧ�ܣ������������Ӣ����", cfg.en_name.c_str()));
            return false;
        }

		return true;
	}

    bool is_unique_key_by_str(std::string &str)
    {
        bool is_unique_key = false;
        is_unique_key |= (str.find("unique") != string::npos);
        is_unique_key |= (str.find("Ψһ") != string::npos);
        return is_unique_key;
    }

    bool is_primary_key_by_str(std::string &str)
    {
        bool is_unique_key = false;
        is_unique_key |= (str.find("primary") != string::npos);
        is_unique_key |= (str.find("����") != string::npos);
        return is_unique_key;
    }

    bool is_array_by_str(std::string &str)
    {
        bool is_array = false;
        is_array |= (str.find("vector") != string::npos);
        is_array |= (str.find("vec") != string::npos);
        is_array |= (str.find("array") != string::npos);
        is_array |= (str.find("����") != string::npos);
        return is_array;
    }

    // �Ƿ��Ǽ�������
    bool is_set_by_str(std::string &str)
    {
        bool is_array = false;
        is_array |= (str.find("set") != string::npos);
        is_array |= (str.find("����") != string::npos);
        return is_array;
    }
    
    // ����ָ���е��ֶζ���
    bool parse_field(libxl::Sheet &sheet, cfg_t &cfg, int col, field_t &field, errvec_t& errvec)
	{
        // ȡ���ֶ�Ӣ����
		field.en_name = strutil::trim(get_cell_str(sheet, cfg.row_fields_begin + field_row_en_name, col));
		if(field.en_name.empty()){
            // �������ֶ���ֹͣ����
			return true;
		}

        // ȡ���ֶ�����
		std::string fieldtype_cell = strutil::trim(get_cell_str(sheet, cfg.row_fields_begin + field_row_data_type, col));
		field.fieldtype = cfgutil::type_name_2_enum(fieldtype_cell.c_str());
		
        // ȡ���ֶ�����
        std::string fieldattr_cell = strutil::trim(get_cell_str(sheet, cfg.row_fields_begin + field_row_is_unique, col));

        field.fieldattr = field_t::fieldattr_none;
        if(is_unique_key_by_str(fieldattr_cell)){
            field.fieldattr = field_t::fieldattr_1_key;
        }else if(is_primary_key_by_str(fieldattr_cell)){
            field.fieldattr = field_t::fieldattr_n_key;
        }else if(is_array_by_str(fieldattr_cell)){
            field.fieldattr = field_t::fieldattr_array;
        }else if(is_set_by_str(fieldattr_cell)){
            field.fieldattr = field_t::fieldattr_set;
        }

        field.cn_name = strutil::trim(get_cell_str(sheet, cfg.row_data_begin, col));
        field.comment = field.cn_name;

        if(field.cn_name.empty()){
            errvec.push_back(getmsg("������<%s>��ʱ��������������������Ϊ��", col));
            return false;
        }

        if(fieldtype_cell.empty()){
            errvec.push_back(getmsg("����<%s>�ֶ�ʱ�������󣺸��ֶε�����Ϊ��", field.cn_name.c_str()));
            return false;
        }

        if(fieldtype_none == field.fieldtype){
            errvec.push_back(getmsg("����<%s>�ֶ�ʱ�������󣺲�֧��<%s>���͵��ֶ�", field.cn_name.c_str(), fieldtype_cell.c_str()));
            return false;
        }

		return true;
	}

    // �����ֶζ�����
	bool parse_fields(libxl::Sheet &sheet, int row_cnt, int col_cnt, cfg_t &cfg, errvec_t& errvec)
	{
        if (0 == cfg.row_fields_begin){
            return false;
        }

		bool succ = true;

        field_t field;

        // �ӵ�һ�п�ʼ��һ��һ�����ҽ������ֶΣ�ֱ����������
        for(int col = 1; col <= col_cnt; col++){
            // �������ֶ�
            bool ok = parse_field(sheet, cfg, col, field, errvec);
            if(false == ok){
                succ = false;
                continue;
            }

            // �������ֶ���ֹͣ����
            if (field.en_name.empty()){
                break;
            }

            field_t *old_field = cfg.getfield(field.en_name.c_str());
			if(old_field){
				errvec.push_back(getmsg("���󣺶���������ͬ�����ֶ�<%s>", field.en_name.c_str()));
				errvec.push_back(getmsg("       <%-6s = %s>", old_field->get_field_type_name().c_str(), old_field->en_name.c_str()));
				errvec.push_back(getmsg("       <%-6s = %s>", field.get_field_type_name().c_str(), field.en_name.c_str()));

				succ = false;
				continue;
			}

            // ������ֶ�������֮һ���򽫸��ֶε�λ�ô��������б�
			if(field.is_n_key()){
				cfg.keys.push_back(cfg.fields.size());
			}

			cfg.fields.push_back(field);
		}

		if(cfg.fields.empty()){
			errvec.push_back(getmsg("����δ��<%s>�����ֶ�", cfg.cn_name.c_str()));
		}

        // �����������1���ֶ���ɣ��������ֶε������滻Ϊ<Ψһ>
        size_t n_key = cfg.keys.size();
        if (1 == n_key){
            field_t &primary_key_field = cfg.fields[cfg.keys[0]];
            primary_key_field.fieldattr = field_t::fieldattr_1_key;
        }

		std::sort(cfg.keys.begin(), cfg.keys.end());
		return succ;
	}

    // ��������������
    bool parse_data(libxl::Sheet &sheet, int row_cnt, int col_cnt, cfg_t &cfg, errvec_t& errvec)
    {
        bool is_empty = (cfg.row_data_begin + 1 > (size_t)row_cnt);
        if (is_empty){
            return true;
        }

        bool is_ok = true;

        row_t r;
        r.resize(cfg.fields.size());
        cfg.table.reserve(row_cnt - cfg.row_data_begin);

        // �����������к��д����Ӧ������
        for(int row = cfg.row_data_begin + 1; row <= row_cnt; row++){
            bool is_empty_row = false;

            for(size_t col = 1; col <= cfg.fields.size(); col++){
                 r[col - 1] = get_cell_str(sheet, row, col);
                
                 // һ������ĳ�еĵ�һ����Ԫ��Ϊ�գ���ֹͣ����
                 if (1 == col){
                    if (r[col - 1].empty()){
                        is_empty_row = true;
                        break;
                    }
                    /*
                    else{
                        errvec.push_back(getmsg("������<%u>��ʱ��������<%s>�ֶε�ֵΪ�գ��������ݺ�������", row, cfg.fields[col - 1].cn_name.c_str()));
                        cfg.table.clear();
                        is_ok = false;
                        break;
                    }
                    */
                }
            }

            if (is_empty_row){
                break;
            }

            cfg.table.push_back(r);
        }
        
        return is_ok;
    }

    // ��������������������ݣ��������������ŵ���Ӧ�ṹ����
	bool parse_cfg_from_sheet(libxl::Sheet &sheet, cfg_t &cfg, errvec_t& errvec, enum_parse_option parse_option /* = parse_option_ignore_data */)
	{
        // 1. ��ȡexcel�������������
		int row_cnt = get_row_cnt(sheet);
		int col_cnt = get_col_cnt(sheet);

        if(0 == row_cnt || 0 == col_cnt){
            errvec.push_back(getmsg("��������<%s>���ñ�����Ϊ��", sheet.name()));
            return false;
        }

		if(row_cnt < excel_row_min){
			errvec.push_back(getmsg("����<%s>ʧ�ܣ�����е�ǰֻ��<%u>�У�����Ӧ��<%u>��", sheet.name(), row_cnt, excel_row_min));
			return false;
		}

        if(col_cnt < cfg_col_max - 1){
            errvec.push_back(getmsg("����<%s>ʧ�ܣ�����е�ǰֻ��<%u>�У�����Ӧ��<%u>��", sheet.name(), col_cnt, cfg_col_max - 1));
            return false;
        }

        std::wstring w_name = sheet.name();

        // 2. ȡ�������������
		cfg.cn_name = strutil::wstring2string(sheet.name());

        // ��ʼ����
        bool succ = true;

        // 3. ���������������ʼ�У�����3�������ļ����������ֶζ�������������
        succ &= parse_each_region_begin_row(sheet, row_cnt, cfg, errvec);

        // 4. �����ļ�������
		succ &= parse_cfg(sheet, row_cnt, cfg, errvec);

        // 5. �����ֶζ�����
        succ &= parse_fields(sheet, row_cnt, col_cnt, cfg, errvec);

        // 6. ����������
        if (parse_option_read_data == parse_option){
            succ &= parse_data(sheet, row_cnt, col_cnt, cfg, errvec);
        }

		return succ;
	}

    // ����Ƿ������oleԤ���أ��Լӿ�֮��Ķ�ȡ�ٶ�
    void check_need_preload_sheet(CWorksheets &sheets, int sheet_idx, bool need_ole_load)
    {
        if (need_ole_load){
            CWorksheet ole_sheet = sheets.get_Item(COleVariant((long)(sheet_idx)));

            static COleSafeArray s_ole_safe_array;
            s_ole_safe_array.Clear();
            parser::g_ole_cell_array = &s_ole_safe_array;

            excelutil::pre_load_sheet(ole_sheet, *parser::g_ole_cell_array);
        }
    }
};

bool parser::parse_excel(const string &xlsx, cfgbase_t &cfgbase, errvec_t &errvec, enum_parse_option parse_option /* = parse_option_skip_data */)
{
    tick_t parse_tick;

    if(false == fileutil::exist(xlsx)){
        errvec.push_back(xlsx + "�ļ�������!");
        return false;
    }
    
    libxl::Book *book = xlCreateXMLBook();
    
    // ���ǽ�ʹ��2�ַ�����ȡexcel��libxl�⡢ole��2�������ǣ�
    //     a. libxl�ٶȺܿ죬ole�ٶȺ���
    //     b. libxl��֧�ֹ�ʽ��ole֧�ֹ�ʽ
    
    // 1. ��libxl�ķ�ʽ����excel
    std::wstring w_xlsx = strutil::string2wstring(xlsx);
    if(!book->load(w_xlsx.c_str())){
        return false;
    }

    CApplication excel_app;
    CWorkbooks books;
    CWorkbook olebook;
    CWorksheets sheets;

    bool succ = true;

    // 2. ʹ��libxl���excel�ļ����Ƿ��й�ʽ
    excelutil::formula_flag_vec each_sheet_formula_flags;
    bool is_need_ole_open = is_excel_contain_formula_cell(*book, each_sheet_formula_flags);

    // 2.1. ����й�ʽ����ͨ��ole��ʽ�ټ���һ��excel
    if (is_need_ole_open){
        succ = excelutil::ole_open_excel(xlsx, excel_app, books, olebook, sheets);
        if (!succ){
            return false;
        }
    }

    // 3. ���ν�������������
    for(int i = 0; i < book->sheetCount(); i++){   
        cfg_t cfg;
        libxl::Sheet *sheet = book->getSheet(i);
        if (!sheet){
            continue;
        }
        
        // 3.1 ����������к���ʽ�������oleԤ��ȡ���Լӿ�֮��Ķ�ȡ�ٶ�
        parseutil::check_need_preload_sheet(sheets, i + 1, each_sheet_formula_flags[i]);

        // 3.2 ����������������ݣ����������ŵ�cfg��
        bool ok = parseutil::parse_cfg_from_sheet(*sheet, cfg, errvec, parse_option);
        if(false == ok){
            succ = false;
            continue;
        }

        cfg_t *conflict_by_prop = cfgbase.find_by_en_name(cfg.en_name.c_str());
        if(conflict_by_prop){
            errvec.push_back(getmsg("���󣺶���������ͬ�����ļ�<%s>", cfg.cn_name.c_str()));
            errvec.push_back(getmsg("       <%s = %s>", conflict_by_prop->cn_name.c_str(), conflict_by_prop->en_name.c_str()));
            errvec.push_back(getmsg("       <%s = %s>", cfg.cn_name.c_str(), cfg.en_name.c_str()));

            succ = false;
            continue;
        }

        cfgbase.cfgs.push_back(cfg);
    }

    // ����һ������������Ϊ�ļ��������磬excel����2��������item��hero����item��Ϊ�ļ�����
    if (!cfgbase.cfgs.empty()){
        cfgbase.filename = cfgbase.cfgs[0].en_name;
    }

    // 4. �ͷ�ole��Դ
    if (is_need_ole_open){
        tick_t close_tick;
        excelutil::ole_close_excel(w_xlsx, excel_app, books, olebook, sheets);
    }

    ECHO_WARN("ִ�����, ����ʱ<%0.3f>��", parse_tick.end_tick());
    return succ;
}
