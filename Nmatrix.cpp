#include "Nmatrix.h"
#include<iostream>
#include<iomanip>
Nmatrix::Nmatrix()
{
    _n=size;
    _vecsize=3*_n-2;
    _v= new int[_vecsize];
}
Nmatrix::Nmatrix(int meret)
{
    if(meret<=0) throw Hibas_Meret;
    _n=meret;
    _vecsize=3*_n-2;
    _v=new int[_vecsize];
}


Nmatrix::Nmatrix(const Nmatrix& A)
{
    _n=A._n;
    _vecsize=3*_n-2;
    _v=new int[_vecsize];
    for(int i=0;i<_vecsize;i++)
        _v[i]=A._v[i];

}
void Nmatrix::reSize(int meret)
{
    delete[] _v;
    _n=meret;
    _vecsize=3*_n-2;
    _v= new int[_vecsize];
}
int Nmatrix::operator()(int i,int j) const
{
        if(i<=0||i>_n||j<=0||j>_n) throw Nmatrix::Hibas_Index;
        else
        {
            if(i!=j&&j!=1&&j!=_n) return 0;
            else if(i==j) return _v[3*(i-1)];
            else if(j==1&&i!=1) return _v[3*(i-1)-1];
            else if(j==_n&&i!=_n) return _v[3*(i-1)+1];
        }
}
Nmatrix& Nmatrix::operator=(const Nmatrix& A)
{
    if(_n!=A._n) throw Nmatrix::Nem_Egyezo_Meretek;
    if(this==&A) return *this;
        for(int i=0;i<_vecsize;++i)
            _v[i]=A._v[i];
    return *this;
}
Nmatrix operator+(const Nmatrix& A, const Nmatrix& B)
{
    if(A._n!=B._n) throw Nmatrix::Nem_Egyezo_Meretek;

    Nmatrix C(A._n);
    for(int i=0;i<A._vecsize;++i)
        C._v[i]=A._v[i]+B._v[i];
    return C;
}
void Next(int& ci,int& cj,int msize)
{
    if(cj==1&&ci!=1) cj=ci;
    else if(cj==ci) cj=msize;
    else if(cj==msize)
    {
            ci++;
            cj=1;
    }
}
Nmatrix operator*(const Nmatrix& A, const Nmatrix& B)
{
    if(A._n!=B._n) throw Nmatrix::Nem_Egyezo_Meretek;

    Nmatrix C(A._n);
    int ci=1,cj=1,msize=A._n;
    for(int i=0;i<A._vecsize;i++)
    {
        C._v[i]=A(ci,1)*B(1,cj)+A(ci,msize)*B(msize,cj);
        if(ci!=1&&ci!=msize) C._v[i]+=A(ci,ci)*B(ci,cj);
        Next(ci,cj,msize);
    }

    return C;
}
std::ostream& operator<< (std::ostream& s, const Nmatrix& A)
{
    for(int i=1;i<=A._n;++i)
    {
        for(int j=1;j<=A._n;++j)
            s<<std::setw(5)<<A(i,j);
        s<<std::endl;
    }
    return s;

}
std::istream& operator>> (std::istream& s, Nmatrix& A)
{
    int ci=1,cj=1;
    for(int i=0;i<A._vecsize;i++)
    {
        std::cout<<"M["<<ci<<"]["<<cj<<"]=";
        s>>A._v[i];
        Next(ci,cj,A._n);
    }
    return s;
}

