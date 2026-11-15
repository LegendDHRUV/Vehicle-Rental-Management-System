# 🚗 Vehicle Rental Management System

A console-based **Vehicle Rental Management System** developed using C++ and Object-Oriented Programming (OOP). The application manages vehicle records, tracks availability, processes rental and return operations, and automatically calculates rental charges with file-based data persistence.

## ✨ Features

- **Add Vehicles:** Register cars and bikes with vehicle numbers, models, and daily rental rates.
- **Display Vehicles:** View all registered vehicles and their current availability.
- **Search Vehicles:** Find vehicles using their registration numbers.
- **Rental Management:** Rent available vehicles for a specified number of days.
- **Automatic Billing:** Calculate rental charges based on vehicle category and rental duration.
- **Vehicle Returns:** Process returns and automatically restore vehicle availability.
- **Update Rental Rates:** Modify daily rental charges for available vehicles.
- **Remove Vehicles:** Delete vehicle records when they are not currently rented.
- **Input Validation:** Handle invalid inputs, duplicate vehicle numbers, unavailable vehicles, and invalid rental durations.
- **File Handling:** Save and retrieve vehicle records using `vehicles.txt`, preserving data between program executions.

## 🛠️ Technologies Used

| Technology | Purpose |
|---|---|
| C++ | Core programming language |
| STL Vector | Dynamic vehicle storage |
| File Handling | Persistent data management |
| GCC / G++ | Compilation |

## 🧠 OOP Concepts Implemented

- **Classes and Objects:** `Vehicle`, `Car`, `Bike`, and `RentalSystem`.
- **Encapsulation:** Private vehicle attributes with controlled access through public member functions.
- **Constructors:** Initialize vehicle properties and rental system objects.
- **Inheritance:** `Car` and `Bike` inherit from the base `Vehicle` class.
- **Polymorphism:** Virtual functions implement category-specific vehicle types and rental calculations.
- **Abstraction:** Common vehicle functionality is organised in a base class.

## 💰 Rental Calculation

The system calculates rental charges according to the vehicle category:

| Vehicle Category | Rental Calculation |
|---|---|
| Car | (Rent per day × Days) + ₹200 |
| Bike | (Rent per day × Days) + ₹50 |

The additional fixed amount is applied as a category-specific charge.

## ⚙️ Getting Started

### Prerequisites

- C++ compiler (GCC / G++)
- Visual Studio Code or any C++ compatible IDE
- C++11 or later

### Installation

**1. Clone the repository**

```bash
git clone https://github.com/your-username/Vehicle-Rental-Management-System.git
```

**2. Navigate to the project directory**

```bash
cd Vehicle-Rental-Management-System
```

**3. Compile the program**

```bash
g++ -std=c++11 main.cpp -o rental
```

**4. Run the application**

Windows:

```bash
rental.exe
```

Linux / macOS:

```bash
./rental
```

*Replace `main.cpp` with the actual source filename if it differs.*

## 📋 Application Menu

The application provides the following menu-driven operations:

```text
========================================
     VEHICLE RENTAL MANAGEMENT SYSTEM
========================================
1. Add Vehicle
2. Display All Vehicles
3. Display Available Vehicles
4. Search Vehicle by Number
5. Update Rent per Day
6. Remove Vehicle
7. Rent a Vehicle
8. Return a Vehicle
9. Exit
Enter your choice (1-9):
```

## 💾 Data Storage

Vehicle information is stored in `vehicles.txt` using file handling.

The stored records include:
- Vehicle category
- Registration number
- Model name
- Daily rental rate
- Rental status
- Number of rented days

The application automatically loads saved records when it starts and updates the file after vehicle management and rental operations.

## 📂 Project Structure

```text
Vehicle-Rental-Management-System/
│
├── main.cpp
├── vehicles.txt
└── README.md
```

`vehicles.txt` is generated when vehicle records are saved.

## 🎯 Project Objective

To demonstrate the practical implementation of Object-Oriented Programming concepts in C++ through a menu-driven vehicle rental application, focusing on inheritance, encapsulation, polymorphism, dynamic vehicle management, rental calculations, and file handling.

---

**Developed as an academic C++ OOP project.**

## Application Output & Screenshots

The following screenshots demonstrate the working of the Vehicle Rental Management System.

### 1. Main Menu
![Main Menu]<img width="732" height="412" alt="ss1" src="https://github.com/user-attachments/assets/de934763-55ef-4eed-8d0e-099d0cc9578e" />


### 2. Add Vehicle
![Add Vehicle]<img width="732" height="412" alt="ss1" src="https://github.com/user-attachments/assets/de934763-55ef-4eed-8d0e-099d0cc9578e" />

### 3. Display Vehicles
![Display Vehicles]<img width="584" height="347" alt="ss2" src="https://github.com/user-attachments/assets/ee5b516c-1037-48bf-a502-9d49d817aa1b" />


###  Rent Vehicle
![Rent Vehicle]<img width="488" height="399" alt="ss3" src="https://github.com/user-attachments/assets/4eb3a51a-822d-486b-a006-0fd165141418" />





