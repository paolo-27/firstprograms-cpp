using namespace std;
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
#include<cstring>
#include<algorithm>
#include<iomanip>

struct debt_info{

    string lender;
    string name;
    double amount;
    string contact_num;
    string borrow_date;
    string due_date; 
};

struct debter_account{

    string username;
    string password;
};


struct debt_system_function{

void register_account(vector<debter_account>&debter){
    debter_account d;
    cout<<"Enter Username:";
    cin>>ws;getline(cin,d.username);
    for(int i=0;i<debter.size();i++){
        if(debter[i].username == d.username){
            cout<<"Username already exists\n";
            return;
        }
    }
    cout<<"Enter password:";
    cin>>ws;getline(cin, d.password);
    cout<<"Registration Successfully\n";
    debter.push_back(d);
    
}
void display_menu1(){  
          
    system("clear");
    cout<<string(29, '-');cout<<"DEBT MANAGEMENT SYSTEM";cout<<string(29, '-')<<endl;
    cout<<"[1] Add Debt\n[2] View Debt\n[3] Save added and Deleted Debt\n[4] Exit\n ";
}

void add_debt(vector<debt_info>&debt,const string &current_user){
    debt_info df;
    df.lender = current_user;
    double init_debt;
    double init_interest;
    cout<<string(29, '-');cout<<"Borrower's Information";cout<<string(29, '-')<<endl;
    cout<<"Enter Fullname:";
    cin>>ws;getline(cin,df.name);
        for(int i = 0; i<debt.size(); i++){
            if(debt[i].lender == current_user){
                if(debt[i].name == df.name){
                    cout<<"Please Make "<<df.name<<" Pay Before Making New Debt Record\n";
                    return;
                }       
            } 
        }
    cout<<"Enter Contact Number: ";
    cin>>ws;getline(cin,df.contact_num);
    cout<<"Enter Amount: ";
    cin>>init_debt;
    cin.ignore();
    do{
        cout<<"Enter Interest Rate(%):";
        cin>>init_interest;
        cin.ignore();
            if(init_interest>=0){
                double interest = init_interest/100;
                    if(interest > 0){
                    df.amount = init_debt + (init_debt * interest);
                    }
                    else{df.amount = init_debt;}
            }
            else{
                cout<<"Please Enter Equal or Greater than 0\n";
            }
    }while(init_interest<0);
    cout<<"Enter Borrow date: ";
    cin>>ws;getline(cin,df.borrow_date);
    cout<<"Enter Due Date: ";
    cin>>ws;getline(cin,df.due_date);
    cout<<"Debt Added Successfully!\n";
    cout<<"Expect "<<df.name<<" to pay "<<df.amount<<" before "<<df.due_date<<endl;
    debt.push_back(df);
}



void view_debt(vector<debt_info>&debt,const string& current_user){
    system("clear");
    cout<<string(29, '-');cout<<"Borrower's List";cout<<string(36, '-')<<endl;
    cout<<string(80, '-')<<endl;
    cout<<left<<setw(25)<<"NAME"<<setw(20)<<"CONTACT NUMBER"<<setw(20)<<"AMOUNT BORROWED"<<setw(15)<<"DUE DATE"<<endl;
    cout<<string(80, '-')<<endl;
        for( int i = 0; i<debt.size(); i++){
            if(debt[i].lender == current_user){
                cout<<left<<setw(25)<<debt[i].name<<setw(20)<<debt[i].contact_num<<setw(20)<<debt[i].amount<<setw(15)<<debt[i].due_date<<endl<<endl<<endl;
            }
        }

}

void view_debt_menus(vector<debt_info>& debt, const string& current_user){
    int chs;
    view_debt(debt,current_user);
    do{
    cout<<"[1] Sort by Date\n[2] Sort by Amount(highest to lowest)\n[3] Sort by Amount(lowest to highest)\n[4] Remove Debt\n[5] Exit\n";
    cout<<"Enter Choice: ";
    cin>>chs;
    cin.ignore();
        switch(chs){
            case 1:
                system("clear");
                debt_sort_date(debt);
                view_debt(debt,current_user);
                break;
            case 2:
                system("clear");
                debt_sort_amount_highest(debt);
                view_debt(debt,current_user);
                break;
            case 3:
                system("clear");
                debt_sort_amount_lowest(debt);
                view_debt(debt,current_user);
                break;

            case 4:
                system("clear");
                remove_debt(debt,current_user);
                view_debt(debt,current_user);
                break;

            case 5:
                return;
        }
    if(chs!=5){
        cout<<"Press Enter to continue....\n";
        cin.ignore();
    }
    }while(chs!=5);
}


void save_debt(vector<debt_info>&debt, const string& filename, const string& current_user){
    
    ofstream file(filename);
    for(int i = 0; i<debt.size(); i++){
        if(debt[i].lender == current_user){
            file<<debt[i].name<<","<<debt[i].contact_num<<","<<debt[i].amount<<","<<debt[i].borrow_date<<","<<debt[i].due_date<<"\n";
        }
    }
    file.close();
    cout<<"Debt Saved Successfully!\n";

}

void save_account(vector<debter_account>&debter, const string filename){
    ofstream file(filename);
    for( const auto&d : debter){
        file<<d.username<<","<<d.password<<"\n";
    }
    file.close();
    cout<<"Account Registered Saved!\n";
}

vector<string> csvline(const string& line, const char delimeter = ','){
    vector<string> result;
    istringstream ss(line);
    string item;
    while(getline(ss,item,delimeter)){
        result.push_back(item);
    }
    return result;
}

void load_debt_file(vector<debt_info>&debt,const string& filename,const string& current_user){

    debt.erase(remove_if(debt.begin(), debt.end(), [&](const debt_info& d){
        return d.lender == current_user;}), debt.end());

    ifstream file(filename);
    string line;
    while(getline(file,line)){
        vector<string> part = csvline(line);
            if (part.size() == 5){
                string name = part[0];
                string contact_num = part[1];
                double amount = stod(part[2]);
                string borrow_date = part[3];
                string due_date = part[4];
                debt.push_back({current_user,name, amount, contact_num, borrow_date, due_date});
            }
    }
    file.close();
}

void remove_debt(vector<debt_info>& debt, const string& current_user){
    string name;
    cout<<"enter name of the borrower: ";
    cin>>ws;getline(cin,name);
        for(int i = 0; i<debt.size(); i++){
            if(debt[i].lender == current_user){
                debt.erase(remove_if(debt.begin(), debt.end(), [&](const debt_info& d){
                return d.name == name;}), debt.end());
            }
        }
}

void load_account(vector<debter_account> &debter, const string&filename){
    ifstream file(filename);
    string line;
    while(getline(file,line)){
        vector<string> part = csvline(line);
        if (part.size() == 2 ){
            string username = part[0];
            string password = part[1];
            debter.push_back({username,password});
        }
    }
    file.close();
}

void debt_sort_date(vector<debt_info>& debt){
    sort(debt.begin() , debt.end() , [] (const debt_info& d, const debt_info& e){ return d.due_date < e.due_date ; });
}

void debt_sort_amount_highest(vector<debt_info>& debt){
    sort(debt.begin(),debt.end() , [] (const debt_info& d, const debt_info& e){return d.amount > e.amount;});
}

void debt_sort_amount_lowest(vector<debt_info>& debt){
    sort(debt.begin(), debt.end() , [] (const debt_info& d, const debt_info& e){return d.amount < e.amount;});
}

void log_in(vector<debter_account>&debter, vector<debt_info>&debt ){
    debter_account d;
    int chs;
    cout<<"enter username:";
    cin>>ws;getline(cin,d.username);
    cout<<"enter password:";
    cin>>ws;getline(cin,d.password);
    bool found = false;
        for(int i=0; i<debter.size(); i++){
            if(debter[i].username == d.username && debter[i].password == d.password){
                string current_user = d.username;
                string filename = current_user + ".txt";
                load_debt_file(debt,filename,current_user);
                cout<<"Log in Successfully!\n";
                found = true;
                do{
                display_menu1();
                cout<<"Enter Choice:";
                cin>>chs;
                cin.ignore();
                    switch(chs){
                        case 1: 
                            add_debt(debt, current_user );
                            break;

                        case 2:
                            view_debt_menus(debt,current_user);
                            break;
                        
                        case 3:
                            save_debt(debt,filename, current_user);
                            break;

                        case 4:
                            save_debt(debt,filename, current_user);
                            cout<<"Logging out...\n";
                            return;
                              
                    }

                    if(chs!=4){
                        cout<<"Press Enter to continue...\n";
                        cin.ignore();
                    }
                }while(chs!=4);
            }
           
        }   
    if(!found){cout<<"Username or Password is Incorrect!\n";}
}
};



int main(){
    vector<debt_info> debt;
    vector<debter_account> debter;
    string filename2 = "accounts.txt";
    debt_system_function go;
    go.load_account(debter, filename2);
    int chs;
        do{
            system("clear");
            cout<<string(29, '-');cout<<"Debt Management System";cout<<string(29, '-')<<endl;
            cout<<"[1] Register\n[2] Log in\n[3] Exit\n";
            cout<<"Enter Choice:";
            cin>>chs;
            cin.ignore();
                switch(chs){
                    case 1:
                        go.register_account(debter);
                        break;
                    
                    case 2:
                        go.log_in(debter, debt);
                        break;
                    
                    case 3:
                        go.save_account(debter, filename2);
                        cout<<"Exiting program....\n";
                        break;
                }
                if(chs!=3){
                    cout<<"Press Enter to continue.....\n";
                    cin.ignore();
                }
        }while(chs!=3);


    return 0;
}