//Program To Create A Squad complete with A team name, its players and staff

#include <iostream>
#include <fstream>

using namespace std;

ofstream f,g,h,X,Y;
ifstream l,m,n;

//Class for players
class players
{
    char Name[50],Nationality[20],position[20];
    int age,trophies,Jno;
    long salary;
public:
    int Pcode;
    void getDataP()
    {
        cout<<"Enter player Name,Nationality,Jersey No,Position, Age,and salary.\n";
        cin>>Name>>Nationality>>Jno>>position>>age>>salary;
    }
    void showDataP()
    {
        cout<<Name<<'\t'<<Nationality<<"\t\t"<<Jno<<"\t\t"<<position<<"\t\t"<<age<<"\t"<<salary;
    }
    int pJersey(){return Jno;}
};

//Class for Staff
class staff
{
    char Name[50],Role[30];
    int year,SNo;
    long salary;
public:
    int Scode;
    void getDataS()
    {
        cout<<"Enter SNo support staff's Name,Role/Designation,year of joining,Salary \n";
        cin>>SNo>>Name>>Role>>year>>salary;
    }
    void showDataS()
    {
        cout<<SNo<<"\t"<<Name<<"\t"<<Role<<"\t\t"<<year<<"\t"<<salary;
    }
    int sSNo(){return SNo;}
};

//Class for Club which inherits Players and Staff
class Club: public players, public staff
{
    char ClubName[40];
public:
    int clubCode;
    void getData()
    {
        cin>>clubCode;
        cin>>ClubName;
    }
    void associate(char X,int Y)
    {
        if(X=='P')
            Pcode=Y;
        if(X=='S')
            Scode=Y;
    }
    void associateS(char X,int Y)
    {
        if(X=='S')
            Scode=Y;
    }
    void showData(){cout<<clubCode<<"    "<<ClubName<<'\n';}
};

//Prototypes of all the functions used
void createTeam(Club &p);
void showTeam(Club &p);
void addClubs(Club &p);
void addPlayers(Club &p,int X);
void addStaff(Club &p,int X);
void viewClubs(Club &p);
void viewPlayers(Club &p, int association);
void viewStaff(Club &p,int association);
void modTeam(Club &p);
void delPlayer(int x,int associate, Club &p);
void delStaff(int x, int associate, Club &p);
int showMenu();
//Main Function
int main()
{
    cout<<"\n>>SQUAD MANAGEMENT<< \n \n";
    char choose='Y';
    Club p;
    while(choose=='Y' || choose=='y')
    {
        switch(showMenu())
        {
        case 1:
            createTeam(p);
            break;
        case 2:
            viewClubs(p);
            break;
        case 3:
            showTeam(p);
            break;
        case 4:
            modTeam(p);
            break;
        default:
            cout<<"\nOOps! You need to select a VALID option!\n";
        }
        cout<<"\nDo you want to perform another operation on Your team??\n";
        cin>>choose;
    }

    return 0;
}

//Function to show a menu prompting user to perform different functions on squad
int showMenu()
{
    int X;
    cout<<"Enter one of the following operations \n";
    cout<<"1. Create team \n";
    cout<<"2. View teams \n";
    cout<<"3. Show squad Database(with players and Staff) \n";
    cout<<"4. Modify team \n";
    cin>>X;
    return X;
}

//Function to add clubs
void addClubs(Club &p)
{
    cout<<"Enter club code and name \n";
    f.open("Clubs.dat",ios::binary|ios::app);
    p.getData();
    f.write((char*)&p,sizeof(p));
    f.close();
}

//Function to add players in the created club
void addPlayers(Club &p,int X)
{
    char ch='Y';
    cout<<"\n>>Players<<\n";
    while(ch=='y' || ch=='Y')
    {
        g.open("Players.dat",ios::binary|ios::app);
        p.getDataP();
        p.associate('P',X);
        g.write((char*)&p,sizeof(p));
        g.close();
        cout<<"\nDo you want to add another player?\n";
        cin>>ch;
    }
}

//Function to add Staff members in the created club
void addStaff(Club &p,int X)
{
    char ch='y';
    cout<<"\n>>Staff<<\n";
    ch='Y';
    while(ch=='y' || ch=='Y')
    {
        h.open("Staff.dat",ios::binary|ios::app);
        p.getDataS();
        p.associateS('S',X);
        h.write((char*)&p,sizeof(p));
        h.close();
        cout<<"\nDo you want to add another staff?\n";
        cin>>ch;
    }
}

