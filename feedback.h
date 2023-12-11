#pragma once
#ifndef FEEDBACK_H
#define FEEDBACK_H
#include <iostream>
#include <fstream>
#include <string>

class Feedback {
public:
    virtual void saveFeedback(const std::string& feedback, bool isAnonymous = false) = 0;
    virtual ~Feedback() = default; // Додано віртуальний деструктор для абстрактного класу
};

class ConcreteFeedback : public Feedback {
public:
    void saveFeedback(const std::string& feedback, bool isAnonymous = false) override {
        std::ofstream file("feedback.txt", std::ios::app);
        if (file.is_open()) {
            if (isAnonymous) {
                file << "Anonymous: " << feedback << std::endl;
            }
            else {
                file << "From User: " << feedback << std::endl;
            }
            file.close();
            std::cout << "Thank you for your reply.\n" << std::endl;
        }
        else {
            std::cout << "Error\n";
        }
    }
};

#endif
