#ifndef _USERMANAGER_H
#define _USERMANAGER_H


#include <iostream>
#include <map>
#include <vector>
#include "component.h"

// 对所有用户进行管理
class UsersManager
{
private:
    map<USER *, ROLE *> table;

public:
    map<ROLE *, ROLE *> mutexROLE;
    void add(USER *u, ROLE *r);
    void print();
    void printMutexRule();
};

#endif