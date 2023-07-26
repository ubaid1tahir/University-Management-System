#include<iostream>
#include<fstream>
#include<conio.h>
#include<string.h>
#include<string>
using namespace std;

class StudentDetails { // Abstract Class
public:
    float cgpa;
    long long fees;
    string name;
    string fatherName;
    string cnic;
    string courseName;
    string email;
    string password;
    bool isPresent;
    bool isShortAttendance;
    bool isFeesPaid;
    bool isAuthorize;
    virtual void getAdmission(int _id, string _name, string _fatherName, string _cnic, string _email, string _password, string _courseName, long long _fees) = 0;
};


class Student : public StudentDetails {
    static int id;
    static long long numberOfStudents;
public:
    
    static long getId() { // static method
        return id;
    }
    float getGpa() {
        return cgpa;
    }
    long long getFees() {
        return fees;
    }
    string getName() {
        return name;
    }
    string getFather() {
        return fatherName;
    }
    string getCnic() {
        return cnic;
    }
    string getCourse() {
        return courseName;
    }
    string getEmail() {
        return email;
    }
    string getPassword() {
        return password;
    }
    bool getIsPresent() {
        return isPresent;
    }
    Student(){
        id++;
    }
    Student(string _name, string _fatherName, string _cnic, string _email, string _password, string _courseName, long long _fees) {
        id++;
        name = _name;
        fatherName = _fatherName;
        cnic = _cnic;
        email = _email;
        password = _password;
        courseName = _courseName;
        fees = _fees;
        numberOfStudents++;
        getAdmission(id, name, fatherName, cnic, email, password, courseName, fees);
    }
    void getAdmission(int _id,string _name, string _fatherName, string _cnic, string _email, string _password, string _courseName, long long _fees) {
        fstream students;
        students.open("EnrolledStudents", ios::app);
        if (students.is_open()) {
            if (_name != "" && _fatherName != "" && _cnic != "" && _email != "" && _password != "" && _courseName != "" && _fees != 0) {
                students << "{" << _id << "," <<  _name << "," << _fatherName << "," << _cnic << ","
                    << _email << "," << _password << "," << _courseName << "," << _fees << "}" << endl;
                cout << "Successfully admitted one student ;)" << endl;
            }
            else {
                cout << "Please enter valid information" << endl;
            }
        }
        else {
            cout << "There is some error in file writing:(" << endl;
        }
        students.close();
    }
    void getDetails(string id) {
        fstream students;
        students.open("EnrolledStudents", ios::in);
        if (students.is_open()) {
            while (students) {
                string str = "";
                string strId = "";
                getline(students, str);
                int commas = 0;
                for (int i = 0; i < str.length(); i++) {
                    if (str[i] == ',') {
                        break;
                    }
                    if (commas == 0 && str[i] != '{') {
                        strId += str[i];
                    }
                }
                if (strId == id) {
                    cout << str << endl;
                    break;
                }
                commas = 0;
            }
        }
    }
};
class Admin {
    static int id;
    int numberOfStudents;
    int numberOfTeachers;
    int numberOfCourses;
    string name;
    string email;
    string password;
    bool isAuthorize;
public:
    Admin() {
    }
    Admin(string name, string email, string password) {
        id++;
        this->name = name;
        this->email = email;
        this->password = password;
        addAdmin();
    }
    void addCourse();
    void giveSalary();
    void addAdmin() {
        fstream admin;
        admin.open("EnrolledAdmin", ios::app);
        if (admin.is_open()) {
            if (name != "" && email != "" && password != "") {
                admin << "{" << id << "," << name << "," << email << "," << password << "}" << endl;
            }
        }
        admin.close();
    }
    void adminDashboard() {
        cout << "\t\t\t ************ University Management System **************" << endl;
        cout << "\t\t\t ************ Welcome to Our Dashboard ******************" << endl;
        cout << "\t\t Press the related numbers given in the menu to proceed" << endl;
        cout << "1. Add Students" << endl;
        cout << "2. Hire Teachers" << endl;
        cout << "3. Add Course" << endl;
        cout << "4. Exit" << endl;
    }
};
int Admin::id = 0;

