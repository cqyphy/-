#include  <iostream>
using namespace std;
class Point
{
  double x , y ;
public:
	Point(){};
    Point (int a,int b):x(a),y(b){}
//重载运算符">>"
    friend istream & operator >> (istream &in, Point &p) ; 
//重载运算符"<<" 
    friend ostream & operator << (ostream &out, Point &p) ;  
} ;
istream & operator >> (istream &in, Point &p)
{
    in >> p.x>>p.y;
    return in;
}
ostream & operator << (ostream &out, Point &p)
{
    out <<'('<<p.x<<','<<p.y<<')'<<endl;
    return out;
}
int main()
{
    Point a1,a2(5,2);
    cout <<"Input first coordinates:"<<endl;
    cin >>a1;
    cout <<a1<<a2<<endl;
}