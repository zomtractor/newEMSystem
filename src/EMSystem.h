//
// Created by 90828 on 2022-02-17.
//

#ifndef NEWEMSYSTEM_EMSYSTEM_H
#define NEWEMSYSTEM_EMSYSTEM_H


#include "Employee.h"
#include "Array.hpp"
#include "HashSet.hpp"
#define DEBUG
class EMSystem {
//#ifdef DEBUG
//public:
//#endif
    Array<Employee*> temp; //缓存职工信息
    HashSet<Employee*> hashset; //保存职工信息
public:
    ~EMSystem();
    void showWelcome(); //显示欢迎界面
    bool showMenu();  //显示菜单
    void add(); //添加职工
    void remove(); //删除职工
    void query(); //查询职工
    void modify(); //修改职工信息
    void sort(); //排序职工信息

    void readData(); //保存职工信息
    void writeData(); //读取职工信息
    void writeFile(Array<Employee*> &arr, string filename); //输出职工文件
};


#endif //NEWEMSYSTEM_EMSYSTEM_H
