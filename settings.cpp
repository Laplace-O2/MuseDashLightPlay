#ifndef _MDLP_SETTING
#define _MDLP_SETTING

#include <vector>
#include <set>
#include "include/header.h"

using namespace std;

/**
 * @details KeyChecker Class
*/
class Setting{
    
    private:
        vector<pair<char,int> > keys;
        int num;
        void write()
        {
            FILE* fw = fopen("data/settings.laf","w");
            for(auto key : keys)
                fprintf(fw, "%c %d\n", key.first, key.second);
            fclose(fw);
        }
        void read()
        {
            FILE* fr = fopen("data/settings.laf","r");
            keys.clear();
            char c; int x;
            while(fscanf(fr, "%c %d\n", &c, &x) != EOF)
                keys.emplace_back(c, x);
            fclose(fr);
        }
    public:
        void load()
        {
            ClearScreen();
            Print("Loading...\n", 20);
            
            if(access("data/settings.laf",0) == -1)
            {
                keys = {{'d',1}, {'f',1}, {'j',2}, {'k',2}};
                num = 2;
                write();
            }
            
            read();
            puts("Completed!");
            Sleep(OneSecond/20);
        }
        int checkKey(char c)
        {
            for(auto key : keys)
                if(c == key.first or c == key.first-32)
                    return key.second;
            return -1;
        }
        void printKey()
        {
            ClearScreen();
            puts("Your key is:");
            for(auto key : keys)
                printf("%c %d\n", key.first, key.second);
            WaitForInput();
        }
        void set(vector<pair<char,int>> newkeys, int num)
        {
            keys = newkeys;
            this->num = num;
            write();
        }
        int getKeyNum()
        {
            return num;
        }
    
};

Setting setting;

void ResetKey();

void SettingsMain()
{
    system("cls");
    Print("Settings:\n",20);
    cout << "1. Reset the keys" << endl;
    cout << "2. Print the keys" << endl;
    cout << "3. Back\n" << endl;
    while(true)
    {
        char c = WaitForInput();
        switch(c)
        {
            case '1': ResetKey(); goto end;
            case '2': setting.printKey(); goto end;
            case '3': goto end; break;
            default: break;
        }
    }
    end:;
}

void ResetKey()
{
    vector<pair<char,int>> keys;
    set<char> st; int num;
    
    begin:
    system("cls");
    puts("Input a char and a num on a line, you can input many until \"0\"");
    
    keys.clear();
    st.clear();
    num = 0;
    
    while(true)
    {
        char c; int x;
        scanf("%c", &c);
        if(c == '0') break;
        scanf("%d\n", &x);
        
        c = lower(c);
        if(st.count(c))
        {
            puts("Error: The key cannot be the same!");
            continue;
        }
        keys.emplace_back(c, x);
        num = max(num, x);
    }
    
    puts("Sure to Save?(y/n)");
    while(true)
    {
        if(!_kbhit()) continue;
        char c = _getch();
        if(c == 'n' or c == 'N') goto begin;
        else if(c == 'y' or c == 'Y') break;
    }
    
    Sleep(OneSecond);
    puts("Saving...");
    setting.set(keys, num);
    puts("The settings has saved!");
}

#endif // _MDLP_SETTING
