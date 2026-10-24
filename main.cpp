#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "applicant.h"

using namespace std;

// Comparison function for sorting:
// 1. State Region (ascending alphabetical: NE, NW, SE, SW)
// 2. Student GPA (descending: highest GPA first)
// 3. AP Courses Taken (descending: most AP courses first)
bool compareApplicants(const Applicant& a, const Applicant& b) {
    if (a.getRegion() != b.getRegion()) {
        return a.getRegion() < b.getRegion();
    }
    if (a.getGpa() != b.getGpa()) {
        return a.getGpa() > b.getGpa();
    }
    return a.getApCourses() > b.getApCourses();
}

// Adapted Merge Sort Implementation from source code from prof. Gauch
void merge_sort2(vector<Applicant>& data, vector<Applicant>& copy, int low, int high) {
    int range = high - low + 1;
    if (range > 1) {
        int mid = (low + high) / 2;
        merge_sort2(data, copy, low, mid);
        merge_sort2(data, copy, mid + 1, high);

        int index1 = low;
        int index2 = mid + 1;
        int index = 0;

        while (index1 <= mid && index2 <= high) {
            if (compareApplicants(data[index1], data[index2])) {
                copy[index++] = data[index1++];
            } else {
                copy[index++] = data[index2++];
            }
        }

        while (index1 <= mid)
            copy[index++] = data[index1++];

        while (index2 <= high)
            copy[index++] = data[index2++];

        for (index = 0; index < range; index++)
            data[low + index] = copy[index];
    }
}

void merge_sort(vector<Applicant>& data, int low, int high) {
    int range = high - low + 1;
    if (range > 1) {
        vector<Applicant> copy(range);
        merge_sort2(data, copy, low, high);
    }
}

int main() {
    // 1. Read applicant data file into vector of Applicant objects
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

    cout << "Successfully read " << applicants.size() << " applicant records from applicant.csv." << endl;

    // 2. Sort the Applicant vector using merge sort
    if (!applicants.empty()) {
        merge_sort(applicants, 0, applicants.size() - 1);
    }
    cout << "Successfully sorted applicants by State Region, GPA, and AP Courses." << endl;

    // 3. Prompt user for scholarship selection percentage P (0 to 100)
    int p = -1;
    while (true) {
        cout << "\nEnter scholarship selection percentage P (0 to 100): ";
        cin >> p;

        if (cin.fail() || p < 0 || p > 100) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter an integer between 0 and 100." << endl;
        } else {
            break;
        }
    }

    // 4. Print top P percent of students in each state region
    cout << "\n========================================\n";
    cout << " SCHOLARSHIP WINNERS (Top " << p << "% per Region)\n";
    cout << "========================================\n";

    size_t i = 0;
    while (i < applicants.size()) {
        string currentRegion = applicants[i].getRegion();
        
        vector<const Applicant*> regionApplicants;
        while (i < applicants.size() && applicants[i].getRegion() == currentRegion) {
            regionApplicants.push_back(&applicants[i]);
            i++;
        }

        int totalRegionApplicants = regionApplicants.size();
        int numWinners = (totalRegionApplicants * p + 50) / 100; 
        if (p > 0 && numWinners == 0 && totalRegionApplicants > 0) {
            numWinners = 1; // Guarantee at least 1 winner if P > 0
        }

        cout << "\n----------------------------------------\n";
        cout << "Region: " << currentRegion << " (Total Applicants: " << totalRegionApplicants 
             << " | Selected Winners: " << numWinners << ")\n";
        cout << "----------------------------------------\n";

        for (int j = 0; j < numWinners && j < totalRegionApplicants; ++j) {
            cout << "Rank " << (j + 1) << ":\n";
            regionApplicants[j]->print();
        }
    }

    return 0;
}