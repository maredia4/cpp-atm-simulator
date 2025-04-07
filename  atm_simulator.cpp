#include <iostream>
#include <limits>
#include <vector>

using namespace std;

double checkBalance(double balance);
void deposit(double &balance, double amount);
void withdraw(double &balance, double amount);
bool authenticateUser(int pin, int enteredPin);
void viewTransactionHistory();

vector<string> transactionHistory;
const double dailyLimit = 500.0;
double totalWithdrawnToday = 0.0;

int main() {
const int userPin = 1234;  // this is PIN
int enteredPin;

cout << "Please enter your PIN: ";
cin >> enteredPin;

if (!authenticateUser(userPin, enteredPin)) {
cout << "Incorrect PIN. Access denied.\n";
return 1; 
}

double balance = 1000.0; 
int choice;
double amount;

while (true) {
// Display menu
cout << "\nWelcome to the ATM\n";
cout << "1. Check Balance\n";
cout << "2. Deposit Money\n";
cout << "3. Withdraw Money\n";
cout << "4. Exit\n";
cout << "5. View Transaction History\n";
cout << "Enter your choice: ";

cin >> choice;

if (cin.fail()) {
cin.clear();
cin.ignore(numeric_limits<streamsize>::max(), '\n');
cout << "Invalid input. Please enter a number.\n";
continue;
}

switch (choice) {
case 1:
cout << "Current balance: $" << checkBalance(balance) << endl;
break;
case 2:
cout << "Enter deposit amount: $";
cin >> amount;
if (amount < 0) {
cout << "Amount cannot be negative.\n";
} else {
deposit(balance, amount);
cout << "Deposit successful. New balance: $" << balance << endl;
}
break;
case 3:
cout << "Enter withdrawal amount: $";
cin >> amount;
if (amount < 0) {
cout << "Amount cannot be negative.\n";
} else {
withdraw(balance, amount);
cout << "Withdrawal successful. New balance: $" << balance << endl;
}
break;
case 4:
cout << "Thank you for using the ATM. Goodbye!\n";
return 0;
case 5:
viewTransactionHistory();
break;
default:
cout << "Invalid choice. Please try again.\n";
}
}
}

bool authenticateUser(int pin, int enteredPin) {
return pin == enteredPin;
}

double checkBalance(double balance) {
return balance;
}

void deposit(double &balance, double amount) {
balance += amount;
transactionHistory.push_back("Deposited: $" + to_string(amount));
}

void withdraw(double &balance, double amount) {
if (totalWithdrawnToday + amount > dailyLimit) {
cout << "You have exceeded the daily withdrawal limit of $" << dailyLimit << ".\n";
return;
}

if (balance >= amount) {
balance -= amount;
totalWithdrawnToday += amount;
transactionHistory.push_back("Withdrew: $" + to_string(amount));
} else {
cout << "Insufficient funds for withdrawal.\n";
}
}

void viewTransactionHistory() {
if (transactionHistory.empty()) {
cout << "\nNo transactions to display.\n";
} else {
cout << "\nTransaction History:\n";
for (const string &transaction : transactionHistory) {
cout << transaction << endl;
}
}
}