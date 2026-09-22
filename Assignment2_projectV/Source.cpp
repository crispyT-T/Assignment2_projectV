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
};

int main()
{
    vector<STUDENT_DATA> students;

    ifstream inputFile("StudentData.txt");

    if (!inputFile.is_open())
    {
        cerr << "Error: Could not open StudentData.txt" << endl;
        return 1;
    }

    string line;

    while (getline(inputFile, line))
    {
        stringstream ss(line);

        STUDENT_DATA student;

        getline(ss, student.lastName, ',');
        getline(ss, student.firstName);

        // Remove leading space from first name if present
        if (!student.firstName.empty() && student.firstName[0] == ' ')
        {
            student.firstName.erase(0, 1);
        }

        students.push_back(student);
    }

    inputFile.close();

    return 0;
}