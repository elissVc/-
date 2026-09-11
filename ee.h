#pragma once

class ee
{
private:
	double first;
	double second;

public:
	bool Init(double a, double b);
	void Read();
	void Display() const;
	double function(double x) const;
};
