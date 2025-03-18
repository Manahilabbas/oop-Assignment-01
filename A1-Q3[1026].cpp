#include <iostream>
#include <string>

using namespace std;

class Vehicle {
private:
    string model;
    double rentalPrice;
    string requiredLicense; // "Learner", "Intermediate", "Full"
public:
    Vehicle(string mod, double price, string license)
        : model(mod), rentalPrice(price), requiredLicense(license) {}

    string getModel() const { return model; }
    double getPrice() const { return rentalPrice; }
    string getRequiredLicense() const { return requiredLicense; }

    void displayVehicle() const {
        cout << "Model: " << model << endl;
        cout << "Rental Price: $" << rentalPrice << " per day" << endl;
        cout << "Required License: " << requiredLicense << endl;
    }
};

class User {
private:
    string name;
    int age;
    string licenseType;
    string contact;
    int userID;
public:
    User(int id, string nm, int ag, string license, string con)
        : userID(id), name(nm), age(ag), licenseType(license), contact(con) {}

    void updateDetails(string newName, int newAge, string newLicense, string newContact) {
        name = newName;
        age = newAge;
        licenseType = newLicense;
        contact = newContact;
        cout << "User details updated successfully!\n";
    }

    string getLicenseType() const { return licenseType; }
    int getUserID() const { return userID; }

    void displayUser() const {
        cout << "User ID: " << userID << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "License: " << licenseType << endl;
        cout << "Contact: " << contact << endl;
    }
};

class RentalSystem {
private:
    User** users;
    Vehicle** vehicles;
    int userCount;
    int vehicleCount;
    int userCapacity;
    int vehicleCapacity;

    void resizeUsers() {
        userCapacity *= 2;
        User** newUsers = new User*[userCapacity];
        for (int i = 0; i < userCount; i++) {
            newUsers[i] = users[i];
        }
        delete[] users;
        users = newUsers;
    }

    void resizeVehicles() {
        vehicleCapacity *= 2;
        Vehicle** newVehicles = new Vehicle*[vehicleCapacity];
        for (int i = 0; i < vehicleCount; i++) {
            newVehicles[i] = vehicles[i];
        }
        delete[] vehicles;
        vehicles = newVehicles;
    }

public:
    RentalSystem() : userCount(0), vehicleCount(0), userCapacity(2), vehicleCapacity(2) {
        users = new User*[userCapacity];
        vehicles = new Vehicle*[vehicleCapacity];
    }

    ~RentalSystem() {
        for (int i = 0; i < userCount; i++) {
            delete users[i];
        }
        delete[] users;

        for (int i = 0; i < vehicleCount; i++) {
            delete vehicles[i];
        }
        delete[] vehicles;
    }

    void registerUser(int id, string name, int age, string license, string contact) {
        if (userCount == userCapacity) {
            resizeUsers();
        }
        users[userCount++] = new User(id, name, age, license, contact);
        cout << "User registered successfully!\n";
    }

    void updateUser(int id) {
        for (int i = 0; i < userCount; i++) {
            if (users[i]->getUserID() == id) {
                string newName, newLicense, newContact;
                int newAge;
                cout << "Enter new name: ";
                cin.ignore();
                getline(cin, newName);
                cout << "Enter new age: ";
                cin >> newAge;
                cout << "Enter new license type (Learner / Intermediate / Full): ";
                cin >> newLicense;
                cout << "Enter new contact: ";
                cin >> newContact;
                users[i]->updateDetails(newName, newAge, newLicense, newContact);
                return;
            }
        }
        cout << "User not found!\n";
    }

    void addVehicle(string model, double price, string license) {
        if (vehicleCount == vehicleCapacity) {
            resizeVehicles();
        }
        vehicles[vehicleCount++] = new Vehicle(model, price, license);
        cout << "Vehicle added successfully!\n";
    }

    void showVehicles() const {
        cout << "\nAvailable Vehicles:\n";
        for (int i = 0; i < vehicleCount; i++) {
            vehicles[i]->displayVehicle();
            cout << "----------------------\n";
        }
    }

    void rentVehicle(int userID, string model) {
        User* user = nullptr;
        for (int i = 0; i < userCount; i++) {
            if (users[i]->getUserID() == userID) {
                user = users[i];
                break;
            }
        }

        if (!user) {
            cout << "User not found!\n";
            return;
        }

        for (int i = 0; i < vehicleCount; i++) {
            if (vehicles[i]->getModel() == model) {
                if (user->getLicenseType() == vehicles[i]->getRequiredLicense() ||
                    (user->getLicenseType() == "Full" && vehicles[i]->getRequiredLicense() != "Learner")) {
                    cout << "Rental Successful! " << user->getLicenseType()
                         << " licensed user rented " << model << " for $" << vehicles[i]->getPrice() << " per day.\n";
                } else {
                    cout << "Sorry! You are not eligible to rent this vehicle.\n";
                }
                return;
            }
        }
        cout << "Vehicle not found!\n";
    }
};

int main() {
    RentalSystem system;
    int choice;

    while (true) {
        cout << "\n===== Car Rental System =====\n";
        cout << "1. Register User\n";
        cout << "2. Update User Details\n";
        cout << "3. Add Vehicle\n";
        cout << "4. Show Available Vehicles\n";
        cout << "5. Rent a Vehicle\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string name, licenseType, contact;
            int age, ID;
            cout << "Enter ID: ";
            cin >> ID;
            cout << "Enter Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Age: ";
            cin >> age;
            cout << "Enter License Type (Learner / Intermediate / Full): ";
            cin >> licenseType;
            cout << "Enter Contact: ";
            cin >> contact;

            system.registerUser(ID, name, age, licenseType, contact);
        } 
        else if (choice == 2) {
            int ID;
            cout << "Enter User ID to update: ";
            cin >> ID;
            system.updateUser(ID);
        }
        else if (choice == 3) {
            string model, requiredLicense;
            double price;
            cout << "Enter Vehicle Model: ";
            cin.ignore();
            getline(cin, model);
            cout << "Enter Rental Price per Day: ";
            cin >> price;
            cout << "Enter Required License Type (Learner / Intermediate / Full): ";
            cin >> requiredLicense;

            system.addVehicle(model, price, requiredLicense);
        } 
        else if (choice == 4) {
            system.showVehicles();
        } 
        else if (choice == 5) {
            int userID;
            string model;
            cout << "Enter User ID: ";
            cin >> userID;
            cout << "Enter Vehicle Model to Rent: ";
            cin.ignore();
            getline(cin, model);

            system.rentVehicle(userID, model);
        } 
        else if (choice == 6) {
            cout << "Exiting system. Thank you!\n";
            break;
        } 
        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
