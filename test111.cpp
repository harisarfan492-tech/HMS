#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<cstring>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

template<class Temp> class Store;
class Patient;
class Appointment;
class Doctor;
class Bill;
class Prescription;
class MedicalRecords;




class MedicalRecord
{
private:
	int patientId;
	string disease;
	string allergies;
	string bloodGroup;

public:
	MedicalRecord(int id = 0, string d = "", string a = "", string b = "")
	{
		patientId = id;
		disease = d;
		allergies = a;
		bloodGroup = b;
	}

	int getId() const
	{
		return patientId;
	}
	string getDisease() const
	{
		return disease;
	}

	string getAllergies() const
	{
		return allergies;
	}

	string getBloodGroup() const
	{
		return bloodGroup;
	}

	friend ostream& operator<<(ostream& out, const MedicalRecord& m)
	{
		out << "Patient ID: " << m.patientId << endl;
		out << "Disease: " << m.disease << endl;
		out << "Allergies: " << m.allergies << endl;
		out << "Blood Group: " << m.bloodGroup << endl;
		return out;
	}
};
class File
{
public:
	static void checkfileopen(const string& fn)
	{
		ifstream file(fn);
		if (!file)
		{
			cout << "File not found by the name of " << fn << endl;
		}
		file.close();
	}
	static void loadPatients(Store<Patient>& patients);
	static void appendAppointment(const Appointment& a);
	static void appendPatient(const Patient& p);
	static void updatePatient(Store<Patient>& patients);
	static void deletePatient(Store<Patient>& patients, int id);
	static void loadAppointments(Store<Appointment>& appointments);
	static void updateAppointments(Store<Appointment>& appointments);
	static void loadDoctors(Store<Doctor>& doctors);
	static void appendDoctor(const Doctor& d);
	static void updateDoctors(Store<Doctor>& doctors);
	static void loadBills(Store<Bill>& bills);
	static void appendBill(const Bill& b);
	static void updateBills(Store<Bill>& bills);
	static void appendPrescription(const Prescription& p);
	static void loadPrescriptions(Store<Prescription>& prescriptions);
	static void appendMedicalRecord(const MedicalRecord& m);
	static void loadMedicalRecords(Store<MedicalRecord>& records);
};
class Person {
protected:
	int id;
	string name;
	string password;

public:
	Person() {
		id = 0;
		name = " ";
		password = " ";

	}

	Person(int id, string name, string password) {
		this->id = id;
		this->name = name;
		this->password = password;
	}

	int getId() const {
		return id;
	}
	string getName() const {
		return name;
	}
	string getPassword() const {
		return password;
	}

	virtual void display() const = 0;
	virtual bool login(int enteredId, string enteredPass) const = 0;

	virtual ~Person() {}
};
class Patient : public Person
{
private:
	int age;
	char gender;
	char contact[12];
	float balance;
public:
	Patient() : Person()
	{
		age = 0;
		gender = 'T';
		strcpy(contact, "");
		balance = 0.0;

	}
	Patient(int id, string name, int age, char gender, string contact, string password, float balance) :Person(id, name, password)
	{
		this->age = age;
		this->balance = balance;
		this->gender = gender;
		strncpy(this->contact, contact.c_str(), 11);
		this->contact[11] = '\0';
	}
	float getBal()const
	{
		return balance;
	}
	int getage()const
	{
		return age;
	}
	char getgender()const
	{
		return gender;
	}
	const char* getcont()const
	{
		return contact;
	}
	Patient& operator+=(int amt)
	{
		balance += amt;
		return *this;
	}
	Patient& operator-=(int amt)
	{
		balance -= amt;
		return *this;
	}
	bool operator==(const Patient& ot)const
	{
		if (this->id == ot.id)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	friend ostream& operator<<(ostream& out, const Patient& p)
	{
		out << "ID: " << p.id << endl;
		out << "Name: " << p.name << endl;
		out << "Age: " << p.age << endl;
		out << "Gender: " << p.gender << endl;
		out << "Contact: " << p.contact << endl;
		out << "Balance [PKR]: " << p.balance << endl;
		return out;
	}
	void display()const override
	{

		cout << *this << endl;
	}
	bool login(int eID, string pass)const override
	{
		if (id == eID && password == pass)
		{
			return true;
		}
		return false;
	}


};
class Doctor : public Person
{
private:
	float fee;
	string special;
	string contact;
public:
	Doctor() :Person()
	{
		fee = 0;
		special = "";
		contact = " ";
	}
	Doctor(float fee, string special, string contact, int ID, string name, string password) :Person(ID, name, password)
	{
		this->fee = fee;
		this->special = special;
		this->contact = contact;
	}
	bool operator==(const Doctor& ot)const
	{
		if (this->id == ot.id)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	friend ostream& operator<<(ostream& out, const Doctor& d)
	{
		out << "ID: " << d.id << endl;
		out << "Name: " << d.name << endl;
		out << "Contact: " << d.contact << endl;
		out << "Fee:  " << d.fee << endl;
		return out;
	}
	void display()const override
	{

		cout << *this << endl;
	}
	bool login(int eID, string pass)const override
	{
		if (id == eID && password == pass)
		{
			return true;
		}
		return false;
	}
	float getFee() const
	{
		return fee;
	}
	string getSpecialization() const {
		return special;
	}
	string getContact() const {
		return contact;
	}

};
class Admin : public Person
{

public:
	Admin() : Person() {

	}

	Admin(int id, string name, string password)
		: Person(id, name, password) {
	}
	void display()const override
	{

		cout << "ID: " << id << endl;
		cout << "Name : " << name << endl;
	}
	bool login(int eID, string pass)const override
	{
		if (id == eID && password == pass)
		{
			return true;
		}
		return false;
	}

};
template<class Temp>
class Store {
private:
	Temp data[100];
	int count;
public:
	Store() { count = 0; }

