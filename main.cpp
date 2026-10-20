#include "plot.h"
#include "SignalHandler.h"
#include "PCM.h"
#include "LineEncoding.h"
using namespace std;

string RandomBits(int size){
    string s = "";
    for(int i=0; i<size; i++){
        s += to_string(rand()%2);
    }
    return s;
}

string randomBitsWithZero(int size, int zero){
    string s = RandomBits(size);
    if(size < zero){
        cout << "Size too short for " << zero << " zeroes" << endl;
        exit(0);
    }
    int pos = rand()%(size - zero);
    for(int i=pos; i<(pos + zero); i++){
        s[i] = '0';
    }
    
    return s;
}

vector<double> readAnalogSamples() {
    int n;
    cout << "Enter no of sample points" << endl;
    cin >> n;

    vector<double> samples(n);
    cout << "Enter Samples" << endl;
    for (double& x : samples)
        cin >> x;

    return samples;
}

 // Need to be studied
 string longestPalindrome(string s) {
        if (s.empty()) {
            return "";
        }

        string transformed = "^";
        for (char ch : s) {
            transformed += '#';
            transformed += ch;
        }
        transformed += "#$";

        int n = static_cast<int>(transformed.size());
        vector<int> radius(n, 0);
        int center = 0;
        int right = 0;
        int bestCenter = 0;
        int bestRadius = 0;

        for (int i = 1; i < n - 1; i++) {
            int mirror = 2 * center - i;

            if (i < right) {
                radius[i] = min(right - i, radius[mirror]);
            }

            while (transformed[i + 1 + radius[i]]
                   == transformed[i - 1 - radius[i]]) {
                radius[i]++;
            }

            if (i + radius[i] > right) {
                center = i;
                right = i + radius[i];
            }

            if (radius[i] > bestRadius) {
                bestRadius = radius[i];
                bestCenter = i;
            }
        }

        int start = (bestCenter - bestRadius) / 2;
        return s.substr(start, bestRadius);
    }

void DigitalDataHandler(){
    int n;
    cout << "Enter length of bit stream" << endl;
    cin >> n;
    cout << "1. Fully Random \n";
    cout << "2. Include 4 consecutive zeros\n";
    cout << "3. Include 8 consecutive zeros\n";
    int choice;
    cin >> choice;
    string bits;
    switch(choice){
        case 1: bits=RandomBits(n);
        break;
        case 2: bits=randomBitsWithZero(n,4);
        break;
        case 3: bits=randomBitsWithZero(n,8);
        break;
        default: cout << "Enter a valid choice\n";
    }
    cout<<"bits generated : "<<bits<<endl;
    cout<<"longest pallindrome present here : "<<longestPalindrome(bits)<<endl;
    EncodingDashboard(bits);
    if (!encodeSignal.empty())
        plotSignal(encodeSignal, encodeSignal.size() / bits.size());

}

void dashboard(){
    cout << "============================================\n";
    cout << "       DIGITAL SIGNAL ENCODER/DECODER\n";
    cout << "============================================\n";
    cout << "1. Digital Data Generation\n";
    cout << "2. Analog Data Generation\n";
    cout << "3. Exit\n";
    cout << "============================================\n";
}


int main(){
    while (true)
    {
        srand(time(0));
        dashboard();
        int option;
        cin >> option;
        vector<double> sample;
        string pcm_bits;
        switch(option){
            case 1: DigitalDataHandler();
            break;
            case 2: sample = readAnalogSamples();
                    pcm_bits = PCM_Modulation(sample);
                    cout << pcm_bits << endl;
                    EncodingDashboard(pcm_bits);
                     if (!encodeSignal.empty())
        plotSignal(encodeSignal, encodeSignal.size() / pcm_bits.size());

            break;
            case 3: return 0;
            break;
            default: cout << "Enter a valid input";
        }
    }
return 0;
}