#include <iostream>
#include <string>
#include <array>

using namespace std;
using BYTE = unsigned char;
using SIZE = size_t;

class RC4
{
public:
    RC4(const string& key)
    {
        for (SIZE i = 0; i < 256; ++i)
            S[i] = (BYTE)i;

        BYTE j(0);
        for (SIZE i = 0; i < 256; ++i)
        {
            j = (j + S[i] + key[i % key.size()]) % 256;
            swap(S[i], S[j]);
        }
    }

    string encode(const string& plain)
    {
        string cipher;

        for (SIZE m = 0; m < plain.size(); m++)
            cipher.push_back((BYTE)(plain[m] ^ keyItem()));

        return cipher;
    }

    string decode(const string& crypted)
    {
        return encode(crypted);
    }

    ~RC4()
    {
        S.fill(0);
        x = 0; y = 0;
    }

private:
    BYTE keyItem()
    {
        x = (x + 1) % 256;
        y = (y + S[x]) % 256;

        swap(S[x], S[y]);

        return S[(S[x] + S[y]) % 256];
    }

private:
    array<BYTE, 256> S;
    SIZE x = 0, y = 0;
};

int main()
{
    string key("password");

    RC4 rc4en(key);
    RC4 rc4de(key);
    auto crypted = rc4en.encode("Hello, World!\n");
    cout << "Encode:\n" << crypted << "\n"
    << "Decode:\n" << rc4de.decode(crypted) << endl;
}
