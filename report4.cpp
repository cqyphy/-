#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

//-----------------------------------------------------------------图书基类-----------------------------------------------------------------
class Book
{
protected:
    string ISBN,
    Book_name,
    Auther,
    Publishing_house,
    Publishing_time;
    int inventory;
public:
    Book(string isbn,string book_name,string auther,string publishing_h,string publishing_t,int inventory):
        ISBN(isbn),Book_name(book_name),Auther(auther),Publishing_house(publishing_h),Publishing_time(publishing_t),inventory(inventory){};
    virtual ~Book()= default;
    virtual void show();
    virtual bool borrowbook();
    virtual bool returnbook();
    //------------------------------------------------getters------------------------------------------------
    string getISBN(){return ISBN;}
    string getbookName(){return Book_name;}
    string getAuther(){return Auther;}
    string getPublishingHouse(){return Publishing_house;}
    string getPublishingTime(){return Publishing_time;}
    //virtual string getType(){return "Book";}
    string getinventorystr(){
        string inventorystr = to_string(inventory);
        return inventorystr;
    }
};

void Book::show()
{
    cout <<"ISBN\t\t\t"<<"Book_name\t"<<"Auther\t\t"<<"Publishing_house\t"<<"Publishing_time\t"<< "inventory\t"<<endl
         <<ISBN<<"\t"<<Book_name<<"\t"<<Auther<<"\t"<<Publishing_house<<"\t\t"<<Publishing_time<<"\t\t"<<inventory<<"\t"<<endl<<endl;
}

bool Book::borrowbook()//管理书类的库存
{
    if (inventory == 0) 
    {
        cout<<"Sorry,there is no this book."<<endl;
        return 0;
    }
    cout << "Borrow succesfully."<<endl;
    inventory--;
    return 1;
}

bool Book::returnbook()
{
    cout << "You have successfully return the book."<<endl;
    inventory++;
    return 1;
}

//-----------------------------------------------------------------Ebook类-----------------------------------------------------------------
class EBook:virtual public Book
{
private:
    double FileSize;
    string Format;
public:
    EBook(string isbn,string book_name,string auther,string publishing_h,string publishing_t,int inventory,double size,string format):
    Book(isbn,book_name,auther,publishing_h,publishing_t,inventory),FileSize(size),Format(format){};
    ~EBook()= default;
    void show();
    //-----------------getters---------------------
    double getFileSize(){return FileSize;};
    string getFormat(){return Format;};
    //string getType(){return "EBook";}
};

void EBook::show()
{
    cout <<"ISBN\t"<<"Book_name\t"<<"Auther\t"<<"Publishing_house\t"<<"Publishing_time\t"<<"File_Size\t"<<"Format\t"<< "inventory\t"<<endl
         <<ISBN<<"\t"<<Book_name<<"\t"<<Auther<<"\t"<<Publishing_house<<"\t"<<Publishing_time<<"\t"<<FileSize<<"\t"<<Format<<"\t"<<inventory<<"\t"<<endl<<endl;
}

//-----------------------------------------------------------------User类-----------------------------------------------------------------
class User
{
protected:
    string userID,Name,type;
    int Max_Borrow_Limit;
    vector<Book*> borrowedbooks;
public:
    User(string userid,string name):userID(userid),Name(name){};
    virtual ~User()=default;
    virtual void borrow(Book* book) = 0;//用户类借书动作
    virtual void returnbook(Book* book);
    void showborrowedbooks();
    void showuserinformation();
    void borrowedbooks_fromfile(vector<Book*> v1);//用于从文件中提取已借书本
    //-------------getters-----------------
    string getID(){return userID;}
    string getname(){return Name;}
    string gettype(){return type;}
    string getborrowedbookisbn();
};

void User::borrowedbooks_fromfile(vector<Book*> v1)
{
    borrowedbooks= v1;
}

void User::showborrowedbooks()
{
    for (int i = 0; i < borrowedbooks.size(); i++)
    {
        cout <<"book"<<i+1<<":"<<endl;
        borrowedbooks[i]->show();
    }
    
}

void User::showuserinformation()
{
    cout <<"userID\t"<<"Name\t"<<"Borrowed Books\t"<<endl
    <<userID<<"\t"<<Name<<"\t"<<borrowedbooks.size()<<"\t"<<endl<<endl;
}

void User::returnbook(Book* book)
{
    string temp = book->getISBN();
    for (int i = 0; i < borrowedbooks.size(); i++)
    {
        if (borrowedbooks[i]->getISBN() == temp)
        {
            borrowedbooks.erase(borrowedbooks.begin()+i);
            book->returnbook();
            break;
        }
        
    }
    
}

