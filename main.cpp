#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    string accountHolderName;
    int accountNumber;
    double balance;
    int pin; 
    static int totalAccounts; 

public:
    BankAccount(string name, int number, double initialBalance, int accountPIN) {
        this->accountHolderName = name;
        this->accountNumber = number;
        this->balance = initialBalance;
        this->pin = accountPIN;
        totalAccounts++; 
    }

    ~BankAccount() {
        cout << "BankAccount object for " << accountHolderName << " destroyed" << endl;
        totalAccounts--;  
    }

    static int getTotalAccounts() {
        return totalAccounts;
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

int BankAccount::totalAccounts = 0;

class ATM {
private:
    BankAccount* currentAccount;
    static int totalATMs;  

public:
    ATM() : currentAccount(nullptr) {
        totalATMs++;  
        cout << "ATM object created" << endl;
    }

    ~ATM() {
        totalATMs--;  
        cout << "ATM object destroyed" << endl;
    }

    static int getTotalATMs() {
        return totalATMs;
    }

    bool selectAccount(BankAccount* accounts[], int totalAccounts, int enteredAccountNumber, int enteredPIN) {
        for (int i = 0; i < totalAccounts; ++i) {
            if (accounts[i]->getAccountNumber() == enteredAccountNumber) {
                if (accounts[i]->validatePIN(enteredPIN)) {
                    this->currentAccount = accounts[i];
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
        if (this->currentAccount) {
            delete this->currentAccount;  
            this->currentAccount = nullptr;
            cout << "Session ended." << endl;
        } else {
            cout << "No account selected!" << endl;
        }
    }
};

int ATM::totalATMs = 0;

int main() {
    BankAccount* accounts[] = {
        new BankAccount("John Doe", 123456, 500.0, 1234),
        new BankAccount("Jane Smith", 789012, 1000.0, 5678),
        new BankAccount("Alice Johnson", 345678, 1500.0, 9012),
        new BankAccount("Michael Brown", 456789, 2000.0, 2345),
        new BankAccount("Emily Davis", 567890, 1200.0, 6789),
        new BankAccount("Chris Wilson", 678901, 750.0, 3456),
        new BankAccount("Olivia Garcia", 789012, 3000.0, 7890),
        new BankAccount("Daniel Martinez", 890123, 500.0, 1235),
        new BankAccount("Sophia Lee", 901234, 1500.0, 6781),
        new BankAccount("Ethan Harris", 123789, 2200.0, 9876),
        new BankAccount("Mia Clark", 234890, 950.0, 5432),
        new BankAccount("James Lewis", 345901, 1700.0, 6543),
        new BankAccount("Ava Robinson", 456012, 1250.0, 3210)
    };
    
    int totalAccounts = sizeof(accounts) / sizeof(accounts[0]);

    ATM* myATM = new ATM();

    int enteredAccountNumber, enteredPIN;

    cout << "Enter account number: ";
    cin >> enteredAccountNumber;
    cout << "Enter PIN: ";
    cin >> enteredPIN;

    if (myATM->selectAccount(accounts, totalAccounts, enteredAccountNumber, enteredPIN)) {
        myATM->showMenu();
    }

    cout << "Total Bank Accounts: " << BankAccount::getTotalAccounts() << endl;
    cout << "Total ATMs: " << ATM::getTotalATMs() << endl;

    delete myATM;  

    return 0;
}
