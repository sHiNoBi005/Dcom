#include "PCM.h"
#include <cmath>
#include <algorithm>
#include <bitset>

using namespace std;

vector<double> PCM_Demodulation(
    const string& bitstream,
    double v_min,
    double v_max)
{
    vector<double> reconstructed;

    // Each PCM sample is represented by 3 bits.
    if (bitstream.empty() || bitstream.size() % 3 != 0)
    {
        return reconstructed;
    }

    // Handle constant-valued input samples.
    if (v_min == v_max)
    {
        for (size_t i = 0; i < bitstream.size() / 3; i++)
        {
            reconstructed.push_back(v_min);
        }

        return reconstructed;
    }

    double height = (v_max - v_min) / 8.0;

    for (size_t i = 0; i < bitstream.size(); i += 3)
    {
        string binary = bitstream.substr(i, 3);

        // Convert binary to a quantization index.
        int index = stoi(binary, nullptr, 2);

        // Reconstruct the midpoint of the quantization interval.
        double value = v_min + (index + 0.5) * height;

        reconstructed.push_back(value);
    }

    return reconstructed;
}