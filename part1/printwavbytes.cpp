// https://www.dreamincode.net/forums/topic/279619-viewing-hex-bytes-of-a-wav-file/
// https://stackoverflow.com/questions/14733761/printf-formatting-for-hexadecimal
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[])
{
   ifstream is;
   is.open("bt.wav"); // openb file

   unsigned char chunk[16];
   while (is.read(reinterpret_cast<char *>(chunk), 16)) // read the file, but it needs to be reiunterpreted as char*
   {
      // print out the bytes
      for (int i = 0; i < 16; i++)
      {
         printf("%02x", (int)chunk[i]);
         cout << " ";
      }
      cout << endl;
   }
}
