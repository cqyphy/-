#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
class Student
{
private:
    int mId;
    int mMath;
    int mEnglish;
    int mProgramming;
    double mAverageScore;
public:
    Student(/* args */);
    ~Student();
    void InScore(int id,int math,int Eng,int program)
    {
        mId =id;
        mMath = math;
        mEnglish = Eng;
        mProgramming = program;
    }
    void ShowScore()
    {
        cout << left << setw(18) << "ID:" << mId << endl;
        cout << left << setw(18) << "mathScore:" << mMath << endl;
        cout << left << setw(18) << "EnglishScore:" << mEnglish << endl;
        cout << left << setw(18) << "ProgrammingScore:" << mProgramming << endl;
        cout << left << setw(18) << "Average_Score:" << fixed << setprecision(2) << mAverageScore << endl<<endl;
    }
    void count_averagescore()
    {
        mAverageScore = (mMath + mEnglish + mProgramming)/3.0;
    }
};

Student::Student(/* args */)
{
}

Student::~Student()
{
}
int main()
{
    vector <Student> v1;
    bool is_running = true;
    while (is_running)
    {
        Student *temp = new Student;
        cout <<"Please input the id,math_Score,english_Score and programming_Score"<<endl;
        int id,math,english,programming;
        cin >> id >> math >> english >> programming ;
        temp->InScore(id,math,english,programming);
        temp->count_averagescore();
        v1.push_back(*temp);
        delete temp;
        cout <<"input next student?(Y or N)"<<endl;
        char a;
        cin >> a;
        if (a == 'Y' || a == 'y')
            continue;   
        else
            is_running = false;
    }
    cout <<"Show each student's score?(Y or N)"<<endl;
    char a;
    cin >> a;
    if (a == 'Y' || a == 'y')
    {
        for (int i = 0; i < v1.size(); i++)
        {
            v1.at(i).ShowScore();
        }
    }        
    return 0;        
}
