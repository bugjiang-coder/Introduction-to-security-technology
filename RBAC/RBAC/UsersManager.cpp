#include "UsersManager.h"

using namespace std;

void UsersManager::add(USER *u, ROLE *r)
{
    (table).insert(make_pair(u, r));
}

void UsersManager::print()
{
    for (auto it = table.begin(); it != table.end(); it++)
        ;
    // cout << it->first.ID << "\t<--->\t" << it->second.roleID << endl;
}