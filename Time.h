#pragma once
#include <string>

class Time {
private:
    int hours;
    int minutes;
    int seconds;

    void normalize();

public:
    Time();

    void Init(int h, int m, int s);
    void Init(const std::string& timeStr);
    void Init(long totalSeconds);
    void Init(const Time& otherTime);

    void Read();
    std::string toString() const;
    void Display() const;

    long toSeconds() const;
    long differenceInSeconds(const Time& other) const;
    void addSeconds(long s);
    void subtractSeconds(long s);
    int compare(const Time& other) const;
    int toMinutesRounded() const;
};