	void adddata(const Temp& t) {
		if (count < 100)
		{
			data[count++] = t;
		}
		else
		{
			cout << "Cannot Store anymore!\n";
		}
	}
	Temp* findId(int id) {
		for (int i = 0; i < count; i++) {
			if (data[i].getId() == id) {
				return &data[i];
			}
		}
		return nullptr;
	}
	void removeId(int id) {
		for (int i = 0; i < count; i++) {
			if (data[i].getId() == id) {
				for (int j = i; j < count - 1; j++) {
					data[j] = data[j + 1];
				}
				count--;
				return;
			}
		}
		cout << "ID not found.\n";
	}

	Temp* getAll() {
		return data;
	}
	int size() const {
		return count;
	}
};
class Appointment
{
private:
	int appointmentid;
	int patientid;
	int doctorid;
	string date;
	string time;
	string stat;
public:
	Appointment(int aid = 0, int pid = 0, int did = 0, string dt = " ", string t = " ", string stat = "pending") {
		appointmentid = aid;
		patientid = pid;
		doctorid = did;
		date = dt;
		time = t;
		this->stat = stat;
	}

	int getAppID()const
	{
		return appointmentid;
	}
	int getPatID()const
	{
		return patientid;
	}
	int getDocID()const
	{
		return doctorid;
	}
	string getdate()const
	{
		return date;
	}
	string gettime()const
	{
		return time;
	}
	string getstatus()const
	{
		return stat;
	}
	void setStatus(string s) { stat = s; }
	bool operator==(const Appointment& ot)const
	{
		return (doctorid == ot.doctorid && patientid == ot.patientid && date == ot.date && time == ot.time && stat != "cancelled" && ot.stat != "cancelled");

	}
	friend ostream& operator<<(ostream& out, const Appointment ap)
	{
		out << "Appointment ID: " << ap.appointmentid << endl;
		out << "Patient ID: " << ap.patientid << endl;
		out << "Doctor ID: " << ap.doctorid << endl;
		out << "Date: " << ap.date << endl;
		out << "Time: " << ap.time << endl;
		out << "Status: " << ap.stat << endl;
		return out;
	}
	void bookAppointment(Store<Appointment>& appointments, int patientId, int doctorId, string date, string timeSlot)
	{
		int newID = appointments.size() + 1;
		Appointment newApp(newID, patientId, doctorId, date, timeSlot);
		for (int i = 0; i < appointments.size(); i++) {
			if (appointments.getAll()[i] == newApp) {
				cout << "Slot already taken!\n";
				return;
			}
		}

		appointments.adddata(newApp);
		cout << "Appointment booked successfully! ID: " << newID << endl;
	}

};

class Bill
{
private:
	int billId;
	int patientId;
	int appointmentId;
	float amount;
	string status;
	string date;

public:

	Bill(
		int billId = 0,
		int patientId = 0,
		int appointmentId = 0,
		float amount = 0,
		string status = "unpaid",
		string date = " "
	)
	{
		this->billId = billId;
		this->patientId = patientId;
		this->appointmentId = appointmentId;
		this->amount = amount;
		this->status = status;
		this->date = date;
	}

	int getId() const
	{
		return billId;
	}

	int getBillId() const
	{
		return billId;
	}

	int getPatientId() const
	{
		return patientId;
	}

	int getAppointmentId() const
	{
		return appointmentId;
	}

	float getAmount() const
	{
		return amount;
	}

	string getStatus() const
	{
		return status;
	}

	string getDate() const
	{
		return date;
	}

	void setStatus(string s)
	{
		status = s;
	}

	friend ostream& operator<<(ostream& out, const Bill& b)
	{
		out << "Bill ID: " << b.billId << endl;
		out << "Patient ID: " << b.patientId << endl;
		out << "Appointment ID: " << b.appointmentId << endl;
		out << "Amount [PKR]: " << b.amount << endl;
		out << "Status: " << b.status << endl;
		out << "Date: " << b.date << endl;

		return out;
	}
};
class HospitalException
{
protected:
	char message[200];

public:

	HospitalException(const char* msg = "Hospital Exception")
	{
		strcpy(message, msg);
	}

	virtual const char* what() const
	{
		return message;
	}
};

class FileNotFoundException : public HospitalException
{
public:

	FileNotFoundException(const char* msg)
		: HospitalException(msg)
	{
	}
};

class InsufficientFundsException : public HospitalException
{
public:

	InsufficientFundsException(const char* msg)
		: HospitalException(msg)
	{
	}
};

class InvalidInputException : public HospitalException
{
public:

	InvalidInputException(const char* msg)
		: HospitalException(msg)
	{
	}
};

class SlotUnavailableException : public HospitalException
{
public:

	SlotUnavailableException(const char* msg)
		: HospitalException(msg)
	{
	}
};
class Prescription
{
private:
	int prescriptionId;
	int patientId;
	int doctorId;
	string medicines;
	string instructions;
	string date;

public:
	Prescription(int pid = 0, int patId = 0, int docId = 0,
		string meds = "", string inst = "", string d = "")
	{
		prescriptionId = pid;
		patientId = patId;
		doctorId = docId;
		medicines = meds;
		instructions = inst;
		date = d;
	}

	int getId() const {
		return prescriptionId;
	}
	int getPrescriptionId() const {
		return prescriptionId;
	}
	int getPatientId() const {
		return patientId;
	}
	int getDoctorId() const {
		return doctorId;
	}
	string getDate() const {
		return date;
	}
	string getMedicines() const
	{
		return medicines;
	}

	string getInstructions() const
	{
		return instructions;
	}

