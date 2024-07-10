#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

struct Student {
    string firstName;
    string surname;
    string gender;
    int age;
    int group;
    string sport;
    vector<string> clubs;
};

struct Activity {
    string name;
    int maxCapacity;
    int currentCapacity;
    int maxMaleRatio; // Percentage
    int currentMale;
    int currentFemale;
};

vector<Student> students;
vector<Activity> sports = {
        {"Rugby", 20, 0, 75, 0, 0},
        {"Athletics", 20, 0, 75, 0, 0},
        {"Swimming", 20, 0, 75, 0, 0},
        {"Soccer", 20, 0, 75, 0, 0}
};
vector<Activity> clubs = {
        {"Journalism Club", 60, 0, 50, 0, 0},
        {"Red Cross Society", 60, 0, 50, 0, 0},
        {"AISEC", 60, 0, 50, 0, 0},
        {"Business Club", 60, 0, 50, 0, 0},
        {"Computer Science Club", 60, 0, 50, 0, 0}
};

void displayActivities(vector<Activity>& activities) {
    for (int i = 0; i < activities.size(); i++) {
        cout << i + 1 << ". " << activities[i].name << " (Capacity: "
            << activities[i].currentCapacity << "/" << activities[i].maxCapacity << ")" << endl;
    }
}

bool addStudentToActivity(Activity& activity, string gender) {
    if (activity.currentCapacity >= activity.maxCapacity) {
        return false;
    }
    if (gender == "Male" && activity.currentMale + 1 > activity.maxCapacity * activity.maxMaleRatio / 100) {
        return false;
    }
    if (gender == "Female" && activity.currentFemale + 1 > activity.maxCapacity * (100 - activity.maxMaleRatio) / 100) {
        return false;
    }
    activity.currentCapacity++;
    if (gender == "Male") {
        activity.currentMale++;
    }
    else {
        activity.currentFemale++;
    }
    return true;
}

void addStudent() {
    Student student;
    cout << "Enter First Name: ";
    cin >> student.firstName;
    cout << "Enter Surname: ";
    cin >> student.surname;
    cout << "Enter Gender (Male/Female): ";
    cin >> student.gender;
    if (student.gender !="male" && student.gender!= "female")
     { cout << "Invalid gender. Please try again"<<endl;return;}
    cout << "Enter Age: ";
    cin >> student.age;
    cout << "Enter BBIT Group (1-3): ";
    cin >> student.group;

    int choice;
    cout << "Choose a sport (or 0 to skip):" << endl;
    displayActivities(sports);
    cin >> choice;

    if (choice > 0 && choice <= sports.size()) {
        if (addStudentToActivity(sports[choice - 1], student.gender)) {
            student.sport = sports[choice - 1].name;
        } else {
            cout << "Unable to add to sport (capacity or gender ratio exceeded)." << endl;
        }
    }

    if (choice==0){
        cout << "Choose up to 3 clubs"<< endl;
    }
    else{
    cout << "Choose up to 2 clubs (enter 0 to finish):" << endl;}
    displayActivities(clubs);
    while (student.clubs.size() < (student.sport.empty() ? 3 : 2)) {
        cin >> choice;
        if (choice == 0) {
            break;
        }
        if (choice > 0 && choice <= clubs.size()) {
            if (addStudentToActivity(clubs[choice - 1], student.gender)) {
                student.clubs.push_back(clubs[choice - 1].name);
            } else {
                cout << "Unable to add to club (capacity or gender ratio exceeded)." << endl;
            }
        }
    }

    if (student.sport.empty() && student.clubs.empty()) {
        cout << "Student must choose at least one sport or club." << endl;
    } else {
        students.push_back(student);
        cout << "Student added successfully." << endl;
    }
}

void viewStudents() {
    for (const auto& student : students) {
        cout << student.firstName << " " << student.surname << " (Group " << student.group << ") - Sport: "
             << student.sport << ", Clubs: ";
        for (const auto& club : student.clubs) {
            cout << club << " ";
        }
        cout << endl;
    }
}

void viewActivities(const vector<Activity>& activities) {
    for (const auto& activity : activities) {
        cout << activity.name << " (Capacity: " << activity.currentCapacity << "/" << activity.maxCapacity << ")" << endl;
    }
}

void saveToFile(const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        file << "First Name,Surname,Gender,Age,Group,Sport,Clubs\n";
        for (const auto& student : students) {
            file << student.firstName << "," << student.surname << "," << student.gender << ","
                 << student.age << "," << student.group << "," << student.sport << ",";
            for (const auto& club : student.clubs) {
                file << club << " ";
            }
            file << "\n";
        }
        file.close();
        cout << "Data saved to " << filename << endl;
    } else {
        cout << "Unable to open file." << endl;
    }
}

int main() {
    int choice;
    do {
        cout << "1. Add Student\n2. View Students\n3. View Clubs/Societies\n4. View Sports\n5. Save to File\n6. Exit\n";
        cin >> choice;
        switch (choice) {
            case 1:
                addStudent();
                break;
             case 2:
                viewStudents();
                break;
             case 3:
                viewActivities(clubs);
                break;
             case 4:
                viewActivities(sports);
                break;
             case 5:
                saveToFile("students.csv");
                break;
             case 6:
                cout << "Exiting program." << endl;
                break;
              default:
                cout << "Invalid choice. Please try again." << endl;return 0;
         }
    } while (choice != 6);

    system("pause");
    return 0;
}
