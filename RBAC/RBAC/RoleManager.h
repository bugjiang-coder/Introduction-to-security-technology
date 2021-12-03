#ifndef _ROLEMANAGER_H
#define _ROLEMANAGER_H


#include "component.h"
using namespace std;


// ����һ�� role manager ��ɫ������ �����ɫ��Ȩ�޵�ӳ��
// ��ʵ����ʵ��һ�����Ĺ���

class RoleManager
{
private:
    // ����һ������������role���б�
    vector<ROLE *> roleList;

public:
    /*------------------------��---------------------------*/
    // ���һ��role
    int addROLE(int id, const char *name);
    // �ӽ�ɫ�̳����и�role��Ȩ��
    int addChildROLE(int P_id, int id, const char *name);

    /*------------------------ɾ---------------------------*/
    // ɾ��һ��role
    int deleteROLE(int id);

    /*------------------------��---------------------------*/
    // �޸�role��Ȩ�޵�
    // ��ĳһ��role���Ȩ��
    int addPERMISSION(int id, PERMISSION *permision);
    // ɾ��ĳһrole��Ȩ��
    int deletePERMISSION(int id, int permision_id);

    /*------------------------��---------------------------*/
    // ��ӡ����role�Լ������е�Ȩ��
    void printList(void);
};

#endif