#include "Text.h"
void Text::TransformPN(string filepath, string ReadString) // Positional Notation进位制
{
    fstream infile1(filepath);
    int Numbers[1000] = {0}, Num = 0;
    string outcome, temp = "";
    for (int i = 0; i < ReadString.size(); i++)
    {
        int N = 114514;
        infile1 >> N;
        if (N != 114514)
            Numbers[i] = N;
    }
    int PositionalNotation;
    cout << "请输入目标进位制（2/8/16）：";
    cin >> PositionalNotation;
    for (int i = 0; Numbers[i] != 0; i++)
    {
        temp = intToA(Numbers[i], PositionalNotation);
        outcome = outcome + " " + temp;
    }
    outcome.erase(0, 1);
    cout << "已从10进制转换为" << PositionalNotation << "进制！转换后的内容为：";
    chart();
    cout << outcome;
    cout << "\n请输入新文件以储存（格式为文件名.格式）：";
    cin >> name;
    filepath = this->location + name; // 理应正确的文件路径
    Create(filepath, outcome);
}
void Text::Modify(string filepath, string ReadString, int function)
{
    this->filepath = filepath;
    string endnote, input;
    switch (function)
    {
    case Empty: // 清空文件内容,思路为利用out标识
    {
        mfile.open(filepath, ios::out);
        cout << "文件已清空!" << endl;
        Infomation(name,location,GetTime(),user,Empty);
        break;
    }
    case Add: // 在文件末尾换行添加新内容
    {
        mfile.open(filepath, ios::app); // 用app标识符默认换行再添加数据
        cout << "请在下面输入需要添加的内容（如要结束输入请回车并输入END）" << endl;
        chart();
        mfile << Input("content", "END");
        cout << "文件添加新内容成功!" << endl;
        Infomation(name,location,GetTime(),user,Add);
        break;
    }
    case Find: // 查找指定字符串并在后面插入新的内容
    {
        mfile.open(filepath, ios::out);
        getchar(); // 吸收回车
        cout << "请输入需要查找的内容：";
        getline(cin, input); // 支持查找带空格的字符串
        int length = input.length();
        int position = ReadString.find(input);
        if (position == NotFound)
        {
            cout << "\n查找失败，请按Enter后重新输入!";
            Modify(filepath, ReadString, Find);
        }
        else
        {
            cout << "查找成功!\n请输入需要在后面插入的内容：";
            getline(cin, endnote);
            ReadString.insert(position + length, endnote);
            mfile1.open(filepath, ios::out); // 经测试如果不用新的流mfile1则文件会被清空
            mfile1 << ReadString ;
        }
        cout << "文件插入内容成功!" << endl;
        Infomation(name,location,GetTime(),user,Find);
        break;
    }
    default:
        break;
    }
}
int Text::Create(string filepath, string content) // 创建新文件
{
    file.open(filepath, ios::out);
    while (!file.is_open()) // 流未与文件关联
    {
        file.clear();
        cout << "文件路径输入错误，创建文件失败!" << endl;
        cout << "提醒：不带盘符和文件夹则文件存储于程序根目录，若将已\n      存在的文件夹名称输错，或输入了不存在的文件夹则报错" << endl;
        cout << "     是否重新输入文件路径？ 是请输入1，其余任意键退出\n请输入：";
        int function;
        cin >> function; // 防错误不防作死
        getchar();       // 吸收回车
        if (function == Reinput)
        {
            cout << "请重新输入文件路径：";
            location = Input("location", "/");
            cout << "请重新输入文件（格式为文件名.格式）：";
            cin >> name;
            filepath = location + name; // 理应正确的文件路径
            Create(filepath, content);
            return 0; // 递归结束，即成功创建文件后退出Create()函数
        }
        else
            return 0; // 退出Create()函数
    }
    int position = filepath.find("/"), position1 = filepath.find(":");
    if (position != NotFound && position1 != NotFound) // 含有:和/，即带盘符和文件夹，输出到对应目录
        cout << "文件创建于：" << filepath << endl;
    else
        cout << "文件：" << location + name << " 于程序根目录创建成功!" << endl;
    file << content;
    Infomation(name,location,GetTime(),user,New);
}
int Text::Read(string filepath) // 打开文件
{
    infile.open(filepath);
    while (!infile.is_open())
    {
        if(filepath=="./information.dat")
        {
            cout<<"程序为首次运行，无操作记录！";
            return 0;
        }
        infile.clear();
        cout << filepath;
        cout << "打开文件有误!\n\n请输入数字以进行下一步操作：";
        cout << "1-在路径内创建该新文件 2-重新输入文件路径+文件并打开 3-重启程序\n请输入：";
        int function;
        cin >> function;
        getchar(); // 吸收回车
        while (function != New && function != Open && function != Exit)
        {
            cout << "指令错误,请重新输入：";
            cin >> function;
        }
        if (function == New) // 在路径内创建该新文件
        {
            string content = "";
            this->filepath = location + name;
            Create(this->filepath, content);
            break;
        }
        else if (function == Open)
        {
            cout << "请重新输入文件路径：";
            this->location = Input("location", "/");
            cout << "请重新输入文件（格式为文件名.格式）：";
            cin >> this->name;
            filepath = this->location + this->name;
            infile.open(filepath);
            if (!infile.is_open())
            {
                infile.clear();
                cout << "文件路径有误或路径下无对应文件!" << endl;
                Read(filepath);
                return 0;
            }
        }
        else
            return 0;
    }
    string ReadString((istreambuf_iterator<char>(infile)), istreambuf_iterator<char>()); // 读取文本内容到字符串
    cout << "文件内容为：" << endl;
    chart();
    cout << ReadString << endl;
    chart();
    int f;
    cout << "\n请根据数字选择你的操作：1-清空该文件 2-在文件末尾转行添加新内容 3-查找内容 4-进制转换(仅用于纯数字文件) 5-退出程序\n请输入数字：";
    cin >> f;
    if (f == Empty || f == Add || f == Find) // 防错误不防作死
        Modify(filepath, ReadString, f);
    else if (f == PN)
        TransformPN(filepath, ReadString);
    else
        return 0;
}
string Text::Input(string target, string identifier)
{
    string temp, input;
    if (target == "location")//用于输入地址
        for (int position = NotFound, length = 1; position != length - 1;) // 支持空格输入，若地址结尾不是identifier则报错
        {
            getline(cin, temp);
            position = temp.find_last_of(identifier);
            input += temp;
            length = temp.length();
            if (position != length - 1)
            {
                input = "";
                cout << "格式错误，请重新输入：";
            }
            else
                break;
        }
    if (target == "content")//用于输入内容
        for (int position = NotFound; position == NotFound; input += temp) // 支持空格及换行输入
        {
            getline(cin, temp);
            position = temp.find(identifier);
            if (position != NotFound)
                break; // 这一条并非多余,若无则会将回车符号添加
            temp += "\n";
        }
    return input;
}
void Text::chart()
{
    cout << endl;
    for (int i = 0; i <= 30; i++)
        cout << "___";
    cout << "\n\n";
}