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
    cout << "�����¿��ò�����" << endl;
    for (auto it = Permission_list->begin(); it != Permission_list->end(); ++it)
    {
        (*it)->show();
    }

    while(1)
    {
        cout << "����������ID:" << endl;

        cin >> userID;

        cout << "��������Ҫʹ�õ�Ȩ��ID:" << endl;

        cin >> permisionID;
        if (users.checkPermission(userID, permisionID))
        {
            cout << "ʹ�óɹ�" << endl;
        }
        else
        {
            cout << "xxx ��û�и�Ȩ�� xxx" << endl;
        }
    }
}

int main()
{
    // ����Ȩ��
    // �½�     ɾ��    ��ȡ    ����	ִ��
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

    // ����Ȩ��ִ�кͶ�ȡ����ͬʱӵ��
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

    // ɾ��Ȩ��
    users.deleteUSER(6);
    // ����л����role
    users.addROLE(2, roles.getROLE(101));
    // ���û���л����role
    // users.addROLE(5,roles.getROLE(101));

    users.printList();
    cout << "-----------------------------------------------------------" << endl;

    minShell(Permission_list, roles, users);

    return 0;
}