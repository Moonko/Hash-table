//
//  main.cpp
//  Hash table
//
//  Created by Андрей Рычков on 17.04.13.
//  Copyright (c) 2013 Андрей Рычков. All rights reserved.
//

#include <iostream>
#include "hashTable.h"
using namespace std;

int main(int argc, const char * argv[])
{
    hash_Table<int, string, hasher> a;
    a.insert(25, "I'm ");
    a.insert(48, "dude!");
    a.insert(1, "Hello,");
    a.insert(25, "here,");
    a.erase(1);
    a.print();
    List<std::pair<int, string>>::iterator toFind = a.find(25);
    cout << "Succeded: " << (*toFind).first << ' ' << (*toFind).second << endl;
    a.insert(72, "Bye!");
    a.print();
    a.erase(72);
    a.print();
    toFind = a.find(6);
    if (toFind == a.end())
    {
        cout << "No key " << 6 << " in table";
    }
    return 0;
}

