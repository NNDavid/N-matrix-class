#include <iostream>
#include "Nmatrix.h"
using namespace std;
#define NORMAL_MODE
#ifdef NORMAL_MODE
class Menu{
    public:
        Menu(){A.reSize(3);}
    void run();
    private:
        Nmatrix A;
    void menuWrite();
    void get() const;
    void read();
    void write();
    void sum();
    void mul();
};

int main()
{
    Menu m;
    m.run();
}
void Menu::run()
{
    int n = 0;
    do{
        menuWrite();
        cout << endl << ">>>>" ; cin >> n;
        switch(n){
            case 1: get();
                    break;
            case 2: read();
                    break;
            case 3: write();
                    break;
            case 4: sum();
                    break;
            case 5: mul();
                    break;
        }
    }while(n!=0);
}

void Menu::menuWrite()
{
     cout << endl << endl;
     cout << " 0. -Kilepes" << endl;
     cout << " 1. -Matrix adott elemenek lekerdezese" << endl;
     cout << " 2. -Matrix beolvasasa" << endl;
     cout << " 3. -Matrix kiirasa" << endl;
     cout << " 4. -Matrixok osszeadasa" << endl;
     cout << " 5. -Matrixok szorzasa" << endl;
}

void Menu::get() const
{
    int i,j;
    cout << "Adja meg a sor indexet:"; cin >> i;
    cout << "Adja meg az oszlop indexet:"; cin >> j;
    try{
        cout << "A[" << i << "," << j << "]= " << A(i,j) << endl;
    }catch(Nmatrix::Hibak hiba){
        if(hiba == Nmatrix::Hibas_Index)
            cout << "Hibas index!" << endl;
        else cout << "Kezeletlen kivetel!" << endl;
    }
}

void Menu::read()
{
    cin >> A;
}

void Menu::write()
{
    cout << A << endl;
}

void Menu::sum()
{
    Nmatrix A(3), B(3);

    cout << "Elso matrix:" << endl;
    cin >> A;
    cout << "Masodik matrix:" << endl;
    cin >> B;
    cout << "Osszeg matrix:" << endl;
    cout << A+B << endl;
}

void Menu::mul()
{
    Nmatrix A(3), B(3);

    cout << "Elso matrix:" << endl;
    cin >> A;
    cout << "Masodik matrix:" << endl;
    cin >> B;
    cout << "Szorzat matrix:" << endl;
    cout << A*B << endl;
}
#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
TEST_CASE("Letrehozas es lekerdezes", "input1.txt") {
    const string fileName = "input1.txt";

    ifstream in(fileName.c_str());
    if(in.fail()){
        cout << "Nem lehet kinyitni a file-t!" << endl;
        exit(1);
    }

    Nmatrix A(4);
    in >> A;
    CHECK(A(1,1)==1);
    CHECK(A(2,4)==4);
    CHECK(A(3,4)==3);
    CHECK(A(1,2)==0);

    Nmatrix B(2);
    in >> B;
    CHECK(B(1,1)==50);
    CHECK(B(2,2)==20);

    Nmatrix C(1);
    in >> C;
    CHECK(C(1,1)==100);
}
TEST_CASE("Copy konstruktor","input2.txt")
{
    const string fileName = "input2.txt";

    ifstream in(fileName.c_str());
    if(in.fail()){
        cout << "Nem lehet kinyitni a file-t!" << endl;
        exit(1);
    }
    Nmatrix A(3);
    in >> A;
    Nmatrix B=A;
    CHECK(B(1,1)==A(1,1));
    CHECK(B(1,3)==A(1,3));
    CHECK(B(2,2)==A(2,2));

}
TEST_CASE("Ertekadas operator","input2.txt")
{
    const string fileName = "input2.txt";

    ifstream in(fileName.c_str());
    if(in.fail()){
        cout << "Nem lehet kinyitni a file-t!" << endl;
        exit(1);
    }
    Nmatrix A(3),B(3);
    in >> A;
    B=A;
    CHECK(A(1,1)==B(1,1));
    CHECK(A(1,3)==B(1,3));
    CHECK(A(2,1)==B(2,1));
    CHECK(A(2,2)==B(2,2));
    CHECK(A(2,3)==B(2,3));
    CHECK(A(3,1)==B(3,1));
    CHECK(A(3,3)==B(3,3));
}
TEST_CASE("Osszeadas","input3.txt")
{
    const string fileName = "input3.txt";

    ifstream in(fileName.c_str());
    if(in.fail()){
        cout << "Nem lehet kinyitni a file-t!" << endl;
        exit(1);
    }
    Nmatrix A(4),B(4),C(4),D(4),E(4),F(4),G(4);
    in>>A>>B>>E;
    C=A+B;
    D=B+A;
    F=(A+B)+E;
    G=A+(B+E);

    CHECK(C(1,1)==105);
    CHECK(C(2,4)==510);
    CHECK(C(3,3)==83);
    CHECK(C(4,4)==D(4,4));
    CHECK(C(2,1)==D(2,1));
    CHECK(C(1,4)==D(1,4));
    CHECK(F(4,4)==G(4,4));
    CHECK(F(2,1)==G(2,1));
    CHECK(F(1,4)==G(1,4));

}
TEST_CASE("Szorzas","input3.txt")
{
    const string fileName = "input3.txt";

    ifstream in(fileName.c_str());
    if(in.fail()){
        cout << "Nem lehet kinyitni a file-t!" << endl;
        exit(1);
    }
    Nmatrix A(4),B(4),C(4),D(4),E(4),F(4);
    in>>A>>B>>D;
    C=A*B;
    E=(A*B)*D;
    F=A*(B*D);
    CHECK(C(1,1)==549);
    CHECK(C(1,4)==336);
    CHECK(C(2,1)==5230);
    CHECK(C(2,2)==110);
    CHECK(C(2,4)==4604);
    CHECK(C(3,1)==4567);
    CHECK(C(3,3)==666);
    CHECK(C(3,4)==372328);
    CHECK(C(4,1)==3363);
    CHECK(C(4,4)==1920);
    CHECK(E(1,1)==F(1,1));
    CHECK(E(2,2)==F(2,2));
    CHECK(E(3,4)==F(3,4));
    CHECK(E(4,4)==F(4,4));
}
TEST_CASE("Hibakezeles","input1.txt")
{
 const string fileName = "input1.txt";

    ifstream in(fileName.c_str());
    if(in.fail()){
        cout << "Nem lehet kinyitni a file-t!" << endl;
        exit(1);
    }
      Nmatrix B(4);
        in>>B;
    Nmatrix C(2);
    in>>C;
    try{
        Nmatrix A(-2);
    }
    catch(Nmatrix::Hibak hiba){
        CHECK(hiba==Nmatrix::Hibas_Meret);
    }
    try{
        cout<<B(-1,5)<<endl;

    }
    catch(Nmatrix::Hibak hiba){
        CHECK(hiba==Nmatrix::Hibas_Index);
    }
    try{
        C=B;
    }
    catch(Nmatrix::Hibak hiba){
        CHECK(hiba==Nmatrix::Nem_Egyezo_Meretek);
    }
    try{
        Nmatrix D=B+C;
    }
    catch(Nmatrix::Hibak hiba){
        CHECK(hiba==Nmatrix::Nem_Egyezo_Meretek);
    }
    try{
        Nmatrix E=B*C;
    }
    catch(Nmatrix::Hibak hiba){
        CHECK(hiba==Nmatrix::Nem_Egyezo_Meretek);
    }
}

#endif
