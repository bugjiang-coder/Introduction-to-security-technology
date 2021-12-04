#ifndef _USERMANAGER_H
#define _USERMANAGER_H

#include "component.h"
#include <iostream>
#include <map>
#include <vector>

// 对所有用户进行管理
class UsersManager
{
private:
    // 用户表
    vector<USER *> *usersList;

public:
    // 构造函数
    UsersManager(void);
    // 注意！由于userManager管理用户权限的分配，所以userManager管理role的互斥
    map<ROLE *, ROLE *> *mutexROLE;
    /*------------------------增---------------------------*/
    // 添加一个user
    int addUSER(int id, const char *name);

    /*------------------------删---------------------------*/
    // 删除一个role
    int deleteUSER(int id);

    /*------------------------改---------------------------*/
    // 修改用户的role
    // 给某一个role添加权限
    int addROLE(int id, ROLE *role);
    // 删除某一role的权限
    int deleteROLE(int id, int role_id);

    // 修改互斥规则
    //增加互斥规则
    int addMutexRule(ROLE *r1, ROLE *r2);
    // 删除互斥规则
    int deleteMutexRule(ROLE *r1, ROLE *r2);
    // 检查是否互斥
    bool checkMutex(ROLE *r1, ROLE *r2);

    /*------------------------查---------------------------*/
    // 获取一个用户 rolelist的指针
    vector<ROLE *> *getROLElist(int id);
    // 打印所有user以及其所有的role
    void printList(void);
    // 打印所有互斥规则
    void printMutexRule();


    bool checkPermission(int id, int PermissionID);
};

#endif