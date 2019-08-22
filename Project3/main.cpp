#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class Worker
{
	string name;
	string surname;
	unsigned int age;
public:
	const string& get_name() const
	{
		return this->name;
	}
	const string& get_surname() const
	{
		return this->surname;
	}
	unsigned int get_age() const
	{
		return this->age;
	}
	void set_name(const string& name)
	{
		this->name = name;
	}
	void set_surname(const string& surname)
	{
		this->surname = surname;
	}
	void set_age(unsigned int age)
	{
		this->age = age;
	}

	// Constructors

	Worker(const string& name, const string& surname, unsigned int age)
	{
		set_name(name);
		set_surname(surname);
		set_age(age);
		cout << "WConstructor:\t" << this << endl;
	}
	virtual ~Worker()
	{
		cout << "WDestructor:\t" << this << endl;
	}
	//Methods
	virtual double get_money() const = 0;
};

ostream& operator<<(ostream& os, const Worker& obj)
{
	return os << obj.get_surname() << " " << obj.get_name() << "\t" << obj.get_age() << " years";
}

class FixedPayment :public Worker
{
	double salary;
public:
	double get_salary() const
	{
		return this->salary;
	}
	void set_salary(double salary)
	{
		this->salary = salary;
	}
	FixedPayment(const string&name, const string& surname, unsigned int age, double salary) : Worker(name, surname, age)
	{
		set_salary(salary);
		cout << "FConstructor:\t" << this << endl;
	}
	~FixedPayment()
	{
		cout << "FDestructor:\t" << this << endl;
	}
	//Methods
	double get_money() const
	{
		return this->salary;
	}
};

ostream& operator<<(ostream& os, const FixedPayment& obj)
{
	os << (Worker&)obj << "\tsalary: ";
	return os << obj.get_salary() << " $";
}

class HourPayment :public Worker
{
	double rate;//тариф за час
	int hours; //колличество часов,отработанное за месяц
public:
	double get_rate() const
	{
		return this->rate;
	}
	double get_hours() const
	{
		return this->hours;
	}
	void set_rate(double rate)
	{
		this->rate = rate;
	}
	void set_hours(int hours)
	{
		this->hours = hours;
	}
	// Constructors

	HourPayment(const string& name, const string& surname, unsigned int age, double rate, int hours = 168) : Worker(name, surname, age)
	{
		set_rate(rate);
		set_hours(hours);
		cout << "HConstructor:\t" << this << endl;
	}
	~HourPayment()
	{
		cout << "HDestructor:\t" << this << endl;
	}
	//Methods
	double get_money() const
	{
		return this->rate* hours;
	}
};

ostream& operator<<(ostream& os, const HourPayment& obj)
{
	os << (Worker&)obj << "\tsalary: ";
	return os << obj.get_money() << " $";
}

void main()
{
	setlocale(LC_ALL, "");
	/*Worker w("Василий", "Лентяй", 40);
	cout << w << endl;*/
	/*FixedPayment fr("Antonio", "Montana", 25, 5000);
	cout << fr << endl;
	HourPayment hp("Anton", "Mont", 25, 200, 21);
	cout << hp << endl;*/

	Worker* department[] =
	{
		new FixedPayment("Antonio", "Montana", 25, 5000),
		new HourPayment("Martin", "Scorcese", 60, 100),
		new HourPayment("James", "Cameron", 64, 200)
	};
	for (int i = 0; i < sizeof(department) / sizeof(Worker*); i++)
	{
		//cout << typeid(*department[i]).name() << endl;
		if (typeid(*department[i]) == typeid (HourPayment))
			cout << *(HourPayment*)department[i] << endl;
		if (typeid(*department[i]) == typeid (FixedPayment))
			cout << *(FixedPayment*)department[i] << endl;
	}

	ofstream fout("List of workers.txt");
	for (int i = 0; i < sizeof(department) / sizeof(Worker*); i++)
	{
		//cout << typeid(*department[i]).name() << endl;
		if (typeid(*department[i]) == typeid (HourPayment))
			fout << *(HourPayment*)department[i] << endl;
		if (typeid(*department[i]) == typeid (FixedPayment))
			fout << *(FixedPayment*)department[i] << endl;
	}
	fout.close();

	for (int i = 0; i < sizeof(department) / sizeof(Worker*); i++)
	{
		delete department[i];
	}
}