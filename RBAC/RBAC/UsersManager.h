#ifndef _USERMANAGER_H
#define _USERMANAGER_H

#include "component.h"
#include <iostream>
#include <map>
#include <vector>

// �������û����й���
class UsersManager
{
private:
    // �û���
    vector<USER *> *usersList;

public:
    // ���캯��
    UsersManager(void);
    // ע�⣡����userManager�����û�Ȩ�޵ķ��䣬����userManager����role�Ļ���
    map<ROLE *, ROLE *> *mutexROLE;
    /*------------------------��---------------------------*/
    // ���һ��user
    int addUSER(int id, const char *name);

    /*------------------------ɾ---------------------------*/
    // ɾ��һ��role
    int deleteUSER(int id);

    /*------------------------��---------------------------*/
    // �޸��û���role
    // ��ĳһ��role���Ȩ��
    int addROLE(int id, ROLE *role);
    // ɾ��ĳһrole��Ȩ��
    int deleteROLE(int id, int role_id);

    // �޸Ļ������
    //���ӻ������
    int addMutexRule(ROLE *r1, ROLE *r2);
    // ɾ���������
    int deleteMutexRule(ROLE *r1, ROLE *r2);
    // ����Ƿ񻥳�
    bool checkMutex(ROLE *r1, ROLE *r2);

    /*------------------------��---------------------------*/
    // ��ȡһ���û� rolelist��ָ��
    vector<ROLE *> *getROLElist(int id);
    // ��ӡ����user�Լ������е�role
    void printList(void);
    // ��ӡ���л������
    void printMutexRule();


    bool checkPermission(int id, int PermissionID);
};

#endif