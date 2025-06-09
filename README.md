# Hospital-Management
A C++ console-based Hospital Management System with role-based logins (Patient, Doctor, Admin), appointment booking, and doctor management using core data structures like maps, queues, and stacks.

# Hospital Management System (C++)

A console-based Hospital Management System written in **C++**, designed to simulate real-world hospital operations like patient appointment booking, doctor management, and admin control. It utilizes core data structures such as maps, queues, stacks, and vectors to handle internal processes efficiently.

---

## 🔧 Features

- 📋 **User Roles**: Patient, Doctor, Admin logins
- 🏥 **Patient**:
  - Register or log in
  - Book appointments by specialization
  - View appointment history
- 👨‍⚕️ **Doctor**:
  - View profile
  - View assigned appointments
- 🛠️ **Admin**:
  - Add doctors
  - View all pending appointments
- 🏪 **Other Functionalities**:
  - Services overview
  - About the hospital
  - Emergency contacts
  - Contact information

---

## 📁 Technologies & Concepts Used

- C++ Programming
- Standard Template Library (STL):
  - `map`, `vector`, `queue`, `stack`, `list`
- OOP Concepts (Structs and Modularity)
- CLI Menu-Driven Interface

---

## 🧪 Login Credentials (Hardcoded)

- 👤 **Admin Login**
  - Username: `admin`
  - Password: `password`

- 👨‍⚕️ **Doctor Login**
  - Username and password are set during doctor creation by the Admin in `addDoctor()` function.

- 🧑 **Patient Login**
  - Option to **sign up** with custom username and password
  - Login is validated based on existing patient record

---

## 🚀 How to Run

1. Open any C++ compiler (e.g., VS Code with C++ extension, CodeBlocks, Dev C++)
2. Create a new project and paste the code from `Hospital_Management_2.cpp`
3. Compile and Run the file
