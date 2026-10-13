#include "Time.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>

void Time::normalize() {
    long total = hours * 3600 + minutes * 60 + seconds;

    total = total % 86400;
    if (total < 0) {
        total += 86400;
    }

    hours = total / 3600;
    total %= 3600;
    minutes = total / 60;
    seconds = total % 60;
}

Time::Time() {
    Init(0, 0, 0);
}

Time::Time(int h, int m, int s) {
    Init(h, m, s);
}

Time::Time(const std::string& timeStr) {
    Init(timeStr);
}

Time::Time(long totalSeconds) {
    Init(totalSeconds);
}

Time::Time(const Time& otherTime) {
    Init(otherTime);
}

Time::~Time() {
}

void Time::Init(int h, int m, int s) {
    hours = h;
    minutes = m;
    seconds = s;
    normalize();
}

void Time::Init(const std::string& timeStr) {
    char colon1, colon2;
    std::stringstream ss(timeStr);
    ss >> hours >> colon1 >> minutes >> colon2 >> seconds;
    normalize();
}

void Time::Init(long totalSeconds) {
    hours = 0;
    minutes = 0;
    seconds = totalSeconds;
    normalize();
}

void Time::Init(const Time& otherTime) {
    hours = otherTime.hours;
    minutes = otherTime.minutes;
    seconds = otherTime.seconds;
}

void Time::Read() {
    std::cout << "¬вед≥ть години: "; std::cin >> hours;
    std::cout << "¬вед≥ть хвилини: "; std::cin >> minutes;
    std::cout << "¬вед≥ть секунди: "; std::cin >> seconds;
    normalize();
}

std::string Time::toString() const {
    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << hours << ":"
        << std::setw(2) << std::setfill('0') << minutes << ":"
        << std::setw(2) << std::setfill('0') << seconds;
    return ss.str();
}

void Time::Display() const {
    std::cout << toString() << std::endl;
}

long Time::toSeconds() const {
    return hours * 3600 + minutes * 60 + seconds;
}

long Time::differenceInSeconds(const Time& other) const {
    return std::abs(this->toSeconds() - other.toSeconds());
}

void Time::addSeconds(long s) {
    long currentSeconds = toSeconds();
    Init(currentSeconds + s);
}

void Time::subtractSeconds(long s) {
    long currentSeconds = toSeconds();
    Init(currentSeconds - s);
}

int Time::compare(const Time& other) const {
    long t1 = this->toSeconds();
    long t2 = other.toSeconds();
    if (t1 > t2) return 1;
    if (t1 < t2) return -1;
    return 0;
}

int Time::toMinutesRounded() const {
    int totalMins = hours * 60 + minutes;
    if (seconds >= 30) {
        totalMins++;
    }
    return totalMins;
}

Time Time::operator+(long s) const {
    Time result(*this);
    result.addSeconds(s);
    return result;
}

Time Time::operator-(long s) const {
    Time result(*this);
    result.subtractSeconds(s);
    return result;
}

bool Time::operator==(const Time& other) const {
    return this->compare(other) == 0;
}

bool Time::operator>(const Time& other) const {
    return this->compare(other) > 0;
}