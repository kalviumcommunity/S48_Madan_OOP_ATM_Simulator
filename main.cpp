#include <iostream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

class TransactionLogger {
private:
    vector<string> logs;

public:
    void logTransaction(const string& log) {
        logs.push_back(log);
    }

    void displayLogs() const {
        if (logs.empty()) {
            cout << "No transactions yet!" << endl;
        } else {
            cout << "Transaction History:" << endl;
            for (const auto& log : logs) {
                cout << "- " << log << endl;
            }
        }
    }
};

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

class PremiumSavingsAccount : public SavingsAccount {
private:
    double rewardAmount;

public:
    PremiumSavingsAccount(string name, int number, double initialBalance, int accountPIN, double rate, double reward)
        : SavingsAccount(name, number, initialBalance, accountPIN, rate), rewardAmount(reward) {}

    void deposit(double amount, string message = "") override {
        SavingsAccount::deposit(amount, message);
        if (amount > 5000) {
            balance += rewardAmount;
            cout << "Congratulations! You received a reward of Rs" << rewardAmount << " for depositing more than Rs5000!" << endl;
        }
    }

    string accountType() const override { return "Premium Savings Account"; }
};

class ATM {
private:
    BankAccount* currentAccount;
    TransactionLogger logger; 
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
            cout << "4. Show Transaction History\n";
            cout << "5. Exit\n";
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
                    displayTransactionHistory();
                    break;
                case 5:
                    cout << "Thank you for using the ATM!" << endl;
                    clearAccount();
                    break;
                default:
                    cout << "Invalid choice! Please try again." << endl;
            }
        } while (choice != 5);
    }

    void depositMoney(double amount) {
        if (currentAccount) {
            string message = "Depositing to your account";
            currentAccount->deposit(amount, message);
            logger.logTransaction("Deposited Rs" + to_string(amount));
        } else {
            cout << "No account selected!" << endl;
        }
    }

    void withdrawMoney(double amount) {
        if (currentAccount) {
            currentAccount->withdraw(amount);
            logger.logTransaction("Withdrew Rs" + to_string(amount));
        } else {
            cout << "No account selected!" << endl;
        }
    }

    void displayBalance() {
        if (currentAccount) {
            currentAccount->displayAccountDetails();
            logger.logTransaction("Checked balance");
        } else {
            cout << "No account selected!" << endl;
        }
    }

    void displayTransactionHistory() {
        logger.displayLogs();
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
        new PremiumSavingsAccount("Sophia Brown", 456789, 10000.0, 3456, 4.0, 500.0),
        new SavingsAccount("Michael Smith", 234567, 1500.0, 8765, 3.0),
        new CurrentAccount("Sarah Wilson", 345679, 8000.0, 5432, 5000.0),
        new SavingsAccount("Emma Watson", 789012, 3000.0, 6789, 2.5),
        new CurrentAccount("James Anderson", 456781, 10000.0, 2345, 15000.0),
        new PremiumSavingsAccount("Oliver Green", 567892, 20000.0, 9876, 4.2, 500.0),
        new SavingsAccount("Emily Davis", 345678, 7000.0, 1122, 3.8),
        new CurrentAccount("Liam White", 123489, 5000.0, 3344, 12000.0),
        new PremiumSavingsAccount("Sophia Taylor", 789654, 25000.0, 5566, 4.5, 500.0),
        new SavingsAccount("Isabella Hall", 890123, 4500.0, 7788, 3.2),
        new CurrentAccount("Noah Moore", 123456, 15000.0, 9900, 20000.0),
        new PremiumSavingsAccount("Mia Adams", 456123, 12000.0, 2233, 4.0, 500.0),
        new SavingsAccount("Charlotte Turner", 567891, 6000.0, 4455, 3.7)
    };

    ATM atm;

    int enteredAccountNumber, enteredPIN;
    cout << "Welcome to the ATM!" << endl;
    cout << "Please enter your account number: ";
    cin >> enteredAccountNumber;
    cout << "Please enter your PIN: ";
    cin >> enteredPIN;

    if (atm.selectAccount(accounts, 15, enteredAccountNumber, enteredPIN)) {
        atm.showMenu();
    }

    for (int i = 0; i < 15; ++i) { 
        delete accounts[i];
    }

    return 0;
}