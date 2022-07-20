//
// Created by 90828 on 2022-02-16.
//

#ifndef NEWEMSYSTEM_EMPLOYEE_H
#define NEWEMSYSTEM_EMPLOYEE_H

#pragma pack(push,2)
#include <cstddef>
#include <string>
#include <iostream>
#include "EasyDate.h"
using namespace std;

struct Employee {
public:
    int age;    //年龄
    EasyDate birthday;  //出生日期
    EasyDate employment_time;   //工作时间
    string name;    //姓名
    string IDNumber;    //身份证号
    string sex; //性别
    string education;   //学历
    string job; //工作
    string address; //家庭地址
    string telephoneNum;    //电话号码

    Employee();
    Employee(const string &idNumber);

    Employee(int8_t age, const string &name, const string &idNumber, const string &sex, const EasyDate &birthday,
             const EasyDate &employmentTime, const string &education, const string &job, const string &address,
             const string &telephoneNum);

    bool operator==(const Employee &rhs) const; //重载相等关系，用于查询

    bool operator!=(const Employee &rhs) const;

    string simpleSerialize(); //简易序列化

    static Employee deSerialize(string src);    //简易逆序列化

    friend std::ostream &operator<<(std::ostream &os, const Employee &employee);    //重载输出流
};
template<>
class std::hash<Employee> {
public:
    size_t operator()(const Employee &e) const; //实现职工类的哈希值
};
template<>
class std::hash<Employee*> {
public:
    size_t operator()(const Employee* e) const; //实现职工类指针的哈希值
};



#endif //NEWEMSYSTEM_EMPLOYEE_H
