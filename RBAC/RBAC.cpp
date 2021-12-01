#include <iostream>
#include <map>
#include <vector>
using namespace std;

class USER
{
public:
    USER(int id, const char *name);
    int u_ID;
    const char *u_name;
    void show();
};

USER::USER(int id, const char *n)
{
    u_ID = id;
    u_name = n;
}

void USER::show()
{
    cout << "ID: " << u_ID << "\tname: " << u_name << endl;
}

class PERMISSION
{
public:
    PERMISSION(int id, const char *name);
    int p_ID;
    const char *p_name;
    void show();
};

PERMISSION::PERMISSION(int id, const char *n)
{
    p_ID = id;
    p_name = n;
}

void PERMISSION::show()
{
    cout << "permission ID: " << p_ID << "\tpermission name: " << p_name << endl;
}

class ROLE
{
    // private:
public:
    ROLE *parentROLE;    // ������ڶ���̳� ����ָ�����̳�
    ROLE *childROLE[16]; // ���νṹ �ܹ�ֻ��5��Ȩ������ֻ������16
    int nextFreeChild;   // ��һ�����ӽ�ɫ
    ROLE(int id, const char *name);

    int r_ID;
    const char *r_name;
    void show();
};

ROLE::ROLE(int id, const char *n)
{
    r_ID = id;
    r_name = n;
    parentROLE = NULL;
    for (int i = 0; i < 8; ++i)
        childROLE[i] = NULL;
}

void ROLE::show()
{
    cout << "role ID: " << r_ID << "\trole name: " << r_name << endl;
}

// ����һ�� role manager ��ɫ������ �����ɫ��Ȩ�޵�ӳ��
// ��ʵ����ʵ��һ�����Ĺ���

class RoleManager
{
private:
    vector<ROLE *> roleList;

public:
    void addROLE(int id, const char *name);
    void printList(void);

};

void RoleManager::addROLE(int id, const char *name)
{
    ROLE *r = new ROLE(id, name);
    roleList.push_back(r);
}

void RoleManager::printList()
{
    for (auto i = roleList.begin(); i != roleList.end(); i++)
    {
        (*i)->show();
    }
}
/*
// ����c++������STL�ⶨ����������Ԫ�� �Ĺ�ϵ
// ʹ��һ��
class URtable
{
public:
    map<user, role> entry;
    void add(user u, role r);
    void print();
};

void URtable::add(user u, role r)
{
    entry.insert(make_pair(u, r));
}

void URtable::print()
{
    for (auto it = entry.begin(); it != entry.end(); it++);
        // cout << it->first.ID << "\t<--->\t" << it->second.roleID << endl;
}
*/
int main()
{
    // ���г�Ա
    USER *A = new USER(1, "employee 1");
    USER *B = new USER(2, "employee 2");
    USER *C = new USER(3, "employee 3");
    USER *D = new USER(4, "employee 4");
    USER *M1 = new USER(5, "manager 1");
    USER *M2 = new USER(6, "manager 2");
    USER *BOOS = new USER(7, "boss");

    A->show();

    // ���н�ɫ��Ҫ��һ��������ʾ
    ROLE *r1 = new ROLE(101, "Project Execution");
    ROLE *r2 = new ROLE(102, "Project Design");

    r1->show();
    r2->show();

    // ����Ȩ��
    // �½�     ɾ��    ��ȡ    ����	ִ��
    PERMISSION *p1 = new PERMISSION(1001, "Build");
    PERMISSION *p2 = new PERMISSION(1002, "Delete");
    PERMISSION *p3 = new PERMISSION(1003, "Read");
    PERMISSION *p4 = new PERMISSION(1004, "Change");
    PERMISSION *p5 = new PERMISSION(1005, "Execution");

    p1->show();
    /*

    map<USER *, ROLE *> entry;
    // ���������map�в��ܲ��� �Լ������class ���ǿ��Բ���class��ָ��
    // ��������������û������ �ȽϷ��ŵ��µ� <
    // ���� ����û��ִ�еĴ������ ֻҪ�������ļ��У�class�У�  g++Ҳ����ұ���
    //
    entry.insert(make_pair(A, r1));

    for (auto it = entry.begin(); it != entry.end(); it++)
        cout << it->first->u_ID << "\t<--->\t" << it->second->r_ID << endl;

    */

    RoleManager roles;
    roles.addROLE(101, "Project Execution");
    roles.addROLE(102, "Project Design");
    roles.printList();

    // ��һ����Ϊ ��û��ROLE���� ������ Ȩ�ޱ�ÿ��role�ж�Ҫ����Ȩ��
    // ��vector

    // ��roleManager�ж��� �����
    // ��map

    // ����roleManager����ɾ�Ĳ�

    // δ���--
    // ע��Ҫ����һЩȨ�޵Ļ����ϵ
    // ����ͬʱ�����û��л���Ȩ�޵Ľ�ɫ
    // �����ɫ��ʱ��Ҫ���л�����

    return 0;
}