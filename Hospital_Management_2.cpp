#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <map>
#include <ctime>

using namespace std;

// Structs for user, doctor, and appointment information
struct User {
    string username, password, name, address, city, gender, email;
};

struct Doctor {
    string username, password; // Add username and password fields
    string name, specialization, address, contactNo, email, workExperience;
    double consultancyFees;
};

struct Appointment {
    string patientName, specialization, doctorName;
    double consultancyFees;
    string status;
};

map<string, vector<Doctor>> doctorsBySpecialization; // Store doctors by specialization
map<string, Doctor> doctorLoginData; // Store doctor login data (username and password)
map<string, vector<Appointment>> patientAppointments; // Store appointments for patients
map<string, Appointment> appointmentsHistory; // All appointments stored here
queue<Appointment> appointmentsQueue; // Queue for appointments

// Function prototypes
void homePage();
void services();
void aboutUs();
void contactUs();
void emergency();
void logins();
void patientLogin();
void doctorLogin();
void adminLogin();
void handlePatientActions(User&);
void handleDoctorActions(Doctor&);
void handleAdminActions();
void addSpecialization();
void manageDoctors();
void manageUsers();
void addDoctor();
void viewAppointments();

void homePage() {
    while (true) {
        cout << "Welcome to our Hospital Management\n";
        cout << "1. Services\n2. About Us\n3. Contact Us\n4. Logins\n5. Emergency\n6. Exit\n";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: services(); break;
            case 2: aboutUs(); break;
            case 3: contactUs(); break;
            case 4: logins(); break;
            case 5: emergency(); break;
            case 6: return; // Exit the program
            default: cout << "Invalid choice. Try again.\n"; break;
        }
    }
}

void services() {
    cout << "These services are available in our Hospital:\n";
    cout << "Cardiology\nOrthopaedic\nNeurology\nGastroenterology\n";
}

void aboutUs() {
    cout << "Our hospital is committed to providing the best healthcare services.\n";
    cout << "We have a specialized team of doctors with expertise in various fields.\n";
    cout << "Our hospital management ensures seamless operations and top-notch care for patients.\n";
    cout << "We pride ourselves on using the latest technology and experienced staff to provide exceptional medical services.\n";
}

void contactUs() {
    cout << "Hospital Address: Navi Mumbai, Maharashtra\n";
    cout << "Email: xyz@hospital.in\n";
    cout << "Phone: 861xxxxx98\n";
    cout << "Web Portal: www.xyzhospital.com\n";
    cout << "Please fill out the contact form with your query.\n";
}

void emergency() {
    cout << "Ambulance Contact Numbers:\n";
    cout << "Ambulance 1: 90XXXXXX02\nAmbulance 2: 90XXXXXX52\nAmbulance 3: 90XXXXXX56\n";
    cout << "Ambulance 4: 90XXXXXX86\nAmbulance 5: 90XXXXXX90\n";
}

void logins() {
    while (true) {
        cout << "1. Patient Login\n2. Doctor Login\n3. Admin Login\n4. Back to Home\n";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: patientLogin(); break;
            case 2: doctorLogin(); break;
            case 3: adminLogin(); break;
            case 4: return;
            default: cout << "Invalid choice. Try again.\n"; break;
        }
    }
}

void patientLogin() {
    string username, password;
    cout << "Already Account? (y/n): ";
    char option;
    cin >> option;

    if (option == 'y' || option == 'Y') {
        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter Password: ";
        cin >> password;
        if (patientAppointments.find(username) != patientAppointments.end()) {
            User user = {username, password, "John Doe", "Navi Mumbai", "Maharashtra", "Male", "john.doe@gmail.com"};
            handlePatientActions(user);
        } else {
            cout << "Invalid username or password. Try again.\n";
        }
    } else {
        // Create new account
        User newUser;
        cout << "Enter Full Name: ";
        cin.ignore();
        getline(cin, newUser.name);
        cout << "Enter Address: ";
        getline(cin, newUser.address);
        cout << "Enter City: ";
        getline(cin, newUser.city);
        cout << "Enter Gender: ";
        cin >> newUser.gender;
        cout << "Enter Email: ";
        cin >> newUser.email;
        cout << "Create Username: ";
        cin >> newUser.username;
        cout << "Create Password: ";
        cin >> newUser.password;
        cout << "Account Created!\n";
        patientAppointments[newUser.username]; // Initialize empty appointment list
        handlePatientActions(newUser);
    }
}

