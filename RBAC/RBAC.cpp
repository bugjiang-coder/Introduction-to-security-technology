#include <iostream>
#include <map>
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


class ROLE
{
public:
    ROLE(int id, const char *name);
    int r_ID;
    const char *r_name;
    void show();
};

ROLE::ROLE(int id, const char *n)
{
    r_ID = id;
    r_name = n;
}

void ROLE::show()
{
    cout << "role ID: " << r_ID << "\trole name: " << r_name << endl;
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
    // map<string, int> m;
    // m["abc"] = 5;
    // m["cdf"] = 6;
    // m["b"] = 1;
    // for (auto it = m.begin(); it != m.end(); it++)
    //     cout << it->first << "<->" << it->second << endl;
    const char *a = "user1";
    const char b[6] = "user1";
    const char c[6] = "user1";
    const char d[6] = "user1";
    USER *U1 = new USER(1, a);
    USER u2(2, "user2");
    U1->show();
    u2.show();

    ROLE r1(1,"role1");
    r1.show();

    PERMISSION p1(1,"permission1");
    p1.show();

    map<USER*, ROLE*> entry;
    // ���������map�в��ܲ��� �Լ������class ���ǿ��Բ���class��ָ��
    // ���� ����û��ִ�еĴ������ ֻҪ�������ļ��У�class�У�  g++Ҳ����ұ���
    entry.insert(make_pair(U1, &r1));

    for (auto it = entry.begin(); it != entry.end(); it++)
        cout << it->first->u_ID << "\t<--->\t" << it->second->r_ID << endl;


    // USER u2(2,&b);
    // USER u3(3,&c);
    // USER u4(4,&d);

    // u2.show();
    // u3.show();
    // u4.show();

    return 0;
}