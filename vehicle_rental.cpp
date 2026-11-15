#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <cctype>
using namespace std;

string toUpperCase(string text) {
    for (size_t i = 0; i < text.length(); i++) {
        text[i] = toupper(text[i]);
    }
    return text;
}

int readInt(string message) {
    int value;
    cout << message;
    while (!(cin >> value)) {
        cout << "Invalid input. Please enter a number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

double readDouble(string message) {
    double value;
    cout << message;
    while (!(cin >> value)) {
        cout << "Invalid input. Please enter a number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

string readText(string message) {
    string text;
    while (true) {
        cout << message;
        getline(cin, text);
        if (text.empty()) {
            cout << "Input cannot be empty. Try again.\n";
        } else if (text.find(',') != string::npos) {
            cout << "Comma is not allowed. Try again.\n";
        } else {
            return text;
        }
    }
}

class Vehicle {
private:
    string vehicleNumber;
    string model;
    double rentPerDay;
    bool rented;
    int rentedDays;

public:
    Vehicle(string number, string modelName, double rent,
            bool isRented = false, int days = 0) {
        vehicleNumber = number;
        model = modelName;
        rentPerDay = rent;
        rented = isRented;
        rentedDays = days;
    }

    virtual ~Vehicle() {}

    string getNumber() const { return vehicleNumber; }
    string getModel() const { return model; }
    double getRentPerDay() const { return rentPerDay; }
    bool isRented() const { return rented; }
    int getRentedDays() const { return rentedDays; }

    void setRentPerDay(double rent) { rentPerDay = rent; }

    void rentOut(int days) {
        rented = true;
        rentedDays = days;
    }

    void giveBack() {
        rented = false;
        rentedDays = 0;
    }

    virtual string getType() const { return "Vehicle"; }

    virtual double calculateRent(int days) const {
        return rentPerDay * days;
    }

    void display() const {
        cout << left << setw(8) << getType()
             << setw(16) << vehicleNumber
             << setw(18) << model
             << setw(12) << fixed << setprecision(2) << rentPerDay
             << (rented ? "Rented" : "Available") << endl;
    }
};

class Car : public Vehicle {
public:
    Car(string number, string modelName, double rent,
        bool isRented = false, int days = 0)
        : Vehicle(number, modelName, rent, isRented, days) {}

    string getType() const { return "Car"; }

    double calculateRent(int days) const {
        return getRentPerDay() * days + 200;
    }
};

class Bike : public Vehicle {
public:
    Bike(string number, string modelName, double rent,
         bool isRented = false, int days = 0)
        : Vehicle(number, modelName, rent, isRented, days) {}

    string getType() const { return "Bike"; }

    double calculateRent(int days) const {
        return getRentPerDay() * days + 50;
    }
};

class RentalSystem {
private:
    typedef vector<Vehicle*>::iterator VehicleIterator;

    vector<Vehicle*> vehicles;
    string fileName;

    VehicleIterator findVehicle(string number) {
        number = toUpperCase(number);
        for (VehicleIterator it = vehicles.begin(); it != vehicles.end(); ++it) {
            if ((*it)->getNumber() == number) {
                return it;
            }
        }
        return vehicles.end();
    }

    void printTableHeader() {
        cout << left << setw(8) << "Type"
             << setw(16) << "Vehicle No."
             << setw(18) << "Model"
             << setw(12) << "Rent/Day"
             << "Status" << endl;
        cout << string(62, '-') << endl;
    }

    void saveToFile() {
        ofstream file(fileName.c_str());
        if (!file) {
            cout << "Error: could not save data to file.\n";
            return;
        }
        for (VehicleIterator it = vehicles.begin(); it != vehicles.end(); ++it) {
            file << (*it)->getType() << ","
                 << (*it)->getNumber() << ","
                 << (*it)->getModel() << ","
                 << (*it)->getRentPerDay() << ","
                 << (*it)->isRented() << ","
                 << (*it)->getRentedDays() << "\n";
        }
        file.close();
    }

    void loadFromFile() {
        ifstream file(fileName.c_str());
        if (!file) {
            cout << "No saved data found. Starting with an empty list.\n";
            return;
        }

        string type, number, modelName, rentText, rentedText, daysText;
        while (getline(file, type, ',')) {
            getline(file, number, ',');
            getline(file, modelName, ',');
            getline(file, rentText, ',');
            getline(file, rentedText, ',');
            getline(file, daysText);

            try {
                double rent = stod(rentText);
                bool isRented = (stoi(rentedText) == 1);
                int days = stoi(daysText);

                if (type == "Car") {
                    vehicles.push_back(new Car(number, modelName, rent, isRented, days));
                } else if (type == "Bike") {
                    vehicles.push_back(new Bike(number, modelName, rent, isRented, days));
                }
            } catch (...) {
                cout << "Warning: one damaged record in the file was skipped.\n";
            }
        }
        file.close();

        if (vehicles.empty()) {
            cout << "Data file is empty. Starting with an empty list.\n";
        }
    }

public:
    RentalSystem(string file) {
        fileName = file;
        loadFromFile();
    }

    ~RentalSystem() {
        for (VehicleIterator it = vehicles.begin(); it != vehicles.end(); ++it) {
            delete *it;
        }
    }

    void addVehicle() {
        cout << "\n--- Add New Vehicle ---\n";
        int choice = readInt("Vehicle type (1 = Car, 2 = Bike): ");
        if (choice != 1 && choice != 2) {
            cout << "Invalid type. Vehicle not added.\n";
            return;
        }

        string number = toUpperCase(readText("Enter vehicle number: "));
        if (findVehicle(number) != vehicles.end()) {
            cout << "A vehicle with this number already exists.\n";
            return;
        }

        string modelName = readText("Enter model name: ");
        double rent = readDouble("Enter rent per day (Rs.): ");
        if (rent <= 0) {
            cout << "Rent must be greater than 0. Vehicle not added.\n";
            return;
        }

        if (choice == 1) {
            vehicles.push_back(new Car(number, modelName, rent));
        } else {
            vehicles.push_back(new Bike(number, modelName, rent));
        }
        saveToFile();
        cout << "Vehicle added successfully.\n";
    }

    void displayAll() {
        cout << "\n--- All Vehicles ---\n";
        if (vehicles.empty()) {
            cout << "No vehicles in the system.\n";
            return;
        }
        printTableHeader();
        for (VehicleIterator it = vehicles.begin(); it != vehicles.end(); ++it) {
            (*it)->display();
        }
    }

    void displayAvailable() {
        cout << "\n--- Available Vehicles ---\n";
        bool found = false;
        for (VehicleIterator it = vehicles.begin(); it != vehicles.end(); ++it) {
            if (!(*it)->isRented()) {
                if (!found) {
                    printTableHeader();
                    found = true;
                }
                (*it)->display();
            }
        }
        if (!found) {
            cout << "No vehicle is available right now.\n";
        }
    }

    void searchVehicle() {
        cout << "\n--- Search Vehicle ---\n";
        string number = readText("Enter vehicle number to search: ");
        VehicleIterator it = findVehicle(number);
        if (it == vehicles.end()) {
            cout << "Vehicle not found.\n";
        } else {
            printTableHeader();
            (*it)->display();
        }
    }

    void updateRent() {
        cout << "\n--- Update Rent per Day ---\n";
        string number = readText("Enter vehicle number: ");
        VehicleIterator it = findVehicle(number);
        if (it == vehicles.end()) {
            cout << "Vehicle not found.\n";
            return;
        }
        if ((*it)->isRented()) {
            cout << "Rent cannot be changed while the vehicle is rented.\n";
            return;
        }

        double rent = readDouble("Enter new rent per day (Rs.): ");
        if (rent <= 0) {
            cout << "Rent must be greater than 0. No change made.\n";
            return;
        }
        (*it)->setRentPerDay(rent);
        saveToFile();
        cout << "Rent updated successfully.\n";
    }

    void removeVehicle() {
        cout << "\n--- Remove Vehicle ---\n";
        string number = readText("Enter vehicle number to remove: ");
        VehicleIterator it = findVehicle(number);
        if (it == vehicles.end()) {
            cout << "Vehicle not found.\n";
            return;
        }
        if ((*it)->isRented()) {
            cout << "A rented vehicle cannot be removed.\n";
            return;
        }

        delete *it;
        vehicles.erase(it);
        saveToFile();
        cout << "Vehicle removed successfully.\n";
    }

    void rentVehicle() {
        cout << "\n--- Rent a Vehicle ---\n";
        string number = readText("Enter vehicle number to rent: ");
        VehicleIterator it = findVehicle(number);
        if (it == vehicles.end()) {
            cout << "Vehicle not found.\n";
            return;
        }
        if ((*it)->isRented()) {
            cout << "Sorry, this vehicle is already rented.\n";
            return;
        }

        int days = readInt("Enter number of rental days: ");
        if (days <= 0) {
            cout << "Invalid number of days. Rental cancelled.\n";
            return;
        }

        (*it)->rentOut(days);
        saveToFile();

        double amount = (*it)->calculateRent(days);
        cout << "\nVehicle rented successfully!\n";
        cout << "Vehicle : " << (*it)->getType() << " - " << (*it)->getModel() << endl;
        cout << "Days    : " << days << endl;
        cout << "Rental amount : Rs. " << fixed << setprecision(2) << amount << endl;
    }

    void returnVehicle() {
        cout << "\n--- Return a Vehicle ---\n";
        string number = readText("Enter vehicle number to return: ");
        VehicleIterator it = findVehicle(number);
        if (it == vehicles.end()) {
            cout << "Vehicle not found.\n";
            return;
        }
        if (!(*it)->isRented()) {
            cout << "This vehicle is not rented. Nothing to return.\n";
            return;
        }

        int days = (*it)->getRentedDays();
        double amount = (*it)->calculateRent(days);
        cout << "Vehicle returned. Final bill for " << days
             << " day(s): Rs. " << fixed << setprecision(2) << amount << endl;

        (*it)->giveBack();
        saveToFile();
        cout << "Vehicle is now available for rent.\n";
    }
};

int main() {
    RentalSystem system("vehicles.txt");
    int choice;

    do {
        cout << "\n========================================\n";
        cout << "     VEHICLE RENTAL MANAGEMENT SYSTEM\n";
        cout << "========================================\n";
        cout << "1. Add Vehicle\n";
        cout << "2. Display All Vehicles\n";
        cout << "3. Display Available Vehicles\n";
        cout << "4. Search Vehicle by Number\n";
        cout << "5. Update Rent per Day\n";
        cout << "6. Remove Vehicle\n";
        cout << "7. Rent a Vehicle\n";
        cout << "8. Return a Vehicle\n";
        cout << "9. Exit\n";
        choice = readInt("Enter your choice (1-9): ");

        switch (choice) {
            case 1: system.addVehicle(); break;
            case 2: system.displayAll(); break;
            case 3: system.displayAvailable(); break;
            case 4: system.searchVehicle(); break;
            case 5: system.updateRent(); break;
            case 6: system.removeVehicle(); break;
            case 7: system.rentVehicle(); break;
            case 8: system.returnVehicle(); break;
            case 9: cout << "Data saved. Thank you!\n"; break;
            default: cout << "Invalid choice. Please enter 1 to 9.\n";
        }
    } while (choice != 9);

    return 0;
}