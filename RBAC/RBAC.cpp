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
    ROLE *parentROLE;    // 这个用于定义继承 利用指针来继承
    ROLE *childROLE[16]; // 树形结构 总共只有5类权限所以只定义了16
    int nextFreeChild;   // 下一个空子角色
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

// 定义一个 role manager 角色管理器 管理角色和权限的映射
// 其实就是实现一个数的管理

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
// 利用c++的数据STL库定义上面三个元素 的关系
// 使用一个
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
    // 所有成员
    USER *A = new USER(1, "employee 1");
    USER *B = new USER(2, "employee 2");
    USER *C = new USER(3, "employee 3");
    USER *D = new USER(4, "employee 4");
    USER *M1 = new USER(5, "manager 1");
    USER *M2 = new USER(6, "manager 2");
    USER *BOOS = new USER(7, "boss");

    A->show();

    // 所有角色都要用一个类来表示
    ROLE *r1 = new ROLE(101, "Project Execution");
    ROLE *r2 = new ROLE(102, "Project Design");

    r1->show();
    r2->show();

    // 所有权限
    // 新建     删除    读取    更改	执行
    PERMISSION *p1 = new PERMISSION(1001, "Build");
    PERMISSION *p2 = new PERMISSION(1002, "Delete");
    PERMISSION *p3 = new PERMISSION(1003, "Read");
    PERMISSION *p4 = new PERMISSION(1004, "Change");
    PERMISSION *p5 = new PERMISSION(1005, "Execution");

    p1->show();
    /*

    map<USER *, ROLE *> entry;
    // 奇诡的情况，map中不能插入 自己定义的class 但是可以插入class的指针
    // 这个错误好像是我没有重载 比较符号导致的 <
    // 而其 就是没有执行的错误代码 只要存在在文件中（class中）  g++也会给我报错
    //
    entry.insert(make_pair(A, r1));

    for (auto it = entry.begin(); it != entry.end(); it++)
        cout << it->first->u_ID << "\t<--->\t" << it->second->r_ID << endl;

    */

    RoleManager roles;
    roles.addROLE(101, "Project Execution");
    roles.addROLE(102, "Project Design");
    roles.printList();

    // 下一步认为 在没有ROLE类中 定义域 权限表，每个role中都要包含权限
    // 用vector

    // 在roleManager中定义 互斥表，
    // 用map

    // 完善roleManager的增删改查

    // 未完成--
    // 注意要设置一些权限的互斥关系
    // 不能同时授予用户有互斥权限的角色
    // 授予角色的时候要进行互斥检查

    return 0;
}