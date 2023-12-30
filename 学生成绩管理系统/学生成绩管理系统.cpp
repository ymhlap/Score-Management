#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;
const int MAX_STUDENTS = 1000;

class Student
{
public:
    string id;
    string name;
    string gender;
    string classId;
    int scores[5];
    int totalScore;
    double averageScore;
public:
    Student();
    Student(string Id, string Name, string Gender, string ClassId, int Scores[]);
    void updateScore(int subjectIndex, int newScore);
};

Student::Student(string Id, string Name, string Gender, string ClassId, int Scores[])
{
    id = Id;
    name = Name;
    gender = Gender;
    classId = ClassId;
    totalScore = 0;
    averageScore = 0;
    for (int i = 0; i < 5; i++)
    {
        scores[i] = Scores[i];
        totalScore += Scores[i];
    }
    averageScore = totalScore / 5.0;
}

Student::Student()
{
    totalScore = 0;
    averageScore = 0;
    for (int i = 0; i < 5; i++)
    {
        scores[i] = 0;
    }
}

void Student::updateScore(int subjectIndex, int newScore)
{
    totalScore -= scores[subjectIndex];
    scores[subjectIndex] = newScore;
    totalScore += newScore;
    averageScore = totalScore / 5.0;
}

class StudentManager
{
private:
    Student students[MAX_STUDENTS];
    int studentCount;
public:
    StudentManager();
    void loadStudents();
    void saveStudents();
    void addStudent(Student student);
    void deleteStudent(string idOrName);
    void updateStudent(string idOrName, int subjectIndex, int newScore);
    void printStudent(Student student);
    void printStudents();
    void queryStudent(string idOrName);
    void queryClass(string classId);
    void sortStudents(int order);
    void countFailures(string classId);
};

StudentManager::StudentManager()
{
    studentCount = 0;
}

void StudentManager::loadStudents()
{
    ifstream file("students.txt");
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            istringstream iss(line);
            string id, name, gender, classId;
            int scores[5] = { 0 };
            iss >> id >> name >> gender >> classId;
            for (int i = 0; i < 5; i++)
            {
                iss >> scores[i];
            }
            students[studentCount++] = Student(id, name, gender, classId, scores);
        }
        file.close();
    }
}

void StudentManager::saveStudents()
{
    ofstream file("students.txt");
    if (file.is_open())
    {
        for (int i = 0; i < studentCount; i++)
        {
            Student student = students[i];
            file << student.id << " " << student.name << " " << student.gender << " " << student.classId << " ";
            for (int j = 0; j < 5; j++)
            {
                file << student.scores[j] << " ";
            }
            file << endl;
        }
        file.close();
    }
}

void StudentManager::addStudent(Student student)
{
    students[studentCount++] = student;
}

void StudentManager::deleteStudent(string idOrName)
{
    int index = -1;
    for (int i = 0; i < studentCount; i++)
    {
        if (students[i].id == idOrName || students[i].name == idOrName)
        {
            index = i;
            break;
        }
    }
    if (index != -1)
    {
        for (int i = index; i < studentCount - 1; i++)
        {
            students[i] = students[i + 1];
        }
        studentCount--;
        cout << "删除成功" << endl;
    }
    else
    {
        cout << "未找到该学生" << endl;
    }
}

void StudentManager::updateStudent(string idOrName, int subjectIndex, int newScore)
{
    int index = -1;
    for (int i = 0; i < studentCount; i++)
    {
        if (students[i].id == idOrName || students[i].name == idOrName)
        {
            index = i;
            break;
        }
    }
    if (index != -1)
    {
        students[index].updateScore(subjectIndex, newScore);
        cout << "修改成功" << endl;
    }
    else
    {
        cout << "未找到该学生" << endl;
    }
}

void StudentManager::printStudent(Student student)
{
    cout << "学号：" << student.id << " " << "姓名：" << student.name << " " << "性别：" <<
        student.gender << " " << "班级：" << student.classId;
    cout << " 各科成绩：";
    for (int i = 0; i < 5; i++)
    {
        cout << student.scores[i] << " ";
    }
    cout << "总成绩：" << student.totalScore << " " << "平均成绩：" << student.averageScore << endl;
}

void StudentManager::printStudents()
{
    for (int i = 0; i < studentCount; i++)
    {
        printStudent(students[i]);
    }
}

void StudentManager::queryStudent(string idOrName)
{
    int index = -1;
    for (int i = 0; i < studentCount; i++)
    {
        if (students[i].id == idOrName || students[i].name == idOrName)
        {
            index = i;
            break;
        }
    }
    if (index != -1)
    {
        Student student = students[index];
        cout << "学号：" << student.id << " " << "姓名：" << student.name << " " <<
            "性别：" << student.gender << " " << "班级：" << student.classId << " ";
        cout << " 各科成绩：";
        for (int i = 0; i < 5; i++)
        {
            cout << student.scores[i] << " ";
        }
        cout << "总成绩：" << student.totalScore << " " << "平均成绩：" << student.averageScore << endl;
    }
    else
    {
        cout << "未找到该学生" << endl;
    }
}

