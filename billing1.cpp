#include <iostream>
#include <fstream>
using namespace std;

class shopping
{
private:
    int pcode;
    float price;
    float dis;
    string pname;

public:
    void menu();
    void administrator();
    void buyer();
    void add();
    void edit();
    void rem();
    void list();
    void receipt();
};

void shopping::menu()
{
m:
    int choice;
    string email;
    string password;

    cout << "\t\t\t\t_______________________________________________________\n";
    cout << "\t\t\t\t                                                       \n";
    cout << "\t\t\t\t             Supermarket Meniu Principal               \n";
    cout << "\t\t\t\t                                                       \n";
    cout << "\t\t\t\t_______________________________________________________\n";
    cout << "\t\t\t\t                                                       \n";
    cout << "\t\t\t\t|       1) Administrator        |\n";
    cout << "\t\t\t\t|                               |\n";
    cout << "\t\t\t\t|       2) Cumparator           |\n";
    cout << "\t\t\t\t|                               |\n";
    cout << "\t\t\t\t|       3) Iesire               |\n";
    cout << "\t\t\t\t|                               |\n";
    cout << "\n\t\t\t Please select: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        cout << "\t\t\t Va rog sa va inregistrati.\n";
        cout << "\t\t\t Introduceti email: ";
        cin >> email;
        cout << "\t\t\t Parola: ";
        cin >> password;

        if (email == "admin@example.com" && password == "admin")
        {
            administrator();
        }
        else
        {
            cout << "Email sau parola invalida";
        }
        break;

    case 2:
        buyer();
        break;

    case 3:
        exit(0); 
        break;

    default:
        cout << "Va rog sa selectati o optiune\n";
    }
    goto m;
}

void shopping::administrator()
{
m:
    int choice;
    cout << "\n\n\n\t\t\t     Meniul dministratorului             ";
    cout << "\n\t\t\t|________1) Adaugati produsul_______________|";
    cout << "\n\t\t\t|                                            ";
    cout << "\n\t\t\t|________2) Modificati produsul_____________|";
    cout << "\n\t\t\t|                                            ";
    cout << "\n\t\t\t|________3) Stergeti produsul_______________|";
    cout << "\n\t\t\t|                                            ";
    cout << "\n\t\t\t|________4) Inapoi la meniul principal______|";

    cout << "\n\n\t Va rog sa alegeti o varianta : ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        add();
        break;

    case 2:
        edit();
        break;

    case 3:
        rem();
        break;

    case 4:
        menu();
        break;

    default:
        cout << "Varianta incorecta!\n";
    }

    goto m;
}

void shopping::buyer()
{
m:
    int choice;
    cout << "\t\t\t          Cumparator          \n";
    cout << "____________________________________\n";
    cout << "                                    \n";
    cout << "\t\t\t 1) Cumpara produs            \n";
    cout << "                                    \n";
    cout << "\t\t\t 2) Inapoi                    \n";
    cout << "\t\t\t Va rog sa alegeti o varianta:  ";

    cin >> choice;

    switch (choice)
    {
    case 1:
        receipt();
        break;

    case 2:
        menu();
        break;

    default:
        cout << "Varianta incorecta!\n";
    }
    goto m;
}

void shopping::add()
{
m:
    fstream data;
    int c;
    int token = 0;
    float p;
    float d;
    string n;

    cout << "\n\n\t\t\t Adaugare produs nou ";
    cout << "\n\n\t Codus produsului:       ";
    cin >> pcode;
    cout << "\n\n\t Numele produsului:      ";
    cin >> pname;
    cout << "\n\n\t Pretul pprodusului:     ";
    cin >> price;
    cout << "\n\n\t Discountul produsului:  ";
    cin >> dis;

    data.open("database.txt", ios::in);

    if (!data)
    {
        data.open("database.txt", ios::app | ios::out);
        data << pcode << " " << pname << " " << price << " " << dis << "\n";
        data.close();
    }
    else
    {
        data >> c >> n >> p >> d;

        while (!data.eof())
        {
            if (c == pcode)
            {
                token++;
            }
            data >> c >> n >> p >> d;
        }
        data.close();

        if (token == 1)
        {
            goto m;
        }
        else
        {
            data.open("database.txt", ios::app | ios::out);
            data << pcode << " " << pname << " " << price << " " << dis << "\n";
            data.close();
        }
    }
    cout << "\n\n\t\t Produsul a fost adaugat cu succes !\n";
}

