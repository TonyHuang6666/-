#include <iostream>
#include <fstream> //文件流
#include <cstring> //包含很多字符串处理函数的标准库
#include <string>
#include <ctime> //包含时间函数的头文件
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
    string name, location, filepath, user, content; // 分别为文件名，保存路径，保存路径+文件名，创建者,文件内容
    char t[32];
    void TransformPN(string filepath, string ReadString); // Positional Notation进位制
    string Input(string target, string identifier);
    void Modify(string filepath, string ReadString, int function);
    int Create(string filepath, string content); // 创建新文件
    int Read(string filepath);                   // 打开文件
    void chart();
    string intToA(int Num, int PositionalNotation);        // 进制转换核心功能
    void Infomation(string name,string location,char *time,string user,int function);                     // 记录文件运行后创建的文件、打开过的文件
    char *GetTime()                                        // 求得当前系统时间的函数
    {                                                      // 存当前系统时间的数组,字符数组可以以数组名来用cout输出数组内容,因为 char 型数组中的每一个元素都是一字节，是连续的，输出时读到字符数组中的 \0 便停止
        time_t NowTime = time(0);                          // 构建time_t类的对象nowtime并且实例化
        strftime(t, sizeof(t), "%c", localtime(&NowTime)); //%c表示将时间格式化为 月/日/年 时/分/秒 的形式
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
string Text::intToA(int Num, int PositionalNotation) // 进制转换核心功能
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
    } while (Num != 0); // 使用do{}while()以防止输入为0的情况
    reverse(temp.begin(), temp.end());
    return temp;
}
void Text::Infomation(string name,string location,char *time,string user,int function)
{
    store.open("./information.dat",ios::app);
    store<<"\n操作：";
    if(function==New)
    store<<"创建文件"<<endl;
    else if(function==Add)
    store<<"修改文件：于末尾添加了新内容"<<endl;
    else if(function==Empty)
    store<<"修改文件：清空内容"<<endl;
    else store<<"修改文件：插入了新内容"<<endl;
    store << "文件名："<<name<<'\n'<<"保存路径："<<location<<'\n'<<"操作时间："<< GetTime() <<'\n'<< "操作人：" << user <<endl;
}
