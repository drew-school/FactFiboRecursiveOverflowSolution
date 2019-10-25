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
void factorialRecursiveFunc(uint32_t & i, uint32_t prevFactorial);

void calculateTimeFibonacciLoopFunc(void);
void calculateTimeFibonacciRecursiveFunc(void);
void fibonacciRecursiveFunc(uint32_t & i, uint32_t prevNum0, uint32_t prevNum1, uint32_t & sum);

int main()
{
	// formats all numbers >999 to include separating commas
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

	uint32_t i = 1, prevFactorial = 1;
	// multiply current number i by factorial of previous number
	// if it overflows, return
	for (; SafeMultiply<uint32_t, uint32_t>(prevFactorial, i, prevFactorial); i++)
	{
		cout << setw(3) << i << setw(30) << prevFactorial << endl;
	}

	// finds time taken by the loop
	auto timeTaken = duration_cast<nanoseconds> (steady_clock::now() - timeStart);

	cout << endl;
	cout << "Unsigned overflow at i : " << setw(15) << i << endl;
	cout << "Time Elapsed (nano)    : " << setw(15) << timeTaken.count() << endl;

}

void calculateTimeFactorialRecursiveFunc(void)
{
	auto timeStart = steady_clock::now();

	uint32_t i = 1, prevFactorial = 1;
	factorialRecursiveFunc(i, prevFactorial);

	// finds time taken by the recursive function
	auto timeTaken = duration_cast<nanoseconds> (steady_clock::now() - timeStart);

	cout << endl;
	cout << "Unsigned overflow at i : " << setw(15) << i << endl;
	cout << "Time Elapsed (nano)    : " << setw(15) << timeTaken.count() << endl;
}

void factorialRecursiveFunc(uint32_t & i, uint32_t prevFactorial)
{
	// multiply current number i by factorial of previous number
	// if it overflows, return
	if (SafeMultiply<uint32_t, uint32_t>(prevFactorial, i, prevFactorial))
	{
		cout << setw(3) << i << setw(30) << prevFactorial << endl;
		factorialRecursiveFunc(++i, prevFactorial);
	}
}

void calculateTimeFibonacciLoopFunc(void)
{
	auto timeStart = steady_clock::now();

	// output first two terms of fibonacci series (0 and 1)
	cout << setw(3) << 0 << setw(30) << 0 << endl;
	cout << setw(3) << 1 << setw(30) << 1 << endl;

	uint32_t i = 2, prevNum0 = 0, prevNum1 = 1, sum;
	// add previous two numbers (prevNum0 and prevNum1)
	// if sum overflows, return
	for (; SafeAdd<uint32_t, uint32_t>(prevNum0, prevNum1, sum); i++)
	{
		cout << setw(3) << i << setw(30) << sum << endl;
		prevNum0 = prevNum1;
		prevNum1 = sum;
	}

	// finds time taken by the loop
	auto timeTaken = duration_cast<nanoseconds> (steady_clock::now() - timeStart);

	cout << endl;
	cout << "Unsigned overflow at i : " << setw(15) << i << endl;
	cout << "Time Elapsed (nano)    : " << setw(15) << timeTaken.count() << endl;
}

void calculateTimeFibonacciRecursiveFunc(void)
{
	uint32_t i = 0, sum, prevNum0 = 0, prevNum1 = 1;

	auto timeStart = steady_clock::now();

	// output first two terms of fibonacci series (0 and 1)
	cout << setw(3) <<   i << setw(30) << prevNum0 << endl;
	cout << setw(3) << ++i << setw(30) << prevNum1 << endl;
	fibonacciRecursiveFunc(++i,prevNum0,prevNum1,sum);

	// finds time taken by the recursive function
	auto timeTaken = duration_cast<nanoseconds> (steady_clock::now() - timeStart);

	cout << endl;
	cout << "Unsigned overflow at i : " << setw(15) << i << endl;
	cout << "Time Elapsed (nano)    : " << setw(15) << timeTaken.count() << endl;
}


void fibonacciRecursiveFunc(uint32_t & i, uint32_t prevNum0, uint32_t prevNum1, uint32_t & sum)
{
	// add previous two numbers (prevNum0 and prevNum1)
	// if sum overflows, return
	if (SafeAdd<uint32_t, uint32_t>(prevNum0, prevNum1, sum))
	{
		cout << setw(3) << i << setw(30) << sum << endl;
		fibonacciRecursiveFunc(++i, prevNum1, sum, sum);
	}
	return;
}