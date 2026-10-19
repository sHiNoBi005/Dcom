
#ifndef LINE_ENCODING_H
#define LINE_ENCODING_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Shared encoded signal
extern vector<int> encodeSignal;

// Basic line encoding techniques
void NRZ_L(string bitstream);
void NRZ_I(string bitstream);
void Manchester(const string& bits);
void DiffManchester(const string& bits);

// AMI and scrambling techniques
void AMI_Dashboard(string bitstream);
void AMI(const string& bits);
void B8ZS(const string& bits);
void HDB3(const string& bits);

// Encoding menu
void EncodingDashboard(string bitstream);

#endif
