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
    BankAccount() : accountHolderName("Unknown"), accountNumber(0), balance(0.0), pin(0000) {
        totalAccounts++;
    }

    BankAccount(string name, int number, double initialBalance, int accountPIN) 
        : accountHolderName(name), accountNumber(number), balance(initialBalance), pin(accountPIN) {
        totalAccounts++;
    }

    virtual ~BankAccount() { totalAccounts--; }

    static int getTotalAccounts() { return totalAccounts; }

    void setAccountHolderName(string name) { accountHolderName = name; }
    void setAccountNumber(int number) { accountNumber = number; }
    void setBalance(double bal) { balance = bal; }
    void setPIN(int accountPIN) { pin = accountPIN; }

    string getAccountHolderName() const { return accountHolderName; }
    int getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }
    int getPIN() const { return pin; }

    bool validatePIN(int enteredPIN) const { return pin == enteredPIN; }

    virtual void deposit(double amount, string message = "") {
        if (!message.empty()) cout << message << endl;
        if (amount >= 1000) {
            balance += amount;
            cout << "Deposit successful! New Balance: Rs" << balance << endl;
        } else {
            cout << "Minimum deposit amount is Rs 1000!" << endl;
        }
    }

    virtual void withdraw(double amount) {
        if (amount >= 500 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawal successful! Remaining Balance: Rs" << balance << endl;
        } else if (amount < 500) {
            cout << "Minimum withdrawal amount is Rs 500!" << endl;
        } else {
            cout << "Insufficient funds! Available Balance: Rs" << balance << endl;
        }
    }

    void displayAccountDetails() const {
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance: Rs" << balance << endl;
    }

    virtual string accountType() const = 0; 
    
};

int BankAccount::totalAccounts = 0;

class SavingsAccount : public BankAccount {
private:
    double interestRate;

public:
    SavingsAccount(string name, int number, double initialBalance, int accountPIN, double rate)
        : BankAccount(name, number, initialBalance, accountPIN), interestRate(rate) {}

    void addInterest() {
        double interest = balance * interestRate / 100;
        deposit(interest, "Interest added to your savings account");
    }

    string accountType() const override { return "Savings Account"; }
};

class CurrentAccount : public BankAccount {
private:
    double transactionLimit;

public:
    CurrentAccount(string name, int number, double initialBalance, int accountPIN, double limit)
        : BankAccount(name, number, initialBalance, accountPIN), transactionLimit(limit) {}

    void withdraw(double amount) override {
        if (amount > transactionLimit) {
            cout << "Transaction limit exceeded! Maximum allowable: Rs" << transactionLimit << endl;
        } else {
            BankAccount::withdraw(amount);
        }
    }

    string accountType() const override { return "Current Account"; }
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

    static int getTotalATMs() { return totalATMs; }

    void setCurrentAccount(BankAccount* account) { currentAccount = account; }

    BankAccount* getCurrentAccount() const { return currentAccount; }

    bool selectAccount(BankAccount* accounts[], int totalAccounts, int enteredAccountNumber, int enteredPIN) {
        for (int i = 0; i < totalAccounts; ++i) {
            if (accounts[i]->getAccountNumber() == enteredAccountNumber) {
                if (accounts[i]->validatePIN(enteredPIN)) {
                    setCurrentAccount(accounts[i]);
                    cout << "Welcome, " << currentAccount->getAccountHolderName() << " (" << currentAccount->accountType() << ")!" << endl;
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
            currentAccount->deposit(amount, "Depositing to your account");
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
        if (currentAccount) {
            currentAccount = nullptr;
            cout << "Session ended." << endl;
        } else {
            cout << "No account selected!" << endl;
        }
    }
};

int ATM::totalATMs = 0;

int main() {
    BankAccount* accounts[] = {
        new SavingsAccount("John Doe", 123456, 5000.0, 1234, 3.5),
        new CurrentAccount("Alice Johnson", 345678, 2000.0, 9012, 10000.0),
        new SavingsAccount("Emily Roberts", 987654, 3000.0, 5678, 4.0),
        new SavingsAccount("Michael Smith", 234567, 1500.0, 8765, 3.0),
        new CurrentAccount("Sarah Wilson", 345679, 8000.0, 5432, 5000.0),
        new CurrentAccount("David Johnson", 456780, 7000.0, 6789, 15000.0),
        new SavingsAccount("Jessica Brown", 567890, 12000.0, 3456, 5.0),
        new SavingsAccount("James Taylor", 678901, 4500.0, 2345, 2.5),
        new CurrentAccount("Linda Green", 789012, 2500.0, 1235, 20000.0),
        new CurrentAccount("Robert White", 890123, 3000.0, 3457, 10000.0),
        new SavingsAccount("Patricia Harris", 901234, 6000.0, 5678, 3.8),
        new CurrentAccount("William Thompson", 112233, 9500.0, 6789, 12000.0)

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