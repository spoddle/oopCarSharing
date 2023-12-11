#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Car {
private:
    string carModel;
    string carType;
    int year;
    string licensePlate;
    float rentalPrice;
    bool isDamaged;

public:
    Car();
    Car(string model, string type, int yr, string plate, float price);
    float getPrice() const {
        return rentalPrice;
    }
    void displayCarInfo();
    bool isCarDamaged ();

    void markAsDamaged(bool damaged) {
        isDamaged = damaged;
    }

    float getRentalPrice();
    void writeToDisk(std::ofstream& outFile);
    void readFromDisk(std::ifstream& inFile);
    ~Car();
};

class Order {
private:
    string clientName;
    string passportNumber;
    int rentalDuration;
    Car* rentedCar;
    bool isCancelled; 


public:
    Order();
    Order(string name, string passport, int duration, Car* car);
    void displayOrderDetails();
    void writeToDisk(ofstream& outFile);
    void readFromDisk(ifstream& inFile);
    void interactWithCar(Order& otherOrder); 
    void setCancelled(bool cancelled);
   

    float getDuration() const {
        return rentalDuration;
    }

    float calculateTotalCost() const {
        return rentedCar->getPrice() * getDuration();
    }

   
    ~Order();
};


class PremiumOrder : public Order {
private:
    float premiumAmount;  // Додаткова плата для преміум-замовлення

public:
    PremiumOrder(string name, string passport, int duration, Car* car, float premium)
        : Order(name, passport, duration, car), premiumAmount(premium) {}
};

class System {
private:
    string adminPassword;     
public:
    string availableCars[10]; 
    string rejectedReason;    
    float orderCost;   

    Order createOrder(string carChoice, string clientPassport, int rentalDuration) {
        // Логіка вибору конкретного автомобіля на основі значення carChoice
        Car* selectedCar = new Car(/* параметри автомобіля */);
        Order order("Client", clientPassport, rentalDuration, selectedCar);
        return order;
    }

    PremiumOrder createPremiumOrder(string carChoice, string clientPassport, int rentalDuration, float premiumAmount) {
        // Логіка вибору конкретного автомобіля на основі значення carChoice
        Car* selectedCar = new Car(/* параметри автомобіля */);
        PremiumOrder premiumOrder("Premium Client", clientPassport, rentalDuration, selectedCar, premiumAmount);
        return premiumOrder;
    }

    void rejectOrder(string reason) {
        rejectedReason = reason;
      
    }

    void confirmOrderPayment(float amount) {
        orderCost = amount;
       
    }

};

class Administrator {
private:
    string adminName; 
    string adminID;   
    string adminEmail;  
    string adminPhone;  

public:
    Administrator(string name, string id, string email, string phone)
        : adminName(name), adminID(id), adminEmail(email), adminPhone(phone) {}

    void rejectOrder(System& system, Order& order, string reason) {
        system.rejectOrder(reason);
        order.setCancelled(true);
    }

    void markCarAsDamaged(Car& car, bool isDamaged) {
        car.markAsDamaged(isDamaged);
    }

    void displayAvailableCars(System& system) {
        cout << "Available Cars:" << endl;
        for (const string& car : system.availableCars) {
            cout << car << endl;
        }
    }

    void displayRejectedReason(const System& system) {
        if (!system.rejectedReason.empty()) {
            cout << "Reason for Rejection: " << system.rejectedReason << endl;
        }
        else {
            cout << "No reason provided for rejection." << endl;
        }
    }

    void displayOrderCost(const System& system) {
        cout << "Total Order Cost: " << system.orderCost << endl;
    }

    void displayAdminInfo() {
        cout << "Administrator Name: " << adminName << endl;
        cout << "Administrator ID: " << adminID << endl;
        cout << "Administrator email: " << adminEmail << endl;
        cout << "Administrator phone number: " << adminPhone << endl;
    }
};