int Student::id = 0;
long long Student::numberOfStudents = 0;

class Teacher {
    static int id;
    long long salary;
    string name;
    string major;
    string email;
    string password;
    bool isTakeSalary;
    bool isShortAttendance;
    bool isAuthorize;
public:
    Teacher(){}
    Teacher(string _name, string _major, string email, string password, long long salary) {
        id++;
        name = _name;
        major = _major;
        this->email = email;
        this->password = password;
        this->salary = salary;
        addTeacher();
    }
    void addTeacher() {
        fstream teacher;
        teacher.open("EnrolledTeacher", ios::app);
        if (teacher.is_open()) {
            if (name != "" && email != "" && password != "") {
                teacher << "{" << id << "," << name << "," << email << "," << password << "," << major << "}" << endl;
            }
        }
        teacher.close();
        cout << "The teacher " << name << " is successfully hired " << endl;
    }
    void setAttendance(Student s) {
        fstream attendance;// makes attendance file and stores the string
        attendance.open("AttendanceRecord", ios::app);
        attendance << s.getId() << s.getName() << s.getCnic() << s.getCourse() << s.getIsPresent() << endl;
        attendance.close();
    }
    void setAssessment();
    void gpaCalculation();
};

int Teacher::id = 0;

class Course {
    string name;
    static int id;
    float duration;
    Teacher teachers[100];// Composition
    Student students[500];
    bool isHecApproved;
    string requirements[30];
    static long long numberOfCourses;
public:
    Course(string _name, float _duration, bool _isApproved, int numberOfRequirements, string _requirements[]) {
        id++;
        name = _name;
        duration = _duration;
        isHecApproved = _isApproved;
        for (int i = 0; i < numberOfRequirements; i++) {
            requirements[i] = _requirements[i];
        }
        addCourse(_name,  _duration,  _isApproved,  numberOfRequirements, requirements);
    }
    void addCourse(string name, float duration, bool isApproved, int numberOfRequirements, string requirements[]) {
        fstream courses;
        courses.open("EnrolledCourses", ios::app);
        if (courses.is_open()) {
            if (name != "" && duration != 0.0 && numberOfRequirements != 0) {
                courses << "{" << id << "," << name << "," << duration << "," << isApproved << ",";
                for (int i = 0; i < numberOfRequirements; i++) {
                    courses << requirements[i] << ",";
                }
                courses << "}" << endl;
                cout << "Successfully Added one Course ;)" << endl;
            }
            else {
                cout << "Please enter valid data " << endl;
            }
        }
        else {
            cout << "There is some error in file writing :(" << endl;
        }
        courses.close();
        system("pause");
        system("cls");
    }
};
int Course::id = 0;
long long Course::numberOfCourses = 0;

void menu(){
    cout << "\t\t\t ************ University Management System **************" << endl;
    cout << "\t\t\t ************ Welcome to Our Dashboard ******************" << endl;
    cout << "\t\t Press the related numbers given in the menu to proceed" << endl;
    cout << "\t\t **** Main Menu ****" << endl;
    cout << "1.\t Login as Student" << endl;
    cout << "2.\t Login as Teacher" << endl;
    cout << "3.\t Login as Admin" << endl;
    cout << "4.\t Close" << endl;
}

