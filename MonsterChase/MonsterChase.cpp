// MonsterChase.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include "Monster.h"
#include "Player.h"
#include "MonstersManager.h"
#include "GlobalSettings.h"
using namespace std;

int main()
{
    MonstersManager monsterManager;

    srand((unsigned int)time(NULL));
    cout << "How many monsters? ";
    char cnum[100];
    cin.getline(cnum, 100);
    int num = atoi(cnum);
    for (int i = 0; i < num; i++)
    {
        cout << "Name of " << i << "? ";
        char tempName[100]; //this is just a temporary variable to store a name, exact memory will be allocated in the constructor of objects.
        cin.getline(tempName, 100);
        monsterManager.Add(new Monster(tempName, (int)rand() % RANGE, (int)rand() % RANGE, LIFETIME));
    }

    cout << "Player's name? ";
    char tempName[100];
    cin.getline(tempName, 100);
    Player player(tempName, 50, 50);
    

    while (true)
    {
        cout << endl;
        cout << "---------------------------------------------------" << endl;
        cout << "Area range: x in [0, "<< RANGE << "], y in [0, "<<RANGE<<"]" << endl;
        monsterManager.Print();
        player.Print();

        cout << "Press A to move left, D to move right, W to move up, S to move down, M to create a new monster, Q to quit" << endl;

        bool quit = false;
        char c = _getch();

        while (c != 'q' && c != 'w' && c != 'a' && c != 's' && c != 'd' && c != 'm')
        {
            cout << "Invalid Input" << endl;
            c = _getch();
        }

        cout << endl;

        switch (c)
        {
        case 'q':
            quit = true;
            break;
        case 'w':
            player.Move(0, 1);
            monsterManager.MonstersAct();
            break;
        case 'a':
            player.Move(-1, 0);
            monsterManager.MonstersAct();
            break;
        case 's':
            player.Move(0, -1);
            monsterManager.MonstersAct();
            break;
        case 'd':
            player.Move(1, 0);
            monsterManager.MonstersAct();
            break;
        case 'm':
            cout << "New Monster's name?";
            char tempName[100];
            cin.getline(tempName, 100);
            monsterManager.Add(new Monster(tempName, (int)rand() % RANGE, (int)rand() % RANGE, LIFETIME));
            break;
        default:
            cout << "Invalid" << endl;
        }
        if (quit) break;

        if ((int)rand() % 100 > GENERATING_CHANCE)
        {
            cout << "Oops, generating a new monster." << endl;
            char name[] = "NEWBIE";
            Monster* m = new Monster(name, (int)rand() % RANGE, (int)rand() % RANGE, LIFETIME);
            monsterManager.Add(m);
        }
    }

    return 0;
}
