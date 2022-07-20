//
// Created by 90828 on 2022-02-16.
//

#include "Employee.h"
#include <cstdio>
#include <iostream>
#include <sstream>

using namespace std;

//�������������
std::ostream &operator<<(std::ostream &os, const Employee &employee) {
    os << "[����: " << employee.age << " ����: " << employee.name << " ���֤��: " << employee.IDNumber << " �Ա�: "
       << employee.sex << " ��������: " << employee.birthday.toString() << " ��ְʱ��: " << employee.employment_time.toString()
       << " �����̶�: " << employee.education << " ְλ: " << employee.job << " ��ͥ��ַ: " << employee.address
       << " �绰����: " << employee.telephoneNum << "]";
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
//���캯��
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
//��д���͹�ϣֵ����
size_t std::hash<Employee>::operator()(const Employee &e) const {
    size_t res = 0;
    const int MOD = 1e9;
    if (e.IDNumber.length() < 18) return hash<string>()(e.IDNumber);
    for (int i = 9; i <= 18; i++) res = (res * 10 + e.IDNumber[i] - '0') % MOD;
    return res;
}
//��д���͹�ϣֵ����
size_t std::hash<Employee *>::operator()(const Employee *e) const {
    size_t res = 0;
    const int MOD = 1e9;
    if (e->IDNumber.length() < 18) return hash<string>()(e->IDNumber);
    for (int i = 9; i <= 18; i++) res = (res * 10 + e->IDNumber[i] - '0') % MOD;
    return res;
}
