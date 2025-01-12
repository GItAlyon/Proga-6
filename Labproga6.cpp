#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <vector>

const int RESIDENTS_COUNT = 5;
const char* FILENAME = "residents2.txt";
const char* RESULT_FILENAME = "results2.txt";

class Appearance {
private:
    std::string hairColor;
    std::string clothes;

public:
    Appearance() : hairColor("Unknown"), clothes("Unknown") {}

    void setAppearance(const std::string& hair, const std::string& cloth) {
        hairColor = hair;
        clothes = cloth;
    }

    const std::string& getHairColor() const {
        return hairColor;
    }

    const std::string& getClothes() const {
        return clothes;
    }
};

class Resident {
protected: // Модификатор protected
    std::string firstName;
    std::string lastName;
    std::string id; // Идентификационный номер
    Appearance appearance;
    std::string phone;

public:
    Resident() : firstName("Unknown"), lastName("Unknown"), id("00"), phone("Unknown") {}

    void setResident(const std::string& first, const std::string& last, const std::string& idNum, const std::string& hair,
        const std::string& cloth, const std::string& phoneNum) {
        firstName = first;
        lastName = last;
        id = idNum;
        appearance.setAppearance(hair, cloth);
        phone = phoneNum;
    }

    virtual void displayInfo() const { // Виртуальная функция
        std::cout << "Resident Info: " << firstName << " " << lastName << ", ID: " << id << ", Phone: " << phone << "\n";
    }

    // Перегрузка оператора '+' 
    Resident operator+(const Resident& other) const {
        Resident newResident;
        newResident.firstName = this->firstName + " & " + other.firstName;
        newResident.lastName = this->lastName + " & " + other.lastName;
        newResident.id = this->id + ", " + other.id;
        newResident.phone = this->phone + ", " + other.phone;
        return newResident;
    }

    // Перегрузка оператора присваивания
    Resident& operator=(const Resident& other) {
        if (this != &other) {
            firstName = other.firstName;
            lastName = other.lastName;
            id = other.id;
            phone = other.phone;
            appearance = other.appearance; // Копируем appearance
        }
        return *this;
    }
};

class VIPResident : public Resident {
private:
    std::string vipBenefits;

public:
    VIPResident(const std::string& first, const std::string& last, const std::string& idNum, const std::string& hair,
        const std::string& cloth, const std::string& phoneNum, const std::string& benefits)
        : Resident() {
        setResident(first, last, idNum, hair, cloth, phoneNum);
        vipBenefits = benefits;
    }

    void displayInfo() const override { // Перегрузка метода
        Resident::displayInfo(); // Вызов метода базового класса
        std::cout << "VIP Benefits: " << vipBenefits << std::endl;
    }
};



int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Создаем экземпляры классов
    Resident resident1, resident2;
    resident1.setResident("John", "Doe", "01", "Brown", "Casual", "123456789");
    resident2.setResident("Jane", "Smith", "02", "Blonde", "Formal", "987654321");

    // Используем перегруженный оператор '+'
    Resident combinedResident = resident1 + resident2;
    combinedResident.displayInfo();

    // Используем производный класс
    VIPResident vipResident("Alice", "Johnson", "03", "Black", "Elegant", "555-1234", "Free Parking");
    vipResident.displayInfo();

    return 0;
}
