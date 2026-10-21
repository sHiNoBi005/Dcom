
#ifndef PCM_H
#define PCM_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <bitset>
#include <cmath>

using namespace std;

string PCM_Modulation(vector<double>& sample);

vector<double> PCM_Demodulation(
    const string& bitstream,
    double v_min,
    double v_max);

#endif
