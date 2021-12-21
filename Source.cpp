#include <iostream>
using namespace std;


unsigned char gmul(unsigned char a, unsigned char b) {
    unsigned char p = 0;
    unsigned char counter;
    for (counter = 0; counter < 8; counter++) {
        unsigned char hi_bit_set;
        if ((b & 1) == 1)
            p ^= a;
        hi_bit_set = (a & 0x80);
        a <<= 1;
        if (hi_bit_set == 0x80)
            a ^= 0x1b;
        b >>= 1;
    }
    return p;
}

void inv_mix_column(unsigned char* r) {
    unsigned char a[4];
    unsigned char c;
    for (c = 0; c < 4; c++) {
        a[c] = r[c];
    }
    r[0] = gmul(a[0], 2) ^ gmul(a[3], 1) ^ gmul(a[2], 1) ^ gmul(a[1], 3);
    r[1] = gmul(a[1], 2) ^ gmul(a[0], 1) ^ gmul(a[3], 1) ^ gmul(a[2], 3);
    r[2] = gmul(a[2], 2) ^ gmul(a[1], 1) ^ gmul(a[0], 1) ^ gmul(a[3], 3);
    r[3] = gmul(a[3], 2) ^ gmul(a[2], 1) ^ gmul(a[1], 1) ^ gmul(a[0], 3);
}





int convert(char num[]) {
    int len = strlen(num);
    int base = 1;
    int temp = 0;
    for (int i = len - 1; i >= 0; i--) {
        if (num[i] >= '0' && num[i] <= '9') {
            temp += (num[i] - 48) * base;
            base = base * 16;
        }
        else if (num[i] >= 'A' && num[i] <= 'F') {
            temp += (num[i] - 55) * base;
            base = base * 16;
        }
    }
    return temp;
}



int main() {
    char temp[2];
    unsigned char r[4] = { 18, 133, 213, 30 };

    cout << "WARINING ALL LETTER SHOULD BE CAPITAL";

    for (int i = 0; i < 4; i++)
    {
        cout << "enter a["<<i<<"]=";
        cin >> temp;
        cout << convert(temp)<<endl;
        r[i]=convert(temp);
    }
    inv_mix_column(r);
    cout << "OUTPUT " << endl;
    std::cout << std::hex << (int)r[0] << std::endl;
    std::cout << std::hex << (int)r[1] << std::endl;
    std::cout << std::hex << (int)r[2] << std::endl;
    std::cout << std::hex << (int)r[3] << std::endl;

    return 0;
}
