#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Struct to represent a Bank Account
struct BankAccount {
    string account_holder_name;
    int account_number;
    double balance;
    string status;  // Either "Active" or "Frozen"
};

// Global variables
vector<BankAccount> accounts;
int next_account_number = 10000000;  // Start account numbers from 10000000

// Function Prototypes
void customerMenu();
void employeeMenu();
void openAccount();
void depositAmount();
void withdrawAmount();
void generateStatement();
void viewAllAccounts();
void deductTax();
void addBonus();
void changeAccountStatus();

// Main Function
int main() {
    int role;
    do {
        cout << "Welcome to Haider's Bank simulation program.\n Select Role: \n1. Customer \n2. Employee \n0. Exit \nChoose: ";
        cin >> role;

        if (role == 1) {
            customerMenu();
        } else if (role == 2) {
            employeeMenu();
        } else if (role != 0) {
            cout << "Invalid option. Please retry.\n";
        }
    } while (role != 0);

    return 0;
}

// Customer Menu
void customerMenu() {
    int choice;
    do {
        cout << "\nCustomer Menu:\n";
        cout << "1. Open an Account\n";
        cout << "2. Deposit Amount\n";
        cout << "3. Withdraw Amount\n";
        cout << "4. Generate Statement\n";
        cout << "0. Go Back\n";
        cout << "Choose: ";
        cin >> choice;

        switch (choice) {
            case 1: openAccount(); break;
            case 2: depositAmount(); break;
            case 3: withdrawAmount(); break;
            case 4: generateStatement(); break;
            case 0: break;
            default: cout << "Invalid option. Please retry.\n";
        }
    } while (choice != 0);
}

// Employee Menu
void employeeMenu() {
    int choice;
    do {
        cout << "\nEmployee Menu:\n";
        cout << "1. View All Accounts\n";
        cout << "2. Deduct Tax\n";
        cout << "3. Add Bonus\n";
        cout << "4. Change Account Status\n";
        cout << "0. Go Back\n";
        cout << "Choose: ";
        cin >> choice;

        switch (choice) {
            case 1: viewAllAccounts(); break;
            case 2: deductTax(); break;
            case 3: addBonus(); break;
            case 4: changeAccountStatus(); break;
            case 0: break;
            default: cout << "Invalid option. Please retry.\n";
        }
    } while (choice != 0);
}

// Function to open a new account
void openAccount() {
    BankAccount newAccount;
    cout << "Enter Account Holder's Name: ";
    cin >> ws;
    getline(cin, newAccount.account_holder_name);

    if (newAccount.account_holder_name.length() < 3 || newAccount.account_holder_name.length() > 30) {
        cout << "Invalid name length. Must be between 3 and 30 characters.\n";
        return;
    }

    newAccount.account_number = next_account_number++;
    newAccount.balance = 0.0;
    newAccount.status = "Active";

    accounts.push_back(newAccount);
    cout << "Account created successfully with Account Number: " << newAccount.account_number << "\n";
}

// Function to deposit amount
void depositAmount() {
    int account_number;
    double amount;
    cout << "Enter Account Number: ";
    cin >> account_number;
    cout << "Enter Amount to Deposit: ";
    cin >> amount;

    if (amount < 0) {
        cout << "Invalid amount.\n";
        return;
    }

    for (auto& account : accounts) {
        if (account.account_number == account_number && account.status == "Active") {
            account.balance += amount;
            cout << "Amount deposited successfully. New Balance: " << account.balance << "\n";
            return;
        }
    }

    cout << "Account not found or account is not active.\n";
}

// Function to withdraw amount
void withdrawAmount() {
    int account_number;
    double amount;
    cout << "Enter Account Number: ";
    cin >> account_number;
    cout << "Enter Amount to Withdraw: ";
    cin >> amount;

    for (auto& account : accounts) {
        if (account.account_number == account_number && account.status == "Active") {
            if (amount <= account.balance) {
                account.balance -= amount;
                cout << "Amount withdrawn successfully. New Balance: " << account.balance << "\n";
            } else {
                cout << "Insufficient balance.\n";
            }
            return;
        }
    }

    cout << "Account not found or account is not active.\n";
}

// Function to generate account statement
void generateStatement() {
    string name;
    cout << "Enter Account Holder's Name: ";
    cin >> ws;
    getline(cin, name);

    bool found = false;
    for (const auto& account : accounts) {
        if (account.account_holder_name == name) {
            cout << "Account Number: " << account.account_number << "\n";
            cout << "Balance: " << account.balance << "\n";
            cout << "Status: " << account.status << "\n\n";
            found = true;
        }
    }

    if (!found) {
        cout << "No account found with the given name.\n";
    }
}

// Function to view all accounts (Employee)
void viewAllAccounts() {
    for (const auto& account : accounts) {
        cout << "Account Holder: " << account.account_holder_name << "\n";
        cout << "Account Number: " << account.account_number << "\n";
        cout << "Balance: " << account.balance << "\n";
        cout << "Status: " << account.status << "\n\n";
    }
}

// Function to deduct tax (Employee)
void deductTax() {
    for (auto& account : accounts) {
        if (account.status == "Active") {
            double tax = account.balance * 0.10;
            account.balance -= tax;
            cout << "Tax deducted from Account " << account.account_number << ". New Balance: " << account.balance << "\n";
        }
    }
}

// Function to add bonus (Employee)
void addBonus() {
    for (auto& account : accounts) {
        if (account.status == "Active") {
            double bonus = account.balance * 0.10;
            account.balance += bonus;
            cout << "Bonus added to Account " << account.account_number << ". New Balance: " << account.balance << "\n";
        }
    }
}

// Function to change account status (Employee)
void changeAccountStatus() {
    int account_number;
    cout << "Enter Account Number: ";
    cin >> account_number;

    for (auto& account : accounts) {
        if (account.account_number == account_number) {
            if (account.status == "Active") {
                account.status = "Frozen";
            } else {
                account.status = "Active";
            }
            cout << "Account status changed to " << account.status << ".\n";
            return;
        }
    }

    cout << "Account not found.\n";
}
