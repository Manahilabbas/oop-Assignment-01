#include <iostream>
#include <string>
using namespace std;

class Student;
class Mentor;
class Sport;
class Skill;

class Skill {
public:
    int skillID;
    string skillName;
    string description;

    Skill(int id, string name, string desc);
    Skill(){}
    void showSkillDetails();
    void updateSkillDescription(string newDescription);
};

class Sport {
public:
    int sportID;
    string name;
    string description;
    Skill** requiredSkills;
    int skill_count;

    Sport(int id, string n, string desc);
    Sport(){}
    void addSkill(Skill* s);
    void removeSkill(int skillID);
};

class Mentor {
public:
    int mentorID;
    string name;
    Sport** sportsExpertise;
    int sport_count;
    int maxLearners;
    Student** assignedLearners;
    int learner_count;

    Mentor(int id, string n, Sport* expertise, int maxL);
    Mentor(){}
    void assignLearner(Student* stu);
    void removeLearner(Student* s);
    void viewLearners();
    void provideGuidance();
};

class Student {
public:
    int studentID;
    string name;
    int age;
    Sport** sportsInterests;
    int sports_count;
    Mentor* mentorAssigned;

    Student(int id, string n, int a, int maxSports);
    Student(){}
    void registerForMentorship(Mentor* m);
    void viewMentorDetails();
    void updateSportsInterest(Sport* sport);
};

// Global function definitions

Skill::Skill(int id, string name, string desc) : skillID(id), skillName(name), description(desc) {}

void Skill::showSkillDetails() {
    cout << "Skill ID: " << skillID << endl;
    cout << "Name: " << skillName << endl;
    cout << "Description: " << description << endl;
}

void Skill::updateSkillDescription(string newDescription) {
    description = newDescription;
}

Sport::Sport(int id, string n, string desc) : sportID(id), name(n), description(desc), skill_count(0) {
    requiredSkills = new Skill*[10];
}

void Sport::addSkill(Skill* s) {
    if (skill_count < 10) {
        requiredSkills[skill_count++] = new Skill(*s);
    } else {
        cout << "Maximum skills reached for " << name << endl;
    }
}

void Sport::removeSkill(int skillID) {
    for (int i = 0; i < skill_count; i++) {
        if (skillID == requiredSkills[i]->skillID) {
            delete requiredSkills[i];
            for (int j = i; j < skill_count - 1; j++) {
                requiredSkills[j] = requiredSkills[j + 1];
            }
            skill_count--;
            cout << "Skill " << skillID << " removed from " << name << endl;
            return;
        }
    }
    cout << "Skill " << skillID << " not found in " << name << endl;
}

Mentor::Mentor(int id, string n, Sport* expertise, int maxL) : mentorID(id), name(n), sport_count(1), maxLearners(maxL), learner_count(0) {
    sportsExpertise = new Sport*[10];
    sportsExpertise[0] = expertise;
    assignedLearners = new Student*[maxLearners];
}

void Mentor::assignLearner(Student* stu) {
    if (learner_count < maxLearners) {
        assignedLearners[learner_count++] = stu;
        cout << stu->name << " assigned to mentor " << this->name << endl;
    } else {
        cout << "Max learners reached for mentor " << name << endl;
    }
}

void Mentor::removeLearner(Student* s) {
    for (int i = 0; i < learner_count; i++) {
        if (assignedLearners[i]->studentID == s->studentID) {
            for (int j = i; j < learner_count - 1; j++) {
                assignedLearners[j] = assignedLearners[j + 1];
            }
            learner_count--;
            assignedLearners[learner_count] = nullptr;
            cout << s->name << " removed from " << name << "'s mentorship." << endl;
            return;
        }
    }
    cout << s->name << " is not assigned to " << name << endl;
}

void Mentor::viewLearners() {
    cout << "Mentor: " << name << "'s Learners:" << endl;
    for (int i = 0; i < learner_count; i++) {
        cout << " - " << assignedLearners[i]->name << endl;
    }
}

