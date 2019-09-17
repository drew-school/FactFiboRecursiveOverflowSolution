/*
Module Name:	Factorial Fibonacci Recursive Overflow
Date:			9-17-2019
Author:			Drew Pulliam

Module Purpose
Calculates factorials and Fibonacci numbers using both loops and recursive functions

Module Design Description

Inputs:
None

Outputs:
Sequence of factorials and Fibonacci numbers until overflow is reached (using 32 bit numbers)

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
void factorialRecursiveFunc(uint32_t & i, uint32_t iResult);

void calculateTimeFibonacciLoopFunc(void);
void calculateTimeFibonacciRecursiveFunc(void);
void fibonacciRecursiveFunc(uint32_t & i, uint32_t num0, uint32_t num1, uint32_t & sum);

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
	cout << endl;

	system("pause");	system("cls");

	cout << "32 bit unsigned Fibonacci Loop" << endl;
	cout << "------------------------------" << endl;
	calculateTimeFibonacciLoopFunc();
	cout << endl;

	cout << "32 bit unsigned Fibonacci Recursion" << endl;
	cout << "-----------------------------------" << endl;
	calculateTimeFibonacciRecursiveFunc();
	cout << endl;

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
	auto timeStart = steady_clock::now();

	uint32_t i = 1, iResult = 1;
	factorialRecursiveFunc(i, iResult);
	auto timeTaken = duration_cast<nanoseconds> (steady_clock::now() - timeStart);

	cout << endl;
	cout << "Unsigned overflow at i : " << setw(15) << i << endl;
	cout << "Time Elapsed (nano)    : " << setw(15) << timeTaken.count() << endl;
}

void factorialRecursiveFunc(uint32_t & i, uint32_t iResult)
{
	if (SafeMultiply<uint32_t, uint32_t>(iResult, i, iResult))
	{
		cout << setw(3) << i << setw(30) << iResult << endl;
		factorialRecursiveFunc(++i, iResult);
	}
}

void calculateTimeFibonacciLoopFunc(void)
{
	auto timeStart = steady_clock::now();

	cout << setw(3) << 0 << setw(30) << 0 << endl;
	cout << setw(3) << 1 << setw(30) << 1 << endl;

	uint32_t i = 2, num0 = 0, num1 = 1, sum;
	for (; SafeAdd<uint32_t, uint32_t>(num0, num1, sum); i++)
	{
		cout << setw(3) << i << setw(30) << sum << endl;
		num0 = num1;
		num1 = sum;
	}

	auto timeTaken = duration_cast<nanoseconds> (steady_clock::now() - timeStart);

	cout << endl;
	cout << "Unsigned overflow at i : " << setw(15) << i << endl;
	cout << "Time Elapsed (nano)    : " << setw(15) << timeTaken.count() << endl;
}

void calculateTimeFibonacciRecursiveFunc(void)
{
	//this func gets timing, other func actually does the factorial math
	uint32_t i = 0, sum, num0 = 0, num1 = 1;

	auto timeStart = steady_clock::now();

	cout << setw(3) <<   i << setw(30) << num0 << endl;
	cout << setw(3) << ++i << setw(30) << num1 << endl;
	fibonacciRecursiveFunc(++i,num0,num1,sum);

	auto timeTaken = duration_cast<nanoseconds> (steady_clock::now() - timeStart);

	cout << endl;
	cout << "Unsigned overflow at i : " << setw(15) << i << endl;
	cout << "Time Elapsed (nano)    : " << setw(15) << timeTaken.count() << endl;
}


void fibonacciRecursiveFunc(uint32_t & i, uint32_t num0, uint32_t num1, uint32_t & sum)
{
	if (SafeAdd<uint32_t, uint32_t>(num0, num1, sum))
	{
		cout << setw(3) << i << setw(30) << sum << endl;
		fibonacciRecursiveFunc(++i, num1, sum, sum);
	}
	return;
}