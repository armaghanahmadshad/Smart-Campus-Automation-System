#include <iostream>
#include <vector>
#include <string>
using namespace std;

//COURSE CLASS
class Course {
private:
    string courseCode;
    string courseName;
    int creditHours;

public:
    Course(string code = "", string name = "", int ch = 0) {
        courseCode = code;
        courseName = name;
        creditHours = ch;
    }

    string getCode() { return courseCode; }
    string getName() { return courseName; }
    int getCreditHours() { return creditHours; }

    void display() {
        cout << "\nCourse Code: " << courseCode;
        cout << "\nCourse Name: " << courseName;
        cout << "\nCredit Hours: " << creditHours << endl;
    }
};

//PERSON CLASS
class Person {
protected:
    int id;
    string name;

public:
    Person(int i = 0, string n = "") {
        id = i;
        name = n;
    }

    int getId() { return id; }
    string getName() { return name; }

    virtual void display() {
        cout << "\nID: " << id;
        cout << "\nName: " << name;
    }
};

//ATTENDANCE RECORD CLASS
class AttendanceRecord {
private:
    string date;
    char status;
public:
    AttendanceRecord(string d, char s) {
        date = d;
        status = s;
    }
    char getStatus() {
        return status;
    }
    void display() {
        cout << "\nDate: " << date << " | Status: " << status;
    }
};

// RESULT CLASS 
class Result {
private:
    string courseCode;
    float marks;
public:
    Result(string code = "", float m = 0) {
        courseCode = code;
        marks = m; 
    }
    float getMarks() {
        return marks;
    }
    string getGrade() {
        if (marks >= 85)
            return "A";
        else if (marks >= 70)
            return "B";
        else if (marks >= 60)
            return "C";
        else if (marks >= 50)
            return "D";
        else
            return "F";
    }
    float getPoint() {
        if (marks >= 85)
            return 4.0;
        else if (marks >= 70)
            return 3.0;
        else if (marks >= 60)
            return 2.0;
        else if (marks >= 50)
            return 1.0;
        else
            return 0.0;
    }
    void display() {
        cout << "\nCourse: " << courseCode;
        cout << "\nMarks: " << marks;
        cout << "\nGrade: " << getGrade();
    }
};

// STUDENT CLASS 
class Student : public Person {
private:
    float attendance;
    string feeStatus;
    vector<Course> courses;
    vector<AttendanceRecord> attendanceList;
    vector<Result> results;

public:
    Student(int i = 0, string n = "", float a = 0.0, string f = "Unpaid")
        : Person(i, n) {
        attendance = a;
        feeStatus = f;
    }

    void addResult(string code, float marks) {
        results.push_back(Result(code, marks));
    }

    float calculateGPA() {
        if (results.empty())
            return 0;
        float total = 0;
        for (int i = 0; i < results.size(); i++) {
            total += results[i].getPoint();
        }
        return total / results.size();
    }

    void showResult() {
        if (results.empty()) {
            cout << "No results available!\n";
            return;
        }

        for (int i = 0; i < results.size(); i++) {
            results[i].display();
        }

        cout << "\nGPA: " << calculateGPA() << endl;
    }

    void markAttendance(string date, char status) {
        attendanceList.push_back(AttendanceRecord(date, status));
    }

    float calculateAttendance() {
        if (attendanceList.empty()) {
            return 0;
        }
        int present = 0;
        for (int i = 0; i < attendanceList.size(); i++) {
            if (attendanceList[i].getStatus() == 'P' || attendanceList[i].getStatus() == 'p')
                present++;
        }
        return (present * 100.0) / attendanceList.size();
    }

    void showAttendance() {
        if (attendanceList.empty()) {
            cout << "No Attendance Record!" << endl;
            return;
        }
        for (int i = 0; i < attendanceList.size(); i++) {
            attendanceList[i].display();
        }
        cout << "\nAttendance %: " << calculateAttendance() << "%\n";
    }

    void setAttendance(float a) { attendance = a; }
    void setFeeStatus(string f) { feeStatus = f; }

    float getAttendance() { return attendance; }
    string getFeeStatus() { return feeStatus; }

    void addCourse(Course c) {
        courses.push_back(c);
    }

    void showCourses() {
        cout << "\n--- Courses of " << name << " ---";

        if (courses.empty()) {
            cout << "\nNo courses assigned.\n";
            return;
        }

        for (int i = 0; i < courses.size(); i++) {
            courses[i].display();
        }
    }

    void display() override {
        cout << "\n\n--- Student Details ---";
        cout << "\nID: " << id;
        cout << "\nName: " << name;
        cout << "\nAttendance: " << calculateAttendance() << "%";
        cout << "\nFee Status: " << feeStatus;
    }
};

// STUDENT MANAGER 
class StudentManager {
private:
    vector<Student> students;

public:
    vector<Student>& getStudents() {
        return students;
    }

    void addStudent() {
        int id;
        string name;

        cout << "\nEnter Student ID: ";
        cin >> id;

        cin.ignore();
        cout << "Enter Student Name: ";
        getline(cin, name);

        Student s(id, name);
        students.push_back(s);

        cout << "Student Added Successfully!\n";
    }

    void showAllStudents() {
        if (students.empty()) {
            cout << "\nNo students found!\n";
            return;
        }

        for (int i = 0; i < students.size(); i++) {
            students[i].display();
        }
    }

    Student* findStudent(int id) {
        for (int i = 0; i < students.size(); i++) {
            if (students[i].getId() == id)
                return &students[i];
        }
        return NULL;
    }
};

