//
// Created by 90828 on 2022-02-17.
//

#include <fstream>
#include "EMSystem.h"
#include "functional"

using namespace std;

//提示输入的输出
void elegantPrint(const char* message, bool input=true){
    cout<<message<<endl;
    if(input) cout<<"--> ";
}

void EMSystem::showWelcome() {
    cout << "=========================================欢迎使用职工管理系统！=========================================" << endl;
}
//根据名字查找职工
Array<Employee *> findEmployeeByName(Array<Employee *> &temp, string name = "") {   //设置默认值，提高代码复用性
    if (name == "") {
        elegantPrint("请输入待查询人的姓名：");
        cin >> name;
    }
    return temp.findElemBy([&](Employee *e) { return e->name == name; });
}
//根据性别
Array<Employee *> findEmployeeBySex(Array<Employee *> &temp, string sex = "") {
    if (sex == "") {
        elegantPrint("请输入待查询人的性别：");
        cin >> sex;
    }
    return temp.findElemBy([&](Employee *e) { return e->sex == sex; });
}
//根据入职时间
Array<Employee *> findEmployeeByTime(Array<Employee *> &temp, int year = 0, int month = 0, int day = 0) {
    EasyDate date;
    if (year == 0 && month == 0 && day == 0) {
        elegantPrint("请输入待查询人的入职时间（yyyy mm dd）：");
        cin >> year >> month >> day;
    }
    while (!date.setDate(year, month, day)) {
        elegantPrint("输入的日期不正确！请再次输入.");
        cin >> year >> month >> day;
    }
    return temp.findElemBy([&](Employee *e) { return date < e->employment_time; });
}
//根据身份证id
Employee *findEmployeeByID(HashSet<Employee*> &hashset, string id = "") {
    if (id == "") {
        elegantPrint("请输入待查询人的身份证号：");
        cin >> id;
    }
    Employee e(id);
    return hashset.find(&e,[](Employee *a,Employee *b){return  a->IDNumber==b->IDNumber;});
}
//显示菜单
bool EMSystem::showMenu() {
    cout << "---------------------------------------------------------------------------------------------------" << endl;
    elegantPrint("1、新建职工信息 2、删除职工信息 3、查询职工信息 4、修改职工信息 5、对职工信息进行排序 0、保存退出系统 -1、直接退出系统" );
    void (EMSystem::*functions[5])()={  //函数指针数组存放功能函数
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
    else (this->*functions[choice-1])();    //避免使用switch语句
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
    cin.clear();//处理输入流
    cin.sync();
    return true;
}
//输出职工缓存数组
void outputPtrMessage(Array<Employee*> &t){
    if(t.size()==0){
        cout<<"[empty]"<<endl;
        return;
    }
    cout<<"[";
    for(int i=0;i+1<t.size();i++) cout<<*(t[i])<<endl;
    cout<<*t[t.size()-1]<<"]"<<endl;
}
//改
void EMSystem::modify() {
    elegantPrint("请输入要修改的职工的身份证号，或输入0进行查询");
    string id;
    cin >> id;
    if (id[0] == '0') return query();
    Employee *d = findEmployeeByID(hashset, id);
    if (d == nullptr) {
        cout << "没有找到该职工！" << endl;
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
    elegantPrint("请输入要修改的姓名和身份证号（或输入0保留原有信息）");
    cin >> name >> id;
    while (findEmployeeByID(hashset, id)) {
        elegantPrint("已经存在该身份信息，请重新输入身份证号!");
        cin >> id;
    }
    if (name[0] != '0') e->name = name;else e->name=d->name;
    if (id[0] != '0') e->IDNumber = id; else e->IDNumber=d->IDNumber;
    elegantPrint("请依次输入性别、年龄、家庭住址、学历、工作、电话号码(或输入0保留原有信息):");
    cin >> sex >> age >> address >> education >> job >> telephoneNum;
    if (sex[0] != '0') e->sex = sex; else e->sex=d->sex;
    if (age != 0) e->age = age; else e->age = d->age;
    if (address[0] != '0') e->address = address; else e->address=d->address;
    if (education[0] != '0') e->education = education; else e->education=d->education;
    if (job[0] != '0') e->job = job; else e->job=d->job;
    if (telephoneNum[0] != '0') e->telephoneNum = telephoneNum; else e->telephoneNum=d->telephoneNum;
    elegantPrint("请输入出生日期的年、月、日(或输入3次0保留原有信息):");
    int year, month, day;
    while(cin >> year >> month >> day){
        if(year&&month&&day){
            if(e->birthday.setDate(year,month,day)) {
                break;
            } else {
                cout<<"输入的信息有误！请重新输入！"<<endl;
            }
        } else {
            e->birthday=d->birthday;
            break;
        }
    }
    elegantPrint("请输入入职日期的年、月、日:(或输入3次0保留原有信息)");
    while(cin >> year >> month >> day){
        if(year&&month&&day){
            if(e->employment_time.setDate(year,month,day)) {
                break;
            } else {
                cout<<"输入的信息有误！请重新输入！"<<endl;
            }
        } else {
            e->employment_time=d->employment_time;
            break;
        }
    }
    cout << "当前职工信息被修改为：" << *e << ",是否要保存？(y/n)--> ";
    char operation = 0;
    while (cin >> operation) {
        if (operation == 'n' || operation == 'N') {
            cout << "取消了操作。" << endl;
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
    cout << "修改信息成功。" << endl;
}
//增
void EMSystem::add() {
    elegantPrint("请输入要添加的职工的姓名和身份证号：");
    string name, ID;
    cin >> name >> ID;
    char operation;
    Employee *x = findEmployeeByID(hashset, ID);
    if (x != nullptr) {
        cout << "该身份证已被使用！" << endl;
        cout<<endl;
        return;
    }
    Employee *employee = new Employee(ID);
    employee->name = name;
    elegantPrint("请依次输入性别、年龄、家庭住址、学历、工作、电话号码:");
    int year;
    string sex, address, education, job, tel;
    cin >> sex >> year >> address >> education >> job >> tel;
    employee->sex = sex;
    employee->age = year;
    employee->address = address;
    employee->education = education;
    employee->job = job;
    employee->telephoneNum = tel;
    elegantPrint("请输入出生日期的年、月、日:");
    int month, day;
    while(cin >> year >> month >> day) {
        if (!employee->birthday.setDate(year, month, day)){
            elegantPrint("输入不合法！请重新输入。");
        }
        else break;
    }
    elegantPrint("请输入入职日期的年、月、日:");
    while(cin >> year >> month >> day) {
        if (!employee->employment_time.setDate(year, month, day)){
            elegantPrint("输入不合法！请重新输入。");
        }
        else break;
    }
    cout << "当前要添加的职工信息为：" << *employee << ",是否要保存？(y/n)--> ";
    while (cin >> operation) {
        if (operation == 'n' || operation == 'N') {
            cout << "取消了操作。" << endl;
            return;
        } else if (operation != 'Y' && operation != 'y') {
            cout << endl;
        } else break;
    }
    temp.push_back(employee);
    hashset.insert(employee);
    cout << "成功添加了新职工。" << endl;
}
//查
void EMSystem::query() {
    elegantPrint("1、根据身份证号直接查询 2、根据姓名查询 3、根据性别查询 4、根据入职时长大小查询 5、查询当前全部信息 0、返回");
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
        cout << "查询到的结果为：" << endl;
        outputPtrMessage(t);
        elegantPrint("是否要输出查询信息？(y/n)");
        char operation;
        while (cin >> operation) {
            if (operation == 'n' || operation == 'N') {
                return;
            } else if (operation != 'Y' && operation != 'y') {
                cout << endl;
            } else break;
        }
        writeFile(t,"result");
        cout<<"成功输出文件到：outputfiles/result.csv,可用excel进行查看"<<endl;
    }
    else if(choice==1) {
        if(e== nullptr) cout<<"没有查询到结果"<<endl;
        else cout << "查询到的结果为：" << *e << endl;
    }
}
//删
void EMSystem::remove() {
    cout << "请输入要修改的职工的身份证号，或输入0进行查询,输入-1取消" << endl;
    cout << "-->";
    string id;
    cin >> id;
    if (id[0] == '0') return query();
    else if (id[0] == '-') return;
    Employee *e = findEmployeeByID(hashset, id);
    if (e == nullptr) {
        cout << "没有找到该职工！" << endl;
        return remove();
    }
    hashset.remove(e);
    temp.remove(e);
    cout << "成功删除了选择的职工" << endl;
}
//排序
void EMSystem::sort() {
    elegantPrint("1、根据姓名字典序排序 2、根据年龄排序、 3、根据入职时间排序 0、返回");
    function<bool(Employee *, Employee *)> compare[] = {
            [](Employee *a, Employee *b) { return a->name <= b->name; },
            [](Employee *a, Employee *b) { return a->age <= b->age; },
            [](Employee *a, Employee *b) { return a->employment_time <= b->employment_time; },
    };
    int choice;
    cin >> choice;
    if (choice > 3) {
        cout << "输入不合法！" << endl;
    } else if (choice == 0) return;
    temp.sort(compare[choice - 1]);
    cout<<"排序完成，结果为："<<endl;
    outputPtrMessage(temp);
    elegantPrint("是否输出排序文件？(y/n)");
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
    cout<<"成功输出文件到：outputfiles/"+names[choice-1]+".csv,可用excel进行查看"<<endl;
}
//备份系统文件
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
//保存系统文件
void EMSystem::writeData() {
    try {
        backups();
        fstream fos("data/EMinfo.dat", ios::out);
        if (!fos.is_open()) {
            cout << "未能保存文件" << endl;
            return;
        }
        string s;
        for (int i = 0; i < temp.size(); i++) {
            s = temp[i]->simpleSerialize();
            fos << s << endl;
        }
        cout << "已保存" << endl;
        fos.close();
    } catch (std::exception &e){
        cout<<e.what()<<endl;
    }
}
//读取系统文件
void EMSystem::readData() {
    try {
        fstream fis("data/EMinfo.dat",ios::in);
        if(!fis.is_open()){
            system("mkdir data");
            system("mkdir outputfiles");
            cout<<"正在初始化"<<endl;
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
//写出表格文件
void EMSystem::writeFile(Array<Employee*> &arr, string filename) {
    try{
        fstream fos("outputfiles/"+filename+".csv",ios::out);
        fos<<"姓名,年龄,性别,身份证号,出生日期,入职时间,教育程度,工作职位,家庭住址,电话号码"<<endl;
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
//析构函数
EMSystem::~EMSystem() {
    for(int i=0;i<temp.size();i++) delete temp[i];
}


