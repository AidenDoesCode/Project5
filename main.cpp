#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "applicant.h"

using namespace std;

int main() {
    ifstream file("applicant.csv");
    if (!file.is_open()) {
        cerr << "Error: Could not open file applicant.csv" << endl;
        return 1;
    }

    vector<Applicant> applicants;
    string line;

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string name, streetAddress, city, region, gpaStr, apStr;

        if (getline(ss, name, ',') &&
            getline(ss, streetAddress, ',') &&
            getline(ss, city, ',') &&
            getline(ss, region, ',') &&
            getline(ss, gpaStr, ',') &&
            getline(ss, apStr, ',')) {
            
            double gpa = stod(gpaStr);
            int apCourses = stoi(apStr);

            applicants.emplace_back(name, streetAddress, city, region, gpa, apCourses);
        }
    }

    file.close();

    // Print out each student's application materials
    cout << "Successfully loaded " << applicants.size() << " applicants.\n\n";
    for (const auto& applicant : applicants) {
        applicant.print();
    }

    return 0;
}