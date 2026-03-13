#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

// BASE CLASS
class Account {
protected:
    string account_type; // Added to distinguish accounts in the text file
    int acc_no;
    string name;
    float balance;

public:
    Account(string type, int acc_no, string name, float balance) 
        : account_type(type), acc_no(acc_no), name(name), balance(balance) {}

    virtual ~Account() {} // Virtual destructor for memory safety

    virtual void print(ostream& os) const {
        os << "[" << account_type << "] Account No: " << acc_no 
           << " | Name: " << name << " | Balance: Rs " << balance;
    }

    friend ostream& operator<<(ostream& os, const Account& a) {
        a.print(os);
        return os;
    }

    virtual void saveToFile(ofstream& file) const {
        file << account_type << "\n" << acc_no << "\n" << name << "\n" << balance << "\n";
        saveExtraData(file); 
    }

    virtual void saveExtraData(ofstream& file) const = 0;
    virtual void deposit(float amount) = 0;
    virtual void withdraw(float amount) = 0;
};

//DERIVED CLASS: SAVINGS
class SavingsAccount : public Account {
private:
    float interest_rate;

public:
    SavingsAccount(int acc_no, string name, float balance, float rate)
        : Account("SAVINGS", acc_no, name, balance < 1000 ? 1000 : balance), interest_rate(rate) {}

    void print(ostream& os) const override {
        Account::print(os);
        os << " | Interest: " << interest_rate * 100 << "%";
    }

    void saveExtraData(ofstream& file) const override {
        file << interest_rate << "\n";
    }

    void deposit(float amount) override { balance += amount; }
    void withdraw(float amount) override {
        if (balance - amount >= 1000) balance -= amount;
        else cout << "Failed: Minimum balance is 1000.\n";
    }
};

// DERIVED CLASS: CURRENT
class CurrentAccount : public Account {
private:
    float overdraft_limit;

public:
    CurrentAccount(int acc_no, string name, float balance, float limit)
        : Account("CURRENT", acc_no, name, balance), overdraft_limit(limit) {}

    void print(ostream& os) const override {
        Account::print(os);
        os << " | Overdraft Limit: Rs " << overdraft_limit;
    }

    void saveExtraData(ofstream& file) const override {
        file << overdraft_limit << "\n";
    }

    void deposit(float amount) override { balance += amount; }
    void withdraw(float amount) override {
        if (balance - amount >= -overdraft_limit) balance -= amount;
        else cout << "Failed: Overdraft limit exceeded.\n";
    }
};

//MAIN EXECUTION
int main() {
    // Create accounts
    SavingsAccount sa(101, "Charan", 5000, 0.05);
    CurrentAccount ca(102, "Sahiti", 2000, 10000);

    cout << "--- Initial Accounts ---\n";
    cout << sa << "\n" << ca << "\n\n";

    // 2. Save multiple accounts to a single file
    ofstream outFile("bank_database.txt");
    if (outFile.is_open()) {
        sa.saveToFile(outFile);
        ca.saveToFile(outFile);
        outFile.close();
    }

    return 0;

}
