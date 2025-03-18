#include <iostream>
#include <string>

using namespace std;

class Student {
private:
    int studentID;
    string name;
    double balance;
    string assignedStop;
    bool activeCard;  

public:
    Student(int id, string nm, string stop) : studentID(id), name(nm), assignedStop(stop), balance(0), activeCard(false) {}

    int getID() const { return studentID; }
    string getName() const { return name; }
    double getBalance() const { return balance; }
    string getAssignedStop() const { return assignedStop; }
    bool isCardActive() const { return activeCard; }

    void paySemesterFee(double amount) {
        if (amount >= 5000) {  
            balance += amount;
            activeCard = true;
            cout << "Payment successful! Transportation card activated for " << name << ".\n";
        } else {
            cout << "Insufficient payment. Minimum required is 5000.\n";
        }
    }

    void tapCard() {
        if (activeCard) {
            cout << "Attendance recorded for " << name << " at stop: " << assignedStop << ".\n";
        } else {
            cout << "Card inactive! Please pay your semester fee.\n";
        }
    }
};

class BusRoute {
private:
    string routeName;
    string* stops;
    int numStops;
    Student** assignedStudents;
    int studentCount;

public:
    BusRoute(string name, int stopCount) : routeName(name), numStops(stopCount), studentCount(0) {
        stops = new string[numStops];
        assignedStudents = new Student*[50];  

        cout << "Enter " << numStops << " stops for route '" << routeName << "':\n";
        for (int i = 0; i < numStops; i++) {
            cin >> stops[i];
        }
    }

    ~BusRoute() {
        delete[] stops;
        delete[] assignedStudents;
    }

    string getRouteName() const { return routeName; }

    void assignStudent(Student* student) {
        assignedStudents[studentCount++] = student;
        cout << student->getName() << " assigned to stop: " << student->getAssignedStop() << " on route: " << routeName << ".\n";
    }

    void displayRoute() const {
        cout << "Route: " << routeName << "\nStops: ";
        for (int i = 0; i < numStops; i++) {
            cout << stops[i] << " | ";
        }
        cout << "\nTotal Students Assigned: " << studentCount << "\n";
    }
};

class TransportationService {
private:
    Student** students;
    BusRoute** routes;
    int studentCount, routeCount;
    int maxStudents, maxRoutes;

public:
    TransportationService() {
        maxStudents = 10;
        maxRoutes = 5;
        studentCount = 0;
        routeCount = 0;
        
        students = new Student*[maxStudents];
        routes = new BusRoute*[maxRoutes];
    }

    ~TransportationService() {
        for (int i = 0; i < studentCount; i++) {
            delete students[i];
        }
        delete[] students;

        for (int i = 0; i < routeCount; i++) {
            delete routes[i];
        }
        delete[] routes;
    }

    void registerStudent(int id, string name, string stop) {
        if (studentCount >= maxStudents) {
            maxStudents *= 2;
            Student** temp = new Student*[maxStudents];

            for (int i = 0; i < studentCount; i++) {
                temp[i] = students[i];
            }
            delete[] students;
            students = temp;
        }

        students[studentCount++] = new Student(id, name, stop);
        cout << "Student " << name << " registered successfully!\n";
    }

    void addRoute(string name, int numStops) {
        if (routeCount >= maxRoutes) {
            maxRoutes *= 2;
            BusRoute** temp = new BusRoute*[maxRoutes];

            for (int i = 0; i < routeCount; i++) {
                temp[i] = routes[i];
            }
            delete[] routes;
            routes = temp;
        }

        routes[routeCount++] = new BusRoute(name, numStops);
        cout << "Bus route " << name << " added successfully!\n";
    }

    void assignStudentToRoute(int studentID) {
        Student* student = nullptr;
        for (int i = 0; i < studentCount; i++) {
            if (students[i]->getID() == studentID) {
                student = students[i];
                break;
            }
        }

        if (!student) {
            cout << "Student not found!\n";
            return;
        }

        for (int i = 0; i < routeCount; i++) {
            BusRoute* route = routes[i];
            route->assignStudent(student);
            return;
        }

        cout << "No available route for the student's assigned stop.\n";
    }

    void payFee(int studentID, double amount) {
        for (int i = 0; i < studentCount; i++) {
            if (students[i]->getID() == studentID) {
                students[i]->paySemesterFee(amount);
                return;
            }
        }
        cout << "Student not found!\n";
    }

    void markAttendance(int studentID) {
        for (int i = 0; i < studentCount; i++) {
            if (students[i]->getID() == studentID) {
                students[i]->tapCard();
                return;
            }
        }
        cout << "Student not found!\n";
    }

    void displayRoutes() const {
        for (int i = 0; i < routeCount; i++) {
            routes[i]->displayRoute();
            cout << "----------------------\n";
        }
    }
};

int main() {
    TransportationService system;
    int choice;

    while (true) {
        cout << "\n===== FAST Transport System =====\n";
        cout << "1. Register Student\n";
        cout << "2. Pay Semester Fee\n";
        cout << "3. Add Bus Route\n";
        cout << "4. Assign Student to Route\n";
        cout << "5. Tap Card for Attendance\n";
        cout << "6. Show All Routes\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int id;
            string name, stop;
            cout << "Enter Student ID: ";
            cin >> id;
            cout << "Enter Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Assigned Stop: ";
            cin >> stop;

            system.registerStudent(id, name, stop);
        } 
        else if (choice == 2) {
            int id;
            double amount;
            cout << "Enter Student ID: ";
            cin >> id;
            cout << "Enter Payment Amount: ";
            cin >> amount;

            system.payFee(id, amount);
        } 
        else if (choice == 3) {
            string name;
            int numStops;
            cout << "Enter Route Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Number of Stops: ";
            cin >> numStops;

            system.addRoute(name, numStops);
        } 
        else if (choice == 4) {
            int id;
            cout << "Enter Student ID: ";
            cin >> id;

            system.assignStudentToRoute(id);
        } 
        else if (choice == 5) {
            int id;
            cout << "Enter Student ID: ";
            cin >> id;

            system.markAttendance(id);
        } 
        else if (choice == 6) {
            system.displayRoutes();
        } 
        else if (choice == 7) {
            cout << "Exiting system. Thank you!\n";
            break;
        }
    }

    return 0;
}
