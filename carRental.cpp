#include "CarRental.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <ctime>
using namespace std;

Car::Car() : year(0), rentalPrice(0), isDamaged(false) {}

Car::Car(string model, string type, int yr, string plate, float price)
    : carModel(model), carType(type), year(yr), licensePlate(plate), rentalPrice(price), isDamaged(false) {}

void Car::displayCarInfo() {
    cout << endl;
    cout << "Car Model: " << carModel << endl;
    cout << "Car Type: " << carType << endl;
    cout << "Year: " << year << endl;
    cout << "License Plate: " << licensePlate << endl;
    cout << "Rental Price: " << rentalPrice << endl;
    cout << "Is Damaged: " << (isDamaged ? "Yes" : "No") << endl;
}

bool Car::isCarDamaged() {
    return isDamaged;
}


float Car::getRentalPrice() {
    return rentalPrice;
}

void Car::writeToDisk(ofstream& outFile) {
    outFile << carModel << " " << carType << " " << year << " " << licensePlate << " " << rentalPrice << " " << isDamaged << endl;
}

void Car::readFromDisk(ifstream& inFile) {
    inFile >> carModel >> carType >> year >> licensePlate >> rentalPrice >> isDamaged;
}


Car::~Car() {}


Order::Order() : rentalDuration(0), rentedCar(nullptr) {}

Order::Order(string name, string passport, int duration, Car* car)
    : clientName(name), passportNumber(passport), rentalDuration(duration), rentedCar(car) {}

void Order::displayOrderDetails() {
    
    cout << "Client Name: " << clientName << endl;
    cout << "Passport Number: " << passportNumber << endl;
    cout << "Rental Duration: " << rentalDuration << " days" << endl;
    cout << "Total Cost: " << calculateTotalCost() << "$" << endl;
}
void Order::interactWithCar(Order& otherOrder) {
    if (rentedCar->isCarDamaged() || otherOrder.rentedCar->isCarDamaged()) {
        cout << "One of the cars is damaged. Please contact the administrator." << endl;
    }
    else {
        cout << "Both cars are available. Orders can proceed." << endl;
    }
}

void Order::writeToDisk(ofstream& outFile) {
    outFile << clientName << " " << passportNumber << " " << rentalDuration << endl;
    rentedCar->writeToDisk(outFile);
}

void Order::readFromDisk(ifstream& inFile) {
    inFile >> clientName >> passportNumber >> rentalDuration;
    rentedCar->readFromDisk(inFile);
}

void Order::setCancelled(bool cancelled) {
    isCancelled = cancelled;
}


Order::~Order() {}
