//
// Created by 90828 on 2022-02-16.
//

#include "Employee.h"
#include <cstdio>
#include <iostream>
#include <sstream>

using namespace std;

//重载输出流运算
std::ostream &operator<<(std::ostream &os, const Employee &employee) {
    os << "[年龄: " << employee.age << " 姓名: " << employee.name << " 身份证号: " << employee.IDNumber << " 性别: "
       << employee.sex << " 出生日期: " << employee.birthday.toString() << " 入职时间: " << employee.employment_time.toString()
       << " 教育程度: " << employee.education << " 职位: " << employee.job << " 家庭地址: " << employee.address
       << " 电话号码: " << employee.telephoneNum << "]";
    return os;
}

Employee::Employee(const string &idNumber) : IDNumber(idNumber) {}

Employee::Employee() {}

bool Employee::operator==(const Employee &rhs) const {
    return IDNumber == rhs.IDNumber;
}

bool Employee::operator!=(const Employee &rhs) const {
    return !(rhs == *this);
}
//构造函数
Employee::Employee(int8_t age, const string &name, const string &idNumber, const string &sex, const EasyDate &birthday,
                   const EasyDate &employmentTime, const string &education, const string &job, const string &address,
                   const string &telephoneNum) : age(age), name(name), IDNumber(idNumber), sex(sex), birthday(birthday),
                                                 employment_time(employmentTime), education(education), job(job),
                                                 address(address), telephoneNum(telephoneNum) {}

string Employee::simpleSerialize() {
    char buf[2048];
    int d1,d2,d3,d4,d5,d6;
    int len = sprintf(buf,"%d %d %d %d %d %d %d %s %s %s %s %s %s %s",
                      age,birthday.year,birthday.month,birthday.day,employment_time.year,employment_time.month,employment_time.day,
                      name.c_str(),IDNumber.c_str(),sex.c_str(),education.c_str(),job.c_str(),address.c_str(),telephoneNum.c_str()
    );
    return string(buf,buf+len);
}

Employee Employee::deSerialize(string src) {
    string s1,s2,s3,s4,s5,s6,s7;
    int age,d1,d2,d3,d4,d5,d6;
    const char *buf=src.c_str();
    istringstream iss(src);
    iss>>age>>d1>>d2>>d3>>d4>>d5>>d6>>s1>>s2>>s3>>s4>>s5>>s6>>s7;
    return Employee(age,s1,s2,s3,{d1,d2,d3},{d4,d5,d6},s4,s5,s6,s7);
}
//重写类型哈希值函数
size_t std::hash<Employee>::operator()(const Employee &e) const {
    size_t res = 0;
    const int MOD = 1e9;
    if (e.IDNumber.length() < 18) return hash<string>()(e.IDNumber);
    for (int i = 9; i <= 18; i++) res = (res * 10 + e.IDNumber[i] - '0') % MOD;
    return res;
}
//重写类型哈希值函数
size_t std::hash<Employee *>::operator()(const Employee *e) const {
    size_t res = 0;
    const int MOD = 1e9;
    if (e->IDNumber.length() < 18) return hash<string>()(e->IDNumber);
    for (int i = 9; i <= 18; i++) res = (res * 10 + e->IDNumber[i] - '0') % MOD;
    return res;
}