void shopping::edit()
{
    fstream data, data1;
    int pkey;
    int token = 0;
    int c;
    float p;
    float d;
    string n;

    cout << "\n\t\t\t Modificati un produs";
    cout << "\n\t\t\t Codus produsului: ";
    cin >> pkey;

    data.open("database.txt", ios::in);
    if (!data)
    {
        cout << "\n\n Fisierul nu exista !\n";
    }
    else
    {
        data1.open("database1.txt", ios::app | ios::out);

        data >> pcode >> pname >> price >> dis;
        while (!data.eof())
        {
            if (pkey == pcode)
            {
                cout << "\n\t\t Codul noului produs: ";
                cin >> c;
                cout << "\n\t\t Numele noului produs: ";
                cin >> n;
                cout << "\n\t\t Pretul: ";
                cin >> p;
                cout << "\n\t\t Discountul: ";
                cin >> d;
                data1 << c << " " << n << " " << p << " " << d << "\n";
                cout << "\n\n\t\t Produs modoficat cu succes !\n";
                token++;
            }
            else
            {
                data1 << pcode << " " << pname << " " << price << " " << dis << "\n";
            }
            data >> pcode >> pname >> price >> dis;
        }
        data.close();
        data1.close();

        remove("database.txt");
        rename("database1.txt", "database.txt");

        if (token == 0)
        {
            cout << "\n\n Produs negasit!\n";
        }
    }
}

void shopping::rem()
{
    fstream data, data1;
    int pkey;
    int token = 0;

    cout << "\n\n\t Stergere produs";
    cout << "\n\n\t Codus produsului:: ";
    cin >> pkey;

    data.open("database.txt", ios::in);
    if (!data)
    {
        cout << "Fisierul nu exista!\n";
    }
    else
    {
        data1.open("database1.txt", ios::app | ios::out);
        data >> pcode >> pname >> price >> dis;
        while (!data.eof())
        {
            if (pcode == pkey)
            {
                cout << "\n\n\t Produsul a fost sters cu succes. \n";
                token++;
            }
            else
            {
                data1 << pcode << " " << pname << " " << price << " " << dis << "\n";
            }
            data >> pcode >> pname >> price >> dis;
        }
        data.close();
        data1.close();
        remove("database.txt");
        rename("database1.txt", "database.txt");

        if (token == 0)
        {
            cout << "\n\n Produs negasit! \n";
        }
    }
}

void shopping::list()
{
    fstream data;
    data.open("database.txt", ios::in);
    cout << "\n\n|__________________________________________________________________________\n";
    cout << "ProNo\t\tName\t\tPrice\n";
    cout << "\n\n|__________________________________________________________________________\n";
    data >> pcode >> pname >> price >> dis;
    while (!data.eof())
    {
        cout << pcode << "\t\t" << pname << "\t\t" << price << "\n";
        data >> pcode >> pname >> price >> dis;
    }
    data.close();
}

void shopping::receipt()
{
    fstream data;
    int arrc[100];
    int arrq[100];
    char choice;
    int c = 0;
    float amount = 0;
    float discount = 0;
    float total = 0;

    cout << "\n\n\t\t\t\t Factura";
    data.open("database.txt", ios::in);
    if (!data)
    {
        cout << "\n\n Baza de date este goala ! \n";
    }
    else
    {
        data.close();

        list();
        cout << "\n___________________________________________________________________\n";
        cout << "\n|                                                                  \n";
        cout << "\n|          Va rog sa plasati comanda !                             \n";
        cout << "\n|                                                                  \n";
        cout << "\n|                                                                  \n";
        cout << "\n___________________________________________________________________\n";
        do
        {
        m:
            cout << "\n\n Codus produsului: ";
            cin >> arrc[c];
            cout << "\n\n Cantitatea: ";
            cin >> arrq[c];
            for (int i = 0; i < c; i++)
            {
                if (arrc[c] == arrc[i])
                {
                    cout << "\n\n Codul produs se repeta. Va rog sa incercati din nou !\n";
                    goto m;
                }
            }
            c++;
            cout << "\n\n Doriti sa mai cumparati si alte prduse? Daca da, apasati 'y', altfel apasati 'n': ";
            cin >> choice;
        } while (choice == 'y');

        cout << "\n\n\t\t\t _____________________________FACTURA__________________________\n";
        cout << "\n Cod produs \t Nume \t\t Cantitate \t Pret \t\t Total  \t Total dupa reducerea aplicata \n";

        for (int i = 0; i < c; i++)
        {
            data.open("database.txt", ios::in);
            data >> pcode >> pname >> price >> dis;
            while (!data.eof())
            {
                if (pcode == arrc[i])
                {
                    amount = price * arrq[i];
                    discount = amount - (amount * dis / 100);
                    total += discount;
                    cout << "\n" << pcode << "\t\t" << pname << "\t\t" << arrq[i] << "\t\t" << price << "\t\t" << amount << "\t\t" << discount;
                }
                data >> pcode >> pname >> price >> dis;
            }
            data.close();
        }
    }

    cout << "\n\n_______________________________________________________________________________";
    cout << "\n Total : " << total << "\n";
}

int main()
{
    shopping s;
    s.menu();
    return 0;
}
