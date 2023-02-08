// Fill out your copyright notice in the Description page of Project Settings.


#include "BigNumBPFunLibrary.h"
#include"stddef.h"
#include<string>
#include<cstdio>
#include<iostream>
#include<sstream>
#include <iomanip>
#include <stdlib.h>

using namespace std;
#define n 10

FString UBigNumBPFunLibrary::BigNumFun_Add(FString numA, FString numB)
{
	string numa = TCHAR_TO_UTF8(*numA);
	if (numa[0] == '-' || numa[0] == '0' || numa.empty())
	{
		numa = "0";
	}
	string numb = TCHAR_TO_UTF8(*numB);
	if (numb[0] == '-' || numb[0] == '0' || numb.empty())
	{
		numb = "0";
	}
	//UE_LOG(LogTemp, Log, TEXT("=======s_add == numA ==%s"), UTF8_TO_TCHAR(numa.c_str()));
	//UE_LOG(LogTemp, Log, TEXT("=======s_add == numB ==%s"), UTF8_TO_TCHAR(numb.c_str()));
	FString showString = s_add(numa, numb).c_str();
	//UE_LOG(LogTemp, Log, TEXT("=======s_add == showString ==%s"), showString);
	return showString;
}

FString UBigNumBPFunLibrary::BigNumFun_Minus(FString numA, FString numB)
{
	string numa = TCHAR_TO_UTF8(*numA);
	if (numa[0] == '-' || numa[0] == '0' || numa.empty())
	{
		numa = "0";
	}
	string numb = TCHAR_TO_UTF8(*numB);
	if (numb[0] == '-' || numb[0] == '0' || numb.empty())
	{
		numb = "0";
	}
	FString showString = s_minus(numa,numb).c_str();
	return showString;
}

FString UBigNumBPFunLibrary::BigNumFun_Divide(FString num, int divisor, int digit)
{
	FString showString = "0";
	string a = TCHAR_TO_UTF8(*num);
	if (a[0] == '-' || a[0] == '0' || a.empty()|| divisor == 0)
	{
		return showString;
	}
	showString = s_divide(a, divisor, digit).c_str();
	return showString;
}

FString UBigNumBPFunLibrary::BigNumFun_multiply(FString numA, FString numB)
{
	string numa = TCHAR_TO_UTF8(*numA);
	if (numa[0] == '-' || numa[0] == '0' || numa.empty())
	{
		numa = "0";
	}
	string numb = TCHAR_TO_UTF8(*numB);
	if (numb[0] == '-' || numb[0] == '0' || numb.empty())
	{
		numb = "0";
	}
	FString showString = s_multiply(numa,numb).c_str();
	return showString;
}

int UBigNumBPFunLibrary::BigNumFun_Judge(FString numA, FString numB)
{
	string numa = TCHAR_TO_UTF8(*numA);
	if (numa[0] == '-' || numa[0] == '0' || numa.empty())
	{
		numa = "0";
	}
	string numb = TCHAR_TO_UTF8(*numB);
	if (numb[0] == '-' || numb[0] == '0' || numb.empty())
	{
		numb = "0";
	}
	int sum = s_judge(numa, numb);
	return sum;
}

string UBigNumBPFunLibrary::s_divide(string num, int divisor, int digit)
{
	if (num.empty() || num[0] == '-' || divisor == 0)
	{
		return "0";
	}

	if (s_judge(num, to_string(divisor)) == 0) return "1";

	if (digit <= 0)
	{
		digit = 10;
	}

	string result;
	int index = 0;
	// extracting the part that is greater than the given divisor
	int dividend = num[index] - '0';
	while (dividend < divisor) {
		dividend = dividend * 10 + (num[++index] - '0');
	}
	// iterating until all digits participate in the division
	while (num.size() > index) {
		result += (dividend / divisor) + '0';
		dividend = (dividend % divisor) * 10 + num[++index] - '0';
	}
	if (result.length() == 0) {
	/*
		long double NumA = s_stringToDouble(num);
		if (NumA <= 0)
		{
			return "0";
		}
		double sum = NumA / divisor;
		string s_sum = "0";
		s_DoubleToStr(sum, 10, s_sum);
		return s_sum;
	*/
		return "0";
	}
	return result;
}


int UBigNumBPFunLibrary::s_judge(string a, string b)
{
	a = s_dezero(a);
	b = s_dezero(b);
	if (a.at(0) == 0 || a[0] == '-' || a.empty())
	{
		if (b.at(0) == 0 || b[0] == '-')
		{
			return 0;
		}
		else
		{
			return -1;
		}
	}
	else if (b.at(0) == 0 || b[0] == '-' || a.empty())
	{


		return 1;

	}
	if (a.length() > b.length()) return 1;
	if (a.length() < b.length()) return -1;
	long int i;
	for (i = 0; i < a.length(); i++)
	{
		if (a.at(i) > b.at(i)) return 1;
		if (a.at(i) < b.at(i)) return -1;
	}
	return 0;
}

