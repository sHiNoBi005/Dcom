#include<iostream>
#include<vector>
#include<random>
#include<string>
#include<ctime>
#include<cstdlib>

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



void DigitalDataHandler(){
    int n;
    cout << "Enter length of bit stream" << endl;
    cin >> n;
    cout << "1. Fully Random \n";
    cout << "2. Include 4 consecutive zeros\n";
    cout << "3. Include 8 consecutive zeros\n";
    int choice;
    cin >> choice;
    switch(choice){
        case 1: cout<< RandomBits(n) << endl;
        break;
        case 2: cout << randomBitsWithZero(n,4) <<endl;
        break;
        case 3: cout << randomBitsWithZero(n,8) <<endl;
        break;
        default: cout << "Enter a valid choice\n";
    }
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
        switch(option){
            case 1: DigitalDataHandler();
            break;
            case 2: cout << 2 << endl;
            break;
            case 3: return 0;
            break;
            default: cout << "Enter a valid input";
        }
    }
return 0;
}