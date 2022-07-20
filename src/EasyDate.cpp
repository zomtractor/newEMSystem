//
// Created by 90828 on 2022-02-20.
//

#include "EasyDate.h"
using namespace std;
bool checkLeap(int year){
    if(year&1) return false;    //奇数年份肯定不是论年
    return (year%100!=0)? (year%4==0): (year%400==0);
    //年份如果能不能被100整除，那么它只要能被4整除就是闰年，否则，它需要能被400整除才是闰年
}
bool EasyDate::setDate(int y, int m, int d) {
    if(y>9999||m>12||d>31||m<=0||d<=0) return false;    //去除边界条件
    bool legal=false;
    switch(m){
        case 2: //特殊月份需要特殊判断
            legal=checkLeap(y)?d<=29:d<=28;
            break;
        case 3:case 5:case 7:case 8:case 10:case 12:case 1: //31天的月
            legal=d<=31;
            break;
        default:legal=d<=30;    //30天的月
    }
    if(!legal) {
        return false;
    }
    year=y,month=m,day=d;    return true;
}

string EasyDate::toString() const { //转换为字符串
    char date[]="yyyy.mm.dd";
    sprintf(date,"%.4d.%.2d.%.2d",year,month,day);
    return string(date);
}

bool EasyDate::operator<(const EasyDate &d) const {
    if(year==d.year){
        if(month==d.month) {
            if (day == d.day) {
                return false;
            }
            return day < d.day;
        }
        return month<d.month;
    }
    return year<d.year;
}

bool EasyDate::operator<=(const EasyDate &rhs) const {
    return *this<rhs || *this==rhs;
}

bool EasyDate::operator==(const EasyDate &rhs) const {
    return year == rhs.year &&
           month == rhs.month &&
           day == rhs.day;
}

bool EasyDate::operator!=(const EasyDate &rhs) const {
    return !(rhs == *this);
}

EasyDate::EasyDate(int year,int month,int day):year(year),month(month),day(day){}


