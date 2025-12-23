#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;
//classes
// Transaction class
class Transaction {
public:
    string type; // "Deposit" or "Withdraw"
    double amount;

    Transaction(string t, double a) : type(t), amount(a) {}
};

// Account class
class Account {
private:
    int accountNumber;
    string name;
    double balance;
    vector<Transaction> history;

public:
    Account(int accNum, string n, double b = 0) : accountNumber(accNum), name(n), balance(b) {}

    int getAccountNumber() { return accountNumber; }
    string getName() { return name; }
    double getBalance() { return balance; }

    void deposit(double amount) {
        balance += amount;
        history.push_back(Transaction("Deposit", amount));
        cout << "Deposited $" << amount << ". New balance: $" << balance << endl;
    }

    void withdraw(double amount) {
        if(amount > balance) {
            cout << "Insufficient balance!\n";
            return;
        }
        balance -= amount;
        history.push_back(Transaction("Withdraw", amount));
        cout << "Withdrew $" << amount << ". New balance: $" << balance << endl;
    }

    void printTransactions() {
        cout << "Transaction History for Account #" << accountNumber << ":\n";
        cout << left << setw(15) << "Type" << setw(10) << "Amount" << endl;
        for(auto &t : history) {
            cout << left << setw(15) << t.type << setw(10) << t.amount << endl;
        }
    }

    // Save account data to file
    void saveToFile() {
        ofstream out("accounts.txt", ios::app);
        out << accountNumber << "," << name << "," << balance << "\n";
        out.close();
    }
};

// Bank   class
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
        for(auto &acc : accounts) {
            if(acc.getAccountNumber() == accNum)
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
        if(acc == nullptr) {
            cout << "Account not found!\n";
            return;
        }
        cout << "Enter amount to deposit: ";
        cin >> amount;
        acc->deposit(amount);
    }

    void withdraw() {
        int accNum;
        double amount;
        cout << "Enter account number: ";
        cin >> accNum;
        Account* acc = findAccount(accNum);
        if(acc == nullptr) {
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
        if(acc == nullptr) {
            cout << "Account not found!\n";
            return;
        }
        acc->printTransactions();
    }

    void analytics() {
        double totalDeposits = 0, totalWithdrawals = 0;
        for(auto &acc : accounts) {
            totalDeposits += acc.getBalance(); // sum of balances
        }
        cout << "Total Money in Bank: $" << totalDeposits << endl;
        cout << "Number of Accounts: " << accounts.size() << endl;
    }
};

// Main function
int main() {
    Bank bank;
    int choice;
    while(true) {
        cout << "\n=== Banking System ===\n";
        cout << "1. Create Account\n2. Deposit\n3. Withdraw\n4. Show Transactions\n5. Analytics\n6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: bank.createAccount(); break;
            case 2: bank.deposit(); break;
            case 3: bank.withdraw(); break;
            case 4: bank.showTransactions(); break;
            case 5: bank.analytics(); break;
            case 6: cout << "Exiting..."; return 0;
            default: cout << "Invalid choice!\n";
        }
    }
    return 0;
}
  