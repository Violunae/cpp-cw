#include <iostream>
#include <vector>
#include <fstream>

#include "json.hpp"

using json = nlohmann::json;

struct Student {
    unsigned int id;
    std::string firstName;
    std::string lastName;
    float score;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Student, id, firstName, lastName, score)
};

void dump() {
    std::vector<Student> v = {
        { 10234, "Jan", "Kowalski", 78.5f },
        { 10567, "Anna", "Nowak", 92.3f },
        { 11002, "Piotr", "Wiśniewski", 65.7f },
        { 11543, "Katarzyna", "Wójcik", 88.1f },
        { 12011, "Michał", "Kowalczyk", 73.9f },
        { 12567, "Agnieszka", "Kamińska", 81.4f },
        { 13045, "Tomasz", "Lewandowski", 59.8f },
        { 13521, "Magdalena", "Zielińska", 94.6f },
        { 14009, "Paweł", "Szymański", 68.2f },
        { 14588, "Ewa", "Woźniak", 77.0f }
    };

    json data = v;
    std::cout << data.dump() << std::endl;
}

void parse() {
    /* Wczytanie ze stringa */
    std::string text = "[\
        { \"id\": 15023, \"firstName\": \"Marcin\", \"lastName\": \"Dąbrowski\", \"score\": 82.5 },\
        { \"id\": 15567, \"firstName\": \"Joanna\", \"lastName\": \"Kozłowska\", \"score\": 91.2 },\
        { \"id\": 16001, \"firstName\": \"Łukasz\", \"lastName\": \"Jankowski\", \"score\": 64.3 },\
        { \"id\": 16543, \"firstName\": \"Monika\", \"lastName\": \"Mazur\", \"score\": 86.7 },\
        { \"id\": 17022, \"firstName\": \"Krzysztof\", \"lastName\": \"Krawczyk\", \"score\": 72.1 },\
        { \"id\": 17567, \"firstName\": \"Natalia\", \"lastName\": \"Piotrowska\", \"score\": 89.9 },\
        { \"id\": 18045, \"firstName\": \"Adam\", \"lastName\": \"Grabowski\", \"score\": 55.6 },\
        { \"id\": 18521, \"firstName\": \"Aleksandra\", \"lastName\": \"Pawlak\", \"score\": 96.4 },\
        { \"id\": 19009, \"firstName\": \"Damian\", \"lastName\": \"Michalski\", \"score\": 69.5 },\
        { \"id\": 19588, \"firstName\": \"Karolina\", \"lastName\": \"Król\", \"score\": 80.3 }\
    ]";
    json data = json::parse(text);

    std::vector<Student> v = data;

    for (const auto &item : v)
    {
        std::cout << " [" << item.id << "] " << item.firstName << " " << item.lastName << ": " << item.score << std::endl;
    }
}

json fileToJson(std::string filename) {
    std::ifstream t(filename);
    std::stringstream buffer;
    buffer << t.rdbuf();
    t.close();
    json data = json::parse(buffer);
    return data;
}

void jsonToFile(json data, std::string filename) {
    std::ofstream t(filename);
    t << data.dump(4); 
    t.close();
}

std::vector<Student> jsonToVector(json data) {
    std::vector<Student> v = data;
    return v;
}

json vectorToJson(std::vector<Student> v) {
    json data = v;
    return data;
}

int main()
{
    std::string filein = "data_input.json";
    std::string fileout = "data_output.json";

    json datain = fileToJson(filein);
    std::vector<Student> v = jsonToVector(datain);
    for (int i = 0; i < v.size(); i++) {
        v[i].id = i;
    }
    json dataout = vectorToJson(v);
    jsonToFile(dataout, fileout);

    return 0;
}