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
    Player player((int)rand() % RANGE, (int)rand() % RANGE);

    srand((unsigned int)time(NULL));
    cout << "How many monsters?";
    char cnum[100];
    cin.getline(cnum, 100);
    int num = atoi(cnum);
    for (int i = 0; i < num; i++)
    {
        cout << "name of " << i << "? ";
        char tempName[100];
        cin.getline(tempName, 100);
        monsterManager.Add(new Monster(tempName, (int)rand() % RANGE, (int)rand() % RANGE, LIFETIME));
    }
    

    while (true)
    {
        cout << endl;
        monsterManager.Print();
        player.Print();

        cout << "Press A to move left, D to move right, W to move up, S to move down or Q to quit" << endl;

        bool quit = false;
        char c = _getch();
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
            cout << "Invalid Input" << endl;
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

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
