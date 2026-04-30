# 🏧 ATM Banking System - Cash Withdrawal Subsystem

**Institute:** Veermata Jijabai Technological Institute (VJTI)  
**Course:** Software Engineering (R5IT2009T) – End Semester Lab Exam  
**Date:** 30-05-2026  

## 👨‍🎓 Student Information
- **Name:** Vardhan Mali  
- **ID No:** 241070038  
- **Program:** IV, B.Tech Computer Engineering  

---

## 📌 Project Overview
This repository contains the source code and documentation for the **Cash Withdrawal Subsystem** of an ATM Banking System.  

The project focuses on:
- Robust **Object-Oriented Design**
- Comprehensive **Automated Testing**

---

## ⚙️ Core Functionalities

### 🔐 Card Authentication
- PIN verification with a **maximum of 3 attempts**
- Account is **blocked after 3 failed attempts**

### 💰 Withdrawal Validation
Ensures that:
- Amount is **positive**
- Amount is a **multiple of 100**
- Within **daily withdrawal limits**
- Does **not exceed available balance**

### 🧪 Automated Verification
- Integrated **test runners**
- Ensures all system requirements are verified programmatically

---

## 📂 File Structure

| File Name        | Description |
|-----------------|------------|
| `codecheck.cpp` | Integrated C++ source code with classes and automated test suite |
| `sheet1.csv`    | 15 Black Box test cases (ECP/BVA) |
| `whitebox.csv`  | 15 White Box test cases (Path/Branch Coverage) |

---

## 🏗️ Design & Implementation (Q2 A.1)

The system follows the **Entity-Boundary-Control (EBC)** design pattern:

- **Entity (Account)**  
  Manages persistent data such as PIN, balance, and account status  

- **Control (BankServer)**  
  Handles business logic, transaction processing, and security checks  

- **Boundary (ATMInterface)**  
  Manages user interaction (CLI-based in this implementation)  

---

## 🧪 Testing Report (Q2 A.2)

### 1️⃣ Black Box Testing
- **Techniques Used:**  
  - Equivalence Class Partitioning (ECP)  
  - Boundary Value Analysis (BVA)  

- **Coverage:**  
  - 15 test cases  
  - Validates input types, PIN handling, and boundary conditions  

---

### 2️⃣ White Box Testing
- **Techniques Used:**  
  - Statement Coverage  
  - Branch Coverage  
  - Path Coverage  

- **Cyclomatic Complexity:**  

V(G) = 11


- **Coverage Goal:**  
- Achieved **100% Statement and Branch Coverage**  
- All **11 independent paths** tested  

---

## 🚀 Execution Instructions

### 🔧 Compile
```bash
g++ codecheck.cpp -o codecheck
▶️ Run
./codecheck
📊 Automated Results Summary

After execution, the system displays:

ID: Test Case identifier (e.g., TC01, W05)
Result: SUCCESS / FAILURE
System Message: Output returned by the system
✅ Final Checklist
 UML Use Case and Activity Diagrams (Paper-based)
 Sequence Diagram and ECB Analysis (Paper-based)
 C++ Implementation with Exception Handling
 15 Black Box Test Cases documented
 15 White Box Test Cases documented
 Automated CLI Verification
