#include <iostream>
using namespace std;

class user
{
public:
    int id;
    char name[];
};

class role
{
public:
    int roleID;
    char roleName[];
};

class permission
{
public:
    int permissionID;
    char permissionName[];
};

// 利用c++的数据STL库定义上面三个元素 的关系  

int main()
{
    cout << "Hello, world!" << endl;
    return 0;
}