#pragma once
#ifndef CARLIST_H
#define CARLIST_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

class Vehicle {
public:
    std::string type;
    int year;

    Vehicle(const std::string& t, int y) : type(t), year(y) {}
};

class CarList {
private:
    std::vector<Vehicle> vehicles;

public:
    // Додавання автомобіля в список
    void addVehicle(const std::string& type, const std::string& model, int year) {
        vehicles.emplace_back(type + " " + model, year);
    }

    void readFromFile(const std::string& filename) {
        std::ifstream inputFile(filename);

        if (inputFile.is_open()) {
            std::string type, model;
            int year;

            // Зчитування даних з файлу та додавання автомобілів до списку
            while (inputFile >> type >> model >> year) {
                addVehicle(type, model, year);
            }

            inputFile.close(); // Закриваємо файл
        }
        else {
            std::cerr << "Unable to open file!" << std::endl;
        }
    }

    // Виведення списку автомобілів
    void displayVehicles() const {
        for (const auto& vehicle : vehicles) {
            std::cout << " " << vehicle.type << ", " << vehicle.year << std::endl;
        }
    }

    // Сортування списку автомобілів
    void sortVehicles() {
        std::sort(vehicles.begin(), vehicles.end(), [](const Vehicle& v1, const Vehicle& v2) {
            return v1.year < v2.year; // Сортування за роком
            });
    }
};

// Опис функціональних об'єктів (функторів)

// Функтор для віднімання
struct Subtract {
    int operator()(int a, int b) const {
        return a - b;
    }
};

// Функтор для операції більше
struct Greater {
    bool operator()(int a, int b) const {
        return a > b;
    }
};

// Функтор для логічного "І"
struct LogicalAnd {
    bool operator()(bool a, bool b) const {
        return a && b;
    }
};

#endif 
