#include "Functions.h"

int main()
{
    string location, name, content, temp,user;
    int function;
    Text Object;
    while (true)
    {
        Object.chart();
        cout << "���������ѡ����Ĳ�����\n1-�������ļ� 2-�������ļ� 3-�鿴���м�¼�ļ� �����-�˳�����\n���������֣�";
        cin >> function;
        getchar();
        if (function == Check_Record)
            Text(name, location, content, user, function);
        if (function != New && function != Open)
        {
            cout << "\nȷ���˳�����1-�������ļ� 2-�������ļ� �����-�˳�����" << endl;
            cin >> function;
            getchar();
            if (function != New && function != Open)
                return 0;
        }
        cout << "����������������";
        getline(cin, user); // ֧�ֿո����룬��Ӣ������
        cout << "����:�ļ�·��/�ļ���ʽ:  �̷�:/�ļ�������1/�ļ�������2/�ļ�" << endl;
        cout << "     �ļ�·��/�ļ�ʾ��:  C:/Users/Tony_Huang/Desktop/C.txt   ����C.txtΪ�ļ�" << endl;
        cout << "�������ļ�·��(�����Ŀ¼Ϊ./)��";
        location = Object.Input("location", "/");
        if (function == New)
        {
            cout << "������Ҫ�������ļ���ʽ������ѡ��txt,cpp,��doc���ȣ�";
            string format;
            cin >> format;
            if (format != "cpp" && format != "txt" && format != "doc")
            {
                cout << "�����˲��Ƽ��ĸ�ʽ�����������룺";
                cin >> format;
            }
            getchar(); // ���ջس�
            cout << "�������ļ�����";
            getline(cin, name); // ֧���ļ����ո�����
            name = name + "." + format;
            cout << "�������������ļ����ݣ���Ҫ������س�������END��" << endl;
            Object.chart();
            content = Object.Input("content", "END");
            Text(name, location, content, user, function);
        }
        else if (function == Open)
        {
            cout << "������Ҫ�򿪵��ļ�(��ʽΪ�ļ���.��ʽ)��";
            cin >> name;
            Text(name, location, content, user, function);
        }
    }
    system("pause");
}