void StudentManager::queryClass(string classId)
{
    for (int i = 0; i < studentCount; i++)
    {
        if (students[i].classId == classId)
        {
            printStudent(students[i]);
        }
    }
}

void StudentManager::sortStudents(int order)
{
    if (order == 1)
    {
        for (int i = 0; i < studentCount - 1; i++)
        {
            for (int j = 0; j < studentCount - i - 1; j++)
            {
                if (students[j].averageScore > students[j + 1].averageScore)
                {
                    swap(students[j], students[j + 1]);
                }
            }
        }
    }
    else if (order == 2)
    {
        for (int i = 0; i < studentCount - 1; i++)
        {
            for (int j = 0; j < studentCount - i - 1; j++)
            {
                if (students[j].averageScore < students[j + 1].averageScore)
                {
                    swap(students[j], students[j + 1]);
                }
            }
        }
    }
}

void StudentManager::countFailures(string classId)
{
    int failures[5] = { 0 };
    for (int i = 0; i < studentCount; i++)
    {
        if (students[i].classId == classId)
        {
            for (int j = 0; j < 5; j++)
            {
                if (students[i].scores[j] < 60)
                {
                    failures[j]++;
                }
            }
        }
    }
    for (int i = 0; i < 5; i++)
    {
        cout << "专业课" << i + 1 << "不及格人数：" << failures[i] << endl;
    }
}

void menu()
{
    cout << " 学生成绩管理 " << endl;
    cout << "               " << endl;
    cout << "===============" << endl;
    cout << "1.录入学生信息" << endl;
    cout << "2.修改学生成绩" << endl;
    cout << "3.删除学生信息" << endl;
    cout << "4.增加学生信息" << endl;
    cout << "5.计算总分和平均分" << endl;
    cout << "6.查询学生信息" << endl;
    cout << "7.查询班级信息" << endl;
    cout << "8.成绩排序" << endl;
    cout << "9.统计班级不及格人数" << endl;
    cout << "0.退出系统" << endl;
    cout << "===============" << endl;
}

int main()
{
    StudentManager studentManager;
    studentManager.loadStudents();
    while (true)
    {
        menu();
        cout << "请输入选择：";
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            studentManager.loadStudents();
            system("pause");
            system("cls");
            break;
        }
        case 2:
        {
            string idOrName;
            cout << "请输入学号或姓名：";
            cin >> idOrName;
            int subjectIndex;
            cout << "请输入要修改的专业课序号（1-5）：";
            cin >> subjectIndex;
            subjectIndex--;
            int newScore;
            cout << "请输入新成绩：";
            cin >> newScore;
            studentManager.updateStudent(idOrName, subjectIndex, newScore);
            system("pause");
            system("cls");
            break;
        }
        case 3:
        {
            string idOrName;
            cout << "请输入学号或姓名：";
            cin >> idOrName;
            studentManager.deleteStudent(idOrName);
            system("pause");
            system("cls");
            break;
        }
        case 4:
        {
            string id, name, gender, classId;
            int scores[5] = { 0 };
            cout << "请输入学号：";
            cin >> id;
            cout << "请输入姓名：";
            cin >> name;
            cout << "请输入性别：";
            cin >> gender;
            cout << "请输入班级：";
            cin >> classId;
            cout << "请输入五门专业课成绩：";
            for (int i = 0; i < 5; i++)
            {
                cin >> scores[i];
            }
            studentManager.addStudent(Student(id, name, gender, classId, scores));
            cout << "增加成功" << endl;
            system("pause");
            system("cls");
            break;
        }
        case 5:
        {
            studentManager.printStudents();
            system("pause");
            system("cls");
            break;
        }
        case 6:
        {
            string idOrName;
            cout << "请输入学号或姓名：";
            cin >> idOrName;
            studentManager.queryStudent(idOrName);
            system("pause");
            system("cls");
            break;
        }
        case 7:
        {
            string classId;
            cout << "请输入班级：";
            cin >> classId;
            studentManager.queryClass(classId);
            system("pause");
            system("cls");
            break;
        }
        case 8:
        {
            int order;
            cout << "请输入排序方式（1-升序，2-降序）：";
            cin >> order;
            studentManager.sortStudents(order);
            studentManager.printStudents();
            system("pause");
            system("cls");
            break;
        }
        case 9:
        {
            string classId;
            cout << "请输入班级：";
            cin >> classId;
            studentManager.countFailures(classId);
            system("pause");
            system("cls");
            break;
        }
        case 0:
        {
            studentManager.saveStudents();
            system("pause");
            system("cls");
            return 0;
        }
        default:
            break;
        }
    }
    return 0;
}