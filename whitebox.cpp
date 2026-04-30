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

        // Node 2: Non-numeric PIN check
        for(char c : enteredPin) if(!isdigit(c)) return "Error: Invalid Input Type";

        // Node 3: PIN Length check
        if (enteredPin.length() != 4) return "Error: Invalid PIN length";

        // Node 4: PIN Verification
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

        // Node 5: Non-numeric Amount check (Exception Handling)
        double amount;
        try {
            amount = stod(enteredAmount);
        } catch (...) {
            return "Error: Invalid Input Type";
        }

        // Nodes 6-10: Amount Validations
        if (amount <= 0) return "Error: Invalid Amount";
        if (amount < 100) return "Error: Minimum withdrawal is 100";
        if (amount > 20000) return "Error: Exceeds Daily Limit";
        if ((long)amount % 100 != 0) return "Error: Amount must be multiple of 100";
        if (amount > acc.getBalance()) return "Error: Insufficient Funds";

        // Node 11: Success State
        acc.setBalance(acc.getBalance() - amount);
        return (acc.getBalance() == 0) ? "Transaction Successful; Balance 0" : "Transaction Successful";
    }
};

// --- White Box Automation Suite ---
struct WhiteBoxTestCase {
    string id;
    string target; // Logic Node / Path Description
    string pin;
    string amount;
    string expected;
    bool isMulti; 
};

void runWhiteBoxTests() {
    BankServer server;
    // Test data mapped directly from whitebox.csv
    vector<WhiteBoxTestCase> suite = {
        {"W01", "Happy Path (Nodes 1-11)", "1234", "500", "Successful", false},
        {"W02", "Node 1: isBlocked == true", "1234", "500", "blocked", false},
        {"W03", "Node 2: isdigit failure", "12A4", "500", "Input Type", false},
        {"W04", "Node 3: length < 4", "123", "500", "PIN length", false},
        {"W05", "Node 3: length > 4", "12345", "500", "PIN length", false},
        {"W06", "Node 4: Incorrect PIN", "0000", "200", "Incorrect PIN", false},
        {"W07", "Node 4: Account Block", "0000", "200", "Blocked after 3", true},
        {"W08", "Node 5: stod Exception", "1234", "Five", "Input Type", false},
        {"W09", "Node 6: Zero Amount", "1234", "0", "Invalid Amount", false},
        {"W10", "Node 6: Negative Amount", "1234", "-1", "Invalid Amount", false},
        {"W11", "Node 7: amount < 100", "1234", "99", "withdrawal is 100", false},
        {"W12", "Node 8: amount > 20000", "1234", "20001", "Daily Limit", false},
        {"W13", "Node 9: amount % 100 != 0", "1234", "150", "multiple of 100", false},
        {"W14", "Node 10: amount > balance", "1234", "5100", "Insufficient Funds", false},
        {"W15", "Node 11: balance == 0", "1234", "5000", "Balance 0", false}
    };

    cout << "ID\t| RESULT\t| LOGIC TARGET\t\t\t| SYSTEM OUTPUT" << endl;
    cout << "----------------------------------------------------------------------------------------" << endl;

    for (auto &t : suite) {
        Account testAcc("241070038", "1234", 5000.0);
        
        // Setup state for W02 (Pre-blocked card)
        if (t.id == "W02") testAcc.blockAccount();
        
        string actual;
        if (t.isMulti) {
            // Setup state for W07 (Multi-attempt block)
            server.runTransaction(testAcc, t.pin, t.amount);
            server.runTransaction(testAcc, t.pin, t.amount);
            actual = server.runTransaction(testAcc, t.pin, t.amount);
        } else {
            actual = server.runTransaction(testAcc, t.pin, t.amount);
        }

        string actLow = actual; transform(actLow.begin(), actLow.end(), actLow.begin(), ::tolower);
        string expLow = t.expected; transform(expLow.begin(), expLow.end(), expLow.begin(), ::tolower);

        bool pass = (actLow.find(expLow) != string::npos);
        
        cout << t.id << "\t| " << (pass ? "SUCCESS" : "FAILURE") << "\t| " 
             << (t.target.length() < 25 ? t.target + "\t" : t.target.substr(0, 30)) << "\t| " << actual << endl;
    }
}

int main() {
    cout << "Vardhan Mali | 241070038 | VJTI SE LAB EXAM" << endl;
    cout << "WHITE BOX TESTING AUTOMATION REPORT" << endl;
    cout << "========================================================================================\n" << endl;
    
    runWhiteBoxTests();
    
    return 0;
}