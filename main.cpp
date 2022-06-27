
#include <iostream>
#include<string>
#ifdef __GNUC__
#define __rdtsc __builtin_ia32_rdtsc
#else
#include<intrin.h>
#endif


typedef unsigned long long u64;
using namespace std;
u64
read_u64_hex(const char* data)
{
    u64 ret = 0;
    for (;; ++data)
    {				//read left-to-right 
        unsigned char dec = *data - '0';
        if (dec < 10)
            ret = ret << 4 | dec;
        else
        {
            unsigned char upper = (*data & 0xDF) - 'A';

            if (upper > 5)
                break;
            ret = ret << 4 | upper + 10;
        }
    }
    return ret;
}

u64 pc_1(u64 in)
{
    int pc1[56] = {
      57, 49, 41, 33, 25, 17, 9,
      1, 58, 50, 42, 34, 26, 18,
      10, 2, 59, 51, 43, 35, 27,
      19, 11, 3, 60, 52, 44, 36,
      63, 55, 47, 39, 31, 23, 15,
      7, 62, 54, 46, 38, 30, 22,
      14, 6, 61, 53, 45, 37, 29,
      21, 13, 5, 28, 20, 12, 4
    };
    u64 out = 0;
    for (int i = 0; i < 56; ++i)
    {
        out |= (in >> (64 - pc1[56 - 1 - i]) & 1) << i;
    }
    return out;
}
//
void devide(int max, u64 in, unsigned int* Right, unsigned int* Left)
{
    unsigned int top;
    top = in & 1;
    for (int i = 1; i < (max / 2); i++)
    {
        top |= ((in >> i) & 1) << i;
    }
    *Right = top;
    ///left
    top = ((in >> (max / 2)) & 1);
    for (int i = ((max / 2) + 1); i < max; i++)
    {
        top |= ((in >> i) & 1) << (i - (max / 2));
        //*Left |= ((in >> i) & 1) << (i - 28);
    }
    *Left = top;
}
/////////
void rotate_left(int bits, unsigned int* R, unsigned int* L)
{
    unsigned int temp;
    temp = *R;
    *R = (temp << bits) | (temp >> (28 - bits));
    *R = (*R & 0x0FFFFFFF);
    temp = *L;
    *L = (temp << bits) | (temp >> (28 - bits));
    *L = *L & 0x0FFFFFFF;
}
//
u64 pc_2(u64 in)
{
    int pc2[48] = {
      14, 17, 11, 24, 1, 5,
      3, 28, 15, 6, 21, 10,
      23, 19, 12, 4, 26, 8,
      16, 7, 27, 20, 13, 2,
      41, 52, 31, 37, 47, 55,
      30, 40, 51, 45, 33, 48,
      44, 49, 39, 56, 34, 53,
      46, 42, 50, 36, 29, 32
    };
    u64 out = 0;
    for (int i = 0; i < 48; ++i)
    {
        out |= (in >> (56 - pc2[48 - 1 - i]) & 1) << i;
    }
    return out;
}
//...........................
unsigned int s_box(u64 x)
{
    unsigned int result = 0;
    int box1[64] = { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
      0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
      4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
      15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13
    };

    int box2[64] = { 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
      3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
      0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
      13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9
    };

    int box3[64] = { 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
      13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
      13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
      1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12
    };
    int box4[64] = { 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
      13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
      10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
      3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14
    };
    int box5[64] = { 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
      14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
      4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
      11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3
    };
    int box6[64] = { 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
      10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
      9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
      4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13
    };
    int box7[64] = { 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
      13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
      1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
      6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12
    };
    int box8[64] = { 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
      1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
      7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
      2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11
    };

    unsigned int idx = 0;
    for (int i = 0; i < 8; i++)
    {
        if (i == 0)
        {
            idx = x >> (7 - i) * 6 & 0x3F;
            idx = ((idx >> 1) & 15) | ((idx & 1) << 4) | (idx & 0x20);
            result |= box1[idx] << ((7 - i) * 4);
        }
        if (i == 1)
        {
            idx = x >> (7 - i) * 6 & 0x3F;
            idx = ((idx >> 1) & 15) | ((idx & 1) << 4) | (idx & 0x20);
            result |= box2[idx] << ((7 - i) * 4);
        }
        if (i == 2)
        {
            idx = x >> (7 - i) * 6 & 0x3F;
            idx = ((idx >> 1) & 15) | ((idx & 1) << 4) | (idx & 0x20);
            result |= box3[idx] << (7 - i) * 4;
        }
        if (i == 3)
        {
            idx = x >> (7 - i) * 6 & 0x3F;
            idx = ((idx >> 1) & 15) | ((idx & 1) << 4) | (idx & 0x20);
            result |= box4[idx] << (7 - i) * 4;
        }
        if (i == 4)
        {
            idx = x >> (7 - i) * 6 & 0x3F;
            idx = ((idx >> 1) & 15) | ((idx & 1) << 4) | (idx & 0x20);
            result |= box5[idx] << (7 - i) * 4;
        }
        if (i == 5)
        {
            idx = x >> (7 - i) * 6 & 0x3F;
            idx = ((idx >> 1) & 15) | ((idx & 1) << 4) | (idx & 0x20);
            result |= box6[idx] << (7 - i) * 4;
        }
        if (i == 6)
        {
            idx = x >> (7 - i) * 6 & 0x3F;
            idx = ((idx >> 1) & 15) | ((idx & 1) << 4) | (idx & 0x20);
            result |= box7[idx] << (7 - i) * 4;
        }
        if (i == 7)
        {
            idx = x >> (7 - i) * 6 & 0x3F;
            idx = ((idx >> 1) & 15) | ((idx & 1) << 4) | (idx & 0x20);
            result |= box8[idx] << (7 - i) * 4;
        }

    }
    return result;
}

