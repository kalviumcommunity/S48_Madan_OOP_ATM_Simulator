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
        accountHolderName = name;
        accountNumber = number;
        balance = initialBalance;
        pin = accountPIN;
    }

    bool validatePIN(int enteredPIN) {
        return enteredPIN == pin;
    }

    int getAccountNumber() {
        return accountNumber;
    }

    string getAccountHolderName() {
        return accountHolderName;
    }

    void deposit(double amount) {
        if (amount >= 500) {
            balance += amount;
            cout << "Deposit successful! New Balance: Rs" << balance << endl;
        } else {
            cout << "Minimum deposit amount is Rs 500!" << endl;
        }
    }

    void withdraw(double amount) {
        if (amount >= 500) {
            if (amount <= balance) {
                balance -= amount;
                cout << "Withdrawal successful! Remaining Balance: Rs" << balance << endl;
            } else {
                cout << "Insufficient funds! Available Balance: Rs" << balance << endl;
            }
        } else {
            cout << "Minimum withdrawal amount is Rs 500!" << endl;
        }
    }

    void displayAccountDetails() {
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance: Rs" << balance << endl;
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
                    currentAccount = &accounts[i];
                    cout << "Welcome, " << currentAccount->getAccountHolderName() << "!" << endl;
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
                    depositMoney(amount);
                    break;
                case 2:
                    cout << "Enter amount to withdraw: ";
                    cin >> amount;
                    withdrawMoney(amount);
                    break;
                case 3:
                    displayBalance();
                    break;
                case 4:
                    cout << "Thank you for using the ATM!" << endl;
                    clearAccount();
                    break;
                default:
                    cout << "Invalid choice! Please try again." << endl;
            }
        } while (choice != 4);
    }

    void depositMoney(double amount) {
        if (currentAccount) {
            currentAccount->deposit(amount);
        } else {
            cout << "No account selected!" << endl;
        }
    }

    void withdrawMoney(double amount) {
        if (currentAccount) {
            currentAccount->withdraw(amount);
        } else {
            cout << "No account selected!" << endl;
        }
    }

    void displayBalance() {
        if (currentAccount) {
            currentAccount->displayAccountDetails();
        } else {
            cout << "No account selected!" << endl;
        }
    }

    void clearAccount() {
        currentAccount = nullptr;
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
