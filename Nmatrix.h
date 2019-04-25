#ifndef NMATRIX_H_INCLUDED
#define NMATRIX_H_INCLUDED
#include<iostream>
class Nmatrix
{
    public:
        enum Hibak{Hibas_Index,Hibas_Meret,Nem_Egyezo_Meretek};
        Nmatrix();
        Nmatrix(int meret);
        void reSize(int meret);
        ~Nmatrix(){delete[] _v;}
        Nmatrix(const Nmatrix& other);
        Nmatrix& operator=(const Nmatrix& A);
       int operator()(int i,int j) const;
       friend Nmatrix operator+(const Nmatrix& A,const Nmatrix& B);
       friend Nmatrix operator*(const Nmatrix& A,const Nmatrix &B);
       friend std::ostream& operator<< (std::ostream& s, const Nmatrix& A);
       friend std::istream& operator>> (std::istream& s, Nmatrix& a);

    private:
        int _n,_vecsize;
        int* _v;
        const int size=5;

};


#endif // NMATRIX_H_INCLUDED
