#include <iostream>
#include <string>
using namespace std;

class BankAccount {
protected:
    string accountHolderName;
    int accountNumber;
    double balance;
    int pin;
    static int totalAccounts;

public:
    BankAccount() {
        accountHolderName = "Unknown";
        accountNumber = 0;
        balance = 0.0;
        pin = 0000;
        totalAccounts++;
    }

    BankAccount(string name, int number, double initialBalance, int accountPIN) {
        setAccountHolderName(name);
        setAccountNumber(number);
        setBalance(initialBalance);
        setPIN(accountPIN);
        totalAccounts++;
    }

    ~BankAccount() {
        totalAccounts--;
    }

    static int getTotalAccounts() {
        return totalAccounts;
    }

    void setAccountHolderName(string name) {
        this->accountHolderName = name;
    }

    void setAccountNumber(int number) {
        this->accountNumber = number;
    }

    void setBalance(double balance) {
        this->balance = balance;
    }

    void setPIN(int pin) {
        this->pin = pin;
    }

    string getAccountHolderName() const {
        return this->accountHolderName;
    }

    int getAccountNumber() const {
        return this->accountNumber;
    }

    double getBalance() const {
        return this->balance;
    }

    int getPIN() const {
        return this->pin;
    }

    bool validatePIN(int enteredPIN) const {
        return this->pin == enteredPIN;
    }


    void deposit(double amount) { 
        if (amount >= 500) { 
            setBalance(getBalance() + amount); 
            cout<< "Deposit successful! New Balance: Rs" << getBalance() <<endl; 
        } else { 
            cout<< "Minimum deposit amount is Rs 500!" <<endl; 
        }
    }

    void deposit(double amount, string message) {
        cout << message << endl;
        deposit(amount); 
    }

    void withdraw(double amount) {
        if (amount >= 500) {
            if (amount <= getBalance()) {
                setBalance(getBalance() - amount);
                cout << "Withdrawal successful! Remaining Balance: Rs" << getBalance() << endl;
            } else {
                cout << "Insufficient funds! Available Balance: Rs" << getBalance() << endl;
            }
        } else {
            cout << "Minimum withdrawal amount is Rs 500!" << endl;
        }
    }

    void displayAccountDetails() const {
        cout << "Account Holder: " << getAccountHolderName() << endl;
        cout << "Account Number: " << getAccountNumber() << endl;
        cout << "Balance: Rs" << getBalance() << endl;
    }
};

int BankAccount::totalAccounts = 0;

class SavingsAccount : public BankAccount {
private:
    double interestRate;

public:
    SavingsAccount(string name, int number, double initialBalance, int accountPIN, double rate)
        : BankAccount(name, number, initialBalance, accountPIN), interestRate(rate) {}

    void addInterest() {
        double interest = getBalance() * interestRate / 100;
        deposit(interest, "Interest added to your savings account");
    }
};

class CurrentAccount : public BankAccount {
private:
    double transactionLimit;

public:
    CurrentAccount(string name, int number, double initialBalance, int accountPIN, double limit)
        : BankAccount(name, number, initialBalance, accountPIN), transactionLimit(limit) {}

    void withdraw(double amount) {
        if (amount > transactionLimit) {
            cout << "Transaction limit exceeded! Maximum allowable: Rs" << transactionLimit << endl;
        } else {
            BankAccount::withdraw(amount);  
        }
    }
};

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

    void setCurrentAccount(BankAccount* account) {
        this->currentAccount = account;
    }

    BankAccount* getCurrentAccount() const {
        return this->currentAccount;
    }

    bool selectAccount(BankAccount* accounts[], int totalAccounts, int enteredAccountNumber, int enteredPIN) {
        for (int i = 0; i < totalAccounts; ++i) {
            if (accounts[i]->getAccountNumber() == enteredAccountNumber) {
                if (accounts[i]->validatePIN(enteredPIN)) {
                    setCurrentAccount(accounts[i]);
                    cout << "Welcome, " << getCurrentAccount()->getAccountHolderName() << "!" << endl;
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
        if (getCurrentAccount()) {
            getCurrentAccount()->deposit(amount, "Depositing to your account");
        } else {
            cout << "No account selected!" << endl;
        }
    }

    void withdrawMoney(double amount) {
        if (getCurrentAccount()) {
            getCurrentAccount()->withdraw(amount);
        } else {
            cout << "No account selected!" << endl;
        }
    }

    void displayBalance() {
        if (getCurrentAccount()) {
            getCurrentAccount()->displayAccountDetails();
        } else {
            cout << "No account selected!" << endl;
        }
    }

    void clearAccount() {
        if (getCurrentAccount()) {
            setCurrentAccount(nullptr);
            cout << "Session ended." << endl;
        } else {
            cout << "No account selected!" << endl;
        }
    }
};

int ATM::totalATMs = 0;

int main() {
    BankAccount* accounts[] = {
        new BankAccount("John Doe", 123456, 5000.0, 1234),
        new SavingsAccount("Jane Smith", 789012, 1000.0, 5678, 3.5),
        new CurrentAccount("Alice Johnson", 345678, 2000.0, 9012, 10000.0),
        new BankAccount("David Lee", 111222, 2500.0, 4321),
        new SavingsAccount("Emily Clark", 333444, 8000.0, 8765, 2.0),
        new CurrentAccount("Michael Brown", 555666, 5000.0, 2468, 15000.0),
        new BankAccount("Sophia Miller", 777888, 4500.0, 1357),
        new SavingsAccount("Oliver Davis", 999000, 1200.0, 9876, 4.0),
        new CurrentAccount("Charlotte Wilson", 101112, 3000.0, 1212, 20000.0),
        new BankAccount("Henry Moore", 131415, 6000.0, 3434),
        new SavingsAccount("Amelia Taylor", 161718, 7500.0, 5656, 3.5),
        new CurrentAccount("James Anderson", 192021, 5000.0, 7878, 12000.0),
        new BankAccount("Liam Thomas", 222324, 3500.0, 9090)
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

    for (int i = 0; i < totalAccounts; ++i) {
        delete accounts[i];
    }

    return 0;
}