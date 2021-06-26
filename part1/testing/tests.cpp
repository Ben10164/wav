#include "../functions.cpp"
#include <gtest/gtest.h>

static void SetUpTests(ifstream &is, int amount)
{
   is.open("../bt.wav");
   string trash;
   trash = getNextBytesHexString(is, amount);
}

static void TearDownTests(ifstream &is)
{
   is.close();
}

TEST(StrChecks, RIFFCheck)
{
   ifstream is;
   SetUpTests(is, 0);
   EXPECT_EQ(getNextBytesString(is, 4), "RIFF");
   TearDownTests(is);
}

TEST(IntChecks, LengthOfAllData)
{
   ifstream is;
   SetUpTests(is, 4);
   uint test = getNextBytesHexInt(is, 4);
   unsigned short _byteswap_ushort(test);
   EXPECT_EQ(test, 129426);
   TearDownTests(is);
}

TEST(StrChecks, RIFFTypeCheck)
{
   ifstream is;
   SetUpTests(is, 8);
   EXPECT_EQ(getNextBytesString(is, 4), "WAVE");
   TearDownTests(is);
}

TEST(StrChecks, fmtCheck)
{
   ifstream is;
   SetUpTests(is, 12);
   EXPECT_EQ(getNextBytesString(is, 4), "fmt ");
   TearDownTests(is);
}

int main(int argc, char **argv)
{
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}