	friend ostream& operator<<(ostream& out, const Prescription& p)
	{
		out << "Prescription ID: " << p.prescriptionId << endl;
		out << "Patient ID: " << p.patientId << endl;
		out << "Doctor ID: " << p.doctorId << endl;
		out << "Medicines: " << p.medicines << endl;
		out << "Instructions: " << p.instructions << endl;
		out << "Date: " << p.date << endl;
		return out;
	}
};

// Global Store definitions
Store<Patient> patients;
Store<Doctor> doctors;
Store<Appointment> appointments;
Store<Bill> bills;
Store<Prescription> prescriptions;
Store<MedicalRecord> records;
Store<Admin> admins;

void File::appendPrescription(const Prescription& p)
{
	ofstream file("prescriptions.txt", ios::app);

	file << p.getPrescriptionId() << ","
		<< p.getPatientId() << ","
		<< p.getDoctorId() << ","
		<< p.getMedicines() << ","
		<< p.getInstructions() << ","
		<< p.getDate() << endl;

	file.close();
}
void File::loadPrescriptions(Store<Prescription>& prescriptions)
{
	ifstream file("prescriptions.txt");

	if (!file)
	{
		return;
	}

	string line;

	while (getline(file, line))
	{
		stringstream ss(line);

		string id;
		string patId;
		string docId;
		string meds;
		string inst;
		string date;

		getline(ss, id, ',');
		getline(ss, patId, ',');
		getline(ss, docId, ',');
		getline(ss, meds, ',');
		getline(ss, inst, ',');
		getline(ss, date, ',');

		if (!id.empty())
		{
			Prescription p(
				stoi(id),
				stoi(patId),
				stoi(docId),
				meds,
				inst,
				date
			);

			prescriptions.adddata(p);
		}
	}

	file.close();
}
void File::appendMedicalRecord(const MedicalRecord& m)
{
	ofstream file("records.txt", ios::app);

	file << m.getId() << ","
		<< m.getDisease() << ","
		<< m.getAllergies() << ","
		<< m.getBloodGroup() << endl;

	file.close();
}
void File::loadMedicalRecords(Store<MedicalRecord>& records)
{
	ifstream file("records.txt");

	if (!file)
	{
		return;
	}

	string line;

	while (getline(file, line))
	{
		stringstream ss(line);

		string id;
		string disease;
		string allergies;
		string blood;

		getline(ss, id, ',');
		getline(ss, disease, ',');
		getline(ss, allergies, ',');
		getline(ss, blood, ',');

		if (!id.empty())
		{
			MedicalRecord m(
				stoi(id),
				disease,
				allergies,
				blood
			);

			records.adddata(m);
		}
	}

	file.close();
}
void createPrescription(Store<Prescription>& prescriptions, int patId, int docId)
{
	int id = prescriptions.size() + 1;

	string meds, inst, date;

	cout << "Enter Medicines: ";
	cin.ignore();
	getline(cin, meds);

	cout << "Enter Instructions: ";
	getline(cin, inst);

	cout << "Enter Date: ";
	cin >> date;

	Prescription p(id, patId, docId, meds, inst, date);

	prescriptions.adddata(p);
	File::appendPrescription(p);

	cout << "Prescription created!\n";
}
void File::loadPatients(Store<Patient>& patients) {
	ifstream file("patients.txt");
	if (!file) {
		throw FileNotFoundException("patients.txt not found");

	}

	string line;
	while (getline(file, line)) {
		stringstream ss(line);
		string id, name, age, gender, contact, pass, balance;
		getline(ss, id, ',');
		getline(ss, name, ',');
		getline(ss, age, ',');
		getline(ss, gender, ',');
		getline(ss, contact, ',');
		getline(ss, pass, ',');
		getline(ss, balance, ',');

		if (!id.empty()) {
			Patient p(stoi(id), name, stoi(age), gender[0], contact, pass, stof(balance));
			patients.adddata(p);
		}
	}
	file.close();
}
void File::appendAppointment(const Appointment& a) {
	ofstream file("appointments.txt", ios::app);
	file << a.getAppID() << "," << a.getPatID() << "," << a.getDocID() << "," << a.getdate() << "," << a.gettime() << "," << a.getstatus() << endl;
	file.close();
}
void File::appendPatient(const Patient& p) {
	ofstream file("patients.txt", ios::app);
	file << p.getId() << "," << p.getName() << "," << p.getage() << "," << p.getgender() << "," << p.getcont() << "," << p.getPassword() << "," << p.getBal() << endl;
	file.close();
}
void File::updatePatient(Store<Patient>& patients) {
	ofstream file("patients.txt");
	for (int i = 0; i < patients.size(); i++) {
		Patient& p = patients.getAll()[i];
		file << p.getId() << "," << p.getName() << "," << p.getage() << "," << p.getgender() << "," << p.getcont() << "," << p.getPassword() << "," << p.getBal() << endl;
	}
	file.close();
}
void File::deletePatient(Store<Patient>& patients, int id) {
	patients.removeId(id);
	updatePatient(patients);
}
void File::loadAppointments(Store<Appointment>& appointments)
{
	ifstream file("appointments.txt");

	if (!file) {
		throw FileNotFoundException("appointments.txt not found");
	}

	string line;

	while (getline(file, line)) {
		stringstream ss(line);

		string aid, pid, did, date, time, stat;

		getline(ss, aid, ',');
		getline(ss, pid, ',');
		getline(ss, did, ',');
		getline(ss, date, ',');
		getline(ss, time, ',');
		getline(ss, stat, ',');

		if (!aid.empty()) {
			Appointment a(stoi(aid), stoi(pid), stoi(did), date, time, stat);
			appointments.adddata(a);
		}
	}

	file.close();
}
void File::loadDoctors(Store<Doctor>& doctors)
{
	ifstream file("doctors.txt");

	if (!file) {
		throw FileNotFoundException("doctors.txt not found");
	}

	string line;

	while (getline(file, line)) {
		stringstream ss(line);

		string id, name, pass, fee, special, contact;

		getline(ss, id, ',');
		getline(ss, name, ',');
		getline(ss, pass, ',');
		getline(ss, fee, ',');
		getline(ss, special, ',');
		getline(ss, contact, ',');

		if (!id.empty()) {
			Doctor d(stof(fee), special, contact,
				stoi(id), name, pass);
			doctors.adddata(d);
		}
	}

	file.close();
}
void File::appendDoctor(const Doctor& d)
{
	ofstream file("doctors.txt", ios::app);

	file << d.getId() << ","
		<< d.getName() << ","
		<< d.getPassword() << ","
		<< d.getFee() << ","
		<< d.getSpecialization() << ","
		<< d.getContact() << endl;

	file.close();
}
void File::updateDoctors(Store<Doctor>& doctors)
{
	ofstream file("doctors.txt");

	for (int i = 0; i < doctors.size(); i++) {
		Doctor& d = doctors.getAll()[i];

		file << d.getId() << ","
			<< d.getName() << ","
			<< d.getPassword() << ","
			<< d.getFee() << ","
			<< d.getSpecialization() << ","
			<< d.getContact() << endl;
	}

	file.close();
}

template <class Validator>
Validator* loginWithAttempts(Store<Validator>& users) {
	for (int attempts = 0; attempts < 3; attempts++) {
		int id;
		string pass;
		cout << "Enter ID: ";
		cin >> id;
		cout << "Enter Password: ";
		cin >> pass;
		Validator* user = users.findId(id);
		if (user && user->login(id, pass)) {
			cout << "Login successful\n";
			return user;
		}
		cout << "Invalid credentials. Attempt " << attempts + 1 << "/3\n";
	}
	cout << "Account locked. Contact admin.\n";
	return nullptr;
}
void bookAppointment(
	Store<Appointment>& appointments,
	Store<Doctor>& Doctors,
	Patient& p,
	int doctorId,
	string date,
	string timeSlot)
{
	int newID = appointments.size() + 1;

	Appointment newApp(
		newID,
		p.getId(),
		doctorId,
		date,
		timeSlot
	);

	for (int i = 0; i < appointments.size(); i++)
	{
		if (appointments.getAll()[i] == newApp)
		{
			throw SlotUnavailableException(
				"Selected slot is already booked"
			);
		}
	}

	Doctor* d = Doctors.findId(doctorId);

	if (d == nullptr)
	{
		cout << "Doctor not found!\n";
		return;
	}

	float fee = d->getFee();

	if (p.getBal() < fee)
	{
		throw InsufficientFundsException(
			"Insufficient balance for appointment"
		);
	}

	p -= fee;

	appointments.adddata(newApp);

	File::appendAppointment(newApp);

	int billId = bills.size() + 1;

	Bill b(
		billId,
		p.getId(),
		newID,
		fee,
		"unpaid",
		date
	);

	bills.adddata(b);

	File::appendBill(b);

	File::updatePatient(patients);

	cout << "Appointment booked successfully!\n";
	cout << "Appointment ID: " << newID << endl;
}
void File::updateAppointments(Store<Appointment>& appointments)
{
	ofstream file("appointments.txt");

	for (int i = 0; i < appointments.size(); i++) {
		Appointment& a = appointments.getAll()[i];

		file << a.getAppID() << ","
			<< a.getPatID() << ","
			<< a.getDocID() << ","
			<< a.getdate() << ","
			<< a.gettime() << ","
			<< a.getstatus() << endl;
	}


	file.close();
}
void File::loadBills(Store<Bill>& bills)
{
	ifstream file("bills.txt");

	if (!file)
	{
		throw FileNotFoundException("bills.txt not found");
	}

	string line;

	while (getline(file, line))
	{
		stringstream ss(line);

		string billId;
		string patientId;
		string appointmentId;
		string amount;
		string status;
		string date;

		getline(ss, billId, ',');
		getline(ss, patientId, ',');
		getline(ss, appointmentId, ',');
		getline(ss, amount, ',');
		getline(ss, status, ',');
		getline(ss, date, ',');

		if (!billId.empty())
		{
			Bill b(
				stoi(billId),
				stoi(patientId),
				stoi(appointmentId),
				stof(amount),
				status,
				date
			);

			bills.adddata(b);
		}
	}

	file.close();
}

void File::appendBill(const Bill& b)
{
	ofstream file("bills.txt", ios::app);

	file << b.getBillId() << ","
		<< b.getPatientId() << ","
		<< b.getAppointmentId() << ","
		<< b.getAmount() << ","
		<< b.getStatus() << ","
		<< b.getDate() << endl;

	file.close();
}
void cancelAppointment(Store<Appointment>& appointments, Patient& p, int appId)
{
	for (int i = 0; i < appointments.size(); i++) {
		Appointment& a = appointments.getAll()[i];

		if (a.getAppID() == appId && a.getPatID() == p.getId()) {

			if (a.getstatus() == "pending") {
				a.setStatus("cancelled");

				float refund = 1000;
				p += refund;
				File::updateAppointments(appointments);
				cout << "Cancelled. Refund given.\n";
				return;
			}
		}
	}

	cout << "Invalid appointment ID\n";
}
void File::updateBills(Store<Bill>& bills)
{
	ofstream file("bills.txt");

	for (int i = 0; i < bills.size(); i++)
	{
		Bill& b = bills.getAll()[i];

		file << b.getBillId() << ","
			<< b.getPatientId() << ","
			<< b.getAppointmentId() << ","
			<< b.getAmount() << ","
			<< b.getStatus() << ","
			<< b.getDate() << endl;
	}

	file.close();
}
void viewAppointments(Store<Appointment>& appointments, Patient& p)
{
	Appointment temp[100];
	int n = 0;

	for (int i = 0; i < appointments.size(); i++) {
		if (appointments.getAll()[i].getPatID() == p.getId()) {
			temp[n++] = appointments.getAll()[i];
		}
	}
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (temp[j].getdate() > temp[j + 1].getdate()) {
				swap(temp[j], temp[j + 1]);
			}
		}
	}