string User::getborrowedbookisbn()
{
    string temp;
    int cycletimes;
    if (type == "student")
    {
        cycletimes = 3;
    }
        else if (type == "teacher")
    {
        cycletimes = 5;
    }
    int j=0;
    for (int i = 0; i < borrowedbooks.size(); i++)
    {
        temp += borrowedbooks[i]->getISBN();
        temp += "|";        
        j++;
    }
    for ( ; j < cycletimes; j++)
    {
        temp += " ";
        temp += "|";
    }
    
    
    return temp;
}

//-----------------------------------------------------------------学生类-----------------------------------------------------------------
class Student:virtual public User
{
private:
    /* data */
public:
    Student(string userid,string name):User(userid,name)
    {
        type = "student";
        Max_Borrow_Limit = 3;
        
    };
    ~Student()=default;
    void borrow(Book* book);
};

void Student::borrow(Book* book)
{
    if (borrowedbooks.size() == Max_Borrow_Limit)
    {
        cout <<"You had borrowed 3 books,please return books first."<<endl;
    }
    if (borrowedbooks.size() < Max_Borrow_Limit)
    {
        
        if (book->borrowbook())
        {
            borrowedbooks.push_back(book);
        }        
    }
    
}


//-----------------------------------------------------------------教师类-----------------------------------------------------------------
class Teacher:virtual public User
{
private:
    /* data */
public:
    Teacher(string userid,string name):User(userid,name)
    {
        type = "teacher";
        Max_Borrow_Limit = 5;
        
    };
    ~Teacher()=default;
    void borrow(Book* book);
};

void Teacher::borrow(Book* book)
{
    if (borrowedbooks.size() == Max_Borrow_Limit)
    {
        cout <<"You had borrowed 5 books,please return books first."<<endl;
    }
    if (borrowedbooks.size() < Max_Borrow_Limit)
    {
        
        if (book->borrowbook())
        {
            borrowedbooks.push_back(book);
        }        
    }
    
}

//-----------------------------------------------------------------图书馆类-----------------------------------------------------------------
class Library
{
private:
    vector<Book*> booklist;
    vector<User*> userlist;
public:
    Library(/* args */) = default;
    ~Library() {
        for (auto p : booklist) delete p;
        for (auto p : userlist) delete p;
    }
    void add_book(string type,string isbn,string book_name,string auther,string publishing_h,string publishing_t,int inventory);
    void add_user(string type,string userID,string Name);
    void remove_book(const string& ISBN);
    Book* searchbooksByisbn(const string& ISBN);
    Book* searchbooksByname(const string& name);
    void showall();
    User* searchuserbyID(const string& ID);
    //文件读写功能
    void savebooks();
    void saveusers();
    void readbooklist();
    void readuserlist();
};

void Library::add_user(string type,string userID,string Name){
    User* user = nullptr;
    if (type == "学生") user = new Student(userID,Name);
    else  user = new Teacher(userID,Name);   
    userlist.push_back(user);
}

void Library::add_book(string type,string isbn,string book_name,string auther,string publishing_h,string publishing_t,int inventory)
{
    Book* book = nullptr;
    if (type == "电子")
    {
        double size;
        string format;
        cout <<"please input size,format"<<endl;
        cin >>size>>format;
        book = new EBook(isbn,book_name,auther,publishing_h,publishing_t,inventory,size,format);
    }
    else 
    {
        book = new Book(isbn,book_name,auther,publishing_h,publishing_t,inventory);
    }
    booklist.push_back(book);
}

void Library::remove_book(const string& ISBN)
{
    for (int i = 0; i < booklist.size(); i++)
    {
        if (ISBN == booklist[i]->getISBN())
        {
            delete booklist[i];
            booklist.erase(booklist.begin()+i);
            cout << "Book removed successfully." << endl;
            return;
        }   
          
    }
    cout <<"Can't find the book."<<endl;
}

Book* Library::searchbooksByisbn(const string& ISBN)
{
    
    
        for (int i = 0; i < booklist.size(); i++)
        {
            if (ISBN == booklist[i]->getISBN())
            {
                //booklist[i]->show();
                return booklist[i];
                
            }             
        }
        cout <<"Can't find the book."<<endl;
        return nullptr;
       
}

Book* Library::searchbooksByname(const string& name)
{
    for (int i = 0; i < booklist.size(); i++)
        {
            if (name == booklist[i]->getbookName())
            {
                return booklist[i];
            }             
        }
        cout <<"Can't find the book."<<endl;
        return nullptr;
}

