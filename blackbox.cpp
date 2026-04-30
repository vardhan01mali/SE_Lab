#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// --- Entity Object ---
class Account {
private:
    string cardNumber;
    string pin;
    double balance;
    int pinAttempts;
    bool isBlocked;

public:
    Account(string c, string p, double b) 
        : cardNumber(c), pin(p), balance(b), pinAttempts(0), isBlocked(false) {}

    string getPin() { return pin; }
    double getBalance() { return balance; }
    bool getIsBlocked() { return isBlocked; }
    void setBalance(double newBalance) { balance = newBalance; }
    void blockAccount() { isBlocked = true; }
    void incrementAttempts() { pinAttempts++; }
    void resetAttempts() { pinAttempts = 0; }
    int getAttempts() { return pinAttempts; }
};

// --- Control Object ---
class BankServer {
public:
    string runTransaction(Account &acc, string enteredPin, string enteredAmount) {
        if (acc.getIsBlocked()) return "Error: Account remains blocked";

        // TC12: Non-numeric PIN check
        for(char c : enteredPin) if(!isdigit(c)) return "Error: Invalid Input Type";

        // TC02: PIN Length check
        if (enteredPin.length() != 4) return "Error: Invalid PIN length";

        // PIN Verification (TC03, TC04)
        if (acc.getPin() == enteredPin) {
            acc.resetAttempts();
        } else {
            acc.incrementAttempts();
            if (acc.getAttempts() >= 3) {
                acc.blockAccount();
                return "Error: Account Blocked after 3 failures";
            }
            return "Error: Incorrect PIN; Attempt " + to_string(acc.getAttempts()) + "/3";
        }

        // TC13: Non-numeric Amount check
        double amount;
        try {
            amount = stod(enteredAmount);
        } catch (...) {
            return "Error: Invalid Input Type";
        }

        // Amount Validations (TC06, TC07, TC08, TC10, TC11, TC14)
        if (amount <= 0) return "Error: Invalid Amount";
        if (amount < 100) return "Error: Minimum withdrawal is 100";
        if (amount > 20000) return "Error: Exceeds Daily Limit";
        if ((long)amount % 100 != 0) return "Error: Amount must be multiple of 100";
        if (amount > acc.getBalance()) return "Error: Insufficient Funds";

        acc.setBalance(acc.getBalance() - amount);
        return (acc.getBalance() == 0) ? "Transaction Successful; Balance 0" : "Transaction Successful; Balance Updated";
    }
};

// --- Automation Suite ---
struct TestCase {
    string id;
    string pin;
    string amount; // Kept as string to test non-numeric inputs
    string expected;
    bool isMulti; 
};

void runTests() {
    BankServer server;
    vector<TestCase> suite = {
        {"TC01", "1234", "500", "Transaction Successful", false},
        {"TC02", "12", "200", "Invalid PIN length", false},
        {"TC03", "0000", "200", "Incorrect PIN", false},
        {"TC04", "0000", "200", "Account Blocked", true},
        {"TC05", "1234", "100", "Transaction Successful", false},
        {"TC06", "1234", "50", "Minimum withdrawal is 100", false},
        {"TC07", "1234", "0", "Invalid Amount", false},
        {"TC08", "1234", "-500", "Invalid Amount", false},
        {"TC09", "1234", "5000", "Balance 0", false},
        {"TC10", "1234", "5100", "Insufficient Funds", false},
        {"TC11", "1234", "25000", "Exceeds Daily Limit", false},
        {"TC12", "ABCD", "500", "Invalid Input Type", false},
        {"TC13", "1234", "Five", "Invalid Input Type", false},
        {"TC14", "1234", "155", "multiple of 100", false},
        {"TC15", "1234", "500", "blocked", false}
    };

    cout << "ID\t| RESULT\t| SYSTEM OUTPUT" << endl;
    cout << "--------------------------------------------------------" << endl;

    for (auto &t : suite) {
        Account testAcc("241070038", "1234", 5000.0);
        if (t.id == "TC15") testAcc.blockAccount();
        
        string actual;
        if (t.isMulti) {
            server.runTransaction(testAcc, t.pin, t.amount);
            server.runTransaction(testAcc, t.pin, t.amount);
            actual = server.runTransaction(testAcc, t.pin, t.amount);
        } else {
            actual = server.runTransaction(testAcc, t.pin, t.amount);
        }

        string actLow = actual; transform(actLow.begin(), actLow.end(), actLow.begin(), ::tolower);
        string expLow = t.expected; transform(expLow.begin(), expLow.end(), expLow.begin(), ::tolower);

        bool pass = (actLow.find(expLow) != string::npos);
        cout << t.id << "\t| " << (pass ? "SUCCESS" : "FAILURE") << "\t| " << actual << endl;
    }
}

int main() {
    cout << "Vardhan Mali | 241070038 | VJTI SE LAB EXAM" << endl;
    cout << "========================================================\n" << endl;
    runTests();
    return 0;
}