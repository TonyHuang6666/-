#include "Functions.h"

int main()
{
    string location, name, content, temp,user;
    int function;
    Text Object;
    while (true)
    {
        Object.chart();
        cout << "请根据数字选择你的操作：\n1-创建新文件 2-打开已有文件 3-查看运行记录文件 任意键-退出程序\n请输入数字：";
        cin >> function;
        getchar();
        if (function == Check_Record)
            Text(name, location, content, user, function);
        if (function != New && function != Open)
        {
            cout << "\n确定退出程序？1-创建新文件 2-打开已有文件 任意键-退出程序" << endl;
            cin >> function;
            getchar();
            if (function != New && function != Open)
                return 0;
        }
        cout << "请输入您的姓名：";
        getline(cin, user); // 支持空格输入，如英文名字
        cout << "提醒:文件路径/文件格式:  盘符:/文件夹名字1/文件夹名字2/文件" << endl;
        cout << "     文件路径/文件示例:  C:/Users/Tony_Huang/Desktop/C.txt   其中C.txt为文件" << endl;
        cout << "请输入文件路径(程序根目录为./)：";
        location = Object.Input("location", "/");
        if (function == New)
        {
            cout << "请输入要创建的文件格式（建议选择txt,cpp,或doc）等：";
            string format;
            cin >> format;
            if (format != "cpp" && format != "txt" && format != "doc")
            {
                cout << "输入了不推荐的格式！请重新输入：";
                cin >> format;
            }
            getchar(); // 吸收回车
            cout << "请输入文件名：";
            getline(cin, name); // 支持文件名空格输入
            name = name + "." + format;
            cout << "请在下面输入文件内容（如要结束请回车并输入END）" << endl;
            Object.chart();
            content = Object.Input("content", "END");
            Text(name, location, content, user, function);
        }
        else if (function == Open)
        {
            cout << "请输入要打开的文件(格式为文件名.格式)：";
            cin >> name;
            Text(name, location, content, user, function);
        }
    }
    system("pause");
}