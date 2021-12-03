#ifndef _ROLEMANAGER_H
#define _ROLEMANAGER_H


#include "component.h"
using namespace std;


// 定义一个 role manager 角色管理器 管理角色和权限的映射
// 其实就是实现一个数的管理

class RoleManager
{
private:
    // 这是一个管理这所有role的列表
    vector<ROLE *> roleList;

public:
    /*------------------------增---------------------------*/
    // 添加一个role
    int addROLE(int id, const char *name);
    // 子角色继承所有父role的权限
    int addChildROLE(int P_id, int id, const char *name);

    /*------------------------删---------------------------*/
    // 删除一个role
    int deleteROLE(int id);

    /*------------------------改---------------------------*/
    // 修改role的权限的
    // 给某一个role添加权限
    int addPERMISSION(int id, PERMISSION *permision);
    // 删除某一role的权限
    int deletePERMISSION(int id, int permision_id);

    /*------------------------查---------------------------*/
    // 打印所有role以及其所有的权限
    void printList(void);
};

#endif