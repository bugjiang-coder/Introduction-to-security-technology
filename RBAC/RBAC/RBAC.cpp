#include "RoleManager.h"
#include "UsersManager.h"
#include "component.h"
#include <iostream>
#include <map>
#include <vector>
using namespace std;

void minShell(vector<PERMISSION *> *Permission_list, RoleManager &roles, UsersManager &users)
{
    int userID, permisionID;
    char buf[64];
    cout << "有以下可用操作：" << endl;
    for (auto it = Permission_list->begin(); it != Permission_list->end(); ++it)
    {
        (*it)->show();
    }

    while(1)
    {
        cout << "请输入您的ID:" << endl;

        cin >> userID;

        cout << "请输入你要使用的权限ID:" << endl;

        cin >> permisionID;
        if (users.checkPermission(userID, permisionID))
        {
            cout << "使用成功" << endl;
        }
        else
        {
            cout << "xxx 你没有该权限 xxx" << endl;
        }
    }
}

int main()
{
    // 所有权限
    // 新建     删除    读取    更改	执行
    vector<PERMISSION *> *Permission_list;
    Permission_list = new vector<PERMISSION *>;
    PERMISSION *p1 = new PERMISSION(1001, "Build");
    PERMISSION *p2 = new PERMISSION(1002, "Delete");
    PERMISSION *p3 = new PERMISSION(1003, "Read");
    PERMISSION *p4 = new PERMISSION(1004, "Change");
    PERMISSION *p5 = new PERMISSION(1005, "Execution");
    Permission_list->push_back(p1);
    Permission_list->push_back(p2);
    Permission_list->push_back(p3);
    Permission_list->push_back(p4);
    Permission_list->push_back(p5);

    RoleManager roles;
    roles.addROLE(101, "Project Execution");
    roles.addROLE(102, "Project Design");
    roles.addChildROLE(101, 103, "Project Execution Manager");
    roles.addChildROLE(102, 104, "Project Design Manager");
    roles.addROLE(105, "BOSS");
    roles.addROLE(106, "test");

    roles.addPERMISSION(101, p3);
    roles.addPERMISSION(101, p5);
    roles.addPERMISSION(102, p1);
    roles.addPERMISSION(102, p4);

    roles.addPERMISSION(103, p2);
    roles.addPERMISSION(104, p2);

    roles.addPERMISSION(105, p1);
    roles.addPERMISSION(105, p2);
    roles.addPERMISSION(105, p3);
    roles.addPERMISSION(105, p4);
    roles.addPERMISSION(105, p5);

    roles.printList();
    cout << "-----------------------------------------------------------" << endl;

    roles.deleteROLE(106);
    // roles.deletePERMISSION(101, 1005);
    roles.printList();

    cout << "-----------------------------------------------------------" << endl;

    UsersManager users;

    users.addUSER(1, "employee 1");
    users.addUSER(2, "employee 2");
    users.addUSER(3, "manager 1");
    users.addUSER(4, "manager 2");
    users.addUSER(5, "BOSS");
    users.addUSER(6, "test");

    // 互斥权限执行和读取不能同时拥有
    users.addMutexRule(roles.getROLE(101), roles.getROLE(102));
    users.addMutexRule(roles.getROLE(103), roles.getROLE(104));

    users.addROLE(1, roles.getROLE(101));
    users.addROLE(2, roles.getROLE(102));
    users.addROLE(3, roles.getROLE(103));
    users.addROLE(4, roles.getROLE(104));
    users.addROLE(5, roles.getROLE(105));

    users.printList();
    users.printMutexRule();
    cout << "-----------------------------------------------------------" << endl;

    // 删除权限
    users.deleteUSER(6);
    // 添加有互斥的role
    users.addROLE(2, roles.getROLE(101));
    // 添加没有有互斥的role
    // users.addROLE(5,roles.getROLE(101));

    users.printList();
    cout << "-----------------------------------------------------------" << endl;

    minShell(Permission_list, roles, users);

    return 0;
}