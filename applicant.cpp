#include "applicant.h"
#include <iomanip>

// Default Constructor
Applicant::Applicant() : name(""), streetAddress(""), city(""), region(""), gpa(0.0), apCourses(0) {}

// Parameterized Constructor
Applicant::Applicant(string name, string streetAddress, string city, 
                     string region, double gpa, int apCourses)
    : name(name), streetAddress(streetAddress), city(city), region(region), gpa(gpa), apCourses(apCourses) {}

// Getters
string Applicant::getName() const { return name; }
string Applicant::getStreetAddress() const { return streetAddress; }
string Applicant::getCity() const { return city; }
string Applicant::getRegion() const { return region; }
double Applicant::getGpa() const { return gpa; }
int Applicant::getApCourses() const { return apCourses; }

// Setters
void Applicant::setName(const string& name) { this->name = name; }
void Applicant::setStreetAddress(const string& streetAddress) { this->streetAddress = streetAddress; }
void Applicant::setCity(const string& city) { this->city = city; }
void Applicant::setRegion(const string& region) { this->region = region; }
void Applicant::setGpa(double gpa) { this->gpa = gpa; }
void Applicant::setApCourses(int apCourses) { this->apCourses = apCourses; }

// Print method
void Applicant::print() const {
    cout << "Name: " << name << "\n"
         << "Address: " << streetAddress << ", " << city << " (" << region << ")\n"
         << "GPA: " << fixed << setprecision(2) << gpa << "\n"
         << "AP Courses Taken: " << apCourses << "\n"
         << "----------------------------------------\n";
}