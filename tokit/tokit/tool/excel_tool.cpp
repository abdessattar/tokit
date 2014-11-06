///<------------------------------------------------------------------------------
//< @file:   prop\parser\excel_tool.cpp
//< @author: ������
//< @date:   2014��9��20�� 17:59:55
//< @brief:  
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

#include <afxwin.h>

#include <sstream>
#include <limits>

#include "excel_tool.h"
#include "str_tool.h"
#include "file_tool.h"

#include "excel/CApplication.h"  
#include "excel/CRange.h"  
#include "excel/CWorkbook.h"  
#include "excel/CWorkbooks.h"  
#include "excel/CWorksheet.h"
#include "excel/CWorksheets.h"

#include "Resource.h"
#include "parser.h"

namespace exceltool
{
    bool init_ole()
    {
        if (!AfxOleInit()){
            AfxMessageBox(IDP_OLE_INIT_FAILED);
            return false;
        }

        if (CoInitialize(NULL)!=0) { 
            AfxMessageBox(L"��ʼ��COM֧�ֿ�ʧ��!"); 
            return false;
        }

        return true;
    }

	bool ole_open_excel(const string &xlsx, CApplication &excel_application, CWorkbooks &books, CWorkbook &book, CWorksheets &sheets)
	{
        if(!init_ole()){
            return false;
        }

		if(false == filetool::exist(xlsx)){
			std::string err = xlsx + "�ļ�������!";
			AfxMessageBox(strtool::string2wstring(err).c_str());
			return false;
		}

		//����Excel ������(����Excel)
		if(!excel_application.CreateDispatch(_T("Excel.Application"),NULL)){
			AfxMessageBox(_T("����Excel������ʧ��!"));
			return false;
		}

		excel_application.put_Visible(FALSE);
        excel_application.put_DisplayAlerts(FALSE);
		excel_application.put_UserControl(FALSE);

		//�õ�����������
		books.AttachDispatch(excel_application.get_Workbooks(), TRUE);

        // const std::wstring wstr = 
        const std::wstring w_xlsx = strtool::string2wstring(xlsx); //L"E:\\proj\\github_tokit\\trunk\\example\\excel\\��������.xlsx";

		//��һ�����������粻���ڣ�������һ��������
        LPDISPATCH lpDisp = books.Add(COleVariant(w_xlsx.c_str()));
        if (lpDisp){
            book.AttachDispatch(lpDisp);

            // �õ��������е�Sheet������
            sheets.AttachDispatch(book.get_Sheets());
        }

		return true;
	}

    void ole_close_excel(const std::wstring &xlsx, CApplication &excel_application, CWorkbooks &books, CWorkbook &book, CWorksheets &sheets)
    {
        COleVariant covTrue((short)TRUE), covFalse((short)FALSE);
        COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

        book.Close(COleVariant(short(FALSE)),COleVariant(xlsx.c_str()), covOptional);  
        books.Close(); 

        // �ͷ���Դ
        sheets.ReleaseDispatch();
        book.ReleaseDispatch();
        books.ReleaseDispatch();
        excel_application.Quit();
        excel_application.ReleaseDispatch();
    }

	void pre_load_sheet(CWorksheet &sheet, COleSafeArray &safe_array)
	{
        ///��ǰ�Ĳ�������  
        CRange excel_current_range;
        excel_current_range.AttachDispatch(sheet.get_Cells(), true);  

		CRange used_range = sheet.get_UsedRange();    

		VARIANT ret_ary = used_range.get_Value2();
		if (!(ret_ary.vt & VT_ARRAY)){
			return;
		}

		safe_array.Clear();
		safe_array.Attach(ret_ary); 
	}

    bool is_sheet_contain_formula_cell(libxl::Sheet &sheet)
    {
        int last_row = sheet.lastRow();
        int last_col = sheet.lastCol();

        for(int row = sheet.firstRow(); row < last_row; row++){
            for(int col = sheet.firstCol(); col < last_col; col++){
                if (sheet.isFormula(row, col)){
                    return true;
                    break;
                }
            }
        }

        return false;
    }

    bool is_excel_contain_formula_cell(libxl::Book &book, formula_flag_vec &flags)
    {
        bool is_contain_formula_cell = false;

        int n_sheet = book.sheetCount();
        flags.resize(n_sheet, false);

        for(int i = 0; i < book.sheetCount(); i++){   
            libxl::Sheet *sheet = book.getSheet(i);
            if (is_sheet_contain_formula_cell(*sheet)){
                is_contain_formula_cell = true;
                flags[i] = true;
            }
        }

        return is_contain_formula_cell;
    }

    bool is_cell_empty(libxl::Sheet &sheet, int row, int col)
    {
        row -= 1;
        col -= 1;

        libxl::CellType cell_type = sheet.cellType(row, col);
        return libxl::CELLTYPE_EMPTY == cell_type || libxl::CELLTYPE_BLANK == cell_type;
    }
	