//////////////////////////////
u64 initial_permutation(u64 in)
{
    int initial_permutation_table[64] = {
      58, 50, 42, 34, 26, 18, 10, 2,
      60, 52, 44, 36, 28, 20, 12, 4,
      62, 54, 46, 38, 30, 22, 14, 6,
      64, 56, 48, 40, 32, 24, 16, 8,
      57, 49, 41, 33, 25, 17, 9, 1,
      59, 51, 43, 35, 27, 19, 11, 3,
      61, 53, 45, 37, 29, 21, 13, 5,
      63, 55, 47, 39, 31, 23, 15, 7
    };
    u64 out = 0;
    for (int i = 0; i < 64; ++i)
    {
        out |= (in >> (64 - initial_permutation_table[64 - 1 - i]) & 1) << i;
    }
    return out;
}

u64 inverse_permutation(u64 in)
{
    int inverse_ip[64] = { 40, 8, 48, 16, 56, 24, 64, 32,
      39, 7, 47, 15, 55, 23, 63, 31,
      38, 6, 46, 14, 54, 22, 62, 30,
      37, 5, 45, 13, 53, 21, 61, 29,
      36, 4, 44, 12, 52, 20, 60, 28,
      35, 3, 43, 11, 51, 19, 59, 27,
      34, 2, 42, 10, 50, 18, 58, 26,
      33, 1, 41, 9, 49, 17, 57, 25
    };

    // Final Permu
    u64 out = 0;
    for (int i = 0; i < 64; ++i)
    {
        out |= (in >> (64 - inverse_ip[64 - 1 - i]) & 1) << i;
    }
    return out;
}

////////////////////////////////////////
u64 expansion_pemutation(u64 in)
{
    int expansion_table[48] = {
      32, 1, 2, 3, 4, 5, 4, 5,
      6, 7, 8, 9, 8, 9, 10, 11,
      12, 13, 12, 13, 14, 15, 16, 17,
      16, 17, 18, 19, 20, 21, 20, 21,
      22, 23, 24, 25, 24, 25, 26, 27,
      28, 29, 28, 29, 30, 31, 32, 1
    };
    u64 out = 0;
    for (int i = 0; i < 48; ++i)
    {
        out |= (in >> (32 - expansion_table[48 - 1 - i]) & 1) << i;
    }
    out = out & 0x0000FFFFFFFFFFFF;
    return out;
}

///////////////////
unsigned int permutation(unsigned int in)
{
    int permutation_table[32] = {
      16, 7, 20, 21, 29, 12, 28, 17,
      1, 15, 23, 26, 5, 18, 31, 10,
      2, 8, 24, 14, 32, 27, 3, 9,
      19, 13, 30, 6, 22, 11, 4, 25
    };
    unsigned int out = 0;
    for (int i = 0; i < 32; ++i)
    {
        out |= (in >> (32 - permutation_table[32 - 1 - i]) & 1) << i;
    }
    return out;
}

string To_Hex(unsigned long long num)
{
    unsigned int split = 0;
    char hex_string[8];
    string str = "";

    for (int i = 32; i < 64; i++)
    {
        split |= ((num >> i) & 1) << i - 32;
    }
    sprintf(hex_string, "%X", split);
    for (int i = 0; i < 8; i++)
    {
        str += hex_string[i];
        //str= hex_string;

    }
    split = num & 1;
    for (int i = 0; i < 32; i++)
    {
        split |= ((num >> i) & 1) << i;
    }
    sprintf(hex_string, "%X", split);
    for (int i = 0; i < 8; i++)
    {
        str += hex_string[i];
    }
    return str;
}


