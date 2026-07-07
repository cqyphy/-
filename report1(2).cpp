#include <iostream>
using namespace std;
class Complex
{
    private:
        int mX;
        int mY;
    public:
        Complex(int a ,int b);
        friend void add(Complex &a,Complex &b,Complex &c);
        friend void sub(Complex &a,Complex &b,Complex &c);
        friend void mul(Complex &a,Complex &b,Complex &c);
        friend void div(Complex &a,Complex &b,Complex &c);
        void show()
        {
            cout <<"This complex is:"<<mX<<"+"<<mY<<"i"<<endl;
        }
};
Complex::Complex(int a,int b):mX(a),mY(b){}
void add(Complex &a,Complex &b,Complex &c)
{
    c.mX=a.mX+b.mX;
    c.mY=a.mY+b.mY;
    c.show();
}
void sub(Complex &a,Complex &b,Complex &c)
{
    c.mX=a.mX-b.mX;
    c.mY=a.mY-b.mY;
    c.show();
}
void mul(Complex &a,Complex &b,Complex &c)
{
    c.mX=(a.mX*b.mX)-(a.mY*b.mY);
    c.mY=(a.mY*b.mX)+(a.mX*b.mY);
    c.show();
}
void div(Complex &a,Complex &b,Complex &c)
{
    c.mX=((a.mX*b.mX)+(a.mY*b.mY))/((b.mX*b.mX)+(b.mY*b.mY));
    c.mY=((a.mY*b.mX)-(a.mX*b.mY))/((b.mX*b.mX)+(b.mY*b.mY));
    c.show();
}
int main()
{
    int a,b;
    cout<<"Please input first complex:"<<endl;
    cin >>a>>b;
    Complex comp1 (a,b);
    cout<<"Please input second complex:"<<endl;
    cin >>a>>b;
    Complex comp2 (a,b);
    Complex comp3 (0,0);
    cout << "Which computation would you like to choose?"<<endl<<"+ or - or * or /"<<endl;
    char funtion;
    cin >>funtion;
    switch (funtion)
    {
    case '+':
        add(comp1,comp2,comp3);
        break;
    case '-':
        sub(comp1,comp2,comp3);
        break;
    case '*':
        mul(comp1,comp2,comp3);
        break;
    case '/':
        div(comp1,comp2,comp3);
        break;
    
    default:
        break;
    }
}