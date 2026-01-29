#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

// Account structure
struct Account {
    int accountNumber;
    string name;
    double balance;
    Account* next;
};

// Bank Transaction System Class
class BankSystem {
private:
    Account* head;
    string filename;

public:
    BankSystem() {
        head = NULL;
        filename = "bank_data.txt";
        loadFromFile();
    }

    ~BankSystem() {
        saveToFile();
        clearMemory();
    }

    // Module 1: Create Account
    void createAccount() {
        Account* newAccount = new Account();
        
        cout << "\n=== CREATE NEW ACCOUNT ===" << endl;
        cout << "Enter Account Number: ";
        cin >> newAccount->accountNumber;
        
        // Check if account already exists
        if (searchAccount(newAccount->accountNumber) != NULL) {
            cout << "Account already exists!" << endl;
            delete newAccount;
            return;
        }
        
        cin.ignore();
        cout << "Enter Account Holder Name: ";
        getline(cin, newAccount->name);
        
        cout << "Enter Initial Balance: ";
        cin >> newAccount->balance;
        
        newAccount->next = head;
        head = newAccount;
        
        cout << "Account created successfully!" << endl;
        cout << "Account Number: " << newAccount->accountNumber << endl;
        cout << "Account Holder: " << newAccount->name << endl;
        cout << "Balance: $" << fixed << setprecision(2) << newAccount->balance << endl;
    }

    // Module 2: Display All Accounts
    void displayAllAccounts() {
        if (head == NULL) {
            cout << "\nNo accounts found!" << endl;
            return;
        }
        
        cout << "\n=== ALL ACCOUNTS ===" << endl;
        cout << setw(15) << "Account No." << setw(20) << "Name" << setw(15) << "Balance" << endl;
        cout << string(50, '-') << endl;
        
        Account* temp = head;
        while (temp != NULL) {
            cout << setw(15) << temp->accountNumber 
                 << setw(20) << temp->name 
                 << setw(15) << fixed << setprecision(2) << temp->balance << endl;
            temp = temp->next;
        }
    }

    // Module 3: Deposit Money
    void depositMoney() {
        int accNumber;
        double amount;
        
        cout << "\n=== DEPOSIT MONEY ===" << endl;
        cout << "Enter Account Number: ";
        cin >> accNumber;
        
        Account* account = searchAccount(accNumber);
        if (account == NULL) {
            cout << "Account not found!" << endl;
            return;
        }
        
        cout << "Account Holder: " << account->name << endl;
        cout << "Current Balance: $" << fixed << setprecision(2) << account->balance << endl;
        
        cout << "Enter amount to deposit: $";
        cin >> amount;
        
        if (amount <= 0) {
            cout << "Invalid amount!" << endl;
            return;
        }
        
        account->balance += amount;
        cout << "Deposit successful!" << endl;
        cout << "New Balance: $" << fixed << setprecision(2) << account->balance << endl;
    }

    // Module 4: Withdraw Money
    void withdrawMoney() {
        int accNumber;
        double amount;
        
        cout << "\n=== WITHDRAW MONEY ===" << endl;
        cout << "Enter Account Number: ";
        cin >> accNumber;
        
        Account* account = searchAccount(accNumber);
        if (account == NULL) {
            cout << "Account not found!" << endl;
            return;
        }
        
        cout << "Account Holder: " << account->name << endl;
        cout << "Current Balance: " << fixed << setprecision(2) << account->balance << endl;
        
        cout << "Enter amount to withdraw: ";
        cin >> amount;
        
        if (amount <= 0) {
            cout << "Invalid amount!" << endl;
            return;
        }
        
        if (amount > account->balance) {
            cout << "Insufficient balance!" << endl;
            return;
        }
        
        account->balance -= amount;
        cout << "Withdrawal successful!" << endl;
        cout << "New Balance: " << fixed << setprecision(2) << account->balance << endl;
    }

    // Module 5: Transfer Money
    void transferMoney() {
        int fromAcc, toAcc;
        double amount;
        
        cout << "\n=== TRANSFER MONEY ===" << endl;
        cout << "Enter Sender Account Number: ";
        cin >> fromAcc;
        
        Account* sender = searchAccount(fromAcc);
        if (sender == NULL) {
            cout << "Sender account not found!" << endl;
            return;
        }
        
        cout << "Enter Receiver Account Number: ";
        cin >> toAcc;
        
        Account* receiver = searchAccount(toAcc);
        if (receiver == NULL) {
            cout << "Receiver account not found!" << endl;
            return;
        }
        
        cout << "Sender: " << sender->name << " (Balance:" << fixed << setprecision(2) << sender->balance << ")" << endl;
        cout << "Receiver: " << receiver->name << " (Balance: $" << fixed << setprecision(2) << receiver->balance << ")" << endl;
        
        cout << "Enter amount to transfer: ";
        cin >> amount;
        
        if (amount <= 0) {
            cout << "Invalid amount!" << endl;
            return;
        }
        
        if (amount > sender->balance) {
            cout << "Insufficient balance in sender's account!" << endl;
            return;
        }
        
        sender->balance -= amount;
        receiver->balance += amount;
        
        cout << "Transfer successful!" << endl;
        cout << "Sender's New Balance: " << fixed << setprecision(2) << sender->balance << endl;
        cout << "Receiver's New Balance: " << fixed << setprecision(2) << receiver->balance << endl;
    }