	if (n == 0) {
		cout << "No appointments found\n";
		return;
	}

	for (int i = 0; i < n; i++) {
		cout << temp[i] << endl;
	}
}
void topUp(Patient& p, float amount)
{
	if (amount <= 0)
	{
		throw InvalidInputException(
			"Amount must be greater than 0"
		);
	}

	p += amount;
	cout << "New Balance: " << p.getBal() << endl;
}
void payBill(Patient& p, Store<Bill>& bills)
{
	bool found = false;

	for (int i = 0; i < bills.size(); i++)
	{
		Bill& b = bills.getAll()[i];

		if (
			b.getPatientId() == p.getId()
			&& b.getStatus() == "unpaid"
			)
		{
			cout << b << endl;
			found = true;
		}
	}

	if (!found)
	{
		cout << "No unpaid bills\n";
		return;
	}

	int billId;

	cout << "Enter Bill ID to pay: ";
	cin >> billId;

	for (int i = 0; i < bills.size(); i++)
	{
		Bill& b = bills.getAll()[i];

		if (
			b.getBillId() == billId
			&& b.getPatientId() == p.getId()
			&& b.getStatus() == "unpaid"
			)
		{
			if (p.getBal() < b.getAmount())
			{
				cout << "Insufficient balance\n";
				return;
			}

			p -= b.getAmount();

			b.setStatus("paid");

			File::updateBills(bills);

			File::updatePatient(patients);

			cout << "Bill paid successfully\n";
			cout << "Remaining Balance: "
				<< p.getBal() << endl;

			return;
		}
	}

	cout << "Invalid Bill ID\n";
}
void viewDoctorAppointments(Store<Appointment>& appointments, int doctorId)
{
	bool found = false;

	for (int i = 0; i < appointments.size(); i++) {
		Appointment& a = appointments.getAll()[i];

		if (a.getDocID() == doctorId) {
			cout << a << endl;
			found = true;
		}
	}

	if (!found) {
		cout << "No appointments found\n";
	}
}
void updateAppointmentStatus(Store<Appointment>& appointments, int doctorId)
{
	int appId;
	cout << "Enter Appointment ID: ";
	cin >> appId;

	for (int i = 0; i < appointments.size(); i++) {
		Appointment& a = appointments.getAll()[i];

		if (a.getAppID() == appId && a.getDocID() == doctorId) {

			cout << "1. Mark Completed\n";
			cout << "2. Cancel Appointment\n";
			int choice;
			cin >> choice;

			if (choice == 1) {
				a.setStatus("completed");
				File::updateAppointments(appointments);
				cout << "Marked as completed\n";
			}
			else if (choice == 2) {
				a.setStatus("cancelled");
				File::updateAppointments(appointments);
				cout << "Marked as cancelled\n";
			}

			return;
		}
	}

	cout << "Appointment not found\n";
}
string toLowerCase(string str)
{
	for (int i = 0; i < (int)str.length(); i++) {
		str[i] = tolower(str[i]);
	}
	return str;
}
void searchDoctorBySpecialization(Store<Doctor>& doctors, string spec)
{
	bool found = false;

	for (int i = 0; i < doctors.size(); i++) {
		Doctor& d = doctors.getAll()[i];

		if (toLowerCase(d.getSpecialization()) == toLowerCase(spec)) {
			cout << d << endl;
			found = true;
		}
	}

	if (!found) {
		cout << "No doctors found for this specialization\n";
	}
}
void viewBills(Store<Bill>& bills, Patient& p)
{
	bool found = false;

	float total = 0;

	for (int i = 0; i < bills.size(); i++)
	{
		Bill& b = bills.getAll()[i];

		if (b.getPatientId() == p.getId())
		{
			cout << b << endl;

			found = true;

			if (b.getStatus() == "unpaid")
			{
				total += b.getAmount();
			}
		}
	}

	if (!found)
	{
		cout << "No bills found\n";
		return;
	}

	cout << "Total Outstanding Amount: PKR "
		<< total << endl;
}
void addMedicalRecord(Store<MedicalRecord>& records)
{
	int id;
	string disease, allergies, blood;

	cout << "Patient ID: ";
	cin >> id;

	cout << "Disease: ";
	cin >> disease;

	cout << "Allergies: ";
	cin >> allergies;

	cout << "Blood Group: ";
	cin >> blood;

	MedicalRecord m(id, disease, allergies, blood);

	records.adddata(m);
	File::appendMedicalRecord(m);
	cout << "Record added!\n";
}
void adminReports()
{
	cout << "Total Patients: " << patients.size() << endl;
	cout << "Total Doctors: " << doctors.size() << endl;
	cout << "Total Appointments: " << appointments.size() << endl;
	cout << "Total Bills: " << bills.size() << endl;
}
void addDoctor()
{
	int id;
	string name;
	string password;
	float fee;
	string specialization;
	string contact;

	cout << "Doctor ID: ";
	cin >> id;

	cin.ignore();

	cout << "Doctor Name: ";
	getline(cin, name);

	cout << "Password: ";
	getline(cin, password);

	cout << "Fee: ";
	cin >> fee;

	cin.ignore();

	cout << "Specialization: ";
	getline(cin, specialization);

	cout << "Contact: ";
	getline(cin, contact);

	Doctor d(
		fee,
		specialization,
		contact,
		id,
		name,
		password
	);

	doctors.adddata(d);

	File::appendDoctor(d);

	cout << "Doctor Added Successfully!\n";
}
void doctorMenu(Doctor& d)
{
	int choice;

	while (true)
	{
		cout << "\n--- DOCTOR PANEL ---\n";
		cout << "1. View Appointments\n";
		cout << "2. Update Appointment Status\n";
		cout << "3. Create Prescription\n";
		cout << "4. Logout\n";
		cin >> choice;

		if (choice == 1)
		{
			viewDoctorAppointments(appointments, d.getId());
		}
		else if (choice == 2)
		{
			updateAppointmentStatus(appointments, d.getId());
		}
		else if (choice == 3)
		{
			createPrescription(prescriptions, 0, d.getId());
		}
		else
		{
			break;
		}
	}
}
bool isPositive(float x)
{
	return x > 0;
}

