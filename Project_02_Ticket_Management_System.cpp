#include <bits/stdc++.h>
using namespace std;
#define endl "\n"

#define MAX_TIC 50
int tickets_total = 0;
int tickets_ac = 0;
int tickets_nc = 0;
int total_amm = 0;

void insert();
void del();
void dis_del();
void dis();
void find();
void month();
string dest();

// Node create
struct node
{
    string ac_non;
    string name;
    string from;
    string des;
    string time;
    int seat;
    int amm;
    struct node *next;
};
struct node *head = nullptr;

//--------------------------------------------------------------
//--------------------------------------------------------------
// Main body
int main()
{
    while (true)
    {
        cout << ">>>Ticket Management System<<<" << endl
             << "-----Menu-----" << endl
             << "1.New Ticket" << endl
             << "2.Cancel Ticket" << endl
             << "3.View Ticket List" << endl
             << "4.Monthly total" << endl
             << "5.Search" << endl
             << "6.Exit" << endl;
        int a;
        cin >> a;
        while (a < 1 || a > 6)
        {
            cout << "Enter correct value: ";
            cin >> a;
        }
        if (a == 1)
            insert();
        else if (a == 2)
            del();
        else if (a == 3)
            dis();
        else if (a == 4)
            month();
        else if (a == 5)
            find();
        else
            exit(0);
    }
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
// Insert function
void insert()
{
    if (tickets_total >= MAX_TIC)
    {
        cout << "**\"Ticket Capacity is Full!\"**" << endl;
        cout << ">>> Succesfully Added <<<" << endl
             << "Press any key to continue..." << endl;
        char c;
        cin >> c;
    }
    else
    {
        node *newnode = new node;

        //--------------------------------------------------------AC__NON-AC
        cout << "Bus Type:" << endl
             << "1.AC" << endl
             << "2.Non_AC" << endl
             << "Enter a number: ";
        int type;
        cin >> type;
        while (type != 1 && type != 2)
        {
            cout << "Enter right response: ";
            cin >> type;
        }
        if (type == 1)
            newnode->ac_non = "AC";
        else
            newnode->ac_non = "Non_AC";

        //--------------------------------------------------------TIME
        cout << "Time:" << endl
             << "1.06:00 pm" << endl
             << "2.10:00 pm" << endl
             << "Enter a number: ";
        int time;
        cin >> time;
        while (time != 1 && time != 2)
        {
            cout << "Enter right response: ";
            cin >> time;
        }
        if (time == 1)
            newnode->time = "06:00 pm";
        else
            newnode->time = "10:00 pm";

        //--------------------------------------------------------NAME
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, newnode->name);

        //--------------------------------------------------------DESTINATION
        cout << "Enter Destination: ";
        newnode->des = dest();

        //--------------------------------------------------------SEAT
        cout << "Enter number of seats: ";
        cin >> newnode->seat;

        if (newnode->ac_non == "AC")
            tickets_ac += newnode->seat;
        else
            tickets_nc += newnode->seat;

        if (newnode->seat + tickets_total > MAX_TIC)
        {
            cout << "Not enough tickets available!" << endl;
            delete newnode;
            return;
        }

        //--------------------------------------------------------TICKET
        tickets_total += newnode->seat;

        if (newnode->des == "Chittagong")
            newnode->amm = newnode->seat * 800;
        else if (newnode->des == "Shyllet")
            newnode->amm = newnode->seat * 600;
        else if (newnode->des == "Cox's Bazar")
            newnode->amm = newnode->seat * 1000;
        else if (newnode->des == "Joypurhat")
            newnode->amm = newnode->seat * 600;

        total_amm += newnode->amm;

        newnode->next = nullptr;

        //--------------------------------------------------------ADD
        if (head == nullptr)
            head = newnode;
        else
        {
            node *current = head;
            while (current->next != nullptr)
                current = current->next;

            current->next = newnode;
        }
        cout << ">>> Succesfully Added <<<" << endl
             << "Press any key to continue..." << endl;
        char c;
        cin >> c;
    }
}

