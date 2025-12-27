#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>

using namespace std;


class Transaction {
public:
    string type;
    double amount;
    time_t timestamp;

    Transaction(string t, double a) {
        type = t;
        amount = a;
        timestamp = time(nullptr);
    }
};


class Account {
private:
    int accountNumber;
    string name;
    double balance;
    vector<Transaction> history;
    void logFraud(string reason) {
    ofstream out("fraud_log.txt", ios::app);
    time_t now = time(nullptr); // Store the time in a variable first
out << accountNumber << " | " << reason << " | " << ctime(&now);
out.close();
}
   
    // Fraud detection logic
    void detectFraud(const Transaction& tx) {
    // Rule 1: Large withdrawal
    if (tx.type == "Withdraw" && tx.amount > 50000) {
        cout << "⚠️ FRAUD ALERT: Large withdrawal detected!\n";
        logFraud("Large withdrawal"); // Added this line here
    }

    // Rule 2: Multiple withdrawals within 60 seconds
    if (tx.type == "Withdraw") {
        int count = 0;
        for (auto &t : history) {
            if (t.type == "Withdraw" &&
                difftime(tx.timestamp, t.timestamp) <= 60) {
                count++;
            }
        }
        if (count >= 3) {
            cout << "⚠️ FRAUD ALERT: Multiple rapid withdrawals detected!\n";
            logFraud("Multiple rapid withdrawals"); // Added for consistency
        }
    }
}

public:
    Account(int accNum, string n, double b = 0)
        : accountNumber(accNum), name(n), balance(b) {}

    int getAccountNumber() { return accountNumber; }
    string getName() { return name; }
    double getBalance() { return balance; }

    // Deposit
    void deposit(double amount) {
        if (amount <= 0) {
            cout << "Invalid deposit amount!\n";
            return;
        }

        balance += amount;
        Transaction tx("Deposit", amount);
        history.push_back(tx);

        cout << "Deposited $" << amount
             << ". New balance: $" << balance << endl;
             ofstream out("transactions.txt", ios::app);
out << accountNumber << "," << tx.type << "," << tx.amount << "," << ctime(&tx.timestamp);
out.close();

    }

    // Withdraw
    void withdraw(double amount) {
        if (amount <= 0) {
            cout << "Invalid withdrawal amount!\n";
            return;
        }

        if (amount > balance) {
            cout << "Insufficient balance!\n";
            return;
        }

        balance -= amount;
        Transaction tx("Withdraw", amount);

        detectFraud(tx);
        history.push_back(tx);

        cout << "Withdrew $" << amount
             << ". New balance: $" << balance << endl;
             ofstream out("transactions.txt", ios::app);
out << accountNumber << "," << tx.type << "," << tx.amount << "," << ctime(&tx.timestamp);
out.close();

    }

    // Print transactions
    void printTransactions() {
        cout << "\nTransaction History for Account #" << accountNumber << "\n";
        cout << left << setw(15) << "Type"
             << setw(10) << "Amount"
             << "Time\n";

        for (auto &t : history) {
            cout << left << setw(15) << t.type
                 << setw(10) << t.amount
                 << ctime(&t.timestamp);
        }
    }

    // Save account to file
    void saveToFile() {
        ofstream out("accounts.txt", ios::app);
        out << accountNumber << "," << name << "," << balance << "\n";
        out.close();
    }
};


class Bank {
private:
    vector<Account> accounts;

public:
    void createAccount() {
        int accNum;
        string name;

        cout << "Enter account number: ";
        cin >> accNum;
        cin.ignore();

        cout << "Enter name: ";
        getline(cin, name);

        Account acc(accNum, name);
        accounts.push_back(acc);
        acc.saveToFile();

        cout << "Account created successfully!\n";
    }

    Account* findAccount(int accNum) {
        for (auto &acc : accounts) {
            if (acc.getAccountNumber() == accNum)
                return &acc;
        }
        return nullptr;
    }

    void deposit() {
        int accNum;
        double amount;

        cout << "Enter account number: ";
        cin >> accNum;

        Account* acc = findAccount(accNum);
        if (acc == nullptr) {
            cout << "Account not found!\n";
            return;
        }

        cout << "Enter amount to deposit: ";
        cin >> amount;

        if (cin.fail() || amount <= 0) {
            cout << "Invalid amount!\n";
            cin.clear();
            cin.ignore(1000, '\n');
            return;
        }

        acc->deposit(amount);
    }

    void withdraw() {
        int accNum;
        double amount;

        cout << "Enter account number: ";
        cin >> accNum;

        Account* acc = findAccount(accNum);
        if (acc == nullptr) {
            cout << "Account not found!\n";
            return;
        }

        cout << "Enter amount to withdraw: ";
        cin >> amount;

        acc->withdraw(amount);
    }

    void showTransactions() {
        int accNum;
        cout << "Enter account number: ";
        cin >> accNum;

        Account* acc = findAccount(accNum);
        if (acc == nullptr) {
            cout << "Account not found!\n";
            return;
        }

        acc->printTransactions();
    }

    void analytics() {
        double totalMoney = 0;
        for (auto &acc : accounts) {
            totalMoney += acc.getBalance();
        }

        cout << "\n--- Bank Analytics ---\n";
        cout << "Total Money in Bank: $" << totalMoney << endl;
        cout << "Number of Accounts: " << accounts.size() << endl;
    }
};


int main() {
    Bank bank;
    int choice;

    while (true) {
        cout << "\n=== Banking System ===\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Show Transactions\n";
        cout << "5. Analytics\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: bank.createAccount(); break;
            case 2: bank.deposit(); break;
            case 3: bank.withdraw(); break;
            case 4: bank.showTransactions(); break;
            case 5: bank.analytics(); break;
            case 6: cout << "Exiting...\n"; return 0;
            default: cout << "Invalid choice!\n";
        }
    }
}
