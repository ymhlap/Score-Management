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
        cout << "ɾ���ɹ�" << endl;
    }
    else
    {
        cout << "δ�ҵ���ѧ��" << endl;
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
        cout << "�޸ĳɹ�" << endl;
    }
    else
    {
        cout << "δ�ҵ���ѧ��" << endl;
    }
}

void StudentManager::printStudent(Student student)
{
    cout << "ѧ�ţ�" << student.id << " " << "������" << student.name << " " << "�Ա�" <<
        student.gender << " " << "�༶��" << student.classId;
    cout << " ���Ƴɼ���";
    for (int i = 0; i < 5; i++)
    {
        cout << student.scores[i] << " ";
    }
    cout << "�ܳɼ���" << student.totalScore << " " << "ƽ���ɼ���" << student.averageScore << endl;
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
        cout << "ѧ�ţ�" << student.id << " " << "������" << student.name << " " <<
            "�Ա�" << student.gender << " " << "�༶��" << student.classId << " ";
        cout << " ���Ƴɼ���";
        for (int i = 0; i < 5; i++)
        {
            cout << student.scores[i] << " ";
        }
        cout << "�ܳɼ���" << student.totalScore << " " << "ƽ���ɼ���" << student.averageScore << endl;
    }
    else
    {
        cout << "δ�ҵ���ѧ��" << endl;
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
        cout << "רҵ��" << i + 1 << "������������" << failures[i] << endl;
    }
}

void menu()
{
    cout << " ѧ���ɼ����� " << endl;
    cout << "               " << endl;
    cout << "===============" << endl;
    cout << "1.¼��ѧ����Ϣ" << endl;
    cout << "2.�޸�ѧ���ɼ�" << endl;
    cout << "3.ɾ��ѧ����Ϣ" << endl;
    cout << "4.����ѧ����Ϣ" << endl;
    cout << "5.�����ֺܷ�ƽ����" << endl;
    cout << "6.��ѯѧ����Ϣ" << endl;
    cout << "7.��ѯ�༶��Ϣ" << endl;
    cout << "8.�ɼ�����" << endl;
    cout << "9.ͳ�ư༶����������" << endl;
    cout << "0.�˳�ϵͳ" << endl;
    cout << "===============" << endl;
}

int main()
{
    StudentManager studentManager;
    studentManager.loadStudents();
    while (true)
    {
        menu();
        cout << "������ѡ��";
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
            cout << "������ѧ�Ż�������";
            cin >> idOrName;
            int subjectIndex;
            cout << "������Ҫ�޸ĵ�רҵ����ţ�1-5����";
            cin >> subjectIndex;
            subjectIndex--;
            int newScore;
            cout << "�������³ɼ���";
            cin >> newScore;
            studentManager.updateStudent(idOrName, subjectIndex, newScore);
            system("pause");
            system("cls");
            break;
        }
        case 3:
        {
            string idOrName;
            cout << "������ѧ�Ż�������";
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
            cout << "������ѧ�ţ�";
            cin >> id;
            cout << "������������";
            cin >> name;
            cout << "�������Ա�";
            cin >> gender;
            cout << "������༶��";
            cin >> classId;
            cout << "����������רҵ�γɼ���";
            for (int i = 0; i < 5; i++)
            {
                cin >> scores[i];
            }
            studentManager.addStudent(Student(id, name, gender, classId, scores));
            cout << "���ӳɹ�" << endl;
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
            cout << "������ѧ�Ż�������";
            cin >> idOrName;
            studentManager.queryStudent(idOrName);
            system("pause");
            system("cls");
            break;
        }
        case 7:
        {
            string classId;
            cout << "������༶��";
            cin >> classId;
            studentManager.queryClass(classId);
            system("pause");
            system("cls");
            break;
        }
        case 8:
        {
            int order;
            cout << "����������ʽ��1-����2-���򣩣�";
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
            cout << "������༶��";
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