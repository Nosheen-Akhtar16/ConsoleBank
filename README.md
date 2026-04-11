🏦 Banking System with Fraud Detection (C++)

📌 Overview
This is a console-based Banking System developed in C++ that simulates basic banking operations such as account creation, deposit, withdrawal, and transaction tracking.
The system also includes a fraud detection mechanism to identify suspicious activities like large withdrawals and rapid transactions.

🚀 Features
🔹 Core Banking Features
   Create new bank accounts
   Deposit money
   Withdraw money
   View transaction history
   Bank analytics (total money & number of accounts)
   
🔹 Fraud Detection System
  ⚠️ Detects large withdrawals (> ₹50,000)
  ⚠️ Detects multiple withdrawals within 60 seconds
  Logs suspicious activities in a file (fraud_log.txt)
  
🔹 File Handling
   Stores account details in accounts.txt
   Stores transactions in transactions.txt
   Logs fraud alerts in fraud_log.txt
   
🛠️ Technologies Used
Language: C++
Concepts Used:
Object-Oriented Programming (OOP)
File Handling (fstream)
STL (vector)
Time handling (ctime)
Input validation

📂 Project Structure
Banking-System/
│
├── project.cpp
├── accounts.txt
├── transactions.txt
├── fraud_log.txt
└── README.md

⚙️ How It Works
1. Account Creation
User enters account number and name
Account is stored in memory and saved to file
2. Deposit
Adds money to balance
Logs transaction
3. Withdraw
Checks balance
Applies fraud detection rules
Logs transaction
4. Fraud Detection Logic
If withdrawal > 50000 → 🚨 Alert
If ≥3 withdrawals within 60 seconds → 🚨 Alert

▶️ How to Run
Step 1: Compile
g++ main.cpp -o bank
Step 2: Run
./bank

🖥️ Sample Menu
=== Banking System ===
1. Create Account
2. Deposit
3. Withdraw
4. Show Transactions
5. Analytics
6. Exit
📊 Example Output
Deposited $1000. New balance: $1000
Withdrew $60000. New balance: $40000
⚠️ FRAUD ALERT: Large withdrawal detected!

🔍 Key Learning Outcomes
Practical use of OOP in real-world systems
Implementation of basic fraud detection logic
Working with file persistence
Managing transaction history

🚧 Future Improvements
Add login/authentication system
GUI version (using Qt / Web App)
Database integration (MySQL)
More advanced fraud detection (ML-based)
Multi-user support
