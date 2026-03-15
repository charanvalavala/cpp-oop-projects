# C++ OOP Projects Collection
This repository contains a collection of modular C++ systems built to demonstrate core Object-Oriented Programming principles, memory-safe architecture, and data persistence.

## 📂 Projects Included

### 1. [Bank Account Management System](./01-Bank-Account-System)
A C++ console app with a base Account class and SavingsAccount/CurrentAccount subclasses.

Features:
- Deposit, withdraw, interest calculation
- Operator overloading for printing
- Save/load account state to file

### 2. [Library Management System](./02-Library-Management-System)
A C++ console app where a librarian manages books and magazines, issues them to members, and handles waitlists with automatic notifications.

Features:
- Abstract base class with `Book` and `Magazine` subclasses
- Observer pattern : waitlisted members get notified when an item is returned
- Inventory display and status saved to a `.txt` file

### 3. [Shape Drawing System](./03-Shape-Factory)
A C++ console app where shapes are created from string input using a factory and drawn with their area and perimeter.

Features:
- Abstract `Shape` base class with `Circle`, `Rectangle`, and `Triangle` subclasses
- Factory pattern : creates the right shape object from a string input
- Handles case insensitive input and invalid triangle sides

## 🛠️ Tech Stack
* **Language:** C++11 / C++14
* **Core Libraries:** `<iostream>`, `<fstream>`, `<cmath>`, `<string>`, `<vector>`, `<algorithm>`
