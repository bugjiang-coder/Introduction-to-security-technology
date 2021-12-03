#ifndef _USERMANAGER_H
#define _USERMANAGER_H


#include <iostream>
#include <map>
#include <vector>
#include "component.h"

// �������û����й���
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