void Library::showall()
{
    cout << "There are "<<booklist.size()<<" books in this library:"<<endl;
    for (int i = 0; i < booklist.size(); i++)
    {
        booklist[i]->show();
    }
    cout <<"------------------------------------------------"<<endl
    <<"Users list:"<<endl;
    for (int i = 0; i < userlist.size(); i++)
    {
        userlist[i]->showuserinformation();
    }
    
}

User* Library::searchuserbyID(const string& ID)
{
    for (int i = 0; i < userlist.size(); i++)
    {
        if (userlist[i]->getID() == ID)
        {
            return userlist[i];
        }        
    }
    cout << "User not found"<<endl;
            return nullptr;
}

//----------------------------------------------------文件写入----------------------------------------------------
//--------------------------------------写入书本-----------------------------------------------
void Library::savebooks()
{
    ofstream out;
    out.open("books.txt",ios::out);
    if (!out.is_open())
    {
        cout << "Can't open the file"<<endl;
    }
    else
    {
        for (int i = 0; i < booklist.size(); i++)
        {
            out << booklist[i]->getISBN()<<"|"
            <<booklist[i]->getbookName()<<"|"
            <<booklist[i]->getAuther()<<"|"
            <<booklist[i]->getPublishingHouse()<<"|"
            <<booklist[i]->getPublishingTime()<<"|"
            <<booklist[i]->getinventorystr()<<"|";
            EBook* eb = dynamic_cast<EBook*>(booklist[i]);
                if (eb) 
                {
                    out << "电子|" <<eb->getFileSize()<<"|"<<eb->getFormat()<<"|";
                } 
                else 
                {
                    out << "普通|0|";
                }
            out <<endl;
        }
    }
    
    
    out.close();
}
//----------------------------------------写入用户----------------------------------------------
void Library::saveusers()
{
    ofstream out;
    out.open("User.txt",ios::out);
    if (!out.is_open())
    {
        cout << "Can't open the file"<<endl;
    }
    else
    {
        for (int i = 0; i < userlist.size(); i++)
        {
            out << userlist[i]->getID()<<"|"
            << userlist[i]->getname() << "|"
            << userlist[i]->gettype() << "|"
            << userlist[i]->getborrowedbookisbn()<<"|"<<endl;
        }
    }
    out.close();
}

//-----------------------------------------------------------------文件读取-----------------------------------------------------------------
//-------------------------------------读取书本-------------------------------------------------
void Library::readbooklist()
{
    ifstream in;
    in.open("books.txt");
    if (!in.is_open())
    {
        cout << "Can't open the file"<<endl;
        return;
    }
    string str;
    for (int i = 0;getline(in,str);i++)
    {

        stringstream ss(str);
        string isbn,name,auther,Publishing_house,Publishing_time,inventorystr,type;        
        getline(ss,isbn,'|');
        getline(ss,name,'|');
        getline(ss,auther,'|');
        getline(ss,Publishing_house,'|');
        getline(ss,Publishing_time,'|');
        getline(ss,inventorystr,'|');
        getline(ss,type,'|');
        int inventory = stoi(inventorystr);
        Book* book = nullptr;
        if (type == "普通")
        {
            book = new Book(isbn,name,auther,Publishing_house,Publishing_time,inventory); 
        }
        if (type == "电子")
        {
            string sizestr,format;
            getline(ss,sizestr,'|');
            getline(ss,format,'|');
            double size = stod(sizestr);
            book = new EBook(isbn,name,auther,Publishing_house,Publishing_time,inventory,size,format); 
        }        
        booklist.push_back(book);
    }
    
    in.close();
}

//-------------------------------------读取用户-------------------------------------------------
void Library::readuserlist()
{
    ifstream in;
    in.open("User.txt");
    if (!in.is_open())
    {
        cout << "Can't open the file"<<endl;
        return;
    }
    string str;
    for (int i = 0; getline(in,str); i++)
    {
        stringstream ss(str);
        string id,name,type,borrowedbookisbn;
        getline(ss,id,'|');
        getline(ss,name,'|');
        getline(ss,type,'|');
        
        User* user = nullptr;
        if (type == "student")
        {
            user = new Student(id,name);
            vector<Book*> books;
            for (int i = 0; i < 3; i++)
            {
                getline(ss,borrowedbookisbn,'|');
                if (borrowedbookisbn != " ")
                {
                    Book* book= searchbooksByisbn(borrowedbookisbn);
                    books.push_back(book);
                }                                
            }
            user->borrowedbooks_fromfile(books);            
        }
        if(type == "teacher")
        {
            user = new Teacher(id,name);
            vector<Book*> books;
            for (int i = 0; i < 5; i++)
            {
                getline(ss,borrowedbookisbn,'|');
                if (borrowedbookisbn != " ")
                {
                    Book* book= searchbooksByisbn(borrowedbookisbn);
                    books.push_back(book);
                }
            }
            user->borrowedbooks_fromfile(books);
        }
        if (user) userlist.push_back(user);
    }
    
}
    
