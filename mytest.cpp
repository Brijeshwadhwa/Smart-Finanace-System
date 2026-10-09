
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <algorithm>
#include <memory>
#include <thread>
#include <chrono>
#include <numeric>
#include <iomanip>
#include <functional>
#include <exception>

using namespace std;

// CUSTOM EXCEPTION CLASS
class InvalidAmountException : public exception {
public:
    const char* what() const noexcept override {
        return "Invalid Amount!";
    }
};

// ABSTRACT BASE CLASS
class Transaction {
protected:
    int id;
    string title;
    double amount;
    string date;

public:
    Transaction(int i, string t, double a, string d)
        : id(i), title(t), amount(a), date(d) {}

    virtual ~Transaction() {}

    virtual void display() const = 0;
    virtual string getType() const = 0;

    int getId() const {
        return id;
    }

    double getAmount() const {
        return amount;
    }

    string getDate() const {
        return date;
    }

    string getTitle() const {
        return title;
    }

    friend ostream& operator<<(ostream& out, const Transaction& t) {
        out << t.id << " "
            << t.title << " "
            << t.amount << " "
            << t.date;

        return out;
    }
};
// EXPENSE CLASS
class Expense : public Transaction {
private:
    string category;

public:
    Expense(int i,
            string t,
            double a,
            string d,
            string c)
        : Transaction(i, t, a, d), category(c) {}

    void display() const override {
        cout << left
             << setw(10) << id
             << setw(20) << title
             << setw(15) << category
             << setw(15) << date
             << setw(10) << amount
             << setw(15) << "Expense"
             << endl;
    }

    string getCategory() const {
        return category;
    }

    string getType() const override {
        return "Expense";
    }
};
// INCOME CLASS
class Income : public Transaction {
private:
    string source;

public:
    Income(int i,
           string t,
           double a,
           string d,
           string s)
        : Transaction(i, t, a, d), source(s) {}

    void display() const override {
        cout << left
             << setw(10) << id
             << setw(20) << title
             << setw(15) << source
             << setw(15) << date
             << setw(10) << amount
             << setw(15) << "Income"
             << endl;
    }

    string getType() const override {
        return "Income";
    }
};

// TEMPLATE CLASS
template<typename T>
class DataPrinter {
public:
    static void printVector(const vector<T>& data) {
        for (const auto& item : data) {
            cout << item << endl;
        }
    }
};

// FINANCE MANAGER
class FinanceManager {
private:

    vector<shared_ptr<Transaction>> transactions;

    stack<shared_ptr<Transaction>> deletedStack;

    queue<string> notifications;

    double budget;

public:

    FinanceManager() {
        budget = 0;
        loadFromFile();
    }

    ~FinanceManager() {
        saveToFile();
    }

    // SET BUDGET
    void setBudget() {

        double budget;

        cout << "Enter Monthly Budget: ";
        cin >> budget;

        if (budget < 0)
            throw InvalidAmountException();

        this->budget = budget;

        cout << "Budget Set Successfully!\n";
    }

    // ADD EXPENSE
    void addExpense() {

        int id;
        string title;
        string category;
        string date;
        double amount;

        cout << "Enter Expense ID: ";
        cin >> id;

        cin.ignore();

        cout << "Enter Title: ";
        getline(cin, title);

        cout << "Enter Category: ";
        getline(cin, category);

        cout << "Enter Date: ";
        getline(cin, date);

        cout << "Enter Amount: ";
        cin >> amount;

        if (amount < 0)
            throw InvalidAmountException();

        transactions.push_back(
            make_shared<Expense>(
                id,
                title,
                amount,
                date,
                category
            )
        );

        notifications.push("New Expense Added!");

        saveToFile();

        cout << "Expense Added Successfully!\n";
    }