    // Module 6: Search Account
    void searchAccountByNumber() {
        int accNumber;
        
        cout << "\n=== SEARCH ACCOUNT ===" << endl;
        cout << "Enter Account Number: ";
        cin >> accNumber;
        
        Account* account = searchAccount(accNumber);
        if (account == NULL) {
            cout << "Account not found!" << endl;
            return;
        }
        
        cout << "\n=== ACCOUNT DETAILS ===" << endl;
        cout << "Account Number: " << account->accountNumber << endl;
        cout << "Account Holder: " << account->name << endl;
        cout << "Balance: $" << fixed << setprecision(2) << account->balance << endl;
    }

    // Module 7: Delete Account
    void deleteAccount() {
        int accNumber;
        
        cout << "\n=== DELETE ACCOUNT ===" << endl;
        cout << "Enter Account Number to delete: ";
        cin >> accNumber;
        
        if (head == NULL) {
            cout << "No accounts to delete!" << endl;
            return;
        }
        
        Account* current = head;
        Account* prev = NULL;
        
        // If head node itself holds the account to be deleted
        if (current != NULL && current->accountNumber == accNumber) {
            head = current->next;
            cout << "Account deleted successfully!" << endl;
            cout << "Deleted Account: " << current->accountNumber << " - " << current->name << endl;
            delete current;
            return;
        }
        
        // Search for the account to be deleted
        while (current != NULL && current->accountNumber != accNumber) {
            prev = current;
            current = current->next;
        }
        
        if (current == NULL) {
            cout << "Account not found!" << endl;
            return;
        }
        
        // Unlink the node from linked list
        prev->next = current->next;
        cout << "Account deleted successfully!" << endl;
        cout << "Deleted Account: " << current->accountNumber << " - " << current->name << endl;
        delete current;
    }

private:
    // Helper function to search account
    Account* searchAccount(int accNumber) {
        Account* temp = head;
        while (temp != NULL) {
            if (temp->accountNumber == accNumber) {
                return temp;
            }
            temp = temp->next;
        }
        return NULL;
    }

    // File handling: Save data to file
    void saveToFile() {
        ofstream file(filename);
        if (!file) {
            cout << "Error saving data to file!" << endl;
            return;
        }
        
        Account* temp = head;
        while (temp != NULL) {
            file << temp->accountNumber << ","
                 << temp->name << ","
                 << fixed << setprecision(2) << temp->balance << "\n";
            temp = temp->next;
        }
        
        file.close();
    }

    // File handling: Load data from file
    void loadFromFile() {
        ifstream file(filename);
        if (!file) {
            return; // File doesn't exist yet
        }
        
        string line;
        while (getline(file, line)) {
            Account* newAccount = new Account();
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);
            
            newAccount->accountNumber = stoi(line.substr(0, pos1));
            newAccount->name = line.substr(pos1 + 1, pos2 - pos1 - 1);
            newAccount->balance = stod(line.substr(pos2 + 1));
            newAccount->next = head;
            head = newAccount;
        }
        
        file.close();
    }

    // Clear memory
    void clearMemory() {
        Account* temp;
        while (head != NULL) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }

};

// Main function with menu
int main() {
    BankSystem bank;
    int choice;
    
    cout << "=== BANK TRANSACTION SYSTEM ===" << endl;
    cout << "Developed using C++ & Data Structures" << endl;
    
    do {
        cout << "\n=== MAIN MENU ===" << endl;
        cout << "1. Create New Account" << endl;
        cout << "2. Display All Accounts" << endl;
        cout << "3. Deposit Money" << endl;
        cout << "4. Withdraw Money" << endl;
        cout << "5. Transfer Money" << endl;
        cout << "6. Search Account" << endl;
        cout << "7. Delete Account" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice (1-8): ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                bank.createAccount();
                break;
            case 2:
                bank.displayAllAccounts();
                break;
            case 3:
                bank.depositMoney();
                break;
            case 4:
                bank.withdrawMoney();
                break;
            case 5:
                bank.transferMoney();
                break;
            case 6:
                bank.searchAccountByNumber();
                break;
            case 7:
                bank.deleteAccount();
                break;
            case 8:
                cout << "Thank you for using Bank Transaction System!" << endl;
                cout << "Data saved successfully!" << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
        
    } while (choice != 8);
    
    return 0;
}
