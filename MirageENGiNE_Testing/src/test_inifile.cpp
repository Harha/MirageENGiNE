/*
* Mirage Game Engine Unit Tests
* Tests for IniFile class
* Author: Harha
* (c) 2016-
*/

// gtest includes
#include <gtest/gtest.h>

// mirage includes
#include "util/inifile.h"
#include "util/strutil.h"

using namespace mirage;

extern IniFile inifile("res/testconfig.ini");

TEST(test_ini, load)
{
	EXPECT_TRUE(inifile.getPath().empty() == false);
	EXPECT_TRUE(inifile.getLines().size() > 0);
}

TEST(test_ini, parse)
{
	EXPECT_TRUE(inifile.getEntries().size() > 0);
}

TEST(test_ini, findvalue_string)
{
	EXPECT_FALSE(strcompcasei(inifile.getString("[test]", "name", "test"), "test"));
	EXPECT_TRUE(strcompcasei(inifile.getString("[test]", "name", "test"), "mirage game engine"));
}

TEST(test_ini, findvalue_bool)
{
	EXPECT_TRUE(inifile.getBool("[test]", "boolval", false));
	EXPECT_FALSE(inifile.getBool("[test]", "boolvalnotexist", false));
}

TEST(test_ini, findvalue_int)
{
	EXPECT_EQ(inifile.getInt("[test]", "intval", 0), 128);
	EXPECT_EQ(inifile.getInt("[test]", "intvalnotexist", 0), 0);
}

TEST(test_ini, findvalue_float)
{
	EXPECT_NEAR(inifile.getFloat("[test]", "floatval", 0.0f), 128.128f, 0.00001f);
	EXPECT_NEAR(inifile.getFloat("[test]", "floatvalnotexist", 0.0f), 0.0f, 0.00001f);
}

TEST(test_ini, findvalue_double)
{
	EXPECT_NEAR(inifile.getFloat("[test]", "doubleval", 0.0), 256.256, 0.001);
	EXPECT_NEAR(inifile.getFloat("[test]", "doublevalnotexist", 0.0), 0.0, 0.001);
}