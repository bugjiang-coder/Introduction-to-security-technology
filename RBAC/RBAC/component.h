#ifndef _COMPONENT_H
#define _COMPONENT_H

#include <iostream>
#include <map>
#include <vector>
using namespace std;

class PERMISSION
{
public:
    PERMISSION(int id, const char *name);
    int p_ID;
    const char *p_name;
    void show();
};

class ROLE
{
private:
    bool parentPermissionCheck(int permissionID);

public:
    ROLE *parentROLE;        // 这个用于定义继承 利用指针来继承
    vector<PERMISSION *> *p; //该role所拥有的权限
    // 这可能涉及堆的问题 堆溢出了可能要换用new 的方式
    vector<ROLE *> *childROLE; // 树形结构
    ROLE(int id, const char *name);

    int r_ID;
    const char *r_name;

    // 打印role信息
    void show();
    // 打印拥有的权限
    void printPERMISSION();
    // 递归打印继承的权限
    void printParentPERMISSION();
    // 判断是否含有该权限
    bool permissionCheck(int permissionID);
};

class USER
{
public:
    vector<ROLE *> *ROLEs; // 拥有的role
    USER(int id, const char *name);
    int u_ID;
    const char *u_name;
    void show();
    void printROLE();
};
#endif