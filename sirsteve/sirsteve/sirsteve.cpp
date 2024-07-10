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