bool isValidDate(string date)
{
	return date.length() == 10; // basic YYYY-MM-DD check
}

bool isValidContact(string c)
{
	return c.length() >= 10;
}
void logAction(string action)
{
	ofstream file("logs.txt", ios::app);

	file << action << endl;

	file.close();
}


// --- FIXED SFML 3.0 UI COMPONENTS ---

const Color COLOR_BACKGROUND = Color(15, 20, 30);
const Color COLOR_SURFACE = Color(25, 33, 48);
const Color COLOR_ACCENT = Color(0, 188, 212);
const Color COLOR_SUCCESS = Color(72, 199, 142);
const Color COLOR_DANGER = Color(239, 83, 80);
const Color COLOR_TEXT_PRIMARY = Color(230, 236, 245);
const Color COLOR_TEXT_MUTED = Color(120, 140, 170);
const Color COLOR_BORDER = Color(50, 65, 90);

struct Button {
	RectangleShape shape;
	std::optional<Text> label; // SFML 3 texts must be optional if not created with a font
	Color normalCol, hoverCol;

	void setup(const string& text, Font& font, float x, float y, float w, float h, Color n = Color(35, 46, 65), Color hov = Color(0, 188, 212)) {
		normalCol = n; hoverCol = hov;
		shape.setSize(Vector2f(w, h));
		shape.setPosition(Vector2f(x, y));
		shape.setFillColor(n);

		label.emplace(font, text, 15);
		label->setFillColor(COLOR_TEXT_PRIMARY);

		FloatRect bounds = label->getLocalBounds();
		label->setOrigin(Vector2f(bounds.position.x + bounds.size.x / 2.0f, bounds.position.y + bounds.size.y / 2.0f));
		label->setPosition(Vector2f(x + w / 2.0f, y + h / 2.0f));
	}

