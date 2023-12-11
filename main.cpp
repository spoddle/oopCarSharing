#include "CarRental.h"
#include "feedback.h"
#include <iostream>
#include "date.h"
#include "carList.h"

int main() {
    string model, type, plate;
    int year, duration;
    float price;

    Administrator admin("Vinda Garner", "ADM12815", "admin@gmail.com", "555-232-0987");
    cout << "Administrator Details:" << endl;
    admin.displayAdminInfo();

    CarList vehicleInventory;

    // Зчитування автомобілів з файлу та додавання їх до списку
    vehicleInventory.readFromFile("vehicles.txt");

    // Виведення списку транспортних засобів
    std::cout << "\nList of Vehicles:" << std::endl;
    vehicleInventory.displayVehicles();

    VehicleRental rentalObject;
    rentalObject.SetRentalPeriod();

    // Замінено використання конкретного класу Feedback на використання абстрактного класу через вказівник
    Feedback* feedbackObj = new ConcreteFeedback(); // Використання конкретного класу ConcreteFeedback

    string userFeedback;
    bool isAnonymous;

    std::cout << "\nYou can send us your feedback:\n";
    std::cin.ignore(); // Очистити буфер вводу перед введенням рядка
    getline(cin, userFeedback);

    std::cout << "Do you want to leave an anonymous feedback? (1 for Yes / 0 for No): ";
    std::cin >> isAnonymous;

    feedbackObj->saveFeedback(userFeedback, isAnonymous);



    std::cout << "Enter Car Model: ";
    std::cin >> model;
    std::cout << "Enter Car Type: ";
    std::cin >> type;
    std::cout << "Enter Year: ";
    std::cin >> year;
    std::cout << "Enter License Plate: ";
    std::cin >> plate;
    std::cout << "Enter Rental Price: ";
    std::cin >> price;

    // Статично виділена машина та замовлення
    Car car1(model, type, year, plate, price);
    Order order1;

    // Зчитування даних про перший замовлення
    string name, passport;
    std::cout << "Enter Client Name: ";
    std::cin >> name;
    std::cout << "Enter Passport Number: ";
    std::cin >> passport;
    std::cout << "Enter Rental Duration (in days): ";
    std::cin >> duration;

    // Ініціалізація першого замовлення
    order1 = Order(name, passport, duration, &car1);

    // Виведення даних про перше замовлення та 
    car1.displayCarInfo();
    order1.displayOrderDetails();
    float totalCostOrder1 = order1.calculateTotalCost();

 
    // Зчитування даних про другу машину та замовлення
    std::cout << "\nEnter Car Model: ";
    std::cin >> model;
    std::cout << "Enter Car Type: ";
    std::cin >> type;
    std::cout << "Enter Year: ";
    std::cin >> year;
    std::cout << "Enter License Plate: ";
    std::cin >> plate;
    std::cout << "Enter Rental Price: ";
    std::cin >> price;

    // Динамічно виділена машина та замовлення
    Car* car2 = new Car(model, type, year, plate, price);
    Order* order2;

    // Зчитування даних про другий замовлення
    std::cout << "Enter Client Name: ";
    std::cin >> name;
    std::cout << "Enter Passport Number: ";
    std::cin >> passport;
    std::cout << "Enter Rental Duration (in days): ";
    std::cin >> duration;

    // Ініціалізація другого замовлення
    order2 = new Order(name, passport, duration, car2);

    // Виведення даних про друге замовлення та машину
    car2->displayCarInfo();
    order2->displayOrderDetails();
    float totalCostOrder2 = order2->calculateTotalCost();

    // Взаємодія між замовленнями
    order1.interactWithCar(*order2);

    // Збереження об'єктів у файл
    ofstream outFile("data.txt");
    order1.writeToDisk(outFile);
    order2->writeToDisk(outFile);
    outFile.close();

    // Читання об'єктів з файлу
    ifstream inFile("data.txt");
    Order loadedOrder1;
    Order loadedOrder2;
    loadedOrder1.readFromDisk(inFile);
    loadedOrder2.readFromDisk(inFile);

    // Виведення зчитаних даних
    loadedOrder1.displayOrderDetails();
    loadedOrder2.displayOrderDetails();
    inFile.close();
    cout << "Total Cost for Order 1: " << totalCostOrder1 << endl;
    cout << "Total Cost for Order 2: " << totalCostOrder2 << endl;
    // Звільнення динамічно виділеної пам'яті
    delete car2;
    delete order2;
    delete feedbackObj; // Звільнення пам'яті від використаного вказівника на абстрактний клас Feedback
    return 0;
}

