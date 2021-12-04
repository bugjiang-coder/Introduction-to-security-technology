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
    ROLE *parentROLE;        // ������ڶ���̳� ����ָ�����̳�
    vector<PERMISSION *> *p; //��role��ӵ�е�Ȩ��
    // ������漰�ѵ����� ������˿���Ҫ����new �ķ�ʽ
    vector<ROLE *> *childROLE; // ���νṹ
    ROLE(int id, const char *name);

    int r_ID;
    const char *r_name;

    // ��ӡrole��Ϣ
    void show();
    // ��ӡӵ�е�Ȩ��
    void printPERMISSION();
    // �ݹ��ӡ�̳е�Ȩ��
    void printParentPERMISSION();
    // �ж��Ƿ��и�Ȩ��
    bool permissionCheck(int permissionID);
};

class USER
{
public:
    vector<ROLE *> *ROLEs; // ӵ�е�role
    USER(int id, const char *name);
    int u_ID;
    const char *u_name;
    void show();
    void printROLE();
};
#endif