int main(int argc, char* argv[])
{
    
    string a=argv[2]; 
    const char* charac = a.c_str();
   // u64 input = read_u64_hex(argv[2]);
    u64 input = read_u64_hex(charac);
    a = "";
    a = argv[3];
    const char* charac1 = a.c_str();
    u64 Key = read_u64_hex(charac1);
    string operation = (argv[1]);
    //////////////////////////////////////
    u64 ki[16];
    u64 k;
    unsigned int right, left;
    Key = pc_1(Key);
    //split the key
    devide(56, Key, &right, &left);
    //key for each round
    for (int roundi = 0; roundi < 16; roundi++)
    {

        int bits_rotated;
        if (roundi == 0 || roundi == 1 || roundi == 15 || roundi == 8)
            bits_rotated = 1;
        else
            bits_rotated = 2;

        rotate_left(bits_rotated, &right, &left);

        k = (u64(left) << 28) | u64(right);
        k = pc_2(k);

        ki[roundi] = k;
    }
    //

    u64 cipher = 0;
    u64 plain = 0;
    string output = "";
 // 
    long long t1 = __rdtsc();;
    if (operation == "encrypt")
    {				//ENCRYPT // input in the scope
        input = initial_permutation(input);
        unsigned int p_right, p_left, temp1, temp2;
        devide(64, input, &p_right, &p_left);
        //rounds
        for (int i = 0; i < 16; i++)
        {
            temp1 = p_right;
            temp2 = p_left;
            p_left = temp1;
            p_right =
                temp2 ^
                (permutation
                (s_box(expansion_pemutation(u64(temp1)) ^ ki[i])));

        }
        //swap
        temp1 = p_right;
        //temp2 = p_left;
        p_right = p_left;
        p_left = temp1;
        //
        cipher = (u64(p_left) << 32) | u64(p_right);
        cipher = inverse_permutation(cipher);
        long long t2 = __rdtsc();
        output = To_Hex(cipher);
        cout << "cipher: ";
            cout << output;
        cout << endl;		//
        cout << "cycles: ";
            cout << (t2 - t1);
        cout << endl;

    }
    long long t3 = __rdtsc();	//temp1 = 0;
    //temp2 = 0;
    if (operation == "decrypt")
    {				// DECRYPT
        unsigned int temp11, temp22, c_right, c_left;
        //split
        plain = input;		//cipher
        plain = initial_permutation(plain);
        devide(64, plain, &c_right, &c_left);
        //swap
        temp11 = c_right;
        temp22 = c_left;
        c_right = temp22;
        c_left = temp11;
        //rounds
        for (int i = 15; i >= 0; i--)
        {
            temp11 = c_right;
            temp22 = c_left;
            c_right = temp22;
            c_left =
                temp11 ^
                (permutation
                (s_box(expansion_pemutation(u64(temp22)) ^ ki[i])));
            temp11 = 0;
            temp22 = 0;
        }
        plain = 0;
        plain = (u64(c_left) << 32) | u64(c_right);
        plain = inverse_permutation(plain);
        long long t4 = __rdtsc();
        output = To_Hex(plain);
        cout << "plain: ";
            cout << output;
        cout << endl;
        cout << "cycles: ";
            cout << (t4 - t3);
        cout << endl;
    }
    // DECRYPT
 if (operation == "decrypt")
    {				
        unsigned int temp11, temp22, c_right, c_left;
        //split
        plain = input;		//cipher
        plain = initial_permutation(plain);
        devide(64, plain, &c_right, &c_left);
        //swap
        temp11 = c_right;
        temp22 = c_left;
        c_right = temp22;
        c_left = temp11;
        //rounds
        for (int i = 15; i >= 0; i--)
        {
            temp11 = c_right;
            temp22 = c_left;
            c_right = temp22;
            c_left =
                temp11 ^
                (permutation
                (s_box(expansion_pemutation(u64(temp22)) ^ ki[i])));
            temp11 = 0;
            temp22 = 0;
        }
        plain = 0;
        plain = (u64(c_left) << 32) | u64(c_right);
        plain = inverse_permutation(plain);
        long long t4 = __rdtsc();
        output = To_Hex(plain);
        cout << "plain: ";
            cout << output;
        cout << endl;
        cout << "cycles: ";
            cout << (t4 - t3);
        cout << endl;
    }
    //string h;

    return 0;
}

