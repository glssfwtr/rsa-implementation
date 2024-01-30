#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

char DecryptValue(int encryptedValue);

int main(int argc, char *argv[])
{
      // since [0] is program name, add 1 to total argc
      if (!(argc == 4))
      {
            std::cout << "BAD ARGS\n";
            return 1;
      }

      // 'P'ublic Key, P = (e, n)
      int eVALUE{std::stoi(argv[1])};
      int nVALUE{std::stoi(argv[2])};
      int mVALUE{std::stoi(argv[3])};

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
      for (int i{1}; i < argc; ++i)
      {
            std::cout << argv[i] << " ";
      }
      std::cout << "\n";

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




      /*
            START DOING STUFF HERE
      */

      // use these integers to map to integerToCharacterEncoding
      std::vector<int> decryptedVector{};

      std::cout << "===END===\n";
      return 0;
}