void handlePatientActions(User& user) {
    while (true) {
        cout << "1. My Profile\n2. Book Appointment\n3. My Appointments\n4. Logout\n";
        int choice;
        cin >> choice;
        if (choice == 4) return;

        switch (choice) {
            case 1:
                cout << "Profile Details:\n";
                cout << "Username: " << user.username << "\nAddress: " << user.address
                     << "\nCity: " << user.city << "\nGender: " << user.gender
                     << "\nEmail: " << user.email << "\n";
                break;

            case 2: {
                cout << "Choose Doctor Specialization: ";
                string specialization;
                cin >> specialization;
                if (doctorsBySpecialization.find(specialization) != doctorsBySpecialization.end()) {
                    cout << "Choose Doctor:\n";
                    int index = 1;
                    for (auto& doc : doctorsBySpecialization[specialization]) {
                        cout << index++ << ". " << doc.name << " (" << doc.consultancyFees << ")\n";
                    }
                    int docChoice;
                    cin >> docChoice;
                    Doctor& doctor = doctorsBySpecialization[specialization][docChoice - 1];

                    // Create appointment object
                    Appointment appointment = {user.name, specialization, doctor.name, doctor.consultancyFees, "Pending"};

                    // Add appointment to the patient's personal list
                    patientAppointments[user.username].push_back(appointment);

                    // Add to the appointments queue for doctors to see
                    appointmentsQueue.push(appointment);

                    // Store appointment in appointments history with a unique identifier
                    string appointmentKey = user.username + "_" + to_string(time(nullptr)); // Create unique key using username + timestamp
                    appointmentsHistory[appointmentKey] = appointment; // Store in the history

                    cout << "Appointment Booked Successfully!\n";
                } else {
                    cout << "Specialization not available.\n";
                }
                break;
            }

            case 3: {
                cout << "My Appointments:\n";
                if (!patientAppointments[user.username].empty()) {
                    for (const auto& app : patientAppointments[user.username]) {
                        cout << "Doctor: " << app.doctorName << ", Specialization: " << app.specialization
                             << ", Fees: " << app.consultancyFees << ", Status: " << app.status << "\n";
                    }
                } else {
                    cout << "No Appointments Available.\n";
                }
                break;
            }

            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}

void doctorLogin() {
    string username, password;
    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;

    // Check if the doctor exists in the doctorLoginData map
    if (doctorLoginData.find(username) != doctorLoginData.end() && doctorLoginData[username].password == password) {
        Doctor doctor = doctorLoginData[username];
        handleDoctorActions(doctor);
    } else {
        cout << "Invalid username or password.\n";
    }
}

void handleDoctorActions(Doctor& doctor) {
    while (true) {
        cout << "1. My Profile\n2. My Appointments\n3. Logout\n";
        int choice;
        cin >> choice;
        if (choice == 3) return;

        switch (choice) {
            case 1:
                cout << "Doctor Profile:\n";
                cout << "Name: " << doctor.name << "\nSpecialization: " << doctor.specialization
                     << "\nAddress: " << doctor.address << "\nContact: " << doctor.contactNo
                     << "\nEmail: " << doctor.email << "\nConsultancy Fees: " << doctor.consultancyFees
                     << "\nWork Experience: " << doctor.workExperience << "\n";
                break;

            case 2: {
                cout << "Appointments:\n";
                if (!appointmentsQueue.empty()) {
                    // Doctor views and manages appointments
                    stack<Appointment> tempStack;
                    while (!appointmentsQueue.empty()) {
                        Appointment currentApp = appointmentsQueue.front();
                        appointmentsQueue.pop();
                        if (currentApp.doctorName == doctor.name) {
                            cout << "Patient: " << currentApp.patientName
                                 << ", Specialization: " << currentApp.specialization
                                 << ", Status: " << currentApp.status << "\n";
                        } else {
                            tempStack.push(currentApp); // Store other appointments
                        }
                    }
                    while (!tempStack.empty()) {
                        appointmentsQueue.push(tempStack.top());
                        tempStack.pop();
                    }
                } else {
                    cout << "No appointments available.\n";
                }
                break;
            }

            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}

void adminLogin() {
    string username, password;
    cout << "Enter Admin Username: ";
    cin >> username;
    cout << "Enter Admin Password: ";
    cin >> password;

    if (username == "admin" && password == "password") {
        handleAdminActions();
    } else {
        cout << "Invalid Admin credentials.\n";
    }
}

void handleAdminActions() {
    while (true) {
        cout << "1. Add Doctor\n2. View Appointments\n3. Logout\n";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: addDoctor(); break;
            case 2: viewAppointments(); break;
            case 3: return;
            default: cout << "Invalid choice. Try again.\n"; break;
        }
    }
}

void addDoctor() {
    Doctor newDoctor;
    cout << "Enter Doctor Name: ";
    cin.ignore();
    getline(cin, newDoctor.name);
    cout << "Enter Specialization: ";
    cin >> newDoctor.specialization;
    cout << "Enter Address: ";
    cin.ignore();
    getline(cin, newDoctor.address);
    cout << "Enter Contact No: ";
    cin >> newDoctor.contactNo;
    cout << "Enter Email: ";
    cin >> newDoctor.email;
    cout << "Enter Consultancy Fees: ";
    cin >> newDoctor.consultancyFees;
    cout << "Enter Work Experience (in years): ";
    cin >> newDoctor.workExperience;

    // Add username and password for doctor login
    cout << "Create Username: ";
    cin >> newDoctor.username;
    cout << "Create Password: ";
    cin >> newDoctor.password;

    doctorsBySpecialization[newDoctor.specialization].push_back(newDoctor);
    doctorLoginData[newDoctor.username] = newDoctor; // Store doctor login data

    cout << "Doctor added successfully!\n";
}

void viewAppointments() {
    if (!appointmentsQueue.empty()) {
        cout << "Pending Appointments:\n";
        queue<Appointment> tempQueue = appointmentsQueue;
        while (!tempQueue.empty()) {
            Appointment currentApp = tempQueue.front();
            tempQueue.pop();
            cout << "Patient: " << currentApp.patientName
                 << ", Specialization: " << currentApp.specialization
                 << ", Doctor: " << currentApp.doctorName
                 << ", Status: " << currentApp.status << "\n";
        }
    } else {
        cout << "No pending appointments.\n";
    }
}

int main() {
    homePage();
    return 0;
}