	void update(Vector2f mousePos) {
		shape.setFillColor(shape.getGlobalBounds().contains(mousePos) ? hoverCol : normalCol);
	}

	void draw(RenderWindow& window) {
		window.draw(shape);
		if (label) window.draw(*label);
	}

	bool containsPoint(Vector2f p) { return shape.getGlobalBounds().contains(p); }
};

struct InputField {
	RectangleShape shape;
	std::optional<Text> displayText, placeholder;
	string buffer;
	bool isActive, isPassword;

	void setup(const string& p, Font& f, float x, float y, float w, float h = 40.0f, bool pass = false) {
		isActive = false; isPassword = pass;
		shape.setSize(Vector2f(w, h));
		shape.setPosition(Vector2f(x, y));
		shape.setFillColor(COLOR_SURFACE);
		shape.setOutlineThickness(1.5f);
		shape.setOutlineColor(COLOR_BORDER);

		displayText.emplace(f, "", 14);
		displayText->setFillColor(COLOR_TEXT_PRIMARY);
		displayText->setPosition(Vector2f(x + 10.0f, y + 10.0f));

		placeholder.emplace(f, p, 14);
		placeholder->setFillColor(COLOR_TEXT_MUTED);
		placeholder->setPosition(Vector2f(x + 10.0f, y + 10.0f));
	}

	void handleInput(std::uint32_t unicode) {
		if (!isActive) return;
		if (unicode == 8 && !buffer.empty()) buffer.pop_back(); // Backspace
		else if (unicode >= 32 && unicode < 127 && buffer.size() < 40) buffer += static_cast<char>(unicode);

		string shown = isPassword ? string(buffer.size(), '*') : buffer;
		displayText->setString(shown);
	}

	void draw(RenderWindow& window) {
		window.draw(shape);
		if (buffer.empty() && !isActive) window.draw(*placeholder);
		else window.draw(*displayText);
	}

	void clear() { buffer.clear(); displayText->setString(""); }
};

struct ScrollableTextPanel {
	RectangleShape bg;
	vector<Text> lines;
	Font* panelFont;
	float x, y, w, h, scrollOffset = 0;

	void setup(Font& f, float px, float py, float pw, float ph) {
		panelFont = &f; x = px; y = py; w = pw; h = ph;
		bg.setSize(Vector2f(w, h));
		bg.setPosition(Vector2f(x, y));
		bg.setFillColor(COLOR_SURFACE);
	}

	void setContent(const string& content) {
		lines.clear(); scrollOffset = 0;
		stringstream ss(content); string line; float ly = y + 5;
		while (getline(ss, line)) {
			Text t(*panelFont, line, 13);
			t.setPosition(Vector2f(x + 10.0f, ly));
			t.setFillColor(COLOR_TEXT_PRIMARY);
			lines.push_back(t);
			ly += 18;
		}
	}

	void draw(RenderWindow& window) {
		window.draw(bg);
		// FIX for SFML 3: FloatRect expects {pos}, {size}
		View panelView(FloatRect({ x, y }, { w, h }));
		panelView.setViewport(FloatRect({ x / 800.f, y / 600.f }, { w / 800.f, h / 600.f }));

		View oldView = window.getView();
		window.setView(panelView);
		for (auto& l : lines) {
			Text adj = l;
			adj.move(Vector2f(-x, -y + scrollOffset));
			window.draw(adj);
		}
		window.setView(oldView);
	}
};

struct Notification {
	RectangleShape bg;
	std::optional<Text> textMsg;
	float timer = 0;

	void setup(Font& f) {
		bg.setSize(Vector2f(700.0f, 35.0f));
		bg.setPosition(Vector2f(50.0f, 10.0f));
		textMsg.emplace(f, "", 14);
		textMsg->setPosition(Vector2f(60.0f, 18.0f));
	}

	void show(const string& s, bool isError = false) {
		bg.setFillColor(isError ? COLOR_DANGER : COLOR_SUCCESS);
		textMsg->setString(s); timer = 3.0f;
	}

	void update(float dt) { if (timer > 0) timer -= dt; }

	void draw(RenderWindow& window) {
		if (timer <= 0) return;
		// Fix for SFML 3 type conversion
		Color c = bg.getFillColor();
		float alpha = std::min(1.0f, timer) * 255.0f;
		c.a = static_cast<std::uint8_t>(alpha);
		bg.setFillColor(c);
		window.draw(bg);
		window.draw(*textMsg);
	}
};

enum class AppScreen { Main, PLogin, DLogin, ALogin, PPanel, DPanel, APanel };

class HospitalApplication {
	RenderWindow window;
	Font font;
	AppScreen currentScreen = AppScreen::Main;
	Notification note;
	Clock frameClock;

	Patient* activePatient = nullptr;
	Doctor* activeDoctor = nullptr;
	Admin* activeAdmin = nullptr;
	InputField loginId, loginPass;
	Button loginSub, loginBack;

	vector<Button> mainMenuBtns;
	ScrollableTextPanel pOutput;

