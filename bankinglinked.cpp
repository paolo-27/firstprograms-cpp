using namespace std;
#include <iostream>
#include <cstring>
void displaymenu1(){
    system("clear");
    cout<<"==========Banking System==========\n";
    cout<<"[1]Register\n";
    cout<<"[2]Log In\n";
    cout<<"[3]Exit\n";
    
}//hello
void displaymenu2(){
    system("clear");
    cout<<"==========banking system==========\n";
    cout<<"[1]Deposit\n";
    cout<<"[2]Withdraw\n";
    cout<<"[3]Check Balance\n";
    cout<<"[4]Exit\n";
}

struct node{
    char fullname[21];
    char username[21];
    char password[21];
    int balance;
    node* next;

    node(char* fn, char* un, char* pass){
        strcpy(fullname, fn);strcpy(username, un);strcpy(password, pass);
        next = nullptr;
        balance = 0;
    }
};

struct linkedlist{
    node* head;

    linkedlist(){
        head = nullptr;
    }

    void reg(char* fn, char* un, char* pass){
        node* newnode = new node(fn,un,pass);

        if(head == nullptr){
            head = newnode;
            return;
        }

        node* temp = head;
        while(temp->next!=nullptr){
            temp = temp->next;
        }
        temp->next = newnode;
    }

    void login(char* un, char* pass){
        node* temp = head;
        int chs,dep,with;
        while(temp!=nullptr){
            if(strcmp(temp->username, un)==0 && strcmp(temp->password, pass) == 0){
                do{
                system("clear");
                displaymenu2();
                cout<<"Enter choice:";
                cin>>chs;
                cin.ignore();
                    switch(chs){
                        case 1:
                            cout<<"Enter amount to deposit:";
                            cin>>dep;
                            cin.ignore();
                            if(dep<0){cout<<"Please input right amount\n\n";}
                            else{temp->balance+=dep;}
                            break;
                        
                        case 2:
                            cout<<"Enter amount to withdraw:";
                            cin>>with;
                            cin.ignore();
                            if(with<0 || with>temp->balance){cout<<"Please input right amount\n\n";}
                            else{temp->balance-=with;}
                            break;

                        case 3:
                            system("clear");
                            cout<<"Current Balance:"<<temp->balance<<endl;
                            break;
                        
                        case 4:
                            return;
                    }
                    if(chs!=4){
                        cout<<"Press Enter to continue...\n";
                        cin.ignore();
                    }
                }while(chs!=4);
            }
            temp = temp->next;
        }    
    }

    
};

int main(){
    int chs;
    linkedlist list;
    char un[21];char fn[21];char pass[21];
    do{
        displaymenu1();
        cout<<"Enter choice:";
        cin>>chs;
        cin.ignore();
        switch(chs){
            case 1:
                system("clear");
                {cout<<"Enter Fullname: "; 
                cin.getline(fn, 21);
                cout<<"Enter Username: ";
                cin.getline(un, 21);
                cout<<"Enter Password: ";
                cin.getline(pass,21);
                list.reg(fn, un, pass);}
                break;
            case 2:
                system("clear");
                {cout<<"Enter Username: ";
                cin.getline(un, 21);
                cout<<"Enter Password: ";
                cin.getline(pass,21);
                list.login(un, pass);}
                break;
            case 3:
                cout<<"Exiting the program.....\n";
                exit(0);
        }
        if(chs!=10){
            cout<<"Press Enter to continue......\n";
            cin.ignore();
        }
    }while(chs!=3);


    return 0;
}