//Function to view the list of created clubs
void viewClubs(Club &p)
{
    cout<<"\nCode Name\n";
    l.open("Clubs.dat",ios::binary);

    while((l.read((char*)&p,sizeof(p)))!='\0')
        p.showData();
    l.close();
}

//Function to show all the Players of the club
void viewPlayers(Club &p, int association)
{
        cout<<"\n>>PLAYERS<<\n";
        cout<<"Name"<<'\t'<<"Nationality"<<'\t'<<"Jersey No"<<'\t'<<"Position"<<'\t'<<"Age"<<'\t'<<"Salary";
        m.open("Players.dat",ios::binary);
        while((m.read((char*)&p,sizeof(p)))!='\0')
        {
        if(association==p.Pcode)
            {
                    cout<<'\n';
                    p.showDataP();
                    cout<<'n';
            }
        }
        m.close();
}

//Function to view all the staff members of the club
void viewStaff(Club &p,int association)
{
    cout<<"\n\n>>Staff<<\n";
    cout<<"SNo."<<'\t'<<"Name"<<'\t'<<"Designation"<<'\t'<<"Year"<<'\t'<<"Salary";
    n.open("Staff.dat",ios::binary);
    while((n.read((char*)&p,sizeof(p)))!='\0' )
    {
       if(association==p.Scode)
           {
                cout<<'\n';
                p.showDataS();
                cout<<'n';
           }
    }
    n.close();
}

//Function that creates a Squad-- A team,its players and staff
void createTeam(Club &p)
{
    addClubs(p);
    addPlayers(p,p.clubCode);
    addStaff(p,p.clubCode);
}

//Function that shows a Squad-- The team, its players and staff
void showTeam(Club &p)
{
    int association;
    viewClubs(p);
    cout<<"\nEnter the Club you want to see.\n";
    cin>>association;
    viewPlayers(p,association);
    viewStaff(p,association);
}

//Function to modify an existing squad-- To add/delete a squad player/staff
void modTeam(Club &p)
{
    int Jno,Sno;
    char ch,ch2,ch3='y';
    int association;
    cout<<"\nEnter the team you want to modify\n";
    viewClubs(p);
    cin>>association;
    cout<<"\nStaff or Players(S/P)\n";
    cin>>ch;
    switch(ch)
    {
    case 'P':
    case 'p':
        viewPlayers(p,association);
        cout<<"\nDelete or Add(D/A)\n";
        cin>>ch2;
        switch(ch2)
        {
        case 'D':
        case 'd':

            cout<<"\nEnter Jersey No of the Player you want to delete\n";
            cin>>Jno;
            while(ch3=='y' || ch3=='Y')
            {
                delPlayer(Jno,association,p);
                cout<<"\nDo you want to delete more players?\n";
                cin>>ch3;
                if(ch3=='y' || ch3=='Y')
                {
                   cout<<"\nEnter Jersey No of the Player you want to delete\n";
                   cin>>Jno;
                }
            }
            break;
        case 'a':
        case 'A':
            addPlayers(p,association);
            break;
        }
    break;
    case 'S':
    case 's':
        viewStaff(p,association);
        cout<<"\nDelete or Add(D/A)\n";
        cin>>ch2;
        switch(ch2)
        {
        case 'D':
        case 'd':

            cout<<"\nEnter Serial NO. of the Staff you want to delete\n";
            cin>>Sno;
            while(ch3=='y' || ch3=='Y')
            {
                delStaff(Sno,association,p);
                cout<<"\nDo you want to delete more staff?\n";
                cin>>ch3;
                if(ch3=='y' || ch3=='Y')
                {
                   cout<<"\nEnter Serial No of the Staff you want to delete\n";
                   cin>>Sno;
                }
            }
            break;
        case 'a':
        case 'A':
            addStaff(p,association);
            break;
        }
    }
}

//Function to delete a player
void delPlayer(int x,int associate, Club&p)
{
    X.open("temp.dat",ios::binary);
    m.open("Players.dat",ios::binary);
    while((m.read((char*)&p,sizeof(p))))
        if(p.pJersey()!=x || p.Pcode!=associate)
            X.write((char*)&p,sizeof(p));
    m.close();
    X.close();
    remove("Players.dat");
    rename("temp.dat","Players.dat");
}

//Function to delete a staff member
void delStaff(int x,int associate, Club&p)
{
    Y.open("temp1.dat",ios::binary);
    n.open("Staff.dat",ios::binary);
    while((n.read((char*)&p,sizeof(p))))
        if(p.sSNo()!=x || p.Scode!=associate)
            X.write((char*)&p,sizeof(p));
    n.close();
    Y.close();
    remove("Staff.dat");
    rename("temp1.dat","Staff.dat");
}

