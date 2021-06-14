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
   string RIFFCheck, RIFFType, fmtCheck, typeOfWAV = "";
   uint totalLen, fmtChunkLen, audioFormat, audioChannels, frameRate, avgBytesPerSecond, frameSize, bitsPerSample;
   ifstream is;
   is.open("bt.wav"); // open file

   RIFFCheck = getNextBytesString(is, 4);
   cout << "RIFF check: " << RIFFCheck << endl;

   totalLen = getNextBytesHexInt(is, 4);
   unsigned short _byteswap_ushort(totalLen);
   cout << "Length of all data: " << totalLen << endl;

   RIFFType = getNextBytesString(is, 4);
   cout << "RIFF type: " << RIFFType << endl;

   fmtCheck = getNextBytesString(is, 4);
   cout << "fmt check: '" << fmtCheck << "'" << endl;

   fmtChunkLen = getNextBytesHexInt(is, 4);
   cout << "Length of format chunk: " << fmtChunkLen << endl;

   if (fmtChunkLen == 14)
      typeOfWAV = "WAVEFORMAT";
   else if (fmtChunkLen == 16)
      typeOfWAV = "PCMWAVEFORMAT";
   else if (fmtChunkLen == 18)
      typeOfWAV = "WAVEFORMATEX";
   else if (fmtChunkLen > 18 && fmtChunkLen % 2 == 0)
      typeOfWAV = "WAVEFORMATEXTENSIBLE";
   cout << "Type of wave format: " << typeOfWAV << endl;

   audioFormat = getNextBytesHexInt(is, 2);
   cout << "Format of the audio: " << audioFormat << endl;
   // TRASH = getNextBytesString(is, 1); // before when i was using big endian

   audioChannels = getNextBytesHexInt(is, 2);
   cout << "Number of audio channels: " << audioChannels << endl;

   frameRate = getNextBytesHexInt(is, 4);
   cout << "Frame Rate: " << frameRate << endl;

   avgBytesPerSecond = getNextBytesHexInt(is, 4);
   cout << "Average bytes per second: " << avgBytesPerSecond << endl;

   frameSize = getNextBytesHexInt(is, 2);
   cout << "Frame size: " << frameSize << endl;

   bitsPerSample = getNextBytesHexInt(is, 2);
   cout << "Bits per sample: " << bitsPerSample << endl;
}

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