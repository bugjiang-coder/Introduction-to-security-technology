#include <iostream>
#include <map>
#include <vector>
#include "component.h"
#include "UsersManager.h"
#include "RoleManager.h"
using namespace std;

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

    // 所有权限
    // 新建     删除    读取    更改	执行
    PERMISSION *p1 = new PERMISSION(1001, "Build");
    PERMISSION *p2 = new PERMISSION(1002, "Delete");
    PERMISSION *p3 = new PERMISSION(1003, "Read");
    PERMISSION *p4 = new PERMISSION(1004, "Change");
    PERMISSION *p5 = new PERMISSION(1005, "Execution");

    p1->show();

    RoleManager roles;
    roles.addROLE(101, "Project Execution");
    roles.addROLE(102, "Project Design");
    roles.addPERMISSION(101, p3);
    roles.addPERMISSION(101, p5);
    roles.addPERMISSION(102, p1);
    roles.addPERMISSION(102, p4);
    roles.addChildROLE(101, 103, "Project Execution Manager");
    roles.addChildROLE(102, 104, "Project Design Manager");
    roles.addPERMISSION(103, p2);
    roles.addPERMISSION(104, p2);

    roles.addROLE(100, "BOSS");
    roles.addPERMISSION(100, p1);
    roles.addPERMISSION(100, p2);
    roles.addPERMISSION(100, p3);
    roles.addPERMISSION(100, p4);
    roles.addPERMISSION(100, p5);

    roles.printList();
    cout << "-----------------------------------------------------------" << endl;

    roles.deleteROLE(101);
    roles.deletePERMISSION(100, 1005);
    roles.printList();
    // cout << "123" << endl;

    return 0;
}