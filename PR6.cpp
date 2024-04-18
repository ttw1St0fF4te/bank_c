#include <iostream>
using namespace std;

int main() {
	setlocale(LC_ALL, "rus");

	BankAccount firstAccount(123, 1000.0, 1.3);
	BankAccount secondAccount(321, 800.0, 2.5);
	cout << "Аккаунты созданы\n" << endl;

	cout << "Номер первого аккаунта: " << firstAccount.getAccountNumber() << endl;
	cout << "Номер второго аккаунта: " << secondAccount.getAccountNumber() << endl;

	cout << "Баланс первого аккаунта: " << firstAccount.getBalance() << endl;
	cout << "Баланс второго аккаунта: " << secondAccount.getBalance() << endl;

	cout << "Процентная ставка для первого аккаунта: " << firstAccount.getInterest() << endl;
	cout << "Процентная ставка для второго аккаунта: " << secondAccount.getInterest() << endl;

	if (transfer(firstAccount, secondAccount, 500.0)) {
		cout << "Перевод выполнен!" << endl;
		cout << "Баланс первого аккаунта после перевода: " << firstAccount.getBalance() << endl;
		cout << "Баланс второго аккаунта после перевода: " << secondAccount.getBalance() << endl;
	}
	else
		cout << "Ошибка перевода." << endl;

	firstAccount.deposit(1337.0);
	secondAccount.deposit(7331.0);
	cout << "Баланс первого аккаунта после внесения: " << firstAccount.getBalance() << endl;
	cout << "Баланс второго аккаунта после внесения: " << secondAccount.getBalance() << endl;

	firstAccount.withdraw(52.0);
	secondAccount.withdraw(228.0);
	cout << "Баланс первого аккаунта после снятия: " << firstAccount.getBalance() << endl;
	cout << "Баланс второго аккаунта после снятия: " << secondAccount.getBalance() << endl;

	firstAccount.setInterestRate(2.6);
	secondAccount.setInterestRate(5.0);
	cout << "Процентная ставка для первого аккаунта после обновления ставки: " << firstAccount.getInterest() << endl;
	cout << "Процентная ставка для второго аккаунта после обновления ставки: " << secondAccount.getInterest() << endl;

	return 0;
}

class BankAccount {
private:
	int accountNumber = { };
	double balance = { };
	double interestRate = { };
public:
	BankAccount(int AccountNumber, double Balance, double InterestRate) {
		this->accountNumber = AccountNumber;
		this->balance = Balance;
		this->interestRate = InterestRate;
	}

	double deposit(double amount) {
		if (amount <= 0) {
			cout << "Неверно указана сумма." << endl;
			return;
		}
		else
			this->balance += amount;
	}

	bool withdraw(double amount) {
		if (amount <= 0) {
			cout << "Неверно указана сумма." << endl;
			return false;
		}
		if (this->balance - amount >= 0) {
			this->balance -= amount;
			return true;
		}
		else {
			cout << "Недостаточно средств на балансе." << endl;
			return false;
		}
	}

	double getBalance() {
		return this->balance;
	}

	double getInterest() {
		return this->balance * this->interestRate * (1.0 / 12.0);
	}

	double setInterestRate(double interestRate) {
		if (interestRate < 0) {
			cout << "Неверная процентная ставка" << endl;
			return;
		}
		else
			this->interestRate = interestRate;
	}

	int getAccountNumber() {
		return this->accountNumber;
	}

	friend bool transfer(BankAccount& fromAccount, BankAccount& toAccount, double amount);
};

bool transfer(BankAccount& fromAccount, BankAccount& toAccount, double amount) {
	if (fromAccount.withdraw(amount)) {
		toAccount.deposit(amount);
		return true;
	}
	else 
		return false;
}