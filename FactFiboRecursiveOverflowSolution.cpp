/*
Module Name:	Factorial Fibonacci Recursive Overflow
Date:			9-15-2019
Author:			Drew Pulliam

Module Purpose
Calculates factorials and Fibonacci numbers using both loops and recursive functions

Module Design Description

Inputs:
None

Outputs:
Sequence of factorials and Fibonacci numbers until overflow is reached (on 32 bit numbers)

*/

#include "pch.h"

#include <safeint.h>
#include <chrono>
#include <limits>
#include <locale>

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;
using namespace msl::utilities;
using namespace chrono;

void calculateTimeFactorialLoopFunc(void);
void calculateTimeFactorialRecursiveFunc(void);
void calculateTimeFibonacciLoopFunc(void);
void calculateTimeFibonacciRecursiveFunc(void);

int main()
{
	cout.imbue(locale(""));

	cout << "32 bit unsigned Factorial Loop" << endl;
	cout << "------------------------------" << endl;
	calculateTimeFactorialLoopFunc();

	cout << endl;
	cout << "32 bit unsigned Factorial Recursion" << endl;
	cout << "-----------------------------------" << endl;
	calculateTimeFactorialRecursiveFunc();

	system("pause");	system("cls");

	cout << "32 bit unsigned Fibonacci Loop" << endl;
	cout << "------------------------------" << endl;
	calculateTimeFibonacciLoopFunc();

	cout << endl;
	cout << "32 bit unsigned Fibonacci Recursion" << endl;
	cout << "-----------------------------------" << endl;
	calculateTimeFibonacciRecursiveFunc();

	system("pause");	system("cls");
}

void calculateTimeFactorialLoopFunc(void)
{
	auto timeStart = steady_clock::now();

	uint32_t i = 1, iResult = 1;
	for (; SafeMultiply<uint32_t, uint32_t>(iResult, i, iResult); i++)
	{
		cout << setw(3) << i << setw(30) << iResult << endl;
	}

	auto timeTaken = duration_cast<nanoseconds> (steady_clock::now() - timeStart);

	cout << endl;
	cout << "Unsigned overflow at i : " << setw(15) << i << endl;
	cout << "Time Elapsed (nano)    : " << setw(15) << timeTaken.count() << endl;

}

void calculateTimeFactorialRecursiveFunc(void)
{
	
}

void calculateTimeFibonacciLoopFunc(void)
{
	auto timeStart = steady_clock::now();

	cout << setw(3) << 0 << setw(30) << 0 << endl;
	cout << setw(3) << 1 << setw(30) << 1 << endl;

	uint32_t i = 2, a = 0, b = 1, sum;
	for (; SafeAdd<uint32_t, uint32_t>(a, b, sum); i++)
	{
		cout << setw(3) << i << setw(30) << sum << endl;
		a = b;
		b = sum;
	}

	auto timeTaken = duration_cast<nanoseconds> (steady_clock::now() - timeStart);

	cout << endl;
	cout << "Unsigned overflow at i : " << setw(15) << i << endl;
	cout << "Time Elapsed (nano)    : " << setw(15) << timeTaken.count() << endl;
}

void calculateTimeFibonacciRecursiveFunc(void)
{

}