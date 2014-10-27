@echo off
set excel_dir=./excel/
set tool=tool
set gen_dir=./
set template=%tool%/template
set cur_dir=%~dp0

echo 0. ���ԭ������

rem del /Q /S *.h
rem del /Q /S *.cpp
rem del /Q /S *.xsd
del /Q /S %gen_dir%\*.xml
del /Q /S %gen_dir%\*.xlsx

rem %~dp0 =��ǰ�̷�+·������: d:\xxx\xxx
rem ͬʱ�����������forѭ����
rem %%s   =��ȫ�ļ�·����  ��: d:\abc.txt�����е�s�����Ǳ����ĸ����%%x
rem %%~nxs=�ļ�������չ��  ��: abc.txt
rem %%~ns =�ļ���������չ����: abc


echo 1. ����c++�ļ�
    for /F %%x in ('dir /b /a-d /s "%excel_dir%\*.xlsx"') do (
        echo ���ڴ���[ %%x ]
        %tool%\tokit.exe %%x -c++ %template%/c++_template.h %template%/c++_template.cpp %gen_dir%\c++\c++_example\cfg
    )

echo 2. ����xml�ļ�
    for /F %%x in ('dir /b /a-d /s "%excel_dir%\*.xlsx"') do ( 
        echo ���ڵ���[ %%~nx.xml ]
        %tool%\tokit.exe %%x -saveasxml %gen_dir%\xml
    )

echo 3. ����xsd�ļ�
    for /F %%x in ('dir /b /a-d /s "%excel_dir%\*.xlsx"') do ( 
        echo ���ڵ���[ %%~nx.xsd ]
        %tool%\tokit.exe %%x -xsd %gen_dir%\xsd
    )

echo 4. һ���Ե���c++��xml��xsd�ļ�
    for /F %%x in ('dir /b /a-d /s "%excel_dir%\*.xlsx"') do (
        echo ���ڴ���[ %%x ]
        %tool%\tokit.exe %%x -c++ %template%/c++_template.h %template%/c++_template.cpp %gen_dir%\c++\c++_example\cfg -saveasxml %gen_dir%\xml -xsd %gen_dir%\xsd
    )

pause