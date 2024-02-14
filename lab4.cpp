#include<iostream>

using namespace std;

class Account
{
public:
    int accountNumber;
    double balance;
    string ownerName;
    Account()
    {};
    Account(int accountNumber, double balance, string ownerName)
    {
        this->accountNumber = accountNumber;
        this->balance = balance;
        this->ownerName = ownerName;
    }
    Account(const Account&) = delete;
    Account& operator= (const Account&) = delete;
    void deposit(double sum)
    {
        if (sum < 0) {
            cout << "You cannot add negative amount of money!";
        }
        else balance += sum;
    }
    string withdraw(double sum)
    {
        if (balance < sum) {
            return "You don't have enough money!";
        }
        balance -= sum;
        return "You withdraw some money!";
    }
    double getBalance()
    {
        return balance;
    }
    int getAccountNumber()
    {
        return accountNumber;
    }
    string getOwnerName()
    {
        return ownerName;
    }

};

class SavingsAccount: public Account
{
public:
    double interestRate;
    SavingsAccount(int accountNumber, double balance, string ownerName, double interestRate)
    {
        this->accountNumber = accountNumber;
        this->balance = balance;
        this->ownerName = ownerName;
        this->interestRate = interestRate;
    }
    void calculateInterest()
    {
        double between = interestRate * balance;
        balance += between;
    }
    double getInterestRate()
    {
        return interestRate;
    }

};

int main()
{
    SavingsAccount savings(123456, 1000.0, "John Doe", 2.5);
    savings.deposit(500.0);
    savings.withdraw(200.0);
    savings.calculateInterest();

    cout << "Account Number: " << savings.getAccountNumber() << endl;
    cout << "Owner's Name: " << savings.getOwnerName() << endl;
    cout << "Current Balance: " << savings.getBalance() << endl;
    cout << "Interest Rate: " << savings.getInterestRate() << "%" << endl;
    
    return 0;
}