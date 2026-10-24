#ifndef APPLICANT_H
#define APPLICANT_H

#include <string>
#include <iostream>

using namespace std;

class Applicant {
private:
    string name;
    string streetAddress;
    string city;
    string region; // NE, NW, SE, SW
    double gpa;
    int apCourses;

public:
    // Constructors
    Applicant();
    Applicant(string name, string streetAddress, string city, 
              string region, double gpa, int apCourses);

    // Getters
    string getName() const;
    string getStreetAddress() const;
    string getCity() const;
    string getRegion() const;
    double getGpa() const;
    int getApCourses() const;

    // Setters
    void setName(const string& name);
    void setStreetAddress(const string& streetAddress);
    void setCity(const string& city);
    void setRegion(const string& region);
    void setGpa(double gpa);
    void setApCourses(int apCourses);

    // Print method
    void print() const;
};

#endif // APPLICANT_H