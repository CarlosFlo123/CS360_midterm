/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include <array>

using namespace std;

class Person{
protected:
    string name;
    int age;
public:
    Person(string n, int a) : name(n), age(a){}
    virtual void display(){
        cout << "name = " << name << endl;
        cout << "age = " << age << endl;
    }
    virtual void displayRoles() = 0;  //pure virtual function
};

class Student : virtual public Person{   // virtual inheritance
protected:
    int studentId;
    float gpa;
public:
    Student(string n, int a, int id, float g) : Person(n,a), studentId(id), gpa(g){}
    virtual void display(){
        Person::display();
        cout << "studentId = " << studentId << endl;
        cout << "gpa = " << gpa << endl;
    }
    virtual void displayRoles(){
        cout << "Being a good student" << endl;
    }
};

class Teacher : virtual public Person{
protected:
    string specialty;
    double salary;
public:
    Teacher(string n, int a, string sp, double sa) : Person(n, a), specialty(sp), salary(sa){}
    virtual void display(){
        Person::display();
        cout << "Specialty: " << specialty << endl;
        cout << "Salary: " << salary << endl;
    }
    virtual void displayRoles(){
        cout << "Being a good Teacher" << endl;
    }
};

class TA : public Student, public Teacher{
protected:
    string section;
public:
    TA(string n, int a, string sp, double sa, int id, float g, string s): Person(n,a), Student(n,a,id,g), Teacher(n,a,sp,sa), section(s){}
    virtual void display(){
        Student::display();
        Teacher::display();
        cout << "Section: " << section << endl;
    }
    virtual void displayRoles(){
        cout << "Being a good TA!" << endl;
    }
};

class CatalogItem{
protected:
    string title;
    int catalogID;
    double price;
    int numCopies;
public:
    CatalogItem(string t, int c, double p, int n) : title(t), catalogID(c), price(p), numCopies(n){}
    virtual void display(){
        cout << "Title: " << title << endl;
        cout << "CatalogID: " << catalogID << endl;
        cout << "Price: " << price << endl;
        cout << "NumCopies: " << numCopies << endl;
    }
    int getCatalogId() const{
        return this->catalogID;
    }
    string getTitle() const{
        return this->title;
    }
    double getPrice() const{
        return this->price;
    }
};

class Book : public CatalogItem{
protected:
    string author;
    string isbn;
public:
    Book(string t, int c, double p, int n, string a, string i) : CatalogItem(t, c, p, n), author(a), isbn(i){}
    virtual void display(){
        CatalogItem::display();
        cout << "Author: " << author << endl;
        cout << "ISBN: " << isbn << endl;
    }
    void displayCourseLevels(){
        cout << "Course Levels: CS450, CS360, CS, CS, CS..";
    }
};

class DVD : public CatalogItem{
protected:
    string director;
public:
    DVD(string t, int c, double p, int n, string d) : CatalogItem(t, c, p, n), director(d){}
    virtual void display(){
        CatalogItem::display();
        cout << "Director: " << director << endl;
    }
    void displayActorList(){
        cout << "Angelina\nLeonardo\nDwayne\nVin" << endl;
    }
};

class Library{
protected:
    string name;
    string collegeName;
    array<Person*, 10> users;
    array<CatalogItem*, 50> items;
    int numUsers;
    int numItems;
public:
    Library(string n, string cn) : name(n), collegeName(cn){
        numUsers = 0;
        numItems = 0;
    }
    void addUser(Person *p){
        users[numUsers] = p;
        numUsers++;
    }
    void addItem(CatalogItem *i){
        items[numItems] = i;
        numItems++;
    }
    CatalogItem *searchItem(int catalogID){
        for (int i = 0; i < numItems; i++){
            if (items[i]->getCatalogId() == catalogID)
                return items[i];
        }
        return 0;
    }
    CatalogItem *searchItem(string title){
        for (int i = 0; i < numItems; i++){
            if (items[i]->getTitle() == title)
                return items[i];
        }
        return 0;
    }
    double getTotalItemValue(){
        double value = 0;
        for (int i = 0; i < numItems; i++)
            value += items[i]->getPrice();
        return value;
    }
    int getNumberStudents(){
        int n_students = 0;
        Student *q;
        for (int i = 0; i < numUsers; i++){
            q = dynamic_cast<Student *> (users[i]);
            if (q != NULL)
                n_students++;
        }
        return n_students;
    }
    int getNumberTeachers(){
        int n_teachers = 0;
        Teacher *q;
        for (int i = 0; i < numUsers; i++){
            q = dynamic_cast<Teacher *> (users[i]);
            if (q != NULL)
                n_teachers++;
        }
        return n_teachers;
    }
    int getNumberTAs(){
        int n_tas = 0;
        TA *q;
        for (int i = 0; i < numUsers; i++){
            q = dynamic_cast<TA *> (users[i]);
            if (q != NULL)
                n_tas++;
        }
        return n_tas;
    }
    void display(){
        cout << "Name: " << name << endl;
        cout << "collegeName: " << collegeName << endl;
        for (int i = 0; i < numUsers; i++){
            users[i]->display();
        }
        cout << "___________________________________________\n";
        for (int j = 0; j < numItems; j++){
            items[j]->display();
        }
    }
};



int main(){
    Student s1("Peter", 26, 1234, 4.0);
    Student s2("Lily", 25, 2234, 3.8);
    Teacher t("Carl", 58, "CS", 10000.00);
    TA ta("Tom", 30, "CS", 2000.00, 1008, 3.9, "CS360L");
    //t.display();
    //s2.display();
    //ta.display();
    
    Library col("Hill", "NPU");
    col.addUser(&s1);
    col.addUser(&s2);
    col.addUser(&t);
    col.addUser(&ta);
    //col.display();
    DVD dvd("Harry Potter", 42134, 20.5, 100, "Boston George");
    //dvd.display();
    Book book("Harry Potter 2", 13244, 15.4, 78, "J.K Rowling", "Random ISBN");
    //book.display();
    col.addItem(&dvd);
    col.addItem(&book);
    CatalogItem* tmp = col.searchItem(13244);
    tmp->display();
    tmp = col.searchItem("Harry Potter");
    tmp->display();
    cout << "Total Item value: " << col.getTotalItemValue() << endl;
    cout << "Number of students: " << col.getNumberStudents() << endl;
    cout << "Number of teachers: " << col.getNumberTeachers() << endl;
    cout << "Number of TAs: " << col.getNumberTAs() << endl;
    //col.display();
    
    return 0;
}