    // ADD INCOME
    void addIncome() {

        int id;
        string title;
        string source;
        string date;
        double amount;

        cout << "Enter Income ID: ";
        cin >> id;

        cin.ignore();

        cout << "Enter Title: ";
        getline(cin, title);

        cout << "Enter Source: ";
        getline(cin, source);

        cout << "Enter Date: ";
        getline(cin, date);

        cout << "Enter Amount: ";
        cin >> amount;

        if (amount < 0)
            throw InvalidAmountException();

        transactions.push_back(
            make_shared<Income>(
                id,
                title,
                amount,
                date,
                source
            )
        );

        notifications.push("New Income Added!");

        saveToFile();

        cout << "Income Added Successfully!\n";
    }

    // DISPLAY TRANSACTIONS
    void displayAll() const {

        if (transactions.empty()) {
            cout << "No Transactions Found!\n";
            return;
        }

        cout << left
             << setw(10) << "ID"
             << setw(20) << "Title"
             << setw(15) << "Category"
             << setw(15) << "Date"
             << setw(10) << "Amount"
             << setw(15) << "Type"
             << endl;

        cout << "--------------------------------------------------------------------\n";

        for (const auto& t : transactions) {
            t->display();
        }
    }

    // SORT BY AMOUNT
    void sortByAmount() {

        sort(transactions.begin(),
             transactions.end(),
             [](shared_ptr<Transaction> a,
                shared_ptr<Transaction> b)
             {
                 return a->getAmount() < b->getAmount();
             });

        cout << "Transactions Sorted Successfully!\n";
    }

    // SEARCH TRANSACTION
    void searchTransaction() {

        string keyword;

        cin.ignore();

        cout << "Enter Title to Search: ";
        getline(cin, keyword);

        bool found = false;

        for (const auto& t : transactions) {

            if (t->getTitle() == keyword) {
                t->display();
                found = true;
            }
        }

        if (!found)
            cout << "Transaction Not Found!\n";
    }

    // DELETE TRANSACTION
    void deleteTransaction() {

        int id;

        cout << "Enter ID to Delete: ";
        cin >> id;

        auto it = find_if(transactions.begin(),
                          transactions.end(),
                          [id](shared_ptr<Transaction> t)
                          {
                              return t->getId() == id;
                          });

        if (it != transactions.end()) {

            deletedStack.push(*it);

            transactions.erase(it);

            saveToFile();

            cout << "Transaction Deleted Successfully!\n";
        }
        else {
            cout << "Transaction Not Found!\n";
        }
    }

    // UNDO DELETE
    void undoDelete() {

        if (deletedStack.empty()) {
            cout << "Nothing to Undo!\n";
            return;
        }

        transactions.push_back(deletedStack.top());

        deletedStack.pop();

        saveToFile();

        cout << "Undo Successful!\n";
    }

    // MONTHLY SUMMARY
    void monthlySummary() {

        double totalExpense = 0;
        double totalIncome = 0;

        for (const auto& t : transactions) {

            if (t->getType() == "Expense")
                totalExpense += t->getAmount();

            else
                totalIncome += t->getAmount();
        }

        cout << "\n========== MONTHLY SUMMARY ==========" << endl;

        cout << "Total Income  : " << totalIncome << endl;
        cout << "Total Expense : " << totalExpense << endl;
        cout << "Savings       : "
             << totalIncome - totalExpense
             << endl;

        cout << "Budget        : "
             << budget
             << endl;

        if (totalExpense > budget) {
            cout << "WARNING: Budget Exceeded!\n";
        }
    }

    // CATEGORY ANALYTICS
    void categoryAnalytics() {

        map<string, double> categoryTotals;

        for (const auto& t : transactions) {

            Expense* exp = dynamic_cast<Expense*>(t.get());

            if (exp) {
                categoryTotals[exp->getCategory()] += exp->getAmount();
            }
        }

        cout << "\n========== CATEGORY ANALYTICS ==========" << endl;

        for (const auto& item : categoryTotals) {
            cout << left
                 << setw(20) << item.first
                 << item.second
                 << endl;
        }
    }

