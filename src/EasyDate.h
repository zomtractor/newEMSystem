//
// Created by 90828 on 2022-02-20.
//

#ifndef NEWEMSYSTEM_EASYDATE_H
#define NEWEMSYSTEM_EASYDATE_H
#include <string>
struct EasyDate {
    int year: 16;
    int month: 8;
    int day: 8;

    EasyDate(int year,int month,int day);

    EasyDate(){}
    bool setDate(int y, int m, int d);

    bool operator<(const EasyDate &rhs) const;
    bool operator<=(const EasyDate &rhs) const;

    bool operator==(const EasyDate &rhs) const;

    bool operator!=(const EasyDate &rhs) const;

    std::string toString() const;
};


#endif //NEWEMSYSTEM_EASYDATE_H
