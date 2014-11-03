///<------------------------------------------------------------------------------
//< @file:   prop\parser\excel_util.h
//< @author: ������
//< @date:   2014��9��20�� 17:59:45
//< @brief:  
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

#ifndef _excel_util_h_
#define _excel_util_h_

#include <string>
#include <vector>
#include <libxl.h>
#include <xstring>

class CApplication;
class CWorkbooks;
class CWorkbook;
class CWorksheet;
class CWorksheets;
class COleSafeArray;

using std::string;

namespace excelutil
{
    // ͨ��ole�ķ�ʽ��excel��ʵ�����Ǵ�һ��ϵͳ���е�excel���̣��øý��̼��ظ�excel�ļ������Դ�ʱҪ����ص�excel�ļ����ڹر�״̬��������ʧ�ܣ�
    bool ole_open_excel(const string &xlsx, CApplication&, CWorkbooks&, CWorkbook&, CWorksheets&);

	void ole_close_excel(const std::wstring &xlsx, CApplication&, CWorkbooks&, CWorkbook&, CWorksheets&);

    // Ԥ���ص�Ԫ�񣬽�excel�����������Ԥ���ص������У��ӿ�֮���ȡexcel���ٶ�
    void pre_load_sheet(CWorksheet &sheet, COleSafeArray &safe_array);

    // ���excel�ļ����Ƿ��й�ʽ��һ������Ԫ��ر�����⣩�������������������
    typedef std::vector<bool> formula_flag_vec;
    bool is_excel_contain_formula_cell(libxl::Book&, formula_flag_vec&);

    // ��Ԫ���Ƿ�Ϊ��
    bool is_cell_empty(libxl::Sheet &sheet, int row, int col);

    // ��ȡָ����Ԫ����ı����ݣ���������ָ�ʽ������ȻתΪ�ı�
    std::string& get_cell_str(libxl::Sheet &sheet, int row, int col);

    // ��ȡ��������
	int get_cell_int(libxl::Sheet &sheet, int row, int col);

	int get_row_cnt(libxl::Sheet &sheet);

	int get_col_cnt(libxl::Sheet &sheet);
}
#endif //_excel_util_h_