	Button btnBookApp, btnTopUp, btnLogout;
	Button btnViewApps;
	Button btnComplete;
	Button btnPrescription;
	Button btnDLogout;
	Button btnAddDoctor;
	Button btnAdminReports;
	Button btnALogout;
	void initUI() {
		vector<string> labels = { "Patient Login", "Doctor Login", "Admin Login", "Exit" };
		for (int i = 0; i < 4; i++) {
			Button b;
			b.setup(labels[i], font, 300, 200 + i * 60, 200, 45);
			mainMenuBtns.push_back(b);
		}

		loginId.setup("Enter ID", font, 300, 200, 200);
		loginPass.setup("Password", font, 300, 260, 200, 40, true);
		loginSub.setup("Login", font, 300, 320, 95, 45, COLOR_SUCCESS);
		loginBack.setup("Back", font, 405, 320, 95, 45, COLOR_DANGER);

		pOutput.setup(font, 220, 80, 550, 480); 
			btnBookApp.setup("Book Appt", font, 20, 80, 180, 45);
		btnTopUp.setup("Top Up (500)", font, 20, 140, 180, 45, Color(100, 150, 250));
		btnLogout.setup("Logout", font, 20, 515, 180, 45, COLOR_DANGER);
		btnViewApps.setup("Appointments", font, 20, 80, 180, 45);

		btnComplete.setup(
			"Update Status",
			font,
			20,
			140,
			180,
			45
		);

		btnPrescription.setup(
			"Prescription",
			font,
			20,
			200,
			180,
			45
		);

		btnDLogout.setup(
			"Logout",
			font,
			20,
			515,
			180,
			45,
			COLOR_DANGER
		);
		btnAddDoctor.setup(
			"Add Doctor",
			font,
			20,
			80,
			180,
			45
		);

		btnAdminReports.setup(
			"System Reports",
			font,
			20,
			140,
			180,
			45
		);

		btnALogout.setup(
			"Logout",
			font,
			20,
			515,
			180,
			45,
			COLOR_DANGER
		);
		note.setup(font); 
	}

	void refreshDashboard() {
		if (!activePatient) return;
		stringstream ss;
		ss << "--- PATIENT PROFILE ---\n";
		ss << "Welcome, " << activePatient->getName() << "\n";
		ss << "Patient ID: " << activePatient->getId() << "\n";
		ss << "Current Balance: PKR " << activePatient->getBal() << "\n";
		ss << "--------------------------------------\n";
		pOutput.setContent(ss.str()); 
	}

	void handlePatientLogin() {
		try {
			if (loginId.buffer.empty()) return;
			int id = stoi(loginId.buffer);
			string pass = loginPass.buffer;

			activePatient = patients.findId(id);
				if (activePatient && activePatient->login(id, pass)) {
				
					currentScreen = AppScreen::PPanel;
					refreshDashboard();
					loginId.clear();
					loginPass.clear();
				}
				else {
					note.show("Invalid Credentials", true);
				}
		}
		catch (...) {
			note.show("Invalid ID format", true);
		}
	}
	void handleDoctorLogin()
	{
		try {

			if (loginId.buffer.empty())
				return;

			int id = stoi(loginId.buffer);

			string pass = loginPass.buffer;

			activeDoctor = doctors.findId(id);

			if (
				activeDoctor &&
				activeDoctor->login(id, pass)
				)
			{
				currentScreen = AppScreen::DPanel;

				loginId.clear();
				loginPass.clear();

				note.show("Doctor login successful");
			}
			else {
				note.show("Invalid Credentials", true);
			}
		}
		catch (...) {
			note.show("Invalid ID format", true);
		}
	}
	void handleAdminLogin()
	{
		try {

			if (loginId.buffer.empty())
				return;

			int id = stoi(loginId.buffer);

			string pass = loginPass.buffer;

			activeAdmin = admins.findId(id);

			if (
				activeAdmin &&
				activeAdmin->login(id, pass)
				)
			{
				currentScreen = AppScreen::APanel;

				loginId.clear();
				loginPass.clear();

				note.show("Admin login successful");
			}
			else {
				note.show("Invalid Credentials", true);
			}
		}
		catch (...) {

			note.show("Invalid ID format", true);
		}
	}

public:
	HospitalApplication() : window(VideoMode({ 800, 600 }), "Hospital System") {
		window.setFramerateLimit(60);
		if (!font.openFromFile("arial.ttf")) {  } 
			initUI();
	}

