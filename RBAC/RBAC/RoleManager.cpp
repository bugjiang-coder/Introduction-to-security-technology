#include "RoleManager.h"
using namespace std;

void RoleManager::printList()
{
    for (auto i = roleList.begin(); i != roleList.end(); i++)
    {
        (*i)->show();
        (*i)->printPERMISSION();
        // �����һ���̳е�role ��Ҫ��ӡ�̳е�Ȩ��
        if ((*i)->parentROLE)
        {
            cout << "\t�̳�Ȩ�ޣ�" << endl;
            (*i)->printParentPERMISSION();
        }
    }
}

int RoleManager::addROLE(int id, const char *name)
{
    ROLE *r = new ROLE(id, name);
    roleList.push_back(r);
    return 0;
}

int RoleManager::addPERMISSION(int id, PERMISSION *permision)
{
    // ͨ��role��id�����������û�и�role�򷵻�1���޸ĳɹ�����0
    for (auto i = roleList.begin(); i != roleList.end(); i++)
    {
        if ((*i)->r_ID == id)
        {
            (*i)->p->push_back(permision);
            return 0;
        }
    }
    // û�и�role
    return 1;
}

int RoleManager::deletePERMISSION(int id, int permision_id)
{
    // ͨ��role��id�����������û�и�role�򷵻�1���޸ĳɹ�����0
    for (auto i = roleList.begin(); i != roleList.end(); i++)
    {
        if ((*i)->r_ID == id)
        {
            // ͨ��role��id�����������û�и�role�򷵻�1���޸ĳɹ�����0
            for (auto j = (*i)->p->begin(); j != (*i)->p->end(); j++)
            {
                if ((*j)->p_ID == permision_id)
                {
                    (*i)->p->erase(j);
                    return 0;
                }
            }
            // û�и� Ȩ��PERMISSION
            return 2;
        }
    }
    // û�и�role
    return 1;
}

int RoleManager::addChildROLE(int P_id, int id, const char *name)
{
    // ͨ��role��id�����������û�и�role�򷵻�1���޸ĳɹ�����0
    for (auto i = roleList.begin(); i != roleList.end(); i++)
    {
        if ((*i)->r_ID == P_id)
        {
            ROLE *r = new ROLE(id, name);
            r->parentROLE = *i;
            roleList.push_back(r);
            // ������������û��ʵ���� childROLE ���vector
            (*i)->childROLE->push_back(r);
            return 0;
        }
    }
    // û�и�role
    return 1;
}

int RoleManager::deleteROLE(int id)
{
    // ͨ��role��id�����������û�и�role�򷵻�1���޸ĳɹ�����0
    for (auto i = roleList.begin(); i != roleList.end(); i++)
    {
        if ((*i)->r_ID == id)
        {
            for (auto j = (*i)->childROLE->begin(); j != (*i)->childROLE->end(); ++j)
            {
                // �����е� ��role �ĸ�role ��Ϊ NULL
                (*j)->parentROLE = NULL;
            }
            // ɾ����role
            roleList.erase(i);
            return 0;
        }
    }
    // û�и�role
    return 1;
}