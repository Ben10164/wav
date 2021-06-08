#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
   int length = 100;

   ifstream infile1;
   ifstream infile2;
   infile1.open("bt.wav", ios::in | ios::binary);
   infile2.open("bt.wav", ios::in | ios::binary);
   char bytes[length];
   for (int i = 0; i < length; ++i)
   {
      infile1.read(&bytes[i], 1);
      printf("%02X ", bytes[i]); // This is the hex, for some reason there are random F F F F F_ _
   }
   cout << endl
        << endl
        << endl;

   for (int i = 0; i < length; ++i)
   {
      infile2.read(&bytes[i], 1);
      cout << bytes[i] << " "; // Changed into readable char
   }
   cout << endl;
}
