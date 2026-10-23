#pragma once
#include <string>

#ifdef TIMEDLL_EXPORTS
#define TIMEDLL_API __declspec(dllexport)
#else
#define TIMEDLL_API __declspec(dllimport)
#endif

class TIMEDLL_API Time {
private:
    int hours;
    int minutes;
    int seconds;

    void normalize();

public:
    Time();

    Time(int h, int m, int s);
    Time(const std::string& timeStr);
    Time(long totalSeconds);
    Time(const Time& otherTime);
    ~Time();

    Time operator+(long s) const;
    Time operator-(long s) const;
    bool operator==(const Time& other) const;
    bool operator>(const Time& other) const;

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