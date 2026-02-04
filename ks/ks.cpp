#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;

class Person {
public:
    Person(const string& id, const string& name, const string& gender, const string& phone)
        : id(id), name(name), gender(gender), phone(phone) {}

    string getId() const { return id; }
    string getName() const { return name; }
    string getGender() const { return gender; }
    string getPhone() const { return phone; }

    virtual void display() const {
        cout << "ID: " << id << ", 姓名: " << name << ", 性别: " << gender << ", 电话: " << phone;
    }

    void setName(const string& newName) { name = newName; }
    void setGender(const string& newGender) { gender = newGender; }
    void setPhone(const string& newPhone) { phone = newPhone; }

protected:
    string name;

private:
    string id;
    string gender;
    string phone;
};

class Customer : public Person {
public:
    Customer(const string& id, const string& name, const string& gender, const string& phone)
        : Person(id, name, gender, phone), totalSpent(0) {}

    void addSpending(double amount) { totalSpent += amount; }
    double getTotalSpent() const { return totalSpent; }

    void display() const override {
        Person::display();
        cout << ", 总消费额: ￥" << totalSpent << endl;
    }

    // 添加美发项目记录
    //void addHairService(const string& serviceName) {
    //    hairServices.push_back(serviceName);
    //    cout << "美发项目已添加到顾客记录中。" << endl;
    //}

    // 添加美发服务记录和更新消费总额
    void addServiceRecord(const string& serviceName, double price) {
        hairServices.push_back(serviceName);
        addSpending(price);
        cout << "美发服务: " << serviceName << " 已添加到顾客记录，消费: " << price << " 元。" << endl;
    }

private:
    double totalSpent;
    vector<string> hairServices;

    friend class HairSalon;
};

class Employee : public Person {
public:
    Employee(const string& id, const string& name, const string& gender, const string& phone, const string& job)
        : Person(id, name, gender, phone), job(job), income(0) {}

    string getJob() const { return job; }
    double getIncome() const { return income; }

    void addIncome(double amount) { income += amount; }

    void display() const override {
        Person::display();
        cout << ", 工作: " << job << ", 收入: ￥" << income << endl;
    }

    // 添加员工服务记录和收入
   /* void addEmployeeService(const string& customerId, const string& serviceName, double amount) {
        servicesProvided.push_back("顾客: " + customerId + ", 项目: " + serviceName + ", 金额: ￥" + to_string(amount));
        income += amount;
        cout << "员工服务记录已添加。" << endl;
    }*/
    // 添加提供的服务记录和更新收入
    void addProvidedService(const string& serviceName, double price) {
        servicesProvided.push_back(serviceName);
        addIncome(price);
        cout << "提供的美发服务: " << serviceName << " 已添加到员工记录，收入: " << price << " 元。" << endl;
    }

private:
    string job;
    double income;
    vector<string> servicesProvided;  // 服务记录
    friend class HairSalon;
};

class HairSalon {
public:
    void provideHairService(const string& customerId, const string& employeeId, const string& serviceName, double price) {
        auto customerIt = find_if(customers.begin(), customers.end(), [&customerId](const Customer& c) { return c.getId() == customerId; });
        auto employeeIt = find_if(employees.begin(), employees.end(), [&employeeId](const Employee& e) { return e.getId() == employeeId; });

        if (customerIt != customers.end() && employeeIt != employees.end()) {
            customerIt->addServiceRecord(serviceName, price);  // 更新顾客记录
            employeeIt->addProvidedService(serviceName, price);  // 更新员工记录
            cout << "美发服务提供成功。" << endl;
        }
        else {
            if (customerIt == customers.end()) cout << "未找到对应ID的顾客。" << endl;
            if (employeeIt == employees.end()) cout << "未找到对应ID的员工。" << endl;
        }
    }

    void addCustomer(const Customer& customer) {
        if (!isIdUnique(customer.getId())) {
            cout << "会员卡号重复，数据添加取消。" << endl;
            return;
        }
        customers.push_back(customer);
    }