string UBigNumBPFunLibrary::s_minus(string a, string b)
{
	a = s_dezero(a);
	b = s_dezero(b);
	long int i, j = 0;
	string c = "0";
	string c1, c2;
	string d = "-";
	if (s_judge(a, b) == 0) return c;
	if (s_judge(a, b) == 1)
	{
		c1 = a;
		c2 = b;
	}
	if (s_judge(a, b) == -1)
	{
		c1 = b;
		c2 = a;
		j = -1;
	}
	reverse(c1.begin(), c1.end());
	reverse(c2.begin(), c2.end());
	for (i = 0; i < c2.length(); i++)
	{
		if (c2.at(i) >= 48 && c2.at(i) <= 57) c2.at(i) -= 48;
		if (c2.at(i) >= 97 && c2.at(i) <= 122) c2.at(i) -= 87;
	}
	for (i = 0; i < c1.length(); i++)
	{
		if (c1.at(i) >= 48 && c1.at(i) <= 57) c1.at(i) -= 48;
		if (c1.at(i) >= 97 && c1.at(i) <= 122) c1.at(i) -= 87;
	}
	for (i = 0; i < c2.length(); i++)
	{
		c1.at(i) = c1.at(i) - c2.at(i);
	}
	for (i = 0; i < c1.length() - 1; i++)
	{
		if (c1.at(i) < 0)
		{
			c1.at(i) += n;
			c1.at(i + 1)--;
		}
	}
	for (i = c1.length() - 1; i >= 0; i--)
	{
		if (c1.at(i) > 0) break;
	}
	c1.erase(i + 1, c1.length());
	for (i = 0; i < c1.length(); i++)
	{
		if (c1.at(i) >= 10) c1.at(i) += 87;
		if (c1.at(i) < 10) c1.at(i) += 48;
	}
	reverse(c1.begin(), c1.end());
	if (j == -1) c1.insert(0, d);
	return c1;
}

string UBigNumBPFunLibrary::s_dezero(string a)
{
	long int i;
	for (i = 0; i < a.length(); i++)
	{
		if (a.at(i) > 48) break;
	}
	if (i == a.length()) return "0";
	a.erase(0, i);
	return a;
}

string UBigNumBPFunLibrary::s_add(string a, string b)
{
	a = s_dezero(a);
	b = s_dezero(b);
	string c;
	string d = "0";
	long int kmin, kmax, i;
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	if (a.length() > b.length()) { kmin = b.length(); kmax = a.length(); c = a; }
	else { kmin = a.length(); kmax = b.length(); c = b; }
	c.insert(c.length(), d);
	for (i = 0; i < kmin; i++)
	{
		if (a.at(i) >= 48 && a.at(i) <= 57) a.at(i) -= 48;
		if (a.at(i) >= 97 && a.at(i) <= 122) a.at(i) -= 87;
		if (b.at(i) >= 48 && b.at(i) <= 57) b.at(i) -= 48;
		if (b.at(i) >= 97 && b.at(i) <= 122) b.at(i) -= 87;
		c.at(i) = a.at(i) + b.at(i);
	}
	for (i = kmin; i < kmax + 1; i++)
	{
		if (c.at(i) >= 48 && c.at(i) <= 57) c.at(i) -= 48;
		if (c.at(i) >= 97 && c.at(i) <= 122) c.at(i) -= 87;
	}
	for (i = 0; i < kmax; i++)
	{
		if (c.at(i) >= n)
		{
			c.at(i + 1) += c.at(i) / n;
			c.at(i) = c.at(i) % n;
		}
	}
	if (c.at(kmax) == 0)
	{
		c.erase(kmax, kmax + 1);
	}
	for (i = 0; i < c.length(); i++)
	{
		if (c.at(i) >= 10) c.at(i) += 87;
		if (c.at(i) < 10) c.at(i) += 48;
	}
	reverse(c.begin(), c.end());
	return c;
}

string UBigNumBPFunLibrary::s_multiply(string a, string b)
{
	if (a == "0" || b == "0") {
		return "0";
	}
	string product(a.size() + b.size(), 0);
	for (int i = a.size() - 1; i >= 0; i--) {
		for (int j = b.size() - 1; j >= 0; j--) {
			int c = (a[i] - '0') * (b[j] - '0') + product[i + j + 1];
			product[i + j + 1] = c % 10;
			product[i + j] += c / 10;
		}
	}
	for (int i = 0; i < product.size(); i++) {
		product[i] += '0';
	}
	if (product[0] == '0') {
		return product.substr(1);
	}
	return product;
}

long double UBigNumBPFunLibrary::s_stringToDouble(string a)
{
	long double d;
	d = stold(a.c_str());
	return d;
}

void UBigNumBPFunLibrary::s_DoubleToStr(long double a, int digit, string& outR)
{
	std::ostringstream out;
	out.precision(std::numeric_limits<double>::digits10);
	out << a;

	string res = out.str();
	auto pos = res.find('.');
	if (pos == std::string::npos)
	{
		outR = res;
		return;

	}

	auto splitLen = pos + 1 + digit;
	if (res.size() <= splitLen)
	{
		outR = res;
		return;

	}

	outR = res.substr(0, splitLen);
	return;
}