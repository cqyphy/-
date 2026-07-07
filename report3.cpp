#include <iostream>
#include <string.h>
#include <vector>
#include <unordered_map>
using namespace std;

//职工类

class Employee
{
protected:
    string name;
    string gender;
    string induction_time;
    string position;
    long num;
    float basic_salary = 6000;
public:
    virtual void set(int i)=0;
    virtual int GetPay();
    virtual void ShowMessage();
    virtual ~Employee() = default;
    friend istream & operator >>(istream &in, Employee &p);
};

istream & operator >>(istream &in, Employee &p)
{
    in >> p.num>>p.name>>p.gender>>p.induction_time;
    return in;
}

void Employee::ShowMessage()
{
    cout << "num\t"<<"name\t"<<"gender\t"<<"induction time\t"<<"position\t"<<"salay\t"<<endl
    <<num<<"\t"<<name<<"\t"<<gender<<"\t"<<induction_time<<"\t"<<position<<"\t"<<GetPay()<<endl<<endl;
}

int Employee::GetPay()
{
    //cout << "The salary is:" << basic_salary << endl;
    return basic_salary;
}

//经理类

class Manager:virtual public Employee
{
private:
    float bonus;
public:
    void set(int i){bonus = i;}
    int GetPay();
    Manager(/* args */){position = "Manager";};
    ~Manager()=default;
};

int Manager::GetPay()
{
    float temp;
    temp = basic_salary +bonus;
    //cout << "The salary is:" << temp << endl;
    return temp;
}

//技术人员类

class Technicist:virtual public Employee
{
private:
    /* data */
public:
    Technicist(/* args */){position = "Technicist";};
    ~Technicist()=default;
    void set(int i){};
};

//营销人员类

class SalsePerson:virtual public Employee
{
private:
    float sale_num;
public:
    SalsePerson(/* args */){position = "SalsePerson";};
    ~SalsePerson()=default;
    void set(int i){sale_num = i;}
    int GetPay();
};

int SalsePerson::GetPay()
{
    float temp;
    temp = basic_salary + (sale_num*0.05);
    //cout << "The salary is:" << temp << endl;
    return temp;
}

//枚举类
enum class position
{
    Manager,
    Technicist,
    SalsePerson
};

//映射字符串
position stringToposition(const std::string& s) {
    static const std::unordered_map<std::string, position> map = {
        {"Manager",    position::Manager},
        {"Technicist",    position::Technicist},
        {"SalsePerson",    position::SalsePerson},
    };
    auto it = map.find(s);
    if (it != map.end())
        return it->second;
    return position::Manager;
}

//动态数组
vector<Employee*> group1;

//输入人员
void input()
{
    cout << "Please input the position:"<<endl;
    string temp_position;
    cin >> temp_position;
    position cmd = stringToposition(temp_position);
    Employee *p1 = nullptr;
    int set_num;
    switch (cmd)
    {
    case position::Manager:
        p1 = new Manager;
        cout <<"Please set the bonus:"<<endl;
        cin >>set_num;
        p1->set(set_num);
        break;
    
    case position::SalsePerson:
        p1 = new SalsePerson;
        break;

    case position::Technicist:
        p1 = new Technicist;
        cout <<"Please set the sale number:"<<endl;
        cin >>set_num;
        p1->set(set_num);
        break;
    default:
        break;
    }
    cout <<"Please input number,name,gender,induction time and position:"<<endl;
    cin >> *p1;
    group1.push_back(p1);
}

//菜单
void menu()
{
    cout << "Please choose the funtion:" <<endl
    <<"1.input the Employee"<<endl
    <<"2.show the Employees"<<endl
    <<"3.exit the program"<<endl;
}

//展示信息
void showall()
{
    for (int i = 0; i < group1.size(); i++)
    {
        group1[i]->ShowMessage();
    }
    
}
//主函数

int main()
{
    bool is_exit = false;
    do
    {
        menu();
        int funtion;
        cin >>funtion;
        switch (funtion)
        {
            case 1:
                input();        
                break;
            case 2:
                showall();
                break;
            case 3:
                is_exit = true;
                for(auto p:group1) delete p;
                group1.clear();
            default:
                break;
        }

    } while (is_exit == false);
    
    
}