
#ifndef SIGNAL_HANDLER_H
#define SIGNAL_HANDLER_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <random>

using namespace std;

// Digital data generation
string RandomBits(int size);
string randomBitsWithZero(int size, int zero);
void DigitalDataHandler();

// Analog data generation
vector<double> readAnalogSamples();

// Longest palindrome
string longestPalindrome(string s);

// Dashboard
void dashboard();

#endif