    void addEmployee(const Employee& employee) {
        if (!isIdUnique(employee.getId())) {
            cout << "员工编号重复，数据添加取消。" << endl;
            return;
        }
        employees.push_back(employee);
    }

    void displayCustomers() const {
        cout << "顾客信息:" << endl;
        for (const auto& customer : customers) {
            customer.display();
        }
        cout << endl;
    }

    void displayEmployees() const {
        cout << "员工信息:" << endl;
        for (const auto& employee : employees) {
            employee.display();
        }
        cout << endl;
    }

    void searchCustomerByName(const string& name) const {
        cout << "根据姓名查询顾客信息: " << name << endl;
        bool found = false;
        for (const auto& customer : customers) {
            if (customer.getName() == name) {
                customer.display();
                found = true;
            }
        }
        if (!found) {
            cout << "未找到该顾客信息。" << endl;
        }
    }

    void searchCustomerByPhone(const string& phone) const {
        cout << "根据电话号码查询顾客信息: " << phone << endl;
        bool found = false;
        for (const auto& customer : customers) {
            if (customer.getPhone() == phone) {
                customer.display();
                found = true;
            }
        }
        if (!found) {
            cout << "未找到该顾客信息。" << endl;
        }
    }

    void searchCustomerById(const string& id) const {
        cout << "根据会员卡号查询顾客信息: " << id << endl;
        bool found = false;
        for (const auto& customer : customers) {
            if (customer.getId() == id) {
                customer.display();
                found = true;
            }
        }
        if (!found) {
            cout << "未找到该顾客信息。" << endl;
        }
    }

    void searchEmployeeByName(const string& name) const {
        cout << "根据姓名查询员工信息: " << name << endl;
        bool found = false;
        for (const auto& employee : employees) {
            if (employee.getName() == name) {
                employee.display();
                found = true;
            }
        }
        if (!found) {
            cout << "未找到该员工信息。" << endl;
        }
    }

    void searchEmployeeById(const string& id) const {
        cout << "根据员工编号查询员工信息: " << id << endl;
        bool found = false;
        for (const auto& employee : employees) {
            if (employee.getId() == id) {
                employee.display();
                found = true;
            }
        }
        if (!found) {
            cout << "未找到该员工信息。" << endl;
        }
    }

    void editCustomer(const string& id, const string& newName, const string& newGender, const string& newPhone) {
        for (auto& customer : customers) {
            if (customer.getId() == id) {
                customer.setName(newName);
                customer.setGender(newGender);
                customer.setPhone(newPhone);
                cout << "顾客信息已更新。" << endl;
                return;
            }
        }
        cout << "未找到该顾客信息。" << endl;
    }

    void editEmployee(const string& id, const string& newName, const string& newGender, const string& newPhone) {
        for (auto& employee : employees) {
            if (employee.getId() == id) {
                employee.setName(newName);
                employee.setGender(newGender);
                employee.setPhone(newPhone);
                cout << "员工信息已更新。" << endl;
                return;
            }
        }
        cout << "未找到该员工信息。" << endl;
    }

    void deleteCustomer(const string& id) {
        for (auto it = customers.begin(); it != customers.end(); ++it) {
            if (it->getId() == id) {
                customers.erase(it);
                cout << "顾客信息已删除。" << endl;
                return;
            }
        }
        cout << "未找到该顾客信息。" << endl;
    }

    void deleteEmployee(const string& id) {
        for (auto it = employees.begin(); it != employees.end(); ++it) {
            if (it->getId() == id) {
                employees.erase(it);
                cout << "员工信息已删除。" << endl;
                return;
            }
        }
        cout << "未找到该员工信息。" << endl;
    }

    void saveToFile(const string& filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "无法打开文件进行写入。" << endl;
            return;
        }

        for (const auto& customer : customers) {
            file << "C " << customer.getId() << " " << customer.getName() << " " << customer.getGender() << " " << customer.getPhone() << " " << customer.getTotalSpent() << endl;
        }

        for (const auto& employee : employees) {
            file << "E " << employee.getId() << " " << employee.getName() << " " << employee.getGender() << " " << employee.getPhone() << " " << employee.getJob() << " " << employee.getIncome() << endl;
        }

