#include "UsersManager.h"

using namespace std;

UsersManager::UsersManager()
{
    usersList = new vector<USER *>;
    mutexROLE = new map<ROLE *, ROLE *>;
}

int UsersManager::addUSER(int id, const char *name)
{
    USER *u = new USER(id, name);
    usersList->push_back(u);
    return 0;
}

int UsersManager::deleteUSER(int id)
{
    for (auto i = usersList->begin(); i != usersList->end(); ++i)
    {
        if ((*i)->u_ID == id)
        {
            usersList->erase(i);
            return 0;
        }
    }
    // 没有该user
    return 1;
}

int UsersManager::addROLE(int id, ROLE *role)
{
    for (auto i = usersList->begin(); i != usersList->end(); ++i)
    {
        if ((*i)->u_ID == id)
        {
            // checkMutex()
            for (auto j = (*i)->ROLEs->begin(); j != (*i)->ROLEs->end(); ++j)
            {
                if (checkMutex(*j, role))
                {
                    // 有互斥不能添加
                    return 2;
                }
            }
            (*i)->ROLEs->push_back(role);
            return 0;
        }
    }
    // 没有该user
    // cout<<"没有该user"<<endl;
    return 1;
}

int UsersManager::deleteROLE(int id, int role_id)
{
    for (auto i = usersList->begin(); i != usersList->end(); ++i)
    {
        if ((*i)->u_ID == id)
        {
            for (auto j = (*i)->ROLEs->begin(); j != (*i)->ROLEs->end(); ++j)
            {
                if ((*j)->r_ID == role_id)
                {
                    (*i)->ROLEs->erase(j);
                    return 0;
                }
            }
            // 该user没有该角色role
            return 2;
        }
    }
    // 没有该user
    return 1;
}

int UsersManager::addMutexRule(ROLE *r1, ROLE *r2)
{
    mutexROLE->insert(make_pair(r1, r2));
    return 0;
}

int UsersManager::deleteMutexRule(ROLE *r1, ROLE *r2)
{
    for (auto i = mutexROLE->begin(); i != mutexROLE->end(); ++i)
    {
        if ((i->first == r1 && i->second == r2) || (i->first == r2 && i->second == r1))
        {
            mutexROLE->erase(i);
            return 0;
        }
    }
    // 没有对应互斥组
    return 1;
}

bool UsersManager::checkMutex(ROLE *r1, ROLE *r2)
{
    for (auto i = mutexROLE->begin(); i != mutexROLE->end(); ++i)
    {
        if ((i->first == r1 && i->second == r2) || (i->first == r2 && i->second == r1))
        {
            return true;
        }
    }
    // 没有互斥组
    return false;
}

vector<ROLE *> *UsersManager::getROLElist(int id)
{
    for (auto i = usersList->begin(); i != usersList->end(); ++i)
    {
        if ((*i)->u_ID == id)
        {
            return (*i)->ROLEs;
        }
    }
    // 没有该user
    return NULL;
}

void UsersManager::printList(void)
{
    for (auto i = usersList->begin(); i != usersList->end(); ++i)
    {
        (*i)->show();
        (*i)->printROLE();
    }
}

void UsersManager::printMutexRule()
{
    for (auto i = mutexROLE->begin(); i != mutexROLE->end(); ++i)
    {
        i->first->show();
        cout << "\t|X|"<<endl;
        i->second->show();
        cout << endl;
    }
}

bool UsersManager::checkPermission(int id, int PermissionID)
{
    for (auto i = usersList->begin(); i != usersList->end(); ++i)
    {
        if ((*i)->u_ID == id)
        {
            for (auto j = (*i)->ROLEs->begin(); j != (*i)->ROLEs->end(); ++j)
            {
                if ((*j)->permissionCheck(PermissionID))
                {
                    return true;
                }
            }
        }
    }
    // 没有该user
    return false;
}