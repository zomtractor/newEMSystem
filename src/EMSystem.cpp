//
// Created by 90828 on 2022-02-17.
//

#include <fstream>
#include "EMSystem.h"
#include "functional"

using namespace std;

//��ʾ��������
void elegantPrint(const char* message, bool input=true){
    cout<<message<<endl;
    if(input) cout<<"--> ";
}

void EMSystem::showWelcome() {
    cout << "=========================================��ӭʹ��ְ������ϵͳ��=========================================" << endl;
}
//�������ֲ���ְ��
Array<Employee *> findEmployeeByName(Array<Employee *> &temp, string name = "") {   //����Ĭ��ֵ����ߴ��븴����
    if (name == "") {
        elegantPrint("���������ѯ�˵�������");
        cin >> name;
    }
    return temp.findElemBy([&](Employee *e) { return e->name == name; });
}
//�����Ա�
Array<Employee *> findEmployeeBySex(Array<Employee *> &temp, string sex = "") {
    if (sex == "") {
        elegantPrint("���������ѯ�˵��Ա�");
        cin >> sex;
    }
    return temp.findElemBy([&](Employee *e) { return e->sex == sex; });
}
//������ְʱ��
Array<Employee *> findEmployeeByTime(Array<Employee *> &temp, int year = 0, int month = 0, int day = 0) {
    EasyDate date;
    if (year == 0 && month == 0 && day == 0) {
        elegantPrint("���������ѯ�˵���ְʱ�䣨yyyy mm dd����");
        cin >> year >> month >> day;
    }
    while (!date.setDate(year, month, day)) {
        elegantPrint("��������ڲ���ȷ�����ٴ�����.");
        cin >> year >> month >> day;
    }
    return temp.findElemBy([&](Employee *e) { return date < e->employment_time; });
}
//�������֤id
Employee *findEmployeeByID(HashSet<Employee*> &hashset, string id = "") {
    if (id == "") {
        elegantPrint("���������ѯ�˵����֤�ţ�");
        cin >> id;
    }
    Employee e(id);
    return hashset.find(&e,[](Employee *a,Employee *b){return  a->IDNumber==b->IDNumber;});
}
//��ʾ�˵�
bool EMSystem::showMenu() {
    cout << "---------------------------------------------------------------------------------------------------" << endl;
    elegantPrint("1���½�ְ����Ϣ 2��ɾ��ְ����Ϣ 3����ѯְ����Ϣ 4���޸�ְ����Ϣ 5����ְ����Ϣ�������� 0�������˳�ϵͳ -1��ֱ���˳�ϵͳ" );
    void (EMSystem::*functions[5])()={  //����ָ�������Ź��ܺ���
            &EMSystem::add,
            &EMSystem::remove,
            &EMSystem::query,
            &EMSystem::modify,
            &EMSystem::sort
    };
    int choice = 0;
    cin >> choice;
    if(choice==0) return false;
    else if(choice>5) return showMenu();
    else if(choice==-1) exit(0);
    else (this->*functions[choice-1])();    //����ʹ��switch���
//    switch (choice) {
//        case 0:
//            return false;
//        case 1:
//            add();
//            break;
//        case 2:
//            remove();
//            break;
//        case 3:
//            query();
//            break;
//        case 4:
//            modify();
//            break;
//        case 5:
//        default:
//            return showMenu();
//    }
    cin.clear();//����������
    cin.sync();
    return true;
}
//���ְ����������
void outputPtrMessage(Array<Employee*> &t){
    if(t.size()==0){
        cout<<"[empty]"<<endl;
        return;
    }
    cout<<"[";
    for(int i=0;i+1<t.size();i++) cout<<*(t[i])<<endl;
    cout<<*t[t.size()-1]<<"]"<<endl;
}
//��
void EMSystem::modify() {
    elegantPrint("������Ҫ�޸ĵ�ְ�������֤�ţ�������0���в�ѯ");
    string id;
    cin >> id;
    if (id[0] == '0') return query();
    Employee *d = findEmployeeByID(hashset, id);
    if (d == nullptr) {
        cout << "û���ҵ���ְ����" << endl;
        return modify();
    }
    Employee *e = new Employee();
    int age;
    string name;
    string sex;
    EasyDate birthday;
    EasyDate employment_time;
    string education;
    string job;
    string address;
    string telephoneNum;
    elegantPrint("������Ҫ�޸ĵ����������֤�ţ�������0����ԭ����Ϣ��");
    cin >> name >> id;
    while (findEmployeeByID(hashset, id)) {
        elegantPrint("�Ѿ����ڸ������Ϣ���������������֤��!");
        cin >> id;
    }
    if (name[0] != '0') e->name = name;else e->name=d->name;
    if (id[0] != '0') e->IDNumber = id; else e->IDNumber=d->IDNumber;
    elegantPrint("�����������Ա����䡢��ͥסַ��ѧ�����������绰����(������0����ԭ����Ϣ):");
    cin >> sex >> age >> address >> education >> job >> telephoneNum;
    if (sex[0] != '0') e->sex = sex; else e->sex=d->sex;
    if (age != 0) e->age = age; else e->age = d->age;
    if (address[0] != '0') e->address = address; else e->address=d->address;
    if (education[0] != '0') e->education = education; else e->education=d->education;
    if (job[0] != '0') e->job = job; else e->job=d->job;
    if (telephoneNum[0] != '0') e->telephoneNum = telephoneNum; else e->telephoneNum=d->telephoneNum;
    elegantPrint("������������ڵ��ꡢ�¡���(������3��0����ԭ����Ϣ):");
    int year, month, day;
    while(cin >> year >> month >> day){
        if(year&&month&&day){
            if(e->birthday.setDate(year,month,day)) {
                break;
            } else {
                cout<<"�������Ϣ�������������룡"<<endl;
            }
        } else {
            e->birthday=d->birthday;
            break;
        }
    }
    elegantPrint("��������ְ���ڵ��ꡢ�¡���:(������3��0����ԭ����Ϣ)");
    while(cin >> year >> month >> day){
        if(year&&month&&day){
            if(e->employment_time.setDate(year,month,day)) {
                break;
            } else {
                cout<<"�������Ϣ�������������룡"<<endl;
            }
        } else {
            e->employment_time=d->employment_time;
            break;
        }
    }
    cout << "��ǰְ����Ϣ���޸�Ϊ��" << *e << ",�Ƿ�Ҫ���棿(y/n)--> ";
    char operation = 0;
    while (cin >> operation) {
        if (operation == 'n' || operation == 'N') {
            cout << "ȡ���˲�����" << endl;
            delete e;
            return;
        } else if (operation != 'Y' && operation != 'y') {
            cout << endl;
        } else break;
    }
    temp.remove(d);
    temp.push_back(e);
    hashset.remove(d);
    hashset.insert(e);
    delete d;
    cout << "�޸���Ϣ�ɹ���" << endl;
}
//��
void EMSystem::add() {
    elegantPrint("������Ҫ��ӵ�ְ�������������֤�ţ�");
    string name, ID;
    cin >> name >> ID;
    char operation;
    Employee *x = findEmployeeByID(hashset, ID);
    if (x != nullptr) {
        cout << "�����֤�ѱ�ʹ�ã�" << endl;
        cout<<endl;
        return;
    }
    Employee *employee = new Employee(ID);
    employee->name = name;
    elegantPrint("�����������Ա����䡢��ͥסַ��ѧ�����������绰����:");
    int year;
    string sex, address, education, job, tel;
    cin >> sex >> year >> address >> education >> job >> tel;
    employee->sex = sex;
    employee->age = year;
    employee->address = address;
    employee->education = education;
    employee->job = job;
    employee->telephoneNum = tel;
    elegantPrint("������������ڵ��ꡢ�¡���:");
    int month, day;
    while(cin >> year >> month >> day) {
        if (!employee->birthday.setDate(year, month, day)){
            elegantPrint("���벻�Ϸ������������롣");
        }
        else break;
    }
    elegantPrint("��������ְ���ڵ��ꡢ�¡���:");
    while(cin >> year >> month >> day) {
        if (!employee->employment_time.setDate(year, month, day)){
            elegantPrint("���벻�Ϸ������������롣");
        }
        else break;
    }
    cout << "��ǰҪ��ӵ�ְ����ϢΪ��" << *employee << ",�Ƿ�Ҫ���棿(y/n)--> ";
    while (cin >> operation) {
        if (operation == 'n' || operation == 'N') {
            cout << "ȡ���˲�����" << endl;
            return;
        } else if (operation != 'Y' && operation != 'y') {
            cout << endl;
        } else break;
    }
    temp.push_back(employee);
    hashset.insert(employee);
    cout << "�ɹ��������ְ����" << endl;
}
//��
void EMSystem::query() {
    elegantPrint("1���������֤��ֱ�Ӳ�ѯ 2������������ѯ 3�������Ա��ѯ 4��������ְʱ����С��ѯ 5����ѯ��ǰȫ����Ϣ 0������");
    int choice = 0;
    cin >> choice;
    Array<Employee *> t;
    Employee *e;
    switch (choice) {
        case 1:
            e = findEmployeeByID(hashset);
            break;
        case 2:
            t = findEmployeeByName(temp);
            break;
        case 3:
            t = findEmployeeBySex(temp);
            break;
        case 4:
            t = findEmployeeByTime(temp);
            break;
        case 5:
            t=temp;
            break;
        default:
            return;
    }
    if (choice > 1&&choice<=5) {
        cout << "��ѯ���Ľ��Ϊ��" << endl;
        outputPtrMessage(t);
        elegantPrint("�Ƿ�Ҫ�����ѯ��Ϣ��(y/n)");
        char operation;
        while (cin >> operation) {
            if (operation == 'n' || operation == 'N') {
                return;
            } else if (operation != 'Y' && operation != 'y') {
                cout << endl;
            } else break;
        }
        writeFile(t,"result");
        cout<<"�ɹ�����ļ�����outputfiles/result.csv,����excel���в鿴"<<endl;
    }
    else if(choice==1) {
        if(e== nullptr) cout<<"û�в�ѯ�����"<<endl;
        else cout << "��ѯ���Ľ��Ϊ��" << *e << endl;
    }
}
//ɾ
void EMSystem::remove() {
    cout << "������Ҫ�޸ĵ�ְ�������֤�ţ�������0���в�ѯ,����-1ȡ��" << endl;
    cout << "-->";
    string id;
    cin >> id;
    if (id[0] == '0') return query();
    else if (id[0] == '-') return;
    Employee *e = findEmployeeByID(hashset, id);
    if (e == nullptr) {
        cout << "û���ҵ���ְ����" << endl;
        return remove();
    }
    hashset.remove(e);
    temp.remove(e);
    cout << "�ɹ�ɾ����ѡ���ְ��" << endl;
}
//����
void EMSystem::sort() {
    elegantPrint("1�����������ֵ������� 2�������������� 3��������ְʱ������ 0������");
    function<bool(Employee *, Employee *)> compare[] = {
            [](Employee *a, Employee *b) { return a->name <= b->name; },
            [](Employee *a, Employee *b) { return a->age <= b->age; },
            [](Employee *a, Employee *b) { return a->employment_time <= b->employment_time; },
    };
    int choice;
    cin >> choice;
    if (choice > 3) {
        cout << "���벻�Ϸ���" << endl;
    } else if (choice == 0) return;
    temp.sort(compare[choice - 1]);
    cout<<"������ɣ����Ϊ��"<<endl;
    outputPtrMessage(temp);
    elegantPrint("�Ƿ���������ļ���(y/n)");
    char operation;
    while (cin >> operation) {
        if (operation == 'n' || operation == 'N') {
            return;
        } else if (operation != 'Y' && operation != 'y') {
            cout << endl;
        } else break;
    }
    string names[]={"order_by_name","order_by_age","order_by_employment_time"};
    writeFile(temp,names[choice-1]);
    cout<<"�ɹ�����ļ�����outputfiles/"+names[choice-1]+".csv,����excel���в鿴"<<endl;
}
//����ϵͳ�ļ�
void backups(){
    fstream bk("data/EMinfo.bak",ios::out);
    fstream tp("data/EMinfo.dat",ios::in);
    string s;
    while(getline(tp,s)){
        bk<<s<<endl;
    }
    tp.close();
    bk.close();
}
//����ϵͳ�ļ�
void EMSystem::writeData() {
    try {
        backups();
        fstream fos("data/EMinfo.dat", ios::out);
        if (!fos.is_open()) {
            cout << "δ�ܱ����ļ�" << endl;
            return;
        }
        string s;
        for (int i = 0; i < temp.size(); i++) {
            s = temp[i]->simpleSerialize();
            fos << s << endl;
        }
        cout << "�ѱ���" << endl;
        fos.close();
    } catch (std::exception &e){
        cout<<e.what()<<endl;
    }
}
//��ȡϵͳ�ļ�
void EMSystem::readData() {
    try {
        fstream fis("data/EMinfo.dat",ios::in);
        if(!fis.is_open()){
            system("mkdir data");
            system("mkdir outputfiles");
            cout<<"���ڳ�ʼ��"<<endl;
            system("cls");
            return;
        }
        string s;
        while(getline(fis,s)){
            Employee *e = new Employee();
            *e=Employee::deSerialize(s);
            //cout<<*e<<endl;
            temp.push_back(e);
            hashset.insert(e);
        }
        fis.close();
    } catch (std::exception &e){
        cout<<e.what()<<endl;
    }

}
//д������ļ�
void EMSystem::writeFile(Array<Employee*> &arr, string filename) {
    try{
        fstream fos("outputfiles/"+filename+".csv",ios::out);
        fos<<"����,����,�Ա�,���֤��,��������,��ְʱ��,�����̶�,����ְλ,��ͥסַ,�绰����"<<endl;
        for(int j=0;j<arr.size();j++){
            Employee *const e=arr[j];
            fos<<e->name<<","<<e->age<<","<<e->sex<<","<<e->IDNumber<<","<<e->birthday.toString()<<","<<e->employment_time.toString()<<","
               <<e->education<<","<<e->job<<","<<e->address<<","<<e->telephoneNum<<endl;
        }
        fos.close();
    } catch (std::exception &e){
        cout<<e.what()<<endl;
    }

}
//��������
EMSystem::~EMSystem() {
    for(int i=0;i<temp.size();i++) delete temp[i];
}


