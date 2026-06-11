#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <numeric>

#include "json.hpp"

using json = nlohmann::json;

struct Student {
    unsigned int id;
    std::string firstName;
    std::string lastName;
    float score;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Student, id, firstName, lastName, score)
};

json fileToJson(const std::string& filename)
{
    std::ifstream file(filename);

    if (!file.is_open())
    {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    return json::parse(buffer.str());
}

void jsonToFile(const json& data, const std::string& filename)
{
    std::ofstream file(filename);

    if (!file.is_open())
    {
        throw std::runtime_error("Cannot create file: " + filename);
    }

    file << data.dump(4);
}

std::vector<Student> jsonToVector(const json& data)
{
    return data.get<std::vector<Student>>();
}

json vectorToJson(const std::vector<Student>& v)
{
    return json(v);
}

float calculateGrade(float score)
{
    if (score < 50.0f) return 2.0f;
    if (score < 60.0f) return 3.0f;
    if (score < 70.0f) return 3.5f;
    if (score < 80.0f) return 4.0f;
    if (score < 90.0f) return 4.5f;

    return 5.0f;
}

void printStudents(const std::vector<Student>& students)
{
    std::cout << "\n===== STUDENTS =====\n";

    for (const auto& s : students)
    {
        std::cout
            << "[" << s.id << "] "
            << s.firstName << " "
            << s.lastName
            << " | score: " << s.score << "%"
            << " | grade: " << calculateGrade(s.score)
            << '\n';
    }

    std::cout << std::endl;
}

void sortByScoreDescending(std::vector<Student>& students)
{
    std::sort(
        students.begin(),
        students.end(),
        [](const Student& a, const Student& b)
        {
            return a.score > b.score;
        });
}

void sortByLastNameAscending(std::vector<Student>& students)
{
    std::sort(
        students.begin(),
        students.end(),
        [](const Student& a, const Student& b)
        {
            return a.lastName < b.lastName;
        });
}

void findStudentById(
    const std::vector<Student>& students,
    unsigned int id)
{
    auto it = std::find_if(
        students.begin(),
        students.end(),
        [id](const Student& s)
        {
            return s.id == id;
        });

    if (it != students.end())
    {
        std::cout << "\nStudent found:\n";

        std::cout
            << "[" << it->id << "] "
            << it->firstName << " "
            << it->lastName
            << " | score: " << it->score
            << "% | grade: "
            << calculateGrade(it->score)
            << "\n";
    }
    else
    {
        std::cout << "\nStudent with id "
                  << id
                  << " not found.\n";
    }
}

float averageScore(const std::vector<Student>& students)
{
    float sum = std::accumulate(
        students.begin(),
        students.end(),
        0.0f,
        [](float acc, const Student& s)
        {
            return acc + s.score;
        });

    return students.empty()
        ? 0.0f
        : sum / students.size();
}

int countPassed(const std::vector<Student>& students)
{
    return std::count_if(
        students.begin(),
        students.end(),
        [](const Student& s)
        {
            return s.score >= 50.0f;
        });
}

int countFailed(const std::vector<Student>& students)
{
    return std::count_if(
        students.begin(),
        students.end(),
        [](const Student& s)
        {
            return s.score < 50.0f;
        });
}

void removeFailedStudents(std::vector<Student>& students)
{
    students.erase(
        std::remove_if(
            students.begin(),
            students.end(),
            [](const Student& s)
            {
                return s.score < 50.0f;
            }),
        students.end());
}

int main()
{
    try
    {
        std::string filein = "data_input.json";
        std::string fileout = "data_output.json";

        json datain = fileToJson(filein);

        std::vector<Student> students =
            jsonToVector(datain);

        printStudents(students);

        sortByScoreDescending(students);

        std::cout << "\n===== SORTED BY SCORE DESC =====\n";
        printStudents(students);

        unsigned int searchedId;

        std::cout << "\nEnter student ID: ";
        std::cin >> searchedId;

        findStudentById(students, searchedId);

        float avg = averageScore(students);

        std::cout
            << "\nAverage score: "
            << avg
            << "%\n";

        int passed = countPassed(students);
        int failed = countFailed(students);

        std::cout
            << "\nPassed: "
            << passed
            << "\nFailed: "
            << failed
            << "\n";

        removeFailedStudents(students);

        std::cout
            << "\n===== AFTER REMOVING FAILED STUDENTS =====\n";

        printStudents(students);

        json dataout = vectorToJson(students);
        jsonToFile(dataout, fileout);

        std::cout
            << "\nData saved to "
            << fileout
            << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr
            << "Error: "
            << e.what()
            << std::endl;
    }

    return 0;
}