bool isAuthorize(string name, string email,string password) { // to be changed
    if (name == "student") {
        fstream file;
        file.open("EnrolledStudents", ios::in);
        if (file.is_open()) {
            while (file) {
                string str = "";
                getline(file, str);
                int commas = 0;
                int emailCharacters = 0;
                string emailStr;
                int passwordCharacters = 0;
                string passwordStr;
                for (int i = 0; i < str.length(); i++) {
                    if (str[i] == ',') {
                        commas++;
                    }
                    if (commas == 4 && str[i] != ',') {
                        emailCharacters++;
                        emailStr += str[i];
                    }
                    if (commas == 5 && str[i] != ',') {
                        passwordCharacters++;
                        passwordStr += str[i];
                    }
                    int result1 = email.compare(emailStr);
                    int result2 = password.compare(passwordStr);
                    if (result1 == 0 && result2 == 0) {
                        return true;
                    }
                }
                commas = 0;
            }
        }
        file.close();
        return  false;
    }
    else if (name == "admin") {
        fstream file;
        file.open("EnrolledAdmin", ios::in);
        if (file.is_open()) {
            while (file) {
                string str = "";
                getline(file, str);
                int commas = 0;
                int emailCharacters = 0;
                string emailStr;
                int passwordCharacters = 0;
                string passwordStr;
                for (int i = 0; i < str.length(); i++) {
                    if (str[i] == ',') {
                        commas++;
                    }
                    if (commas == 2 && str[i] != ',') {
                        emailCharacters++;
                        emailStr += str[i];
                    }
                    if (commas == 3 && str[i] != ',') {
                        passwordCharacters++;
                        passwordStr += str[i];
                    }
                    int result1 = email.compare(emailStr);
                    int result2 = password.compare(passwordStr);
                    if (result1 == 0 && result2 == 0) {
                        return true;
                    }
                }
                commas = 0;
            }
        }
        file.close();
        return  false;
    }
    else if (name == "teacher") {
        fstream file;
        file.open("EnrolledTeacher", ios::in);
        if (file.is_open()) {
            while (file) {
                string str = "";
                getline(file, str);
                int commas = 0;
                int emailCharacters = 0;
                string emailStr;
                int passwordCharacters = 0;
                string passwordStr;
                for (int i = 0; i < str.length(); i++) {
                    if (str[i] == ',') {
                        commas++;
                    }
                    if (commas == 2 && str[i] != ',') {
                        emailCharacters++;
                        emailStr += str[i];
                    }
                    if (commas == 3 && str[i] != ',') {
                        passwordCharacters++;
                        passwordStr += str[i];
                    }
                    int result1 = email.compare(emailStr);
                    int result2 = password.compare(passwordStr);
                    if (result1 == 0 && result2 == 0) {
                        return true;
                    }
                }
                commas = 0;
            }
        }
        file.close();
        return  false;
    }
}
int main()
{
    string email, password;
    bool isFound = false;
    int attempts = 0;
    char choose;
    char adminChoose;
    // student variables
    long long fees;
    string name;
    string fatherName;
    string cnic;
    string courseName;
    //teacher variables
    string major;
    long long salary;
    // course variables
    float duration;
    Teacher teachers[100];
    Student students[500];
    bool isHecApproved;
    int reqNumbers;
    string requirements[30];
    /*string email;
    string password;*/
    // variables used
    // initializing admin
    //Admin admin("Ubaid", "admin", "admin");
    //
    // initalizing teacher
    //Teacher t1("Ubaid", "CS", "teacher", "T1234", 120000);
    Admin admin;
    do {
        menu();
        cout << "Enter any number :" << endl;
        choose = _getch();
        switch (choose)
        {
        case '1':
            system("cls");
            menu();
            do {
                cout << " \t\t\t\t ******* Login To Proceed *********" << endl;
                cout << "\t\t\t Email    :";
                cin >> email;
                cout << "\t\t\t Password :";
                cin >> password;
                if (isAuthorize("student", email, password)) {
                    cout << "You are successfully Login as a Student :)" << endl;
                    isFound = true;
                    system("pause");
                    system("cls");
                    Student s;
                    cout << "Enter your id :";
                    string strId;
                    cin >> strId;
                    s.getDetails(strId);
                }
                else {
                    cout << "Email is invalid :(" << endl;
                    system("pause");
                    system("cls");
                    menu();
                    isFound = false;
                    attempts++;
                    if (attempts == 2) {
                        cout << "Your account has been blocked. Please try later" << endl;
                        system("pause");
                        system("cls");
                    }
                }

            } while (!isFound && attempts < 2);
            break;
        case '2':
            attempts = 0;
            system("cls");
            do {
                menu();
                cout << " \t\t\t\t ******* Login To Proceed *********" << endl;
                cout << "\t\t\t Email    :";
                cin >> email;
                cout << "\t\t\t Password :";
                cin >> password;
                if (isAuthorize("teacher", email, password)) {
                    cout << "You are successfully Login as an Teacher :)" << endl;
                    isFound = true;
                    system("pause");
                    system("cls");

                }
                else {
                    cout << "Email is invalid :(" << endl;
                    system("pause");
                    system("cls");
                    menu();
                    isFound = false;
                    attempts++;
                    if (attempts == 2) {
                        cout << "Your account has been blocked. Please try later" << endl;
                        system("pause");
                        system("cls");
                    }
                }

            } while (!isFound && attempts < 2);
            break;
        case '3':
            attempts = 0;
            system("cls");
            menu();
            do {
                cout << " \t\t\t\t ******* Login To Proceed *********" << endl;
                cout << "\t\t\t Email    :";
                cin >> email;
                cout << "\t\t\t Password :";
                cin >> password;
                if (isAuthorize("admin", email, password)) {
                    cout << "You are successfully Login as an Admin :)" << endl;
                    isFound = true;
                    system("pause");
                    system("cls");
                    admin.adminDashboard();
                    cout << "Enter the number :";
                    adminChoose = _getch();
                    cout << endl;
                    if (adminChoose == '1') {
                        cout << "Enter name of the student :";
                        cin >> name;
                        cout << "Enter fathername of the student :";
                        cin >> fatherName;
                        cout << "Enter CNIC of the student :";
                        cin >> cnic;
                        cout << "Enter Course Name which a student wants to study :";
                        cin >> courseName;
                        cout << "Enter email of the student :";
                        cin >> email;
                        cout << "Enter password of the student :";
                        cin >> password;
                        cout << "Enter fees of this course :";
                        cin >> fees;
                        Student student(name, fatherName, cnic, email, password, courseName, fees);
                        system("pause");
                        system("cls");
                    }
                    else if (adminChoose == '2') {
                        cout << "Enter the name of the teacher :";
                        cin >> name;
                        cout << "Enter major subject of the teacher :";
                        cin >> major;
                        cout << "Enter email of the teacher :";
                        cin >> email;
                        cout << "Enter password of the teacher :";
                        cin >> password;
                        cout << "Enter salary of the teacher :";
                        cin >> salary;
                        Teacher teacher(name, major, email, password, salary);
                        system("pause");
                        system("cls");
                    }
                    else if (adminChoose == '3') {
                        cout << "Enter the name of the course :";
                        cin >> courseName;
                        cout << "Enter duration of the course :";
                        cin >> duration;
                        cout << "Enter 1 if this course is HEC approved and 0 if not :";
                        cin >> isHecApproved;
                        cout << "Enter requirements that the student must accomplish to pursue this course :" << endl;
                        cout << "Enter the number of requirements :";
                        cin >> reqNumbers;
                        cout << "Enter the names of them :" << endl;
                        for (int i = 0; i < reqNumbers; i++) {
                            cout << i + 1 << ".";
                            cin >> requirements[i];
                        }
                        Course course(courseName, duration, isHecApproved, reqNumbers, requirements);
                        
                    }
                }
                
                else {
                    cout << "Email is invalid :(" << endl;
                    system("pause");
                    system("cls");
                    menu();
                    isFound = false;
                    attempts++;
                    if (attempts == 2) {
                        cout << "Your account has been blocked. Please try later" << endl;
                        system("pause");
                        system("cls");
                    }
                }

            } while (!isFound && attempts < 2);
            break;
        case '4':
            return false;
            break;
        default:
            break;
        }

    } while (true);
}
