#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

void PrintBadKeyMessage()
{
      std::cout << "Public key is not valid!\n";
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

int main()
{
      // since [0] is program name, add 1 to total argc


      // 'P'ublic Key, P = (e, n)
      int eVALUE{};
      int nVALUE{};
      int mVALUE{};
      std::cin >> eVALUE >> nVALUE >> mVALUE;

      // integer-character mapping
      std::unordered_map<int, char> integerToCharacterEncoding {
            {8, 'A'}, {9, 'B'}, {10, 'C'},
            {11, 'D'}, {12, 'E'}, {13, 'F'},
            {14, 'G'}, {15, 'H'}, {16, 'I'},
            {17, 'J'}, {18, 'K'}, {19, 'L'},
            {20, 'M'}, {21, 'N'}, {22, 'O'},
            {23, 'P'}, {24, 'Q'}, {25, 'R'},
            {26, 'S'}, {27, 'T'}, {28, 'U'},
            {29, 'V'}, {30, 'W'}, {31, 'X'},
            {32, 'Y'}, {33, 'Z'}, {34, ' '},
            {35, '\"'}, {36, ','}, {37, '.'},
            {38, '\''}
      };

      std::cout << "MAPPING:\n";
      for (int i{8}; i < 39; ++i)
      {
            std::cout << integerToCharacterEncoding[i] << " ";
      }

      std::cout << "e, n, m:\n";
      std::cout << eVALUE << " " << nVALUE << " " << mVALUE << "\n";

      // input encrypted integers
      int encryptedValue{};
      std::vector<int> encryptedVector;
      for (int i{0}; i < mVALUE; ++i)
      {
            std::cin >> encryptedValue;
            encryptedVector.push_back(encryptedValue);
      }

      // checksum
      std::cout << "LAST VALUE: " << encryptedVector[mVALUE - 1] << "\n";
      std::cout << (encryptedVector.size() == static_cast<std::vector<int>::size_type>(mVALUE) ? "GOOD MATCH\n" : "BAD MATCH\n");
      std::cout << "\tmVALUE: " << mVALUE << "\n";
      std::cout << "\tENC_VEC_SIZE: " << encryptedVector.size() << "\n";

      std::cout << "===OUTPUT===\n";




      // use these integers to map to integerToCharacterEncoding
      std::vector<int> decryptedVector{};

      /*
            get p,q
      */
      int pVALUE{};
      int qVALUE{};
      SetPrimeFactors(nVALUE, pVALUE, qVALUE);

      if (!(IsPrime_PrimalityTest(qVALUE))) // is it guaranteed for q to be prime? doing this just in case
      {
            PrintBadKeyMessage();
            std::cout << "p is prime, but NOT q\n";
            return 0;
      }

      std::cout << "p: " << pVALUE << "\nq: " << qVALUE << "\n";

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

      std::cout << "gcd(" << eVALUE << ", " << eulerTotient << ") = " << gcd_e_totient << "\n";
      std::cout << "Totient: " << eulerTotient << "\n";




      return 0;
}