// ATTENDANCE MANAGER 
class AttendanceManager {
public:
    void mark(StudentManager& sm) {
        int id;
        string date;
        char status;

        cout << "\nEnter Student ID: ";
        cin >> id;

        Student* s = sm.findStudent(id);

        if (s == NULL) {
            cout << "Student not found!\n";
            return;
        }

        cout << "Enter Date (DD-MM): ";
        cin >> date;

        cout << "Enter Status (P/A): ";
        cin >> status;

        s->markAttendance(date, status);

        cout << "Attendance Marked!\n";
    }

    void view(StudentManager& sm) {
        int id;

        cout << "\nEnter Student ID: ";
        cin >> id;

        Student* s = sm.findStudent(id);

        if (s == NULL) {
            cout << "Student not found!\n";
            return;
        }

        s->showAttendance();
    }
};

// GPA MANAGER 
class GPAManager {
public:
    void assignMarks(StudentManager& sm) {
        int id;
        string code;
        float marks;

        cout << "\nEnter Student ID: ";
        cin >> id;

        Student* s = sm.findStudent(id);

        if (s == NULL) {
            cout << "Student not found!\n";
            return;
        }

        cout << "Enter Course Code: ";
        cin >> code;

        cout << "Enter Marks: ";
        cin >> marks;

        s->addResult(code, marks);

        cout << "Marks Added Successfully!\n";
    }

    void viewResult(StudentManager& sm) {
        int id;

        cout << "\nEnter Student ID: ";
        cin >> id;

        Student* s = sm.findStudent(id);

        if (s == NULL) {
            cout << "Student not found!\n";
            return;
        }

        s->showResult();
    }
};

// COURSE MANAGER 
class CourseManager {
private:
    vector<Course> courses;

public:
    void addCourse() {
        string code, name;
        int ch;

        cout << "\nEnter Course Code: ";
        cin >> code;

        cin.ignore();
        cout << "Enter Course Name: ";
        getline(cin, name);

        cout << "Enter Credit Hours: ";
        cin >> ch;

        courses.push_back(Course(code, name, ch));

        cout << "Course Added Successfully!\n";
    }

    void showCourses() {
        if (courses.empty()) {
            cout << "\nNo courses available!\n";
            return;
        }

        for (int i = 0; i < courses.size(); i++) {
            courses[i].display();
        }
    }

    void assignCourse(StudentManager& sm) {
        int id;
        string code;

        cout << "\nEnter Student ID: ";
        cin >> id;

        cout << "Enter Course Code: ";
        cin >> code;

        Student* student = sm.findStudent(id);

        if (student == NULL) {
            cout << "Student not found!\n";
            return;
        }

        for (int i = 0; i < courses.size(); i++) {
            if (courses[i].getCode() == code) {
                student->addCourse(courses[i]);
                cout << "Course Assigned Successfully!\n";
                return;
            }
        }

        cout << "Course not found!\n";
    }
};

// NOTICE BOARD 
class NoticeBoard {
private:
    vector<string> notices;

public:
    void addNotice() {
        string notice;
        cin.ignore();
        cout << "\nEnter Notice: ";
        getline(cin, notice);

        notices.push_back(notice);

        cout << "Notice Added!\n";
    }

    void showNotices() {
        if (notices.empty()) {
            cout << "\nNo notices available!\n";
            return;
        }

        cout << "\n--- Notices ---\n";

        for (int i = 0; i < notices.size(); i++) {
            cout << i + 1 << ". " << notices[i] << endl;
        }
    }
};

// FEE MANAGER 
class FeeManager {
public:
    void updateFee(StudentManager& sm) {
        int id;
        string status;

        cout << "\nEnter Student ID: ";
        cin >> id;

        Student* s = sm.findStudent(id);

        if (s == NULL) {
            cout << "Student not found!\n";
            return;
        }

        cout << "Enter Fee Status (Paid/Unpaid): ";
        cin >> status;

        s->setFeeStatus(status);

        cout << "Fee Status Updated!\n";
    }

    void viewFee(StudentManager& sm) {
        int id;

        cout << "\nEnter Student ID: ";
        cin >> id;

        Student* s = sm.findStudent(id);

        if (s == NULL) {
            cout << "Student not found!\n";
            return;
        }

        cout << "\nFee Status: " << s->getFeeStatus() << endl;
    }
};

// MAIN 
int main() {
    StudentManager sm;
    CourseManager cm;
    AttendanceManager am;
    GPAManager gm;
    NoticeBoard nb;
    FeeManager fm;

    int choice;

    do {
        cout << "\n\n====== SMART CAMPUS SYSTEM ======";
        cout << "\n1. Add Student";
        cout << "\n2. View Students";
        cout << "\n3. Add Course";
        cout << "\n4. View Courses";
        cout << "\n5. Assign Course";
        cout << "\n6. Mark Attendance";
        cout << "\n7. View Attendance";
        cout << "\n8. Assign Marks";
        cout << "\n9. View Result / GPA";
        cout << "\n10. Add Notice";
        cout << "\n11. View Notices";
        cout << "\n12. Update Fee";
        cout << "\n13. View Fee";
        cout << "\n0. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: sm.addStudent(); break;
        case 2: sm.showAllStudents(); break;
        case 3: cm.addCourse(); break;
        case 4: cm.showCourses(); break;
        case 5: cm.assignCourse(sm); break;
        case 6: am.mark(sm); break;
        case 7: am.view(sm); break;
        case 8: gm.assignMarks(sm); break;
        case 9: gm.viewResult(sm); break;
        case 10: nb.addNotice(); break;
        case 11: nb.showNotices(); break;
        case 12: fm.updateFee(sm); break;
        case 13: fm.viewFee(sm); break;
        case 0: cout << "Exiting...\n"; break;
        default: cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}