///<------------------------------------------------------------------------------
//< @file:   prop\parser\main.cpp
//< @author: ������
//< @date:   2014��9��10�� 14:49:42
//< @brief:  
//< Copyright (c) 2014 Tokit. All rights reserved.
///<------------------------------------------------------------------------------

#include "parser.h"
#include "echoutil.h"
#include "file_util.h"
#include "xsd/xsd_generator.h"
#include "c++/c++_generator.h"
#include "xml/xml_generator.h"

bool parse_excel(std::string &excel, cfgbase_t &cfgbase, enum_parse_option parse_option){
    if(false == fileutil::exist(excel)){
        ECHO_ERR("����: �Ҳ���excel�ṹ�����ļ�<%s>", excel.c_str());
        return false;
    }

    errvec_t errvec;
    if (!parser::parse_excel(excel, cfgbase, errvec, parse_option)){
        ECHO_ERR("���󣺽���<%s>�ļ�ʧ��", excel.c_str());
        echoutil::echo_errvec(errvec);
        return false;
    }

    return true;
}

// ���ѡ�����Ƿ񺬡�--����xml��ѡ����������Ҫ����xml����
enum_parse_option get_parse_option(int argc, char **argv)
{
    enum_parse_option parse_option = parse_option_skip_data;
    for (int i = 1; i < argc; i++){
        if (0 == strcmp(argv[i], "-saveasxml")){
            parse_option = parse_option_read_data;
            break;
        }
    }

    return parse_option;
}

int main(int argc, char **argv)
{
    if (argc < 2){
        ECHO_ERR("������ʽ���󣬸�ʽӦΪ��");
        ECHO_ERR("   excel�ļ���·��  ����1  ����1�Ĳ���  ����2  ����2�Ĳ���...");
        ECHO_ERR("   ����: ../../hello.xlsx  -xsd  ../xsd/  -saveasxml ../xml/");

        return 0;
    }

    std::string excel = argv[1];
    cfgbase_t cfgbase;
    enum_parse_option parse_option = get_parse_option(argc, argv);

    // ����excel�ļ�
    if (!parse_excel(excel, cfgbase, parse_option)){
        return 0;
    }

    // ��ʼִ������
    int pos = 2;
    while(pos < argc){
        std::string cmd = argv[pos++];
        if(cmd == "-xsd"){
            if(pos + 1 > argc){
                ECHO_ERR("����xsd��������󣬸�ʽӦΪ: ");
                ECHO_ERR("   -xsd ���ɵ�xsd�ļ��ŵ��ĸ��ļ�����");
                ECHO_ERR("   ����: -xsd  ../xsd/");

                return 0;
            }

            std::string xsd_dir  = argv[pos++];

            xsd_generator xsd_gen(cfgbase, xsd_dir);
            xsd_gen.generate();
        }else if(cmd == "-c++"){
            if(pos + 3 > argc){
                ECHO_ERR("����c++Դ�����ļ���������󣬸�ʽӦΪ: ");
                ECHO_ERR("   -c++  hģ���ļ� cppģ���ļ� ���ɵ�c++�ļ������ĸ��ļ�����");
                ECHO_ERR("   ����: -c++  ../h_template.h  ../cpp_template.cpp  ./c++/");

                return 0;
            }

            std::string h_templet   = argv[pos++];
            std::string cpp_templet = argv[pos++];
            std::string cpp_dir	    = argv[pos++];

            cpp_generator cpp_gen(cfgbase, cpp_dir, h_templet, cpp_templet);
            cpp_gen.generate();
        }else if(cmd == "-go"){
            if(pos + 2 > argc){
                ECHO_ERR("����goԴ�����ļ�������󣬸�ʽӦΪ: ");
                ECHO_ERR("   -go  goģ���ļ�  ���ɵ�go�ļ������ĸ��ļ�����");
                ECHO_ERR("   ����: -go  ../go_template.go   ./go/");

                return 0;
            }

            std::string go_templet = argv[pos++];
            std::string go_dir	   = argv[pos++];
        }else if(cmd == "-saveasxml"){
            if(pos + 1 > argc){
                ECHO_WARN("����xml�ļ���������󣬸�ʽӦΪ: ");
                ECHO_WARN("   -saveasxml  ���ɵ�xml�ļ�������ĸ��ļ�����");
                ECHO_WARN("   ����: -saveasxml  ../xml/");

                return 0;
            }

            std::string xml_dir = argv[pos++];

            xml_generator xml_gen(cfgbase, xml_dir);
            xml_gen.generate();
        }
    }

    return 0;
}
