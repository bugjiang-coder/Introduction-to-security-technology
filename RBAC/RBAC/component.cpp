#include "component.h"

using namespace std;

USER::USER(int id, const char *n)
{
    u_ID = id;
    u_name = n;
    ROLEs = new vector<ROLE *>;
}

void USER::show()
{
    cout << "ID: " << u_ID << "\tname: " << u_name << endl;
}

void USER::printROLE()
{
    for (auto i = ROLEs->begin(); i != ROLEs->end(); ++i)
    {
        cout << "\t";
        (*i)->show();
    }
}

PERMISSION::PERMISSION(int id, const char *n)
{
    p_ID = id;
    p_name = n;
}

void PERMISSION::show()
{
    cout << "permission ID: " << p_ID << "\tpermission name: " << p_name << endl;
}

ROLE::ROLE(int id, const char *n)
{
    r_ID = id;
    r_name = n;
    parentROLE = NULL;
    p = new vector<PERMISSION *>;
    childROLE = new vector<ROLE *>;
}

void ROLE::show()
{
    cout << "role ID: " << r_ID << "\trole name: " << r_name << endl;
}

void ROLE::printPERMISSION()
{
    for (auto i = p->begin(); i != p->end(); ++i)
    {
        cout << '\t';
        // 打印权限信息
        (*i)->show();
    }
}

void ROLE::printParentPERMISSION()
{
    if (!parentROLE)
    {
        return;
    }

    for (auto i = parentROLE->p->begin(); i != parentROLE->p->end(); ++i)
    {
        cout << '\t';
        // 打印权限信息
        (*i)->show();
    }

    parentROLE->printParentPERMISSION();
}

bool ROLE::permissionCheck(int permissionID)
{
    for (auto i = p->begin(); i != p->end(); ++i)
    {
        if ((*i)->p_ID == permissionID)
        {
            return true;
        }
    }
    return parentPermissionCheck(permissionID);
}

bool ROLE::parentPermissionCheck(int permissionID)
{
    if (!parentROLE)
    {
        return false;
    }

    for (auto i = parentROLE->p->begin(); i != parentROLE->p->end(); ++i)
    {
        if ((*i)->p_ID == permissionID)
        {
            return true;
        }
    }

    return parentROLE->parentPermissionCheck(permissionID);
}