void Mentor::provideGuidance() {
    cout << name << " is providing guidance to mentees." << endl;
}

Student::Student(int id, string n, int a, int maxSports) : studentID(id), name(n), age(a), sports_count(0), mentorAssigned(nullptr) {
    sportsInterests = new Sport*[maxSports];
}

void Student::registerForMentorship(Mentor* m) {
    m->assignLearner(this);
    mentorAssigned = m;
    cout << name << " registered under mentor " << m->name << endl;
}

void Student::viewMentorDetails() {
    if (mentorAssigned) {
        cout << "Mentor: " << mentorAssigned->name << endl;
    } else {
        cout << "No mentor assigned." << endl;
    }
}

void Student::updateSportsInterest(Sport* sport) {
    if (sports_count < 10) {
        sportsInterests[sports_count++] = sport;
    } else {
        cout << "Max sports interests reached for " << name << endl;
    }
}

int main() {
    int numSkills, numSports, numStudents;

    cout << "Enter number of skills: ";
    cin >> numSkills;
    Skill* skills = new Skill[numSkills];

    for (int i = 0; i < numSkills; i++) {
        int id;
        string name, description;
        cout << "Enter skill ID, name, and description: ";
        cin >> id;
        cin.ignore();
        getline(cin, name);
        getline(cin, description);
        skills[i] = Skill(id, name, description);
    }

    cout << "Enter number of sports: ";
    cin >> numSports;
    Sport* sports = new Sport[numSports];

    for (int i = 0; i < numSports; i++) {
        int id;
        string name, description;
        cout << "Enter sport ID, name, and description: ";
        cin >> id;
        cin.ignore();
        getline(cin, name);
        getline(cin, description);
        sports[i] = Sport(id, name, description);

        int skillCount;
        cout << "Enter number of skills required for " << name << ": ";
        cin >> skillCount;
        for (int j = 0; j < skillCount; j++) {
            int skillID;
            cout << "Enter skill ID: ";
            cin >> skillID;
            for (int k = 0; k < numSkills; k++) {
                if (skills[k].skillID == skillID) {
                    sports[i].addSkill(&skills[k]);
                    break;
                }
            }
        }
    }

    cout << "Enter number of mentors: ";
    int numMentors;
    cin >> numMentors;
    Mentor* mentors = new Mentor[numMentors];

    for (int i = 0; i < numMentors; i++) {
        int id, maxLearners;
        string name;
        cout << "Enter mentor ID, name, and max learners: ";
        cin >> id;
        cin.ignore();
        getline(cin, name);
        cin >> maxLearners;
        mentors[i] = Mentor(id, name, &sports[0], maxLearners);
    }

    cout << "Enter number of students: ";
    cin >> numStudents;
    Student* students = new Student[numStudents];

    for (int i = 0; i < numStudents; i++) {
        int id, age, sportID;
        string name;
        cout << "Enter student ID, name, and age: ";
        cin >> id;
        cin.ignore();
        getline(cin, name);
        cin >> age;
        students[i] = Student(id, name, age, numSports);

        cout << "Enter sport ID for student: ";
        cin >> sportID;
        for (int j = 0; j < numSports; j++) {
            if (sports[j].sportID == sportID) {
                students[i].updateSportsInterest(&sports[j]);
                break;
            }
        }

        cout << "Assign mentor by ID: ";
        int mentorID;
        cin >> mentorID;
        for (int j = 0; j < numMentors; j++) {
            if (mentors[j].mentorID == mentorID) {
                students[i].registerForMentorship(&mentors[j]);
                break;
            }
        }
    }

    for (int i = 0; i < numMentors; i++) {
        mentors[i].viewLearners();
    }

    delete[] skills;
    delete[] sports;
    delete[] mentors;
    delete[] students;

    return 0;
}
