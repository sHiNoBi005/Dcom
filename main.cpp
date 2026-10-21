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

void validateBitStream(string& bits){
    for(char c: bits){
        if(c != '0' && c != '1'){
            cout << "Invalid bit stream. Only 0s and 1s are allowed." << endl;
            exit(0);
        }
    }
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
    cout << "4. Enter manually\n";
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
        case 4: cout << "Enter the bit stream: ";
                cin >> bits;
                validateBitStream(bits);
                break;
        default: cout << "Enter a valid choice\n";
    }
    cout<<"bits generated : "<<bits<<endl;
    cout<<"longest pallindrome present here : "<<longestPalindrome(bits)<<endl;
    EncodingDashboard(bits);
    if (!encodeSignal.empty())
        plotSignal(encodeSignal, encodeSignal.size() / bits.size());

}

void dashboard()
{
    cout << "\n";
    cout << "============================================\n";
    cout << "       DIGITAL SIGNAL ENCODER/DECODER\n";
    cout << "============================================\n";
    cout << "1. Digital Data Generation\n";
    cout << "2. Analog Data Generation (PCM Encoder)\n";
    cout << "3. PCM Decoder\n";
    cout << "4. Exit\n";
    cout << "============================================\n";
    cout << "Enter your choice: ";
}

// Store the most recent PCM encoding for later decoding.
string last_pcm_bits;
double last_pcm_min = 0.0;
double last_pcm_max = 0.0;
bool pcm_data_available = false;

void PCMDemodulationDashboard()
{
    cout << "\n";
    cout << "============================================\n";
    cout << "                 PCM DECODER\n";
    cout << "============================================\n";
    cout << "1. Decode last PCM encoded signal\n";
    cout << "2. Enter PCM bitstream manually\n";
    cout << "3. Return to main menu\n";
    cout << "============================================\n";
    cout << "Enter your choice: ";

    int choice;
    cin >> choice;

    string bits;
    double v_min, v_max;

    switch (choice)
    {
        case 1:
            if (!pcm_data_available)
            {
                cout << "No previous PCM encoding found.\n";
                cout << "Encode analog samples first.\n";
                return;
            }

            bits = last_pcm_bits;
            v_min = last_pcm_min;
            v_max = last_pcm_max;
            break;

        case 2:
            cout << "Enter PCM bitstream: ";
            cin >> bits;

            if (bits.empty() || bits.size() % 3 != 0)
            {
                cout << "Invalid PCM stream. "
                     << "Its length must be a multiple of 3.\n";
                return;
            }

            for (char bit : bits)
            {
                if (bit != '0' && bit != '1')
                {
                    cout << "Only 0s and 1s are allowed.\n";
                    return;
                }
            }

            cout << "Enter original minimum amplitude: ";
            cin >> v_min;

            cout << "Enter original maximum amplitude: ";
            cin >> v_max;

            if (!cin || v_min > v_max)
            {
                cout << "Invalid amplitude range.\n";
                return;
            }
            break;

        case 3:
            return;

        default:
            cout << "Invalid choice.\n";
            return;
    }

    vector<double> reconstructed =
        PCM_Demodulation(bits, v_min, v_max);

    if (reconstructed.empty())
    {
        cout << "Decoding failed or bitstream is empty.\n";
        return;
    }

    cout << "\nPCM bitstream: " << bits << "\n";
    cout << "Reconstructed samples:\n";

    for (double value : reconstructed)
    {
        cout << value << " ";
    }

    cout << "\n";

    cout << "Plotting reconstructed signal...\n";
    plotSignal(reconstructed, 1);
}


int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    while (true)
    {
        dashboard();

        int option;
        if (!(cin >> option))
            return 0;

        vector<double> sample;

        switch (option)
        {
            case 1:
                DigitalDataHandler();
                break;

            case 2:
            {
                sample = readAnalogSamples();

                if (sample.empty())
                {
                    cout << "No samples to encode.\n";
                    break;
                }

                last_pcm_min =
                    *min_element(sample.begin(), sample.end());
                last_pcm_max =
                    *max_element(sample.begin(), sample.end());

                last_pcm_bits = PCM_Modulation(sample);
                pcm_data_available = !last_pcm_bits.empty();

                cout << "\nPCM bits: "
                     << last_pcm_bits << "\n";

                cout << "PCM encoding completed.\n";

                cout << "\nDo you want to apply line encoding? (1 = Yes, 0 = No): ";
                int line_choice;
                cin >> line_choice;

                if (line_choice == 1)
                {
                    EncodingDashboard(last_pcm_bits);

                    if (!encodeSignal.empty())
                    {
                        plotSignal(
                            encodeSignal,
                            encodeSignal.size() /
                            last_pcm_bits.size());
                    }
                }

                cout << "\nYou can select option 3 to decode this PCM stream.\n";
                break;
            }

            case 3:
                PCMDemodulationDashboard();
                break;

            case 4:
                cout << "Exiting program.\n";
                return 0;

            default:
                cout << "Enter a valid input.\n";
        }
    }
return 0;
}