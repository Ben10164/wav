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

void displayNextBytesStr(ifstream &is, int amount)
{
   string chunk = getNextBytesString(is, amount); // obtains the next amount of bytes as a string
   cout << chunk << endl;                         // output
}

string getNextBytesString(ifstream &is, int amount)
{
   unsigned char chunk[amount + 1];                      // char[]
   chunk[amount] = '\0';                                 // sets the null character as the final position of the char[]
   is.read(reinterpret_cast<char *>(chunk), amount);     // read the file into the reinterpreted cstring 'chunk'
   string returnVal;                                     // initializes the returnVal
   returnVal = (string) reinterpret_cast<char *>(chunk); // returnVal is changed to be a string cast of a char* reinterpreted cstring
   return returnVal;                                     // return
}

void displayNextBytesHex(ifstream &is, int amount)
{
   string hexVal = getNextBytesHexString(is, amount); // obtains the next amount of bytes as a string of hex data
   cout << hexVal << endl;                            // outputs
}

string getNextBytesHexString(ifstream &is, int amount)
{
   unsigned char chunk[amount];                      // unsigned so there are no negative hex values, this caused me alot of trouble
   is.read(reinterpret_cast<char *>(chunk), amount); // read the file, but it needs to be reiunterpreted as char*
   string hexVal = convertToString(chunk, amount);   // converts the char array of the hex literal values to a readable string of hex characters
   return hexVal;                                    // return
}

string convertToString(unsigned char *chunk, int amount)
{
   stringstream ss;                                     // new stringstream
   ss << hex << setfill('0');                           // this sets the string string to default have all 0s
   for (int i = amount - 1; i >= 0; --i)                // start for loop going up to the amount
      ss << setw(2) << static_cast<unsigned>(chunk[i]); // setw(2) makes it so instead of 000000F9 we get F9
   string hexVal = ss.str();                            // use the built in cast from stringstream to string
   return hexVal;                                       // return
}

unsigned int convertStringHexToInt(string hexString, int amount)
{
   unsigned int temp = stol(hexString, 0, 16); // convert hexString to a unsigned int
   return temp;                                // return
}

unsigned int getNextBytesHexInt(ifstream &is, int amount)
{
   unsigned int temp = convertStringHexToInt(getNextBytesHexString(is, amount), amount * 2); // conversion
   return temp;                                                                              // return
}