//----------------------------------------------------------------
//----------------------------------------------------------------
// Delete function
void del()
{
    if (head == nullptr)
    {
        cout << ">!List is Empty!<" << endl
             << "Press any key to continue..." << endl;
        char c;
        cin >> c;
    }
    else
    {
        dis_del();
        cout << endl
             << "<<Enter SI Number To Be Deleted>>: ";
        int a;
        cin >> a;

        if (a == 1)
        {
            tickets_total -= head->seat;

            if (head->ac_non == "AC")
                tickets_ac -= head->seat;
            else
                tickets_nc -= head->seat;

            struct node *temp = head;
            head = head->next;
            free(temp);
        }
        else
        {
            struct node *prev = head;
            struct node *cur = head->next;
            int i = 2;
            while (cur != nullptr && i != a)
            {
                prev = cur;
                cur = cur->next;
                i++;
            }
            if (cur == nullptr)
                cout << "Invalid index!" << endl;

            else
            {
                tickets_total -= cur->seat;

                if (cur->ac_non == "AC")
                    tickets_ac -= cur->seat;
                else
                    tickets_nc -= cur->seat;

                prev->next = cur->next;
                free(cur);
            }
        }

        cout << ">>>Successfully deleted<<<" << endl
             << "----New List----" endl;
        dis_del();

        cout << "Enter any char to continue" << endl;
        char c;
        cin >> c;
    }


}

//----------------------------------------------------------------
//----------------------------------------------------------------
// Display function
void dis()
{
    struct node *current;
    int count = 1;

    if (head == nullptr)
    {
        cout << "! List is Empty !";
        cout << ">>> Succesfully Added <<<" << endl
             << "Press any key to continue..." << endl;
        char c;
        cin >> c;
    }

    else
    {
        current = head;
        cout << "SI\tName\t\tDestination\tSeat\t  Time  \tBus Type\tCharge" << endl
             << "--\t----\t\t-----------\t----\t--------\t--------\t------" << endl;

        while (current != nullptr)
        {
            cout << count << "."
                 << current->name << "\t"
                 << current->des << "\t"
                 << current->seat << "\t"
                 << current->time << "\t"
                 << current->ac_non << "\t\t"
                 << current->amm << endl;
            current = current->next;
            count++;
        }
        cout << "-----------" << endl
             << "Total Ammount= " << total_amm << endl
             << "Total Passenger= " << tickets_total << endl
             << "AC: " <<tickets_ac <<endl
             << "NON-AC: " <<tickets_nc << endl
             << "06:00 pm" << endl
             << "10:00 pm" << endl
             << "Seat left= " << MAX_TIC - tickets_total << endl;

        cout << "Enter any char to continue" << endl;
        char c;
        cin >> c;
    }
}

//-----------------------------------------------------------
//-----------------------------------------------------------
// Delete display function
void dis_del()
{
    struct node *current;
    int count = 1;

    if (head == nullptr)
    {
        cout << "! List is Empty !" <<endl
             << "Press any key to continue..." << endl;
        char c;
        cin >> c;
    }

    else
    {
        current = head;
        cout << "\tName\t\tSeat" << endl
             << "\t----\t\t----" << endl;

        while (current != nullptr)
        {
            cout << count << "."
                 << current->name << "\t"
                 << current->seat << endl;
            current = current->next;
            count++;
        }
    }
}

//----------------------------------------------------------------
//----------------------------------------------------------------
// Search function
void find()
{
    if (head == nullptr)
    {
        cout << "! List is Empty !" << endl
             << "Press any key to continue..." << endl;
        char c;
        cin >> c;
    }

    else
    {
        int si = 0, c = 0;
        string nm;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, nm);
        struct node *temp = head;

        while (temp != nullptr)
        {
            si++;
            if (temp->name == nm)
            {
                cout << "Found" << endl
                     << "SI: " << si << endl;
                c++;
                break;
            }
            temp = temp->next;
        }
        if (c == 0)
            cout << "Not Found" << endl;


        cout << "Enter any char to continue" << endl;
        char u;
        cin >> u;
    }
}

//----------------------------------------------------------------
//----------------------------------------------------------------
// Monthly income function
void month()
{
    cout << "Daily Total: " << total_amm << endl;
    cout << "Monthly Total: " << (total_amm * 30) << endl;

    cout << "Enter any char to continue" << endl;
    char c;
    cin >> c;
}

//----------------------------------------------------------------
//----------------------------------------------------------------
// Destination
string dest()
{
    cout << endl
         << "From Dhaka To" << endl
         << "1.Chittagong" << endl
         << "2.Shyllet" << endl
         << "3.Cox's Bazar" << endl
         << "4.Joypurhat" << endl;
    char a;
    cin >> a;
    while (a < '1' || a > '4')
    {
        cout << "Enter Correct Destination: ";
        cin >> a;
    }
    if (a == '1')
        return "Chittagong";
    else if (a == '2')
        return "Shyllet";
    else if (a == '3')
        return "Cox's Bazar";
    else
        return "Joypurhat";
}
