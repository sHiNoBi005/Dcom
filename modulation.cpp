#include "PCM.h"
using namespace std;
string PCM_Modulation(vector<double>& sample){
    if (sample.empty()) {
        return "";
    }
    double v_max = *max_element(sample.begin(), sample.end());
    double v_min = *min_element(sample.begin(), sample.end());
    double height = (v_max - v_min)/8;
    string bitstream = "";
    vector<double> quantized(8);
    // Handle constant-valued samples
    if (v_max == v_min) {
        for (size_t i = 0; i < sample.size(); i++) {
            bitstream += "000";
        }
        return bitstream;
    }
    for (int i = 0; i < 8; i++)
    {
        quantized[i] = v_min + (i + 0.5) * height;
    }
     for (double x : sample) {
        int index = round((x - v_min) / height);

        // Keep the index within the valid range
        index = max(0, min(7, index));
    }
    for (double x : sample) {
        int index = static_cast<int>((x - v_min) / height);
        index = max(0, min(7, index));
        cout << bitset<3>(index).to_string();
        bitstream += bitset<3>(index).to_string();
    }
    return bitstream;
}