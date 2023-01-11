#include "Text.h"
void Text::TransformPN(string filepath, string ReadString) // Positional Notation��λ��
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
    cout << "������Ŀ���λ�ƣ�2/8/16����";
    cin >> PositionalNotation;
    for (int i = 0; Numbers[i] != 0; i++)
    {
        temp = intToA(Numbers[i], PositionalNotation);
        outcome = outcome + " " + temp;
    }
    outcome.erase(0, 1);
    cout << "�Ѵ�10����ת��Ϊ" << PositionalNotation << "���ƣ�ת���������Ϊ��";
    chart();
    cout << outcome;
    cout << "\n���������ļ��Դ��棨��ʽΪ�ļ���.��ʽ����";
    cin >> name;
    filepath = this->location + name; // ��Ӧ��ȷ���ļ�·��
    Create(filepath, outcome);
}
void Text::Modify(string filepath, string ReadString, int function)
{
    this->filepath = filepath;
    string endnote, input;
    switch (function)
    {
    case Empty: // ����ļ�����,˼·Ϊ����out��ʶ
    {
        mfile.open(filepath, ios::out);
        cout << "�ļ������!" << endl;
        Infomation(name,location,GetTime(),user,Empty);
        break;
    }
    case Add: // ���ļ�ĩβ�������������
    {
        mfile.open(filepath, ios::app); // ��app��ʶ��Ĭ�ϻ������������
        cout << "��������������Ҫ��ӵ����ݣ���Ҫ����������س�������END��" << endl;
        chart();
        mfile << Input("content", "END");
        cout << "�ļ���������ݳɹ�!" << endl;
        Infomation(name,location,GetTime(),user,Add);
        break;
    }
    case Find: // ����ָ���ַ������ں�������µ�����
    {
        mfile.open(filepath, ios::out);
        getchar(); // ���ջس�
        cout << "��������Ҫ���ҵ����ݣ�";
        getline(cin, input); // ֧�ֲ��Ҵ��ո���ַ���
        int length = input.length();
        int position = ReadString.find(input);
        if (position == NotFound)
        {
            cout << "\n����ʧ�ܣ��밴Enter����������!";
            Modify(filepath, ReadString, Find);
        }
        else
        {
            cout << "���ҳɹ�!\n��������Ҫ�ں����������ݣ�";
            getline(cin, endnote);
            ReadString.insert(position + length, endnote);
            mfile1.open(filepath, ios::out); // ��������������µ���mfile1���ļ��ᱻ���
            mfile1 << ReadString ;
        }
        cout << "�ļ��������ݳɹ�!" << endl;
        Infomation(name,location,GetTime(),user,Find);
        break;
    }
    default:
        break;
    }
}
int Text::Create(string filepath, string content) // �������ļ�
{
    file.open(filepath, ios::out);
    while (!file.is_open()) // ��δ���ļ�����
    {
        file.clear();
        cout << "�ļ�·��������󣬴����ļ�ʧ��!" << endl;
        cout << "���ѣ������̷����ļ������ļ��洢�ڳ����Ŀ¼��������\n      ���ڵ��ļ�����������������˲����ڵ��ļ����򱨴�" << endl;
        cout << "     �Ƿ����������ļ�·���� ��������1������������˳�\n�����룺";
        int function;
        cin >> function; // �����󲻷�����
        getchar();       // ���ջس�
        if (function == Reinput)
        {
            cout << "�����������ļ�·����";
            location = Input("location", "/");
            cout << "�����������ļ�����ʽΪ�ļ���.��ʽ����";
            cin >> name;
            filepath = location + name; // ��Ӧ��ȷ���ļ�·��
            Create(filepath, content);
            return 0; // �ݹ���������ɹ������ļ����˳�Create()����
        }
        else
            return 0; // �˳�Create()����
    }
    int position = filepath.find("/"), position1 = filepath.find(":");
    if (position != NotFound && position1 != NotFound) // ����:��/�������̷����ļ��У��������ӦĿ¼
        cout << "�ļ������ڣ�" << filepath << endl;
    else
        cout << "�ļ���" << location + name << " �ڳ����Ŀ¼�����ɹ�!" << endl;
    file << content;
    Infomation(name,location,GetTime(),user,New);
}
int Text::Read(string filepath) // ���ļ�
{
    infile.open(filepath);
    while (!infile.is_open())
    {
        if(filepath=="./information.dat")
        {
            cout<<"����Ϊ�״����У��޲�����¼��";
            return 0;
        }
        infile.clear();
        cout << filepath;
        cout << "���ļ�����!\n\n�����������Խ�����һ��������";
        cout << "1-��·���ڴ��������ļ� 2-���������ļ�·��+�ļ����� 3-��������\n�����룺";
        int function;
        cin >> function;
        getchar(); // ���ջس�
        while (function != New && function != Open && function != Exit)
        {
            cout << "ָ�����,���������룺";
            cin >> function;
        }
        if (function == New) // ��·���ڴ��������ļ�
        {
            string content = "";
            this->filepath = location + name;
            Create(this->filepath, content);
            break;
        }
        else if (function == Open)
        {
            cout << "�����������ļ�·����";
            this->location = Input("location", "/");
            cout << "�����������ļ�����ʽΪ�ļ���.��ʽ����";
            cin >> this->name;
            filepath = this->location + this->name;
            infile.open(filepath);
            if (!infile.is_open())
            {
                infile.clear();
                cout << "�ļ�·�������·�����޶�Ӧ�ļ�!" << endl;
                Read(filepath);
                return 0;
            }
        }
        else
            return 0;
    }
    string ReadString((istreambuf_iterator<char>(infile)), istreambuf_iterator<char>()); // ��ȡ�ı����ݵ��ַ���
    cout << "�ļ�����Ϊ��" << endl;
    chart();
    cout << ReadString << endl;
    chart();
    int f;
    cout << "\n���������ѡ����Ĳ�����1-��ո��ļ� 2-���ļ�ĩβת����������� 3-�������� 4-����ת��(�����ڴ������ļ�) 5-�˳�����\n���������֣�";
    cin >> f;
    if (f == Empty || f == Add || f == Find) // �����󲻷�����
        Modify(filepath, ReadString, f);
    else if (f == PN)
        TransformPN(filepath, ReadString);
    else
        return 0;
}
string Text::Input(string target, string identifier)
{
    string temp, input;
    if (target == "location")//���������ַ
        for (int position = NotFound, length = 1; position != length - 1;) // ֧�ֿո����룬����ַ��β����identifier�򱨴�
        {
            getline(cin, temp);
            position = temp.find_last_of(identifier);
            input += temp;
            length = temp.length();
            if (position != length - 1)
            {
                input = "";
                cout << "��ʽ�������������룺";
            }
            else
                break;
        }
    if (target == "content")//������������
        for (int position = NotFound; position == NotFound; input += temp) // ֧�ֿո񼰻�������
        {
            getline(cin, temp);
            position = temp.find(identifier);
            if (position != NotFound)
                break; // ��һ�����Ƕ���,������Ὣ�س��������
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