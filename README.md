# 🏦 EMA Bank Management System (C++)

A simple **Bank Management System** built using **C++** and **File Handling**.  
The project simulates basic banking operations such as managing clients, handling transactions, and storing data persistently in files.

---

## 📌 Features

### 🔹 Client Management
- Add new clients
- Update existing client information
- Delete clients
- Find client by account number
- Display all clients in a formatted table

### 🔹 Transactions
- Deposit money to a client account
- Calculate and display total balances of all clients

### 🔹 Data Persistence
- All data is stored in a text file (`ClientsData.txt`)
- Uses file handling to load and save clients automatically

---

## 🧱 Project Structure

- **Struct**
  - `sClient`  
    Holds client data such as account number, pin code, name, phone, and balance.

- **Core Functionalities**
  - File handling (Load / Save)
  - CRUD operations
  - Transaction operations
  - Menu-driven system

---

## 🛠 Technologies Used

- Language: **C++**
- Concepts:
  - File Handling (`fstream`)
  - Vectors
  - Structs
  - Functions
  - Enums
  - Console UI formatting (`iomanip`)

---

## 📂 Data Format

Clients are stored in the file using the following format: AccountNumber#//#PinCode#//#Name#//#Phone#//#Balance

