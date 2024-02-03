#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

void PrintBadKeyMessage()
{
      std::cout << "Public key is not valid!";
}

char DecryptValue(int encryptedValue);

bool IsPrime_PrimalityTest(int sus)
{
      if (sus == 0 || sus == 1)
            return false;

      int roof{std::sqrt(sus)};

      for (int i{2}; i <= roof; ++i)
      {
            if (sus % i == 0)
                  return false; //bad because value is divisible by something other than themselves
      }

      return true;
}

void SetPrimeFactors(int nVAL, int& pVAL, int& qVAL)
{
      for (int i{2}; i <= nVAL / 2; ++i)
      {
            // left to right, short circuit on condition 1
            if ((nVAL % i == 0) && IsPrime_PrimalityTest(i))
            {
                  pVAL = i;
                  qVAL = nVAL / i; // solve for q by n = p * q => q = n / p

                  return;
            }
      }

      return;
}

// brute force divsion i until modulo of totient gives 1
int ComputeInverseModulo(int eVAL, int totient)
{
      for (int i{1}; i < totient; ++i)
      {
            if ((eVAL % totient) * (i % totient) % totient == 1)
                  return i;
      }
}

// exponentiation
int DecryptInteger(int encrypted, int dVAL, int nVAL)
{
    int decryptedInteger = 1;

    while(dVAL) // use call stack vars
      {
            if (dVAL & 1) // check if last bit is 1 : or odd
                  decryptedInteger = (decryptedInteger * encrypted) % nVAL;

            dVAL /= 2; // halve exponent

            encrypted = (encrypted*encrypted) % nVAL;
      }

      return decryptedInteger;
}

int main()
{
      // [0] is program name, add 1 to total argc

      // integer-character mapping
      std::unordered_map<int, char> integerToCharacterEncoding {
            {7, 'A'}, {8, 'B'}, {9, 'C'},
            {10, 'D'}, {11, 'E'}, {12, 'F'},
            {13, 'G'}, {14, 'H'}, {15, 'I'},
            {16, 'J'}, {17, 'K'}, {18, 'L'},
            {19, 'M'}, {20, 'N'}, {21, 'O'},
            {22, 'P'}, {23, 'Q'}, {24, 'R'},
            {25, 'S'}, {26, 'T'}, {27, 'U'},
            {28, 'V'}, {29, 'W'}, {30, 'X'},
            {31, 'Y'}, {32, 'Z'}, {33, ' '},
            {34, '\"'}, {35, ','}, {36, '.'},
            {37, '\''}
      };


      // 'P'ublic Key, P = (e, n)
      int eVALUE{};
      int nVALUE{};
      int mVALUE{};
      std::cin >> eVALUE >> nVALUE >> mVALUE;

      // input encrypted integers
      int encryptedValue{};
      std::vector<int> encryptedVector;
      for (int i{0}; i < mVALUE; ++i)
      {
            std::cin >> encryptedValue;
            encryptedVector.push_back(encryptedValue);
      }

      // checksum
      // std::cout << "LAST VALUE: " << encryptedVector[mVALUE - 1] << "\n";
      // std::cout << (encryptedVector.size() == static_cast<std::vector<int>::size_type>(mVALUE) ? "GOOD MATCH\n" : "BAD MATCH\n");
      // std::cout << "\tmVALUE: " << mVALUE << "\n";
      // std::cout << "\tENC_VEC_SIZE: " << encryptedVector.size() << "\n";

      /*
            get p,q
      */
      int pVALUE{};
      int qVALUE{};
      SetPrimeFactors(nVALUE, pVALUE, qVALUE);

      if (!(IsPrime_PrimalityTest(qVALUE))) // is it guaranteed for q to be prime? doing this just in case
      {
            PrintBadKeyMessage();
            // std::cout << "p is prime, but NOT q\n";
            return 0;
      }

      if (pVALUE == qVALUE)
      {
            PrintBadKeyMessage();
            // std::cout << "p is q\n";
            return 0;
      }

      /*
            get phi(n), Euler's Totient
      */
      int eulerTotient{(pVALUE - 1) * (qVALUE - 1)};

      // make sure eVALUE and phi(n) is relatively prime
      int gcd_e_totient{std::__gcd(eVALUE, eulerTotient)};
      if (!(gcd_e_totient == 1))
      {
            PrintBadKeyMessage();
            return 0;
      }

      // std::cout << "gcd(" << eVALUE << ", " << eulerTotient << ") = " << gcd_e_totient << "\n";

      /*
            get d = e^(-1) mod phi(n)
      */
      int dVALUE{ComputeInverseModulo(eVALUE, eulerTotient)};

      std::cout << pVALUE << " " << qVALUE << " " << eulerTotient << " " << dVALUE << "\n";

      // use these integers to map to integerToCharacterEncoding
      std::vector<int> decryptedVector{};
      std::vector<char> mappedDecryption{};

      for (int i{0}; i < encryptedVector.size(); ++i)
            decryptedVector.push_back(DecryptInteger(encryptedVector[i], dVALUE, nVALUE));

      for (int iter: decryptedVector)
            std::cout << iter << " ";

      std::cout << "\n";

      for (int iter: decryptedVector)
            std::cout << integerToCharacterEncoding[iter];

      return 0;
}