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
This repository contains the implementation of the **Cash Withdrawal Subsystem** of an ATM Banking System with a strong focus on:

- Object-Oriented Design  
- Black Box and White Box Testing  
- Automated validation of system behavior  

---

## ⚙️ Core Functionalities

### 🔐 Card Authentication
- PIN verification with a **3-attempt limit**
- Account **blocked after 3 incorrect attempts**

### 💰 Withdrawal Validation
- Amount must be **positive**
- Must be a **multiple of 100**
- Within **daily limit**
- Must not exceed **available balance**

---

## 📂 File Structure

| File Name        | Description |
|-----------------|------------|
| `blackbox.cpp`  | C++ implementation + Black Box test execution |
| `whitebox.cpp`  | C++ implementation + White Box test execution |
| `sheet1.csv`    | 15 Black Box test cases (ECP/BVA) |
| `whitebox.csv`  | 15 White Box test cases (Path/Branch Coverage) |

---

## 🏗️ Design & Implementation (Q2 A.1)

The system follows the **Entity-Boundary-Control (EBC)** design pattern:

- **Entity (Account)** → Stores PIN, balance, account status  
- **Control (BankServer)** → Handles logic and validation  
- **Boundary (ATMInterface)** → CLI-based interaction  

---

## 🧪 Testing Report (Q2 A.2)

### 1️⃣ Black Box Testing
- Techniques: **ECP, BVA**  
- 15 test cases covering:
  - Valid/invalid inputs  
  - PIN attempts  
  - Boundary values  

---

### 2️⃣ White Box Testing
- Techniques:
  - Statement Coverage  
  - Branch Coverage  
  - Path Coverage  

- Cyclomatic Complexity:

V(G) = 11


- All **independent paths tested**

---

## 🚀 Execution Instructions

### 🔧 Compile & Run Black Box Tests
```bash
g++ blackbox.cpp -o blackbox
./blackbox
🔧 Compile & Run White Box Tests
g++ whitebox.cpp -o whitebox
./whitebox
📊 Output Format

Each test case displays:

Test Case ID
Result: SUCCESS / FAILURE
System Message
✅ Final Checklist
 UML Diagrams (Use Case, Activity)
 Sequence Diagram & ECB Analysis
 C++ Implementation
 15 Black Box Test Cases
 15 White Box Test Cases
 Automated Testing via CLI
