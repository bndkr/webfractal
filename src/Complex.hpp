#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iostream>
#include <string>
#include <math.h>

class Complex
{
public:

	double real, imaginary;
	Complex(double rp, double ip)
	{
		this->imaginary = ip;
		this->real = rp;
	}

	Complex()
	{
		this->imaginary = 0.0f;
		this->real = 0.0f;
	}


	std::string toString()
	{
		if (imaginary < 0)
		{
			return std::to_string(real) + " " + std::to_string(imaginary) + "i" + "\n";
		}
		else if (imaginary == 0)
		{
			return  std::to_string(real) + "\n";
		}
		else
		{
			return std::to_string(real) + " " + std::to_string(imaginary) + "i" + "\n";
		}
	}

	Complex operator+(Complex other)
	{
		return Complex(real + other.real, imaginary + other.imaginary);
	}

	Complex operator-(Complex other)
	{
		return Complex(real - other.real, imaginary - other.imaginary);
	}

	Complex operator-(double other)
	{
		return Complex(real - other, imaginary);
	}

	Complex operator*(Complex& other)
	{
		return Complex(
			(real * other.real) - (imaginary * other.imaginary),
			(real * other.imaginary) + (imaginary * other.real)
		);
	}
	Complex operator*(double other)
	{
		return Complex(other * real, other * imaginary);
	}
	Complex operator/(Complex other)
	{
		return Complex(
			((real * other.real) + (imaginary * other.imaginary)) /
			((other.real * other.real) + (other.imaginary * other.imaginary)),
			((imaginary * other.real) - (real * other.imaginary)) /
			((other.real * other.real) + (other.imaginary * other.imaginary))
		);
	}

	Complex abs()
	{
		return Complex(std::abs(real), std::abs(imaginary));
	}
	Complex square()
	{
		return Complex(
			(real * real) - (imaginary * imaginary),
			(real * imaginary) * 2
		);
	}
	double distanceFromOrigin()
	{
		return sqrt(real * real + imaginary * imaginary);
	}
	Complex returnNewtonFunction()
	{
		Complex n = Complex(real, imaginary);
		Complex s = Complex(1, 0);
		return (n * n * n) - s;
	}
	Complex returnDerivative()
	{
		Complex n = Complex(real, imaginary);
		Complex s = Complex(3, 0);
		return s * n * n;
	}
};
#endif