        file.close();
        cout << "数据已保存到文件 " << filename << "。" << endl;
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "无法打开文件进行读取。" << endl;
            return;
        }

        customers.clear();
        employees.clear();

        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string type;
            iss >> type;
            if (type == "C") {
                string id, name, gender, phone;
                double totalSpent;
                iss >> id >> name >> gender >> phone >> totalSpent;
                Customer customer(id, name, gender, phone);
                customer.addSpending(totalSpent);
                customers.push_back(customer);
            }
            else if (type == "E") {
                string id, name, gender, phone, job;
                double income;
                iss >> id >> name >> gender >> phone >> job >> income;
                Employee employee(id, name, gender, phone, job);
                employee.addIncome(income);
                employees.push_back(employee);
            }
        }

        file.close();
        cout << "从文件 " << filename << " 中加载数据。" << endl;
    }

    void sortByTotalSpent() {
        sort(customers.begin(), customers.end(), [](const Customer& a, const Customer& b) {
            return a.getTotalSpent() > b.getTotalSpent();
            });
    }

    void sortByIncome() {
        sort(employees.begin(), employees.end(), [](const Employee& a, const Employee& b) {
            return a.getIncome() > b.getIncome();
            });
    }

    // 统计顾客消费总额
    //void calculateTotalSpent() {
    //    for (auto& customer : customers) {
    //        double total = 0;
    //        for (const string& serviceName : customer.hairServices) {
    //            // 这里可以根据不同的美发项目定价来计算消费总额
    //            total += 50;  // 假设每个项目价格为50
    //        }
    //        customer.totalSpent = total;
    //    }
    //}


   