//-----------------------------------------------------------------用户菜单-----------------------------------------------------------------
void usermenu(Library* library)
{
    bool is_usermenu_continue = 1;
    string ID;
    cout << "Please input your ID:"<<endl;
    cin >> ID;
    User* user = library->searchuserbyID(ID);
    while (is_usermenu_continue && user)
    {
        
            cout <<"User "<<user->getname()<<':'<<endl
             <<"1.borrow books"<<endl
             <<"2.return books"<<endl
             <<"3.show borrowed books"<<endl
             <<"4.exit"<<endl;
            int funtion_inusermenu;
            cin >> funtion_inusermenu;
            switch (funtion_inusermenu)
            {
                case 1:    
                {
                    cout  <<"input book name:"<<endl;
                    string bookname;
                    cin >> bookname;
                    Book* book = library->searchbooksByname(bookname);
                    if (book)  user->borrow(book);       
                    else cout << "Book not found." << endl;                
                    break;
                }
                case 2:
                {
                    cout  <<"input book name:"<<endl;
                    string bookname;
                    cin >> bookname;
                    Book* book = library->searchbooksByname(bookname);
                    if (book)  user->returnbook(book);       
                    else cout << "Book not found." << endl;
                    break;
                }
                case 3:
                    user->showborrowedbooks();
                    break; 
                default:
                    is_usermenu_continue = 0;
                    break;        
            }
        
        
            
    }
}

//-----------------------------------------------------------------管理员菜单-----------------------------------------------------------------
void Administratormenu(Library* library)
{
    bool is_adminmenu_continue = 1;
    while (is_adminmenu_continue)
    {
        cout << "input numbers to choose:"<<endl<<endl
        <<"1.add book"<<endl
        <<"2.remove book"<<endl
        <<"3.search book by ISBN"<<endl
        <<"4.search book by name"<<endl
        <<"5.show informations"<<endl
        <<"6.add user"<<endl
        <<"7.exit"<<endl;
        int funtion_inadminmenu;
        cin >> funtion_inadminmenu;
        switch (funtion_inadminmenu)
        {
        case 1:
        {
            cout <<"please input type,isbn,book_name,auther,publishing_house,publishing_time,inventory"<<endl;
            string type;
            string isbn;
            string book_name;
            string auther;
            string publishing_h;
            string publishing_t;
            int inventory;
            cin >>type>>isbn>>book_name>>auther>>publishing_h>>publishing_t>>inventory;
            library->add_book(type,isbn,book_name,auther,publishing_h,publishing_t,inventory);
            break;
        }
        case 2:
        {
            cout <<"please input ISBN"<<endl;
            string isbn;
            cin >>isbn;
            library->remove_book(isbn);
            break;
        }    
        case 3:
        {
            cout <<"please input ISBN"<<endl;
            string isbn;
            cin >>isbn;
            Book* book = library->searchbooksByisbn(isbn);
            if (book) book->show();            
            else cout << "Book not found." << endl;
            break;
        }                
        case 4:
        {
            cout <<"please input book name"<<endl;
            string name;
            cin >>name;
            Book* book = library->searchbooksByname(name);
            if (book) book->show();            
            else cout << "Book not found." << endl;
            break;
        }        
            
        case 5:
            library->showall();
            break;
        case 6:
        {
            cout <<"please input user type,userID,name"<<endl;
            string type,id,name;
            cin >>type>>id>>name;
            library->add_user(type,id,name);
            break;
        }    
        default:
            is_adminmenu_continue = 0;
            break;
        }
    }
    
}

int main()
{
    Library GzhuLibrary;
    GzhuLibrary.readbooklist();
    GzhuLibrary.readuserlist();
    bool is_continue = 1;
    do
    {
        int choosefuntion;
        cout << "Welcom to Gzhu library contro pannel,please input numbers to choose funtions:"<<endl<<endl
         <<"1.User menu"<<endl
         <<"2.Administrator menu"<<endl
         <<"3.exit"<<endl;
        cin >> choosefuntion;
        switch (choosefuntion)
        {
            case  1:
                usermenu(&GzhuLibrary);
                break;
            case 2:
                Administratormenu(&GzhuLibrary);
                break;
            default:
                is_continue = 0;
                break;
        }
    } while (is_continue);
    GzhuLibrary.savebooks();
    GzhuLibrary.saveusers();
    
}