    // ͨ��libxl���ȡ��Ԫ�����ݣ����ӿ��ٶȽϿ죬����֧�ֹ�ʽ��ֻ�ܶ�ȡ��ʽ�����ݣ��޷��õ���ʽ��������
    std::string& libxl_get_cell_str(libxl::Sheet &sheet, int row, int col)
    {
        static const int prec=std::numeric_limits<long long>::digits10 + 10; // 18
        static std::string result;

        libxl::CellType cell_type = sheet.cellType(row, col);
        switch (cell_type)
        {
        case libxl::CELLTYPE_STRING:
            {
                //�ַ���
                const wchar_t *w = sheet.readStr(row, col);
                //const std::wstring wstr(w);
                return strtool::wstring2string(w);
            }
        case libxl::CELLTYPE_NUMBER:
            {
                static std::ostringstream o;
                o.str("");
                o.precision(prec);//����Ĭ�Ͼ���

                double dd = sheet.readNum(row, col);
                o << dd;
                result = o.str();
                break;
            }
        default:
            result = "";
            break;
        }

        return result;
    }

    // ͨ��ole�ķ�ʽ��ȡ��Ԫ�����ݣ�����ole��֧�ֹ�ʽ������tokitֻ�ڵ�Ԫ�񺬹�ʽʱ�ŵ��ñ��ӿڣ�����֮��ͨ��libxl�������ã���Ϊlibxl��ȡ�ٶȿ�ܶ�
    std::string& ole_get_cell_str(COleSafeArray &ole_safe_array, int row, int col)
    {
        static const int prec=std::numeric_limits<long long>::digits10 + 10; // 18
        static COleVariant vResult;
        static CString str;

        //�ַ���
        static long read_address[2];
        static VARIANT val;
        static std::string result;

        read_address[0] = row;
        read_address[1] = col;
        ole_safe_array.GetElement(read_address, &val);
        vResult = val;

        switch(vResult.vt){
        case VT_BSTR:
        {
            //�ַ���
            const wchar_t *w = vResult.bstrVal;
            // const std::wstring wstr(w);
            return strtool::wstring2string(w);
        }
        //��Ԫ��յ�
        case VT_EMPTY:
        //����
        case VT_INT:
            result = "";
            break;
        //8�ֽڵ����� 
        case VT_R8:
        {
            static std::ostringstream oss;
            oss.str("");
            oss.precision(prec);//����Ĭ�Ͼ���

            oss << vResult.dblVal;
            result = oss.str();
            break;
        }
        //ʱ���ʽ
        case VT_DATE:
        {
            SYSTEMTIME st;
            VariantTimeToSystemTime(vResult.date, &st);
            CTime tm(st); 
            str = tm.Format("%Y-%m-%d");
            break;
        }

        default:
            result = "";
            break;
        }

        return result;
    }

    std::string& get_cell_str(libxl::Sheet &sheet, int row, int col)
    {
        row -= 1;
        col -= 1;

        static std::string result;
        bool is_formula = sheet.isFormula(row, col);
        if (is_formula){
            return ole_get_cell_str(*parser::g_ole_cell_array, row + 1, col + 1);
        }else{
            return libxl_get_cell_str(sheet, row, col);
        }

        return result;
    }

	int get_cell_int(libxl::Sheet &sheet, int row, int col)
	{
        row -= 1;
        col -= 1;

        int ret = 0;

		libxl::CellType cell_type = sheet.cellType(row, col);
        switch (cell_type)
        {
        case libxl::CELLTYPE_NUMBER:
        case libxl::CELLTYPE_BOOLEAN:
        {
            double dd = sheet.readNum(row, col);
            ret = (int)dd;
            break;
        }
        }

		return ret;
	}

	int get_cell_int(COleSafeArray &ole_safe_array, int row, int col)
	{
		COleVariant vResult ;
		int ret;

		//�ַ���
		long read_address[2];
		VARIANT val;
		read_address[0] = row;
		read_address[1] = col;
		ole_safe_array.GetElement(read_address, &val);
		vResult = val;

		//����
		switch(vResult.vt)
		{
		case VT_INT:
			ret = vResult.intVal;
			break;

		case VT_R8:
			ret = (int)vResult.dblVal;
			break;

		default:
			ret = 0;
			break;
		}

		return ret;
	}

	int get_row_cnt(libxl::Sheet &sheet)
	{
        int first_row = sheet.firstRow();
        int last_row = sheet.lastRow();

        int row_cnt = last_row > first_row ? last_row - first_row : 0;
        return row_cnt;
	}

	int get_col_cnt(libxl::Sheet &sheet)
	{
        int first_col = sheet.firstCol();
        int last_col = sheet.lastCol();

        int col_cnt = last_col > first_col ? last_col - first_col : 0;
        return col_cnt;
	}
}