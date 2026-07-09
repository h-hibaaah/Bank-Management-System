#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
class bank
{
protected:

    string name;
    int amount = 0;
    int balance = 0;
    int withdrawamount;
    string accountno;
    string password;
    int choice;
public:
    int getLastAccountNumber()
    {
        ifstream file("file.txt");
        string n, p, acc;
        int bal;
        int last = 1900;
        while(file >> n >> p >> acc >> bal)
        {
            string num = acc.substr(3);
            last = stoi(num);
        }
        file.close();
        return last;
    }

    bool fileread(string uname, string accno, string pass)
    {
        ifstream file("file.txt");
        while(file >> name >> password >> accountno >> balance)
        {
            if(name == uname && accountno == accno && password == pass)
            {
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }
};

class newaccount : public bank
{
public:
    void createaccount()
    {
        int count = getLastAccountNumber();

        cout << "Enter your name: ";
        cin >> name;

        cout << "Enter your password: ";
        cin >> password;

        cout << "Enter initial balance: ";
        cin >> balance;

        count++;

        accountno = "acc" + to_string(count);

        cout << "Your account number is " << accountno << endl;

        ofstream file("file.txt", ios::app);

        file << name << " "
             << password << " "
             << accountno << " "
             << balance << endl;

        file.close();

        cout << "Account created successfully\n";
    }
};

class oldaccount : public bank
{
public:

    string uname;
    string accno;
    string pass;

    void login()
    {
        cout << "Enter your name: ";
        cin >> uname;

        cout << "Enter your account number: ";
        cin >> accno;

        cout << "Enter your password: ";
        cin >> pass;

        if(fileread(uname, accno, pass))
        {
            cout << "Login Successful\n";
            userchoice();
        }
        else
        {
            cout << "Invalid Credentials\n";
        }
    }

    void userchoice()
    {
        while(true)
        {
            cout << "\n1. Deposit";
            cout << "\n2. Withdraw";
            cout << "\n3. Balance Enquiry";
            cout << "\n4. Exit";

            cout << "\nEnter choice: ";
            cin >> choice;

            switch(choice)
            {
            case 1:
                deposit();
                break;

            case 2:
                withdraw();
                break;

            case 3:
                balanceenquiry();
                break;

            case 4:
                exit(0);

            default:
                cout << "Invalid Choice";
            }
        }
    }

    void deposit()
    {
        cout << "Enter amount to deposit: ";
        cin >> amount;

        if(amount <= 0)
        {
            cout << "Invalid Amount";
            return;
        }

        ifstream file("file.txt");
        ofstream temp("temp.txt");

        string n, p, acc;
        int bal;

        while(file >> n >> p >> acc >> bal)
        {
            if(n == uname && p == pass && acc == accno)
            {
                bal += amount;
                balance = bal;

                temp << n << " "
                     << p << " "
                     << acc << " "
                     << bal << endl;
            }
            else
            {
                temp << n << " "
                     << p << " "
                     << acc << " "
                     << bal << endl;
            }
        }

        file.close();
        temp.close();

        remove("file.txt");
        rename("temp.txt", "file.txt");

        cout << "Deposit Successful\n";
        cout << "Current Balance: " << balance << endl;
    }

    void withdraw()
    {
        cout << "Enter amount to withdraw: ";
        cin >> withdrawamount;

        if(withdrawamount <= 0)
        {
            cout << "Invalid Amount";
            return;
        }

        ifstream file("file.txt");
        ofstream temp("temp.txt");

        string n, p, acc;
        int bal;

        while(file >> n >> p >> acc >> bal)
        {
            if(n == uname && p == pass && acc == accno)
            {
                if(withdrawamount > bal)
                {
                    cout << "Insufficient Balance\n";
                }
                else
                {
                    bal -= withdrawamount;
                    balance = bal;

                    cout << "Withdraw Successful\n";
                    cout << "Current Balance: " << balance << endl;
                }
            }

            temp << n << " "
                 << p << " "
                 << acc << " "
                 << bal << endl;
        }

        file.close();
        temp.close();

        remove("file.txt");
        rename("temp.txt", "file.txt");
    }

    void balanceenquiry()
    {
        cout << "Current Balance: " << balance << endl;
    }
};
class forgot : public bank
{
public:

    void forgotpassword()
    {
        string uname;
        string accno;
        string newpass;

        cout << "Enter your name: ";
        cin >> uname;

        cout << "Enter your account number: ";
        cin >> accno;

        ifstream file("file.txt");
        ofstream temp("temp.txt");

        string n, p, acc;
        int bal;

        bool found = false;

        while(file >> n >> p >> acc >> bal)
        {
            if(uname == n && accno == acc)
            {
                found = true;

                cout << "Enter new password: ";
                cin >> newpass;

                temp << n << " "
                     << newpass << " "
                     << acc << " "
                     << bal << endl;
            }
            else
            {
                temp << n << " "
                     << p << " "
                     << acc << " "
                     << bal << endl;
            }
        }

        file.close();
        temp.close();

        remove("file.txt");
        rename("temp.txt", "file.txt");

        if(found)
            cout << "Password Changed Successfully\n";
        else
            cout << "Invalid Credentials\n";
    }
};

int main()
{
    int ch;

    newaccount obj;
    oldaccount obj1;
    forgot obj2;
    while(true)
    {
        cout << "\n========== BANK MANAGEMENT SYSTEM ==========\n";
        cout << "1. Sign Up\n";
        cout << "2. Login\n";
        cout << "3. Forgot Password\n";
        cout << "4. Exit\n";

        cout << "\nEnter choice: ";
        cin >> ch;

        switch(ch)
        {
        case 1:
            obj.createaccount();
            break;

        case 2:
            obj1.login();
            break;

        case 3:
            obj2.forgotpassword();
            break;

        case 4:
            cout << "Thank you for using Bank Management System.\n";
            exit(0);

        default:
            cout << "Invalid Choice\n";
        }
    }

    return 0;
}
