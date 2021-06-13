// sites used
// https://www.dreamincode.net/forums/topic/279619-viewing-hex-bytes-of-a-wav-file/
// https://stackoverflow.com/questions/14733761/printf-formatting-for-hexadecimal
// https://www.geeksforgeeks.org/convert-character-array-to-string-in-c/
// https://stackoverflow.com/questions/10723403/char-array-to-hex-string-c
// https://stackoverflow.com/questions/7639656/getting-a-buffer-into-a-stringstream-in-hex-representation/7639754#7639754

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

// Actual strings or words
void displayNextBytesStr(ifstream &is, int amount);
string getNextBytesString(ifstream &is, int amount);

// Hex to string
void displayNextBytesHex(ifstream &is, int amount);
string getNextBytesHexString(ifstream &is, int amount);
string convertToString(unsigned char *chunk, int amount);

// string to int
unsigned int convertStringHexToInt(string hex, int amount);
unsigned int getNextBytesHexInt(ifstream &is, int amount);

int main(int argc, char *argv[])
{
   ifstream is;
   is.open("bt.wav"); // openb file

   cout << "RIFF check: " << getNextBytesString(is, 4) << endl;
   cout << "Length of data: " << getNextBytesHexInt(is, 4) << endl;
   cout << "RIFF type: " << getNextBytesString(is, 4) << endl;
   cout << "fmt check: " << getNextBytesString(is, 4) << endl;
}

void displayNextBytesStr(ifstream &is, int amount)
{
   string chunk = getNextBytesString(is, amount);
   cout << chunk << endl;
}

string getNextBytesString(ifstream &is, int amount)
{
   unsigned char chunk[amount + 1];
   chunk[amount] = '\0';
   is.read(reinterpret_cast<char *>(chunk), amount);
   string returnVal;
   returnVal = (string) reinterpret_cast<char *>(chunk);
   return returnVal;
}

void displayNextBytesHex(ifstream &is, int amount)
{
   string hexVal = getNextBytesHexString(is, amount);
   cout << hexVal << endl; // outputs
}

string getNextBytesHexString(ifstream &is, int amount)
{
   unsigned char chunk[amount];                      // unsigned so there are no negative hex values, this caused me alot of trouble
   is.read(reinterpret_cast<char *>(chunk), amount); // read the file, but it needs to be reiunterpreted as char*

   string hexVal = convertToString(chunk, amount); // converts the char array of the hex literal values to a readable string of hex characters
   return hexVal;
}

string convertToString(unsigned char *chunk, int amount)
{
   stringstream ss;           // new stringstream
   ss << hex << setfill('0'); // this sets the string string to default have all 0s
   for (int i = 0; i < amount; ++i)
   {
      ss << setw(2) << static_cast<unsigned>(chunk[i]); // setw(2) makes it so instead of 000000F9 we get F9
   }
   string hexVal = ss.str();
   return hexVal;
}

unsigned int convertStringHexToInt(string hexString, int amount)
{
   unsigned int temp = stol("ffffffff", 0, 16);
   return temp;
}

unsigned int getNextBytesHexInt(ifstream &is, int amount)
{
   unsigned int temp = convertStringHexToInt(getNextBytesHexString(is, amount), amount * 2);
   return temp;
}