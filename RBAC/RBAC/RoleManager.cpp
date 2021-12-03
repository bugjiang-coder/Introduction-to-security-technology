#include "RoleManager.h"
using namespace std;

void RoleManager::printList()
{
    for (auto i = roleList.begin(); i != roleList.end(); i++)
    {
        (*i)->show();
        (*i)->printPERMISSION();
        // 如果是一个继承的role 则要打印继承的权限
        if ((*i)->parentROLE)
        {
            cout << "\t继承权限：" << endl;
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
    // 通过role的id来索引，如果没有该role则返回1，修改成功返回0
    for (auto i = roleList.begin(); i != roleList.end(); i++)
    {
        if ((*i)->r_ID == id)
        {
            (*i)->p->push_back(permision);
            return 0;
        }
    }
    // 没有该role
    return 1;
}

int RoleManager::deletePERMISSION(int id, int permision_id)
{
    // 通过role的id来索引，如果没有该role则返回1，修改成功返回0
    for (auto i = roleList.begin(); i != roleList.end(); i++)
    {
        if ((*i)->r_ID == id)
        {
            // 通过role的id来索引，如果没有该role则返回1，修改成功返回0
            for (auto j = (*i)->p->begin(); j != (*i)->p->end(); j++)
            {
                if ((*j)->p_ID == permision_id)
                {
                    (*i)->p->erase(j);
                    return 0;
                }
            }
            // 没有该 权限PERMISSION
            return 2;
        }
    }
    // 没有该role
    return 1;
}

int RoleManager::addChildROLE(int P_id, int id, const char *name)
{
    // 通过role的id来索引，如果没有该role则返回1，修改成功返回0
    for (auto i = roleList.begin(); i != roleList.end(); i++)
    {
        if ((*i)->r_ID == P_id)
        {
            ROLE *r = new ROLE(id, name);
            r->parentROLE = *i;
            roleList.push_back(r);
            // 这个错误可能是没有实例化 childROLE 这个vector
            (*i)->childROLE->push_back(r);
            return 0;
        }
    }
    // 没有该role
    return 1;
}

int RoleManager::deleteROLE(int id)
{
    // 通过role的id来索引，如果没有该role则返回1，修改成功返回0
    for (auto i = roleList.begin(); i != roleList.end(); i++)
    {
        if ((*i)->r_ID == id)
        {
            for (auto j = (*i)->childROLE->begin(); j != (*i)->childROLE->end(); ++j)
            {
                // 把所有的 子role 的父role 置为 NULL
                (*j)->parentROLE = NULL;
            }
            // 删除该role
            roleList.erase(i);
            return 0;
        }
    }
    // 没有该role
    return 1;
}