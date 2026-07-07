#include <iostream>
using namespace std;
class Matrix
{
private:
    int matrix[3][3];
public:
    Matrix ();
    Matrix(int a1,int a2,int a3,int b1,int b2,int b3,int c1,int c2,int c3);
    ~Matrix();
    friend istream & operator >>(istream &in, Matrix &p);
    friend ostream & operator << (ostream &out, Matrix &p);
    Matrix  operator + (const Matrix &p)
    {
        Matrix temp;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                temp.matrix[i][j] = matrix[i][j] + p.matrix[i][j];
            }
            
        }
        
        return temp;
    }
};

Matrix::Matrix():matrix{}
{
}

Matrix::~Matrix()
{
}

istream & operator >>(istream &in, Matrix &p)
{
    for (int i;i<3;i++)
    {
        for (int j;j<3;j++)
        {
            in >> p.matrix[i][j];
        }
    }
    return in;
}

ostream & operator << (ostream &out,  Matrix &p)
{
    out << p.matrix[0][0] << p.matrix[0][1] << p.matrix[0][2] <<endl
    << p.matrix[1][0] << p.matrix[1][1] << p.matrix[1][2] <<endl
    << p.matrix[2][0] << p.matrix[2][1] << p.matrix[2][2] <<endl;
    return out;
}

int main()
{
    Matrix a1,a2,b;
    cout << "Please input first matrix(3*3):"<<endl;
    cin >> a1;
    cout << "The first matrix is:"<<endl<<a1<<endl;
    cout << "Please input first matrix(3*3):"<<endl;
    cin >> a2;
    cout << "The second matrix is:"<<endl<<a2<<endl;
    b = a1 + a2;
    cout << "The sum is:" <<endl<<b<<endl;
    return 0;
}