    // EXPORT CSV
    void exportCSV() {

        ofstream file("report.csv");

        file << "ID,Title,Amount,Date,Type\n";

        for (const auto& t : transactions) {

            file << t->getId() << ","
                 << t->getTitle() << ","
                 << t->getAmount() << ","
                 << t->getDate() << ","
                 << t->getType() << "\n";
        }

        file.close();

        cout << "CSV Exported Successfully!\n";
    }

    // SAVE TO FILE
    void saveToFile() {

        ofstream file("transactions.txt");

        for (const auto& t : transactions) {

            file << t->getId() << ","
                 << t->getTitle() << ","
                 << t->getAmount() << ","
                 << t->getDate() << ","
                 << t->getType()
                 << endl;
        }

        file.close();
    }

    // LOAD FILE
    void loadFromFile() {

        ifstream file("transactions.txt");

        if (!file)
            return;

        int id;
        string title;
        double amount;
        string date;
        string type;

        while (file >> id) {

            file.ignore();

            getline(file, title, ',');

            file >> amount;

            file.ignore();

            getline(file, date, ',');

            getline(file, type);

            if (type == "Expense") {

                transactions.push_back(
                    make_shared<Expense>(
                        id,
                        title,
                        amount,
                        date,
                        "Loaded"
                    )
                );
            }
            else {

                transactions.push_back(
                    make_shared<Income>(
                        id,
                        title,
                        amount,
                        date,
                        "Loaded"
                    )
                );
            }
        }

        file.close();
    }

    // NOTIFICATIONS
    void showNotifications() {

        if (notifications.empty()) {
            cout << "No Notifications!\n";
            return;
        }

        cout << "\n========== NOTIFICATIONS ==========" << endl;

        while (!notifications.empty()) {

            cout << notifications.front() << endl;

            notifications.pop();
        }
    }
    // MULTITHREADING
    void autoSaveThread() {

        thread saver([this]() {

            while (true) {

                this_thread::sleep_for(chrono::seconds(15));

                this->saveToFile();
            }
        });

        saver.detach();
    }

    // MENU
    void menu() {

        int choice;

        do {

            cout << "\n\n========== SMART FINANCE SYSTEM ==========";

            cout << "\n1. Set Budget";
            cout << "\n2. Add Expense";
            cout << "\n3. Add Income";
            cout << "\n4. Display Transactions";
            cout << "\n5. Monthly Summary";
            cout << "\n6. Search Transaction";
            cout << "\n7. Delete Transaction";
            cout << "\n8. Undo Delete";
            cout << "\n9. Sort By Amount";
            cout << "\n10. Category Analytics";
            cout << "\n11. Export CSV";
            cout << "\n12. Show Notifications";
            cout << "\n13. Exit";

            cout << "\nEnter Choice: ";
            cin >> choice;

            try {

                switch (choice) {

                case 1:
                    setBudget();
                    break;

                case 2:
                    addExpense();
                    break;

                case 3:
                    addIncome();
                    break;

                case 4:
                    displayAll();
                    break;

                case 5:
                    monthlySummary();
                    break;

                case 6:
                    searchTransaction();
                    break;

                case 7:
                    deleteTransaction();
                    break;

                case 8:
                    undoDelete();
                    break;

                case 9:
                    sortByAmount();
                    break;

                case 10:
                    categoryAnalytics();
                    break;

                case 11:
                    exportCSV();
                    break;

                case 12:
                    showNotifications();
                    break;

                case 13:
                    cout << "Exiting Program...\n";
                    break;

                default:
                    cout << "Invalid Choice!\n";
                }
            }

            catch (exception& e) {
                cout << e.what() << endl;
            }

        } while (choice != 13);
    }
};

// MAIN FUNCTION
int main() {

    FinanceManager manager;

    manager.autoSaveThread();

    manager.menu();

    return 0;
}