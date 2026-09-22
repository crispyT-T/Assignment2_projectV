#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct STUDENT_DATA
{
    string firstName;
    string lastName;

#ifdef PRE_RELEASE
    string email;
#endif
};

int main()
{
    vector<STUDENT_DATA> students;

    string fileName;

#ifdef PRE_RELEASE
    cout << "Running Pre-Release Version" << endl;
    fileName = "StudentData_Emails.txt";
#else
    cout << "Running Standard Version" << endl;
    fileName = "StudentData.txt";
#endif

    ifstream inputFile(fileName);

    if (!inputFile.is_open())
    {
        cerr << "Error: Could not open " << fileName << endl;
        return 1;
    }

    string line;

    while (getline(inputFile, line))
    {
        stringstream ss(line);

        STUDENT_DATA student;

        // File format:
        // LastName, FirstName
        // or
        // LastName, FirstName,Email

        getline(ss, student.lastName, ',');
        getline(ss, student.firstName, ',');

        // Remove leading space from first name
        if (!student.firstName.empty() && student.firstName[0] == ' ')
        {
            student.firstName.erase(0, 1);
        }

#ifdef PRE_RELEASE
        getline(ss, student.email);
#endif

        students.push_back(student);
    }

    inputFile.close();

#ifdef _DEBUG

    cout << endl;
    cout << "Student Data:" << endl;
    cout << "-------------" << endl;

    for (const STUDENT_DATA& student : students)
    {
        cout << "First Name: " << student.firstName << endl;
        cout << "Last Name: " << student.lastName << endl;

#ifdef PRE_RELEASE
        cout << "Email: " << student.email << endl;
#endif

        cout << endl;
    }

#endif

    return 0;
}