#include "LineEncoding.h"
using namespace std;

vector<int> encodeSignal;
void NRZ_L(string bitstream)
{
    for (char bit : bitstream)
        encodeSignal.push_back(bit == '0' ? 1 : -1);
}

void NRZ_I(string bitstream)
{
    int level = -1;
    for (char bit : bitstream)
    {
        if (bit == '1')
        {
            level = -level;
        }
        encodeSignal.push_back(level);
    }
}

void Manchester(const string& bits) {

    for (char bit : bits) {
       
        if (bit == '0') {
            encodeSignal.push_back(1);
            encodeSignal.push_back(-1);
        } else {
            encodeSignal.push_back(-1);
            encodeSignal.push_back(1);
        }
    }
}

void DiffManchester(const string& bits) {

    int level = 1;  // Initial level before the first bit

    for (char bit : bits) {
       
        // 0 causes a transition at the beginning of the bit
        if (bit == '0') {
            level = -level;
        }

        encodeSignal.push_back(level);

        // Mandatory transition in the middle of every bit
        level = -level;
        encodeSignal.push_back(level);
    }
}

void AMI_Dashboard(string bitstream) {
    int choice;

    cout << "\n============================================\n";
    cout << "              AMI ENCODING\n";
    cout << "============================================\n";
    cout << "1. Standard AMI (No Scrambling)\n";
    cout << "2. B8ZS Scrambling\n";
    cout << "3. HDB3 Scrambling\n";
    cout << "============================================\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            AMI(bitstream);
            break;

        case 2:
            B8ZS(bitstream);
            break;

        case 3:
            HDB3(bitstream);
            break;

        case 4:
            return;

        default:
            cout << "Invalid choice!\n";
            return;
    }
}

void AMI(const string& bits) {
    
    int lastPulse = -1;

    for (char bit : bits) {
        if (bit == '0') {
            encodeSignal.push_back(0);
        } else {
            lastPulse = -lastPulse;
            encodeSignal.push_back(lastPulse);
        }
    }
}

// Bipolar with 8-Zero Substitution
void B8ZS(const string& bits) {
    
    int lastPulse = -1;
    size_t i = 0;

    while (i < bits.size()) {
        // Detect eight consecutive zeros
        if (bits[i] == '0' && i + 8 <= bits.size()
            && bits.substr(i, 8) == "00000000") {

            int p = lastPulse;

            // 000 V B 0 V B
            // V has the same polarity as the preceding pulse.
            // B has the opposite polarity.
            int pattern[] = {
                0, 0, 0, p, -p, 0, -p, p
            };

            for (int level : pattern) {
                encodeSignal.push_back(level);
            }

            // The final pulse has polarity p.
            lastPulse = p;
            i += 8;
        } else {
            if (bits[i] == '0') {
                encodeSignal.push_back(0);
            } else {
                lastPulse = -lastPulse;
                encodeSignal.push_back(lastPulse);
            }

            ++i;
        }
    }
}

void HDB3(const string& bits) {
    int lastPulse = -1;
    int pulseCount = 0;
    size_t i = 0;

    while (i < bits.size()) {
        if (i + 4 <= bits.size() &&
            bits.substr(i, 4) == "0000") {

            if (pulseCount % 2 == 1) {
                // Odd number of pulses: 000V
                encodeSignal.insert(encodeSignal.end(), {0, 0, 0, lastPulse});
            } else {
                // Even number of pulses: B00V
                int B = -lastPulse;
                encodeSignal.insert(encodeSignal.end(), {B, 0, 0, B});
                lastPulse = B;
            }

            lastPulse = encodeSignal.back();
            pulseCount = 0;
            i += 4;
        } else {
            if (bits[i] == '0') {
                encodeSignal.push_back(0);
            } else {
                lastPulse = -lastPulse;
                encodeSignal.push_back(lastPulse);
                pulseCount++;
            }
            i++;
        }
    }
}

void EncodingDashboard(string bitstream)
{
    cout << "\n";
    cout << "============================================\n";
    cout << "           LINE ENCODING TECHNIQUES\n";
    cout << "============================================\n";
    cout << "1.  NRZ-L\n";
    cout << "2.  NRZ-I\n";
    cout << "3.  Manchester\n";
    cout << "4.  Differential Manchester\n";
    cout << "5.  AMI\n";
    cout << "============================================\n";
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
        NRZ_L(bitstream);
        break;
    case 2:
        NRZ_I(bitstream);
        break;
    case 3:
        Manchester(bitstream);
        break;
    case 4:
        DiffManchester(bitstream);
        break;
    case 5:
        AMI_Dashboard(bitstream);
        break;
    default:
        break;
    }
}
