///<------------------------------------------------------------------------------
//< @file:   prop\parser\excel_util.cpp
//< @author: ������
//< @date:   2014��9��20�� 17:59:55
//< @brief:  
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

#include <afxwin.h>

#include <sstream>
#include <limits>

#include "excel_util.h"

#include "file_util.h"

#include "excel/CApplication.h"  
#include "excel/CRange.h"  
#include "excel/CWorkbook.h"  
#include "excel/CWorkbooks.h"  
#include "excel/CWorksheet.h"
#include "excel/CWorksheets.h"

#include "Resource.h"

namespace excelutil
{
    bool init_ole()
    {
        if (!AfxOleInit()){
            AfxMessageBox(IDP_OLE_INIT_FAILED);
            return false;
        }

        if (CoInitialize(NULL)!=0) { 
            AfxMessageBox("��ʼ��COM֧�ֿ�ʧ��!"); 
            return false;
        }

        return true;
    }

	bool open_sheets_of_excel(const string &xlsx, CApplication &excel_application, CWorkbooks &books, CWorkbook &book, CWorksheets &sheets)
	{
        if(!init_ole()){
            return false;
        }

		if(false == fileutil::exist(xlsx)){
			std::string err = xlsx + "�ļ�������!";
			AfxMessageBox(_T(err.c_str()));
			return false;
		}

		CRange range;
		LPDISPATCH lpDisp = NULL;

		//����Excel ������(����Excel)
		if(!excel_application.CreateDispatch(_T("Excel.Application"),NULL)){
			AfxMessageBox(_T("����Excel������ʧ��!"));
			return false;
		}

        /*
		// �жϵ�ǰExcel�İ汾
		CString strExcelVersion = excel_application.get_Version();
		int iStart = 0;
		strExcelVersion = strExcelVersion.Tokenize(_T("."), iStart);
		if (_T("11") == strExcelVersion){
			AfxMessageBox(_T("��ǰExcel�İ汾��2003��"));
		}else if (_T("12") == strExcelVersion){
			AfxMessageBox(_T("��ǰExcel�İ汾��2007��"));
		}else{
			AfxMessageBox(_T("��ǰExcel�İ汾�������汾��"));
		}
        */

		excel_application.put_Visible(FALSE);
        excel_application.put_DisplayAlerts(FALSE);
		excel_application.put_UserControl(FALSE);

		/*�õ�����������*/
		books.AttachDispatch(excel_application.get_Workbooks(), TRUE);

		/*��һ�����������粻���ڣ�������һ��������*/
		CString strBookPath = _T(xlsx.c_str());

        lpDisp = books.Add(COleVariant(xlsx.c_str()));
        if (lpDisp){
            book.AttachDispatch(lpDisp);

            // �õ��������е�Sheet������
            sheets.AttachDispatch(book.get_Sheets());
        }

        /*
		try
		{
			// ��һ��������
			lpDisp = books.Open(strBookPath, 
				vtMissing, vtMissing, vtMissing, vtMissing, vtMissing,
				vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, 
				vtMissing, vtMissing, vtMissing, vtMissing);
			book.AttachDispatch(lpDisp);
		}
		catch(...)
		{
			// ����һ���µĹ�����
			lpDisp = books.Add(vtMissing);
			book.AttachDispatch(lpDisp);
		}

		// �õ��������е�Sheet������
		sheets.AttachDispatch(book.get_Sheets());
        */
		return true;
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

    bool is_cell_empty(COleSafeArray &ole_safe_array, int row, int col)
    {
        long read_address[2];
        VARIANT val;
        read_address[0] = row;
        read_address[1] = col;
        ole_safe_array.GetElement(read_address, &val);

        return VT_EMPTY == val.vt;
    }

	std::string get_cell_str(COleSafeArray &ole_safe_array, int row, int col)
	{
        std::string result;
        fast_get_cell_str(ole_safe_array, row, col, result);

        return result;
	}

    void fast_get_cell_str(COleSafeArray &ole_safe_array, int row, int col, std::string &result)
    {
        static COleVariant vResult;
        static CString str;

        //�ַ���
        static long read_address[2];
        static VARIANT val;

        static const int prec=std::numeric_limits<long long>::digits10; // 18


        read_address[0] = row;
        read_address[1] = col;
        ole_safe_array.GetElement(read_address, &val);
        vResult = val;

        val.bstrVal;

        switch(vResult.vt){
        case VT_BSTR:
        {
            str = vResult.bstrVal;
            result = str.GetString();
            break;
        }

        //��Ԫ��յ�
        case VT_EMPTY:
            
            result = "";
            break;

        //����
        case VT_INT:
            
            str.Format("%d",vResult.pintVal);
            result = str.GetString();
            break;

        //8�ֽڵ����� 
        case VT_R8:
        {
            std::ostringstream oss;
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
            result = str.GetString();
            break;
        }
        }
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

	int get_row_cnt(CWorksheet &sheet)
	{
		CRange range;
		CRange usedRange;

		usedRange.AttachDispatch(sheet.get_UsedRange(), true);
		range.AttachDispatch(usedRange.get_Rows(), true);
		int row_cnt = range.get_Count();
		usedRange.ReleaseDispatch();
		range.ReleaseDispatch();
		return row_cnt;
	}

	int get_col_cnt(CWorksheet &sheet)
	{
		CRange range;
		CRange usedRange;

		usedRange.AttachDispatch(sheet.get_UsedRange(), true);
		range.AttachDispatch(usedRange.get_Columns(), true);
		int count = range.get_Count();
		usedRange.ReleaseDispatch();
		range.ReleaseDispatch();
		return count;
	}
}