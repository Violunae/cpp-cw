#include <iostream>
#include <string>
#include <stdexcept>
#include <cctype>
#include <algorithm>
#include <chrono>
#include <tuple>

std::tuple<int, int, int> getCurrentDate() {
    const auto now = std::chrono::system_clock::now();
    std::chrono::year_month_day ymd = std::chrono::floor<std::chrono::days>(now);
    return std::make_tuple(int(ymd.year()), unsigned(ymd.month()), unsigned(ymd.day()));
}

std::tuple<int, int, int> parseDate(const std::string &date) {
    int year = std::stoi(date);
    int month = std::stoi(date.substr(5, 2));
    int day = std::stoi(date.substr(8, 2));
    return std::make_tuple(year, month, day);
}

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) ||
           (year % 400 == 0);
}

int daysInMonth(int year, int month) {
    switch (month) {
        case 1: case 3: case 5: case 7:
        case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return isLeapYear(year) ? 29 : 28;
        default:
            return 0;
    }
}

class Company {
public:
    std::string name;
    std::string nip;
    std::string date;
    std::string mail;

    Company(const std::string &_name,
            const std::string &_nip,
            const std::string &_date,
            const std::string &_mail) {
        validateName(_name);
        validateNip(_nip);
        validateDate(_date);
        validateMail(_mail);

        name = _name;
        nip = _nip;
        date = _date;
        mail = _mail;
    }

private:
    static void validateName(const std::string &name) {
        if (name.length() < 3 || name.length() > 100) {
            throw std::length_error(
                "Company name length must be between 3 and 100 characters"
            );
        }
    }

    static void validateNip(const std::string &nip) {
        if (nip.length() != 10) {
            throw std::length_error(
                "NIP must contain exactly 10 digits"
            );
        }

        for (char c : nip) {
            if (!std::isdigit(static_cast<unsigned char>(c))) {
                throw std::invalid_argument(
                    "NIP must contain only digits"
                );
            }
        }

        const int weights[9] = {6, 5, 7, 2, 3, 4, 5, 6, 7};

        int sum = 0;
        for (int i = 0; i < 9; ++i) {
            sum += (nip[i] - '0') * weights[i];
        }

        int control = sum % 11;

        if (control == 10 || control != (nip[9] - '0')) {
            throw std::domain_error(
                "Invalid NIP checksum"
            );
        }
    }

    static void validateDate(const std::string &date) {
        if (date.length() != 10) {
            throw std::length_error(
                "Date must have length 10 in format YYYY-MM-DD"
            );
        }

        if (date[4] != '-' || date[7] != '-') {
            throw std::invalid_argument(
                "Date must be in format YYYY-MM-DD"
            );
        }

        for (size_t i = 0; i < date.size(); ++i) {
            if (i == 4 || i == 7) {
                continue;
            }

            if (!std::isdigit(static_cast<unsigned char>(date[i]))) {
                throw std::invalid_argument(
                    "Date contains invalid characters"
                );
            }
        }

        auto [year, month, day] = parseDate(date);
        auto [currentYear, currentMonth, currentDay] = getCurrentDate();

        if (year < 1900 || year > currentYear) {
            throw std::domain_error(
                "Year must be between 1900 and current year"
            );
        }

        int maxMonth = (year == currentYear)
                           ? currentMonth
                           : 12;

        if (month < 1 || month > maxMonth) {
            throw std::domain_error(
                "Month is out of valid range"
            );
        }

        int maxDay;

        if (year == currentYear &&
            month == currentMonth) {
            maxDay = currentDay;
        } else {
            maxDay = daysInMonth(year, month);
        }

        if (day < 1 || day > maxDay) {
            throw std::domain_error(
                "Day is out of valid range"
            );
        }
    }

    static void validateMail(const std::string &mail) {
        if (std::find(mail.begin(), mail.end(), '@') == mail.end()) {
            throw std::invalid_argument(
                "Email address must contain '@'"
            );
        }
    }
};

int main() {
    try {
        Company company(
            "Example Company",
            "8567346215",
            "2024-05-10",
            "contact@example.com"
        );

        std::cout << "Company object created successfully" << std::endl;
    }
    catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}