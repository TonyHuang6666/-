#include <iostream>
#include <fstream> //�ļ���
#include <cstring> //�����ܶ��ַ����������ı�׼��
#include <string>
#include <ctime> //����ʱ�亯����ͷ�ļ�
#include <sstream>
#include <algorithm>
#pragma warning(disable : 4996)

#define Reinput 1
#define New 1
#define Empty 1
#define Open 2
#define Add 2
#define Exit 3
#define Find 3
#define Check_Record 3
#define PN 4
#define NotFound -1
using namespace std;

class Text
{
public:
    fstream file, mfile,mfile1, infile,store;
    string name, location, filepath, user, content; // �ֱ�Ϊ�ļ���������·��������·��+�ļ�����������,�ļ�����
    char t[32];
    void TransformPN(string filepath, string ReadString); // Positional Notation��λ��
    string Input(string target, string identifier);
    void Modify(string filepath, string ReadString, int function);
    int Create(string filepath, string content); // �������ļ�
    int Read(string filepath);                   // ���ļ�
    void chart();
    string intToA(int Num, int PositionalNotation);        // ����ת�����Ĺ���
    void Infomation(string name,string location,char *time,string user,int function);                     // ��¼�ļ����к󴴽����ļ����򿪹����ļ�
    char *GetTime()                                        // ��õ�ǰϵͳʱ��ĺ���
    {                                                      // �浱ǰϵͳʱ�������,�ַ��������������������cout�����������,��Ϊ char �������е�ÿһ��Ԫ�ض���һ�ֽڣ��������ģ����ʱ�����ַ������е� \0 ��ֹͣ
        time_t NowTime = time(0);                          // ����time_t��Ķ���nowtime����ʵ����
        strftime(t, sizeof(t), "%c", localtime(&NowTime)); //%c��ʾ��ʱ���ʽ��Ϊ ��/��/�� ʱ/��/�� ����ʽ
        return t;
    }
    Text() {}
    Text(string name, string location, string content, string user, int function)
    {
        this->name = name;
        this->location = location;
        this->user = user;
        this->content = content;
        this->filepath = location + name;
        if (function == New)
            Create(this->filepath, content);
        else if (function == Open)
            Read(this->filepath);
        else if (function == Check_Record)
            Read("./information.dat");
    }
    ~Text()
    {
        mfile.close();
        mfile1.close();
        infile.close();
        file.close();
    }
};
string Text::intToA(int Num, int PositionalNotation) // ����ת�����Ĺ���
{
    string temp = "";
    do
    {
        int t = Num % PositionalNotation;
        if (t >= 0 && t <= 9)
            temp += (t + '0');
        else
            temp += (t - 10 + 'A');
        Num /= PositionalNotation;
    } while (Num != 0); // ʹ��do{}while()�Է�ֹ����Ϊ0�����
    reverse(temp.begin(), temp.end());
    return temp;
}
void Text::Infomation(string name,string location,char *time,string user,int function)
{
    store.open("./information.dat",ios::app);
    store<<"\n������";
    if(function==New)
    store<<"�����ļ�"<<endl;
    else if(function==Add)
    store<<"�޸��ļ�����ĩβ�����������"<<endl;
    else if(function==Empty)
    store<<"�޸��ļ����������"<<endl;
    else store<<"�޸��ļ���������������"<<endl;
    store << "�ļ�����"<<name<<'\n'<<"����·����"<<location<<'\n'<<"����ʱ�䣺"<< GetTime() <<'\n'<< "�����ˣ�" << user <<endl;
}