private:
    vector<Customer> customers;
    vector<Employee> employees;

    bool isIdUnique(const string& id) const {
        for (const auto& customer : customers) {
            if (customer.getId() == id) {
                return false;
            }
        }
        for (const auto& employee : employees) {
            if (employee.getId() == id) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    HairSalon salon;
    salon.loadFromFile("salon_data.txt");

    int choice;
    string id, name, gender, phone, job, serviceName;
    double price;

    while (true) {
        cout << "欢迎使用美发店管理系统" << endl;
        cout << "0. 提供美发服务" << endl;
        cout << "1. 添加顾客" << endl;
        cout << "2. 添加员工" << endl;
        cout << "3. 显示顾客信息" << endl;
        cout << "4. 显示员工信息" << endl;
        cout << "5. 根据姓名查询顾客信息" << endl;
        cout << "6. 根据电话号码查询顾客信息" << endl;
        cout << "7. 根据会员卡号查询顾客信息" << endl;
        cout << "8. 根据姓名查询员工信息" << endl;
        cout << "9. 根据员工编号查询员工信息" << endl;
        cout << "10. 编辑顾客信息" << endl;
        cout << "11. 编辑员工信息" << endl;
        cout << "12. 删除顾客信息" << endl;
        cout << "13. 删除员工信息" << endl;
        cout << "14. 保存数据到文件" << endl;
        cout << "15. 从文件加载数据" << endl;
        cout << "16. 根据消费总额排序顾客" << endl;
        cout << "17. 根据收入排序员工" << endl;
        cout << "18. 退出" << endl;
        cout << "请输入您的选择: ";

        int choice;
        cin >> choice;

        switch (choice) {

        case 0: {
            cout << "输入顾客ID: ";
            cin >> id;
            string customerId = id;
            cout << "输入员工ID: ";
            cin >> id;
            string employeeId = id;
            cout << "输入服务名称: ";
            cin >> serviceName;
            cout << "输入消费金额: ";
            cin >> price;
            salon.provideHairService(customerId, employeeId, serviceName, price);
            system("pause");
            system("cls");
            break;
        }

        case 1: {
            string id, name, gender, phone;
            cout << "请输入顾客会员卡号: ";
            cin >> id;
            cout << "请输入顾客姓名: ";
            cin >> name;
            cout << "请输入顾客性别: ";
            cin >> gender;
            cout << "请输入顾客电话号码: ";
            cin >> phone;
            Customer customer(id, name, gender, phone);
            salon.addCustomer(customer);
            system("pause");
            system("cls");
            break;
        }
        case 2: {
            string id, name, gender, phone, job;
            cout << "请输入员工编号: ";
            cin >> id;
            cout << "请输入员工姓名: ";
            cin >> name;
            cout << "请输入员工性别:";
            cin >> gender;
            cout << "请输入员工电话号码: ";
            cin >> phone;
            cout << "请输入员工工作: ";
            cin >> job;
            Employee employee(id, name, gender, phone, job);
            salon.addEmployee(employee);
            system("pause");
            system("cls");
            break;
        }
        case 3:
            salon.displayCustomers();
            system("pause");
            system("cls");
            break;
        case 4:
            salon.displayEmployees();
            system("pause");
            system("cls");
            break;
        case 5: {
            string name;
            cout << "请输入要查询的顾客姓名: ";
            cin >> name;
            salon.searchCustomerByName(name);
            system("pause");
            system("cls");
            break;
        }
        case 6: {
            string phone;
            cout << "请输入要查询的顾客电话号码: ";
            cin >> phone;
            salon.searchCustomerByPhone(phone);
            system("pause");
            system("cls");
            break;
        }
        case 7: {
            string id;
            cout << "请输入要查询的顾客会员卡号: ";
            cin >> id;
            salon.searchCustomerById(id);
            system("pause");
            system("cls");
            break;
        }
        case 8: {
            string name;
            cout << "请输入要查询的员工姓名: ";
            cin >> name;
            salon.searchEmployeeByName(name);
            system("pause");
            system("cls");
            break;
        }
        case 9: {
            string id;
            cout << "请输入要查询的员工编号: ";
            cin >> id;
            salon.searchEmployeeById(id);
            system("pause");
            system("cls");
            break;
        }
        case 10: {
            string id, newName, newGender, newPhone;
            cout << "请输入要编辑的顾客会员卡号: ";
            cin >> id;
            cout << "请输入新姓名: ";
            cin >> newName;
            cout << "请输入新性别: ";
            cin >> newGender;
            cout << "请输入新电话号码: ";
            cin >> newPhone;
            salon.editCustomer(id, newName, newGender, newPhone);
            system("pause");
            system("cls");
            break;
        }
        case 11: {
            string id, newName, newGender, newPhone;
            cout << "请输入要编辑的员工编号: ";
            cin >> id;
            cout << "请输入新姓名: ";
            cin >> newName;
            cout << "请输入新性别: ";
            cin >> newGender;
            cout << "请输入新电话号码: ";
            cin >> newPhone;
            salon.editEmployee(id, newName, newGender, newPhone);
            system("pause");
            system("cls");
            break;
        }
        case 12: {
            string id;
            cout << "请输入要删除的顾客会员卡号: ";
            cin >> id;
            salon.deleteCustomer(id);
            system("pause");
            system("cls");
            break;
        }
        case 13: {
            string id;
            cout << "请输入要删除的员工编号: ";
            cin >> id;
            salon.deleteEmployee(id);
            system("pause");
            system("cls");
            break;
        }
        case 14: {
            string filename;
            cout << "请输入要保存数据的文件名: ";
            cin >> filename;
            salon.saveToFile(filename);
            system("pause");
            system("cls");
            break;
        }
        case 15: {
            string filename;
            cout << "请输入要从文件加载数据的文件名: ";
            cin >> filename;
            salon.loadFromFile(filename);
            system("pause");
            system("cls");
            break;
        }
        case 16:
       /*     salon.calculateTotalSpent();*/
            salon.sortByTotalSpent();
            salon.displayCustomers();
            system("pause");
            system("cls");
            break;
        case 17:
            salon.sortByIncome();
            salon.displayEmployees();
            system("pause");
            system("cls");
            break;
        case 18:
            cout << "感谢使用，再见！" << endl;
            system("pause");
            system("cls");
            return 0;
        default:
            cout << "无效的选择，请重新输入。" << endl;
            system("pause");
            system("cls");
            break;
        }
    }

    return 0;
}