	void run() {
		while (window.isOpen()) {
			float dt = frameClock.restart().asSeconds();
			note.update(dt);
			Vector2f mPos = (Vector2f)Mouse::getPosition(window);

			while (auto eventOptional = window.pollEvent()) {
				auto& e = *eventOptional;
				if (e.is<Event::Closed>()) window.close();

				if (auto* mb = e.getIf<Event::MouseButtonPressed>()) {
					Vector2f clickPos = (Vector2f)mb->position;

					if (currentScreen == AppScreen::Main) {

						if (mainMenuBtns[0].containsPoint(clickPos))
							currentScreen = AppScreen::PLogin;

						if (mainMenuBtns[1].containsPoint(clickPos))
							currentScreen = AppScreen::DLogin;

						if (mainMenuBtns[2].containsPoint(clickPos))
							currentScreen = AppScreen::ALogin;

						if (mainMenuBtns[3].containsPoint(clickPos))
							window.close();
					}
					else if (currentScreen == AppScreen::PLogin) {
						loginId.isActive = loginId.shape.getGlobalBounds().contains(clickPos);
						loginPass.isActive = loginPass.shape.getGlobalBounds().contains(clickPos);
						if (loginBack.containsPoint(clickPos)) currentScreen = AppScreen::Main;
						if (loginSub.containsPoint(clickPos)) handlePatientLogin();
					}
					else if (currentScreen == AppScreen::DLogin) {

						loginId.isActive =
							loginId.shape.getGlobalBounds().contains(clickPos);

						loginPass.isActive =
							loginPass.shape.getGlobalBounds().contains(clickPos);

						if (loginBack.containsPoint(clickPos))
							currentScreen = AppScreen::Main;

						if (loginSub.containsPoint(clickPos))
							handleDoctorLogin();
					}
					else if (currentScreen == AppScreen::ALogin) {

						loginId.isActive =
							loginId.shape.getGlobalBounds().contains(clickPos);

						loginPass.isActive =
							loginPass.shape.getGlobalBounds().contains(clickPos);

						if (loginBack.containsPoint(clickPos))
							currentScreen = AppScreen::Main;

						if (loginSub.containsPoint(clickPos))
							handleAdminLogin();
					}
					else if (currentScreen == AppScreen::PPanel) 
					{
						if (btnLogout.containsPoint(clickPos)) {
							activePatient = nullptr;
							currentScreen = AppScreen::Main;
						}
					
						if (btnTopUp.containsPoint(clickPos)) {
							*activePatient += 500;
							File::updatePatient(patients); 
								note.show("Added PKR 500 successfully");
							refreshDashboard();
						}
						if (btnBookApp.containsPoint(clickPos)) {
							try {
								bookAppointment(appointments, doctors, *activePatient, 1, "2026-05-15", "10:00 AM");
								note.show("Appointment Booked!");
								refreshDashboard();
							}
							catch (HospitalException& ex) {
								note.show(ex.what(), true);
							}
						}
					}
					else if (currentScreen == AppScreen::DPanel) {

						if (btnDLogout.containsPoint(clickPos)) {

							activeDoctor = nullptr;

							currentScreen = AppScreen::Main;
						}

						if (btnViewApps.containsPoint(clickPos)) {

							stringstream ss;

							ss << "--- DOCTOR APPOINTMENTS ---\n\n";

							for (int i = 0; i < appointments.size(); i++) {

								Appointment& a = appointments.getAll()[i];

								if (a.getDocID() == activeDoctor->getId()) {

									ss << "Appointment ID: "
										<< a.getAppID() << "\n";

									ss << "Patient ID: "
										<< a.getPatID() << "\n";

									ss << "Date: "
										<< a.getdate() << "\n";

									ss << "Time: "
										<< a.gettime() << "\n";

									ss << "Status: "
										<< a.getstatus() << "\n\n";
								}
							}

							pOutput.setContent(ss.str());
						}

						if (btnPrescription.containsPoint(clickPos)) {

							createPrescription(
								prescriptions,
								1,
								activeDoctor->getId()
							);

							note.show("Prescription Added");
						}
					}
					else if (currentScreen == AppScreen::APanel) {

						if (btnALogout.containsPoint(clickPos)) {

							activeAdmin = nullptr;

							currentScreen = AppScreen::Main;
						}

						if (btnAddDoctor.containsPoint(clickPos)) {

							addDoctor();

							note.show("Doctor Added");
						}

						if (btnAdminReports.containsPoint(clickPos)) {

							stringstream ss;

							ss << "--- SYSTEM REPORTS ---\n\n";

							ss << "Patients: "
								<< patients.size() << "\n";

							ss << "Doctors: "
								<< doctors.size() << "\n";

							ss << "Appointments: "
								<< appointments.size() << "\n";

							ss << "Bills: "
								<< bills.size() << "\n";

							pOutput.setContent(ss.str());
						}
					}
				}

				if (auto* textEvent = e.getIf<Event::TextEntered>()) {

					if (
						currentScreen == AppScreen::PLogin ||
						currentScreen == AppScreen::DLogin ||
						currentScreen == AppScreen::ALogin
						)
					{
						loginId.handleInput(textEvent->unicode);

						loginPass.handleInput(textEvent->unicode);
					}
				}
			}

			window.clear(COLOR_BACKGROUND);

			if (currentScreen == AppScreen::Main) {
				for (auto& b : mainMenuBtns) { b.update(mPos); b.draw(window); }
			}
			else if (currentScreen == AppScreen::PLogin) {
				loginId.draw(window); loginPass.draw(window);
				loginSub.update(mPos); loginSub.draw(window);
				loginBack.update(mPos); loginBack.draw(window);
			}
			else if (currentScreen == AppScreen::DLogin) {

				loginId.draw(window);

				loginPass.draw(window);

				loginSub.update(mPos);
				loginSub.draw(window);

				loginBack.update(mPos);
				loginBack.draw(window);
			}
			else if (currentScreen == AppScreen::ALogin) {

				loginId.draw(window);

				loginPass.draw(window);

				loginSub.update(mPos);
				loginSub.draw(window);

				loginBack.update(mPos);
				loginBack.draw(window);
			}
			else if (currentScreen == AppScreen::PPanel) {
				pOutput.draw(window); 
					btnBookApp.update(mPos); btnBookApp.draw(window);
				btnTopUp.update(mPos); btnTopUp.draw(window);
				btnLogout.update(mPos); btnLogout.draw(window);
			}
			else if (currentScreen == AppScreen::DPanel) {

				pOutput.draw(window);

				btnViewApps.update(mPos);
				btnViewApps.draw(window);

				btnComplete.update(mPos);
				btnComplete.draw(window);

				btnPrescription.update(mPos);
				btnPrescription.draw(window);

				btnDLogout.update(mPos);
				btnDLogout.draw(window);
			}
			else if (currentScreen == AppScreen::APanel) {

				pOutput.draw(window);

				btnAddDoctor.update(mPos);
				btnAddDoctor.draw(window);

				btnAdminReports.update(mPos);
				btnAdminReports.draw(window);

				btnALogout.update(mPos);
				btnALogout.draw(window);
			}

			note.draw(window);
			window.display();
		}
	}
};
int main() {
	// Original data loading logic
	try {
		File::loadPatients(patients);
		File::loadDoctors(doctors);
		File::loadAppointments(appointments);
		File::loadBills(bills);
		File::loadPrescriptions(prescriptions);
		File::loadMedicalRecords(records);
	}
	catch (HospitalException& ex) {
		cout << ex.what() << endl;
	}
	admins.adddata(
		Admin(
			999,
			"Admin",
			"admin123"
		)
	);
	HospitalApplication app;
	app.run();
	return 0;
}



