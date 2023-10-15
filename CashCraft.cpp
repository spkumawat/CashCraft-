#include <iostream>
#include <iomanip> // Include the iomanip library for formatting
#include <string>

using namespace std;

class User {
private:
    string username;

public:
    User(const string& name) : username(name) {}

    const string& getUsername() const {
        return username;
    }
};

class Account {
protected:
    int accountNumber;
    double balance;
    User user;

public:
    Account(int accNumber, double initialBalance, const string& username)
        : accountNumber(accNumber), balance(initialBalance), user(username) {}

    virtual void deposit(double amount) = 0;
    virtual void withdraw(double amount) = 0;
    virtual void display() const = 0;
    virtual void calculateInterest() {} // Virtual function for interest calculation

    virtual ~Account() {} // Virtual destructor for proper cleanup
};

class SavingsAccount : public Account {
private:
    double interestRate;

public:
    SavingsAccount(int accNumber, double initialBalance, double rate, const string& username)
        : Account(accNumber, initialBalance, username), interestRate(rate) {}

    void deposit(double amount) override {
        balance += amount;
    }

    void calculateInterest() override {
        double interest = balance * interestRate / 100;
        deposit(interest);
    }

    void withdraw(double amount) override {
        if (balance >= amount) {
            balance -= amount;
        } else {
            cout << "Insufficient balance." << endl;
        }
    }

    void display() const override {
        cout << left << setw(25) << "Username: " << setw(30) << user.getUsername() << endl;
        cout << left << setw(25) << "Account Number: " << setw(30) << accountNumber << endl;
        cout << left << setw(25) << "Current Balance (rupees): " << setw(30) << balance << endl;
    }
};

class CurrentAccount : public Account {
public:
    CurrentAccount(int accNumber, double initialBalance, const string& username)
        : Account(accNumber, initialBalance, username) {}

    void deposit(double amount) override {
        balance += amount;
    }

    void withdraw(double amount) override {
        if (balance >= amount) {
            balance -= amount;
        } else {
            cout << "Insufficient balance." << endl;
        }
    }

    void display() const override {
        cout << left << setw(25) << "Username: " << setw(30) << user.getUsername() << endl;
        cout << left << setw(25) << "Account Number: " << setw(30) << accountNumber << endl;
        cout << left << setw(25) << "Current Balance (rupees): " << setw(30) << balance << endl;
    }
};

int main() {
    int accNumber;
    double initialBalance, interestRate, withdrawalAmount = 0;
    string accountType, username;

    cout << "Enter Username: ";
    cin >> username;

    cout << "\nEnter Account Number: ";
    cin >> accNumber;

    cout << "\nEnter Initial Balance: $";
    cin >> initialBalance;

    if (initialBalance < 100) {
        cout << "Minimum initial balance required is 100 rupees." << endl;
        return 1;
    }

    cout << "\nEnter Account Type (S/C): ";
    cin >> accountType;

    Account* account;

    if (accountType == "S" || accountType == "s") {
        cout << "\nEnter Interest Rate (%): ";
        cin >> interestRate;
        account = new SavingsAccount(accNumber, initialBalance, interestRate, username);
        account->calculateInterest(); // Calculate and add interest
        cout << "\nSavings Account Details:" << endl;
        account->display(); // Display updated account information after interest calculation
    } else if (accountType == "C" || accountType == "c") {
        cout << "\nEnter Withdrawal Amount: $";
        cin >> withdrawalAmount;

        if (withdrawalAmount > initialBalance - 100) {
            cout << "Insufficient balance for withdrawal." << endl;
            return 1;
        }

        account = new CurrentAccount(accNumber, initialBalance, username);
        account->withdraw(withdrawalAmount); // Withdraw from the current account
        cout << "\nCurrent Account Details:" << endl;
        account->display(); // Display updated account information after withdrawal
    } else {
        cout << "Invalid account type." << endl;
        return 1;
    }

    delete account; // Free memory

    return 0;
}
