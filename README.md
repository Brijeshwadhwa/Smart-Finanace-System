# Smart Finance System 💰

A console-based personal finance management application built using **C++**. The Smart Finance System helps users manage income and expenses, track their monthly budget, analyze spending by category, and generate financial reports.

## 🚀 Features

* **Budget Management** — Set a monthly budget and receive warnings when expenses exceed it.
* **Expense Tracking** — Record expenses with an ID, title, category, date, and amount.
* **Income Management** — Record income with details such as title, source, date, and amount.
* **Transaction History** — Display all recorded income and expenses in a formatted table.
* **Monthly Financial Summary** — Calculate total income, total expenses, and savings.
* **Transaction Search** — Search transactions by title.
* **Delete Transactions** — Remove transactions using their IDs.
* **Undo Delete** — Restore the most recently deleted transaction during the current session.
* **Sort Transactions** — Sort transactions by amount in ascending order.
* **Category Analytics** — Analyze expenses by category.
* **CSV Export** — Export transaction records to a CSV report for further analysis.
* **File-Based Persistence** — Save transactions to a text file and load them when the application starts.
* **Notification System** — Display notifications when income or expenses are added.
* **Automatic Saving** — Run a background thread that periodically saves transaction data.
* **Object-Oriented Design** — Use inheritance, abstraction, polymorphism, and encapsulation.
* **Custom Exception Handling** — Handle negative budget and transaction amounts using a custom exception.

## 🛠️ Technologies Used

* **Language:** C++
* **Standard Library:** STL (Standard Template Library)
* **File Handling:** `fstream`, `ifstream`, `ofstream`
* **Data Structures:** `vector`, `map`, `stack`, `queue`
* **Object-Oriented Programming:** Abstract classes, inheritance, virtual functions, and polymorphism
* **Memory Management:** `shared_ptr` and `make_shared`
* **Multithreading:** `thread` and `chrono`
* **Algorithms:** `sort` and `find_if`
* **Exception Handling:** Custom exceptions and `try-catch`

## 📋 Prerequisites

Before running the project, make sure you have:

* A C++ compiler such as **GCC/G++**, Clang, or MinGW.
* A terminal or command-line interface.
* Support for **C++11 or later**.

## ⚙️ Installation and Setup

### 1. Clone the repository

```bash
git clone https://github.com/YOUR-USERNAME/Smart-Finance-System.git
```

Replace `YOUR-USERNAME` with your GitHub username and adjust the repository name if necessary.

### 2. Navigate to the project directory

```bash
cd Smart-Finance-System
```

### 3. Compile the program

Using GCC/G++:

```bash
g++ -std=c++11 -pthread main.cpp -o finance
```

Replace `main.cpp` with the name of your C++ source file if it is different.

### 4. Run the application

**Linux / macOS:**

```bash
./finance
```

**Windows:**

```bash
finance.exe
```

If you use MinGW on Windows, compile the program with a compatible threading-enabled compiler.

## 🖥️ Application Menu

When you run the program, the following menu appears:

```text
========== SMART FINANCE SYSTEM ==========

1. Set Budget
2. Add Expense
3. Add Income
4. Display Transactions
5. Monthly Summary
6. Search Transaction
7. Delete Transaction
8. Undo Delete
9. Sort By Amount
10. Category Analytics
11. Export CSV
12. Show Notifications
13. Exit

Enter Choice:
```

Enter the corresponding menu number to perform an operation.

## 📊 Example Usage

### Adding an Expense

```text
Enter Expense ID: 101
Enter Title: Grocery Shopping
Enter Category: Food
Enter Date: 2026-10-09
Enter Amount: 1500

Expense Added Successfully!
```

### Adding Income

```text
Enter Income ID: 201
Enter Title: Monthly Salary
Enter Source: Job
Enter Date: 2026-10-01
Enter Amount: 30000

Income Added Successfully!
```

### Monthly Financial Summary

```text
========== MONTHLY SUMMARY ==========

Total Income  : 30000
Total Expense : 1500
Savings       : 28500
Budget        : 10000
```

*Note: The figures above are illustrative examples.*

## 📁 Project Structure

```text
Smart-Finance-System/
│
├── main.cpp            # Main C++ source code
├── transactions.txt    # Persistent transaction data (generated)
├── report.csv          # Exported financial report (generated)
└── README.md           # Project documentation
```

The `transactions.txt` and `report.csv` files are generated in the application's working directory when the corresponding operations are performed.

## 🧠 Key C++ Concepts Demonstrated

| Concept                     | Implementation                                   |
| --------------------------- | ------------------------------------------------ |
| Abstraction                 | `Transaction` abstract base class                |
| Inheritance                 | `Expense` and `Income` derive from `Transaction` |
| Polymorphism                | Virtual `display()` and `getType()` functions    |
| Encapsulation               | Private category and source data                 |
| Templates                   | Generic `DataPrinter<T>` class                   |
| STL Containers              | `vector`, `map`, `stack`, and `queue`            |
| Smart Pointers              | `shared_ptr<Transaction>`                        |
| Lambda Expressions          | Sorting and transaction searching                |
| Runtime Type Identification | `dynamic_cast` for expense analytics             |
| Exception Handling          | `InvalidAmountException`                         |
| File Handling               | Saving and loading transaction records           |
| Multithreading              | Periodic background saving                       |

## ⚠️ Limitations and Notes

* The monthly budget is maintained in memory and is not persisted between application sessions.
* The current implementation calculates summaries using all stored transactions; it does not filter transactions by month.
* Transaction categories and income sources are not fully preserved when records are reloaded from the text file.
* Transaction IDs are entered manually, so duplicate IDs are possible.
* CSV export does not currently escape commas or quotation marks in field values.
* The undo-delete stack is maintained only in memory and is cleared when the program exits.
* The background auto-save thread is detached and accesses shared transaction data without synchronization. Concurrent file writes and data modifications may cause race conditions or corrupted output.
* Input validation currently checks for negative amounts but does not comprehensively handle non-numeric input or other invalid values.

## 🔮 Future Improvements

* Add monthly and yearly transaction filtering.
* Persist budget settings and transaction categories.
* Implement safer background saving using mutexes and proper thread management.
* Add unique transaction ID validation.
* Improve input validation and error handling.
* Support transaction editing and multiple-level undo.
* Generate detailed reports and spending charts.
* Add user authentication and multiple-user support.
* Introduce a graphical user interface (GUI).
* Add unit tests and improve the project's modular structure.

## 🤝 Contributing

Contributions, suggestions, and bug reports are welcome.

1. Fork the repository.
2. Create a new branch for your feature.
3. Commit your changes.
4. Push the branch to your fork.
5. Open a pull request.

## 📄 License

This project is available for educational and personal use. If you intend to distribute it publicly, consider adding a license such as the MIT License.

---

**Developed with C++ | Smart Finance System**
