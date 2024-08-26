#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    string accountHolderName;
    int accountNumber;
    double balance;
    int pin; 

public:
    BankAccount(string name, int number, double initialBalance, int accountPIN) {
        this->accountHolderName = name;
        this->accountNumber = number;
        this->balance = initialBalance;
        this->pin = accountPIN;
    }

    bool validatePIN(int enteredPIN) {
        return this->pin == enteredPIN;
    }

    int getAccountNumber() {
        return this->accountNumber;
    }

    string getAccountHolderName() {
        return this->accountHolderName;
    }

    void deposit(double amount) {
        if (amount >= 500) {
            this->balance += amount;
            cout << "Deposit successful! New Balance: Rs" << this->balance << endl;
        } else {
            cout << "Minimum deposit amount is Rs 500!" << endl;
        }
    }

    void withdraw(double amount) {
        if (amount >= 500) {
            if (amount <= this->balance) {
                this->balance -= amount;
                cout << "Withdrawal successful! Remaining Balance: Rs" << this->balance << endl;
            } else {
                cout << "Insufficient funds! Available Balance: Rs" << this->balance << endl;
            }
        } else {
            cout << "Minimum withdrawal amount is Rs 500!" << endl;
        }
    }

    void displayAccountDetails() {
        cout << "Account Holder: " << this->accountHolderName << endl;
        cout << "Account Number: " << this->accountNumber << endl;
        cout << "Balance: Rs" << this->balance << endl;
    }
};

class ATM {
private:
    BankAccount* currentAccount;

public:
    bool selectAccount(BankAccount accounts[], int totalAccounts, int enteredAccountNumber, int enteredPIN) {
        for (int i = 0; i < totalAccounts; ++i) {
            if (accounts[i].getAccountNumber() == enteredAccountNumber) {
                if (accounts[i].validatePIN(enteredPIN)) {
                    this->currentAccount = &accounts[i];
                    cout << "Welcome, " << this->currentAccount->getAccountHolderName() << "!" << endl;
                    return true;
                } else {
                    cout << "Invalid PIN! Access denied." << endl;
                    return false;
                }
            }
        }
        cout << "Account number not found!" << endl;
        return false;
    }

    void showMenu() {
        int choice;
        double amount;
        do {
            cout << "\nWhat would you like to do?\n";
            cout << "1. Deposit Money\n";
            cout << "2. Withdraw Money\n";
            cout << "3. Check Balance\n";
            cout << "4. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    cout << "Enter amount to deposit: ";
                    cin >> amount;
                    this->depositMoney(amount);
                    break;
                case 2:
                    cout << "Enter amount to withdraw: ";
                    cin >> amount;
                    this->withdrawMoney(amount);
                    break;
                case 3:
                    this->displayBalance();
                    break;
                case 4:
                    cout << "Thank you for using the ATM!" << endl;
                    this->clearAccount();
                    break;
                default:
                    cout << "Invalid choice! Please try again." << endl;
            }
        } while (choice != 4);
    }

    void depositMoney(double amount) {
        if (this->currentAccount) {
            this->currentAccount->deposit(amount);
        } else {
            cout << "No account selected!" << endl;
        }
    }

    void withdrawMoney(double amount) {
        if (this->currentAccount) {
            this->currentAccount->withdraw(amount);
        } else {
            cout << "No account selected!" << endl;
        }
    }

    void displayBalance() {
        if (this->currentAccount) {
            this->currentAccount->displayAccountDetails();
        } else {
            cout << "No account selected!" << endl;
        }
    }

    void clearAccount() {
        this->currentAccount = nullptr;
        cout << "Session ended. Thank you for using the ATM!" << endl;
    }
};

int main() {
    BankAccount accounts[] = {
        BankAccount("John Doe", 123456, 500.0, 1234),
        BankAccount("Jane Smith", 789012, 1000.0, 5678),
        BankAccount("Alice Johnson", 345678, 1500.0, 9012)
    };
    int totalAccounts = sizeof(accounts) / sizeof(accounts[0]);

    ATM myATM;

    int enteredAccountNumber, enteredPIN;

    cout << "Enter account number: ";
    cin >> enteredAccountNumber;
    cout << "Enter PIN: ";
    cin >> enteredPIN;

    if (myATM.selectAccount(accounts, totalAccounts, enteredAccountNumber, enteredPIN)) {
        myATM.showMenu(); 
    }

    return 0;
}
