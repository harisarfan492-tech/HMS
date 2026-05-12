#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<cstring>
using namespace std;


template<class Temp> class Store;
class Patient;
class Appointment;
class Doctor;
class Bill;
class Prescription;
class MedicalRecord;



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



int main() {
	try {
		File::loadPatients(patients);
		File::loadAppointments(appointments);
		File::loadDoctors(doctors);
		File::loadBills(bills);
		File::loadPrescriptions(prescriptions);
		File::loadMedicalRecords(records);
	}
	catch (HospitalException & e) {

		cout << "Something went Horribly wrong";
	}
	while (true)
	{
		cout << "\n=====================================\n";
		cout << "     HOSPITAL MANAGEMENT SYSTEM\n";
		cout << "=====================================\n";
		cout << "1. Patient Login\n";
		cout << "2. Doctor Login\n";
		cout << "3. Admin Login\n";
		cout << "4. Exit\n";
		cout << "Enter choice: ";
		int choice;
		cin >> choice;

		// =========================
		// PATIENT LOGIN
		// =========================

		if (choice == 1)
		{
			Patient* p = loginWithAttempts(patients);

			if (p == nullptr)
			{
				continue;
			}

			logAction("Patient logged in");

			int pChoice;

			while (true)
			{
				cout << "\n========== PATIENT PANEL ==========\n";
				cout << "1. Book Appointment\n";
				cout << "2. Cancel Appointment\n";
				cout << "3. View Appointments\n";
				cout << "4. Search Doctor by Specialization\n";
				cout << "5. View Bills\n";
				cout << "6. Pay Bills\n";
				cout << "7. Top Up Balance\n";
				cout << "8. Logout\n";
				cout << "Enter choice: ";
				cin >> pChoice;

				if (pChoice == 1)
				{
					int docId;
					string date, time;

					cout << "Enter Doctor ID: ";
					cin >> docId;

					cout << "Enter Date (YYYY-MM-DD): ";
					cin >> date;

					cout << "Enter Time: ";
					cin >> time;

					try
					{
						bookAppointment(
							appointments,
							doctors,
							*p,
							docId,
							date,
							time
						);

						logAction("Appointment booked");
					}
					catch (HospitalException& e)
					{
						cout << e.what() << endl;
					}
				}
				else if (pChoice == 2)
				{
					int appId;

					cout << "Enter Appointment ID: ";
					cin >> appId;

					cancelAppointment(
						appointments,
						*p,
						appId
					);

					logAction("Appointment cancelled");
				}
				else if (pChoice == 3)
				{
					viewAppointments(
						appointments,
						*p
					);
				}
				else if (pChoice == 4)
				{
					string spec;

					cout << "Enter Specialization: ";
					cin >> spec;

					searchDoctorBySpecialization(
						doctors,
						spec
					);
				}
				else if (pChoice == 5)
				{
					viewBills(bills, *p);
				}
				else if (pChoice == 6)
				{
					payBill(*p, bills);

					logAction("Bill paid");
				}
				else if (pChoice == 7)
				{
					float amt;

					cout << "Enter Amount: ";
					cin >> amt;

					try
					{
						topUp(*p, amt);

						logAction("Balance topped up");
					}
					catch (HospitalException& e)
					{
						cout << e.what() << endl;
					}
				}
				else if (pChoice == 8)
				{
					cout << "Logging out...\n";
					break;
				}
				else
				{
					cout << "Invalid choice\n";
				}
			}
		}

		// =========================
		// DOCTOR LOGIN
		// =========================

		else if (choice == 2)
		{
			Doctor* d = loginWithAttempts(doctors);

			if (d == nullptr)
			{
				continue;
			}

			logAction("Doctor logged in");

			int dChoice;

			while (true)
			{
				cout << "\n========== DOCTOR PANEL ==========\n";
				cout << "1. View My Appointments\n";
				cout << "2. Update Appointment Status\n";
				cout << "3. Create Prescription\n";
				cout << "4. Add Medical Record\n";
				cout << "5. Logout\n";
				cout << "Enter choice: ";
				cin >> dChoice;

				if (dChoice == 1)
				{
					viewDoctorAppointments(
						appointments,
						d->getId()
					);
				}
				else if (dChoice == 2)
				{
					updateAppointmentStatus(
						appointments,
						d->getId()
					);

					logAction("Doctor updated appointment");
				}
				else if (dChoice == 3)
				{
					int patId;

					cout << "Enter Patient ID: ";
					cin >> patId;

					createPrescription(
						prescriptions,
						patId,
						d->getId()
					);

					logAction("Prescription created");
				}
				else if (dChoice == 4)
				{
					addMedicalRecord(records);

					logAction("Medical record added");
				}
				else if (dChoice == 5)
				{
					cout << "Logging out...\n";
					break;
				}
				else
				{
					cout << "Invalid choice\n";
				}
			}
		}

		// =========================
		// ADMIN LOGIN
		// =========================

		else if (choice == 3)
		{
			int id;
			string pass;

			cout << "Admin ID: ";
			cin >> id;

			cout << "Password: ";
			cin >> pass;

			Admin admin(
				1,
				"Admin",
				"admin123"
			);

			if (!admin.login(id, pass))
			{
				cout << "Invalid credentials\n";
				continue;
			}

			logAction("Admin logged in");

			int aChoice;

			while (true)
			{
				cout << "\n========== ADMIN PANEL ==========\n";

				cout << "1. View All Patients\n";
				cout << "2. Add Patient\n";
				cout << "3. Delete Patient\n";

				cout << "4. View All Doctors\n";
				cout << "5. Add Doctor\n";

				cout << "6. View All Appointments\n";
				cout << "7. View All Bills\n";
				cout << "8. View Reports\n";
				cout << "9. View Activity Logs\n";

				cout << "10. Logout\n";

				cout << "Enter choice: ";
				cin >> aChoice;

				if (aChoice == 1)
				{
					for (int i = 0; i < patients.size(); i++)
					{
						cout << patients.getAll()[i]
							<< endl;
					}
				}

				else if (aChoice == 2)
				{
					int id, age;
					string name, pass, contact;
					char gender;
					float balance;

					cout << "Enter ID: ";
					cin >> id;

					cout << "Name: ";
					cin >> name;

					cout << "Age: ";
					cin >> age;

					cout << "Gender: ";
					cin >> gender;

					cout << "Contact: ";
					cin >> contact;

					cout << "Password: ";
					cin >> pass;

					cout << "Balance: ";
					cin >> balance;

					Patient p(
						id,
						name,
						age,
						gender,
						contact,
						pass,
						balance
					);

					patients.adddata(p);

					File::appendPatient(p);

					logAction("Patient added");

					cout << "Patient added successfully\n";
				}

				else if (aChoice == 3)
				{
					int id;

					cout << "Enter Patient ID: ";
					cin >> id;

					File::deletePatient(
						patients,
						id
					);

					logAction("Patient deleted");
				}

				else if (aChoice == 4)
				{
					for (int i = 0; i < doctors.size(); i++)
					{
						cout << doctors.getAll()[i]
							<< endl;
					}
				}

				else if (aChoice == 5)
				{
					int id;
					string name;
					string pass;
					string special;
					string contact;
					float fee;

					cout << "Doctor ID: ";
					cin >> id;

					cout << "Name: ";
					cin >> name;

					cout << "Password: ";
					cin >> pass;

					cout << "Specialization: ";
					cin >> special;

					cout << "Contact: ";
					cin >> contact;

					cout << "Fee: ";
					cin >> fee;

					Doctor d(
						fee,
						special,
						contact,
						id,
						name,
						pass
					);

					doctors.adddata(d);

					File::appendDoctor(d);

					logAction("Doctor added");

					cout << "Doctor added successfully\n";
				}

				else if (aChoice == 6)
				{
					for (int i = 0; i < appointments.size(); i++)
					{
						cout << appointments.getAll()[i]
							<< endl;
					}
				}

				else if (aChoice == 7)
				{
					for (int i = 0; i < bills.size(); i++)
					{
						cout << bills.getAll()[i]
							<< endl;
					}
				}

				else if (aChoice == 8)
				{
					adminReports();
				}

				else if (aChoice == 9)
				{
					ifstream file("logs.txt");

					string line;

					while (getline(file, line))
					{
						cout << line << endl;
					}

					file.close();
				}

				else if (aChoice == 10)
				{
					cout << "Logging out...\n";
					break;
				}

				else
				{
					cout << "Invalid choice\n";
				}
			}
		}

		else if (choice == 4)
		{
			cout << "Shutting down system...\n";
			break;
		}

		else
		{
			cout << "Invalid choice\n";
		}
	}

	return 0;
}