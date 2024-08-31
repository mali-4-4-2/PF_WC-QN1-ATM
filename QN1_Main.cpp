#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

// Structure to hold user account information
struct Account {
    string password;
    double balance;
};

// Function prototypes
void showIntroMenu();
void showMainMenu();
bool createAccount(unordered_map<string, Account>& accounts);
bool login(const unordered_map<string, Account>& accounts, string& loggedInUserId);
void deposit(Account& account);
void withdraw(Account& account);
void requestBalance(const Account& account);

int main() {
    unordered_map<string, Account> accounts; // To store account information
    string loggedInUserId;

    while (true) {
        showIntroMenu();

        char choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore leftover input

        if (choice == 'q') {
            cout << "Thank you for using the ATM Machine. Goodbye!" << endl;
            break;
        } else if (choice == 'c') {
            if (createAccount(accounts)) {
                cout << "Thank You! Your account has been created!" << endl;
            } else {
                cout << "Account creation failed!" << endl;
            }
        } else if (choice == 'l') {
            if (login(accounts, loggedInUserId)) {
                cout << "Access Granted!" << endl;
                while (true) {
                    showMainMenu();
                    cin >> choice;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore leftover input

                    if (choice == 'q') {
                        cout << "Logging out. Goodbye!" << endl;
                        break;
                    } else if (choice == 'd') {
                        deposit(accounts[loggedInUserId]);
                    } else if (choice == 'w') {
                        withdraw(accounts[loggedInUserId]);
                    } else if (choice == 'r') {
                        requestBalance(accounts[loggedInUserId]);
                    } else {
                        cout << "Invalid option. Please try again." << endl;
                    }
                }
            } else {
                cout << "*** LOGIN FAILED! ***" << endl;
            }
        } else {
            cout << "Invalid option. Please try again." << endl;
        }
    }

    return 0;
}

void showIntroMenu() {
    cout << "Hi! Welcome to the ATM Machine!" << endl;
    cout << "Please select an option from the menu below:" << endl;
    cout << "l -> Login" << endl;
    cout << "c -> Create New Account" << endl;
    cout << "q -> Quit" << endl;
    cout << "> ";
}

void showMainMenu() {
    cout << "d -> Deposit Money" << endl;
    cout << "w -> Withdraw Money" << endl;
    cout << "r -> Request Balance" << endl;
    cout << "q -> Quit" << endl;
    cout << "> ";
}

bool createAccount(unordered_map<string, Account>& accounts) {
    string userId, password;

    cout << "Please enter your user id: ";
    getline(cin, userId);
    cout << "Please enter your password: ";
    getline(cin, password);

    // Check if the user ID already exists
    if (accounts.find(userId) != accounts.end()) {
        cout << "Account with this user ID already exists." << endl;
        return false;
    }

    // Create new account
    Account newAccount = { password, 0.0 };
    accounts[userId] = newAccount;
    return true;
}

bool login(const unordered_map<string, Account>& accounts, string& loggedInUserId) {
    string userId, password;

    cout << "Please enter your user id: ";
    getline(cin, userId);
    cout << "Please enter your password: ";
    getline(cin, password);

    // Check if the user ID exists and the password matches
    auto it = accounts.find(userId);
    if (it != accounts.end() && it->second.password == password) {
        loggedInUserId = userId;
        return true;
    }
    return false;
}

void deposit(Account& account) {
    double amount;
    cout << "Amount of deposit: $";
    cin >> amount;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore leftover input

    if (amount > 0) {
        account.balance += amount;
        cout << "Deposit successful!" << endl;
    } else {
        cout << "Invalid deposit amount!" << endl;
    }
}

void withdraw(Account& account) {
    double amount;
    cout << "Amount of withdrawal: $";
    cin >> amount;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore leftover input

    if (amount > 0 && amount <= account.balance) {
        account.balance -= amount;
        cout << "Withdrawal successful!" << endl;
    } else if (amount > account.balance) {
        cout << "Insufficient funds!" << endl;
    } else {
        cout << "Invalid withdrawal amount!" << endl;
    }
}

void requestBalance(const Account& account) {
    cout << "Your balance is $" << account.balance << "." << endl;
}
