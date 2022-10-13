
#include "header.cpp"
#include <vector>

class Music{

    public:
        void MusicMain();
        void Load(vector<string>&);
        void PrintList(vector<string>&);

}Music;

void Music::MusicMain(){

    vector<string> list;
    Load(list);
    PrintList(list);

}

void Music::Load(vector<string>& list){

    ClearScreen();
    Print("Loading Music...\n", 20);

    string path=".\\data\\music\\";
    long long hFile = 0;
    struct _finddata_t fileinfo;
    string p;
    if((hFile = _findfirst(p.assign(path).append("\\*.rbq").c_str(),&fileinfo)) !=  -1)
    {
        do
        {
            if(!(fileinfo.attrib &  _A_SUBDIR))
            {
                list.push_back(fileinfo.name);
                vector<string> strlist;
                cout<<"Loading "<<fileinfo.name<<endl;
            }
        }while(_findnext(hFile, &fileinfo)  == 0);
        _findclose(hFile);
    }
    
    Sleep(OneSecond/5);
    cout << "Loaded!" ;
    Sleep(OneSecond/5);

}

void Music::PrintList(vector<string>& list){

    ClearScreen();
    printf("=============== Music List(total %d) ===============\n",list.size());

    for(int i=0;i<list.size();i++)
        cout<<list[i]<<endl;

    printf("===================================================\n");

    cout << "Press 'q' to quit.";

    while(1)
    {
        if(_kbhit())
        {
            char c=_getch();
            if(c=='q' or c=='Q') break;
        }
    }

}