#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
using namespace std;

class Transaction
{private:
    string type;
    double amount;

public:
    Transaction(const string& t, double amt) : type(t), amount(amt) {}

    void displayTransaction() const {
        cout << "Transaction: " << type << " | Amount: " << amount << endl;
    }
};

class Account
{private:
    string accountNumber;
    double balance;
    vector<Transaction> transactions;

public:
    Account(const string& accNum, double initialBalance)
        : accountNumber(accNum), balance(initialBalance) {}

    string getAccountNumber() const {
        return accountNumber;
    }

    double getBalance() const {
        return balance;
    }

    void setAccountNumber(const string& newAccNum) {
        accountNumber = newAccNum;
    }

    void deposit(double amount) {
        if (amount <= 0) {
            throw invalid_argument("Deposit amount must be greater than zero.");
        }
        balance += amount;
        transactions.push_back(Transaction("Deposit", amount));
    }

    void withdraw(double amount) {
        if (amount <= 0) {
            throw invalid_argument("Withdrawal amount must be greater than zero.");
        }
        if (amount > balance) {
            throw runtime_error("Insufficient balance.");
        }
        balance -= amount;
        transactions.push_back(Transaction("Withdrawal", amount));
    }

    void displayTransactions() const {
        cout << "Transactions for Account: " << accountNumber << endl;
        for (const auto& transaction : transactions) {
            transaction.displayTransaction();
        }
    }
};

class Customer
{private:
    string name;
    string customerID;
    vector<Account> accounts;

public:
    Customer(const string& custName, const string& custID)
        : name(custName), customerID(custID) {}

    string getCustomerID() const {
        return customerID;
    }

    string getName() const {
        return name;
    }

    void setName(const string& newName) {
        name = newName;
    }

    void createAccount(const string& accNum, double initialBalance)
    {
        accounts.push_back(Account(accNum, initialBalance));
        cout << "Account " << accNum << " created successfully!" << endl;
    }

    Account* getAccount(const string& accNum) {
        for (auto& account : accounts) {
            if (account.getAccountNumber() == accNum)
            {
                return &account;
            }
        }
        throw runtime_error("Account not found.");
    }

    void displayAccounts() const {
        cout << "Customer: " << name << " | Customer ID: " << customerID << endl;
        for (const auto& account : accounts) {
            cout << "Account Number: " << account.getAccountNumber() << " | Balance: " << account.getBalance() << endl;
        }
    }

    void updateAccountNumber(const string& oldAccNum, const string& newAccNum)
    {
        Account* account = getAccount(oldAccNum);
        account->setAccountNumber(newAccNum);
        cout << "Account number updated successfully!" << endl;
    }
};

class BankingService
{private:
    vector<Customer> customers;

public:
    void addCustomer(const string& custName, const string& custID)
    {
        customers.push_back(Customer(custName, custID));
        cout << "Customer " << custName << " added successfully!" << endl;
    }

    Customer* getCustomer(const string& custID)

     {
        for (auto& customer : customers) {
            if (customer.getCustomerID() == custID)
                {
                return &customer;
            }
        }
        throw runtime_error("Customer not found.");
    }

    void performDeposit(const string& custID, const string& accNum, double amount)
    {
        Customer* customer = getCustomer(custID);
        Account* account = customer->getAccount(accNum);
        account->deposit(amount);
        cout << "Deposit successful!" << endl;
    }

    void performWithdrawal(const string& custID, const string& accNum, double amount)
    {
        Customer* customer = getCustomer(custID);
        Account* account = customer->getAccount(accNum);
        account->withdraw(amount);
        cout << "Withdrawal successful!" << endl;
    }

    void displayCustomerAccounts(const string& custID)
    {
        Customer* customer = getCustomer(custID);
        customer->displayAccounts();
    }

    void displayAccountTransactions(const string& custID, const string& accNum)
    {
        Customer* customer = getCustomer(custID);
        Account* account = customer->getAccount(accNum);
        account->displayTransactions();
    }

    void updateCustomerName(const string& custID, const string& newName)
    {
        Customer* customer = getCustomer(custID);
        customer->setName(newName);
        cout << "Customer name updated successfully!" << endl;
    }

    void updateAccountNumber(const string& custID, const string& oldAccNum, const string& newAccNum)
    {
        Customer* customer = getCustomer(custID);
        customer->updateAccountNumber(oldAccNum, newAccNum);
    }

    void userInteraction()
    {
        int choice;
        do {
            cout << "\n--- Banking System Menu ---\n";
            cout << "1. Add Customer\n";
            cout << "2. Create Account\n";
            cout << "3. Deposit\n";
            cout << "4. Withdraw\n";
            cout << "5. Display Accounts\n";
            cout << "6. Display Transactions\n";
            cout << "7. Update Customer Name\n";
            cout << "8. Update Account Number\n";
            cout << "9. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice)
             {
                case 1:
                {
                    string custName, custID;
                    cout << "Enter customer name: ";
                    cin.ignore();
                    getline(cin, custName);
                    cout << "Enter customer ID: ";
                    getline(cin, custID);
                    addCustomer(custName, custID);
                    break;
                }
                case 2:
                {
                    string custID, accNum;
                    double initialBalance;
                    cout << "Enter customer ID: ";
                    cin.ignore();
                    getline(cin, custID);
                    cout << "Enter account number: ";
                    getline(cin, accNum);
                    cout << "Enter initial balance: ";
                    cin >> initialBalance;
                    getCustomer(custID)->createAccount(accNum, initialBalance);
                    break;
                }
                case 3:
                {
                    string custID, accNum;
                    double amount;
                    cout << "Enter customer ID: ";
                    cin.ignore();
                    getline(cin, custID);
                    cout << "Enter account number: ";
                    getline(cin, accNum);
                    cout << "Enter deposit amount: ";
                    cin >> amount;
                    performDeposit(custID, accNum, amount);
                    break;
                }
                case 4:
                {
                    string custID, accNum;
                    double amount;
                    cout << "Enter customer ID: ";
                    cin.ignore();
                    getline(cin, custID);
                    cout << "Enter account number: ";
                    getline(cin, accNum);
                    cout << "Enter withdrawal amount: ";
                    cin >> amount;
                    performWithdrawal(custID, accNum, amount);
                    break;
                }
                case 5:
                {
                    string custID;
                    cout << "Enter customer ID: ";
                    cin.ignore();
                    getline(cin, custID);
                    displayCustomerAccounts(custID);
                    break;
                }
                case 6:

                {
                    string custID, accNum;
                    cout << "Enter customer ID: ";
                    cin.ignore();
                    getline(cin, custID);
                    cout << "Enter account number: ";
                    getline(cin, accNum);
                    displayAccountTransactions(custID, accNum);
                    break;
                }
                case 7:
                {
                    string custID, newName;
                    cout << "Enter customer ID: ";
                    cin.ignore();
                    getline(cin, custID);
                    cout << "Enter new customer name: ";
                    getline(cin, newName);
                    updateCustomerName(custID, newName);
                    break;
                }
                case 8:
                {
                    string custID, oldAccNum, newAccNum;
                    cout << "Enter customer ID: ";
                    cin.ignore();
                    getline(cin, custID);
                    cout << "Enter old account number: ";
                    getline(cin, oldAccNum);
                    cout << "Enter new account number: ";
                    getline(cin, newAccNum);
                    updateAccountNumber(custID, oldAccNum, newAccNum);
                    break;
                }
                case 9:
                    cout << "Exiting system. Goodbye!" << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 9);
    }
};

int main()
{
    BankingService bankService;
    bankService.userInteraction();
    return 0;
}
