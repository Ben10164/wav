// sites used
// https://www.dreamincode.net/forums/topic/279619-viewing-hex-bytes-of-a-wav-file/
// https://stackoverflow.com/questions/14733761/printf-formatting-for-hexadecimal
// https://www.geeksforgeeks.org/convert-character-array-to-string-in-c/
// https://stackoverflow.com/questions/10723403/char-array-to-hex-string-c
// https://stackoverflow.com/questions/7639656/getting-a-buffer-into-a-stringstream-in-hex-representation/7639754#7639754

#include "functions.cpp"

int main(int argc, char *argv[])
{
   string RIFFCheck, RIFFType, fmtCheck, typeOfWAV = "", fileName = "bt.wav";
   uint totalLen, fmtChunkLen, audioFormat, audioChannels, frameRate, avgBytesPerSecond, frameSize, bitsPerSample;
   ifstream is;

   if (argc > 1) // check and see if there was a custom file name
   {
      fileName = argv[1];
   }

   is.open(fileName); // open file

   if (!is.is_open())
   {
      cout << "The file named " << fileName << " has not been opened correctly" << endl;
      return 0;
   }

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