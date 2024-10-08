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
        setAccountHolderName(name);
        setAccountNumber(number);
        setBalance(initialBalance);
        setPIN(accountPIN);
        totalAccounts++;
    }

    ~BankAccount() {
        cout << "BankAccount object for " << getAccountHolderName() << " destroyed" << endl;
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
            cout << "Deposit successful! New Balance: Rs" << getBalance() << endl;
        } else {
            cout << "Minimum deposit amount is Rs 500!" << endl;
        }
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
            getCurrentAccount()->deposit(amount);
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