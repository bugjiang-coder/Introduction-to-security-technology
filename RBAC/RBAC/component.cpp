#include "component.h"

using namespace std;

USER::USER(int id, const char *n)
{
    u_ID = id;
    u_name = n;
}

void USER::show()
{
    cout << "ID: " << u_ID << "\tname: " << u_name << endl;
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