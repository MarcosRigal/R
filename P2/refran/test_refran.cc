#include <gtest/gtest.h>
#include "refran.h"

using namespace std;
//
//TEST(Refran, Constructor)
//{
//    Refran refran;
//
//    EXPECT_EQ(strcmp(refran.getRefran(), "Marzo lluvioso, mayo copioso."), 0);
//    EXPECT_EQ(strcmp(refran.getRefranOculto(), "_____ ________, ____ _______."), 0);
//}
//
//TEST(Refran, solveRefran)
//{
//    Refran refran;
//
//    EXPECT_TRUE(refran.solveRefran("Marzo lluvioso, mayo copioso.\n"));
//    EXPECT_TRUE(refran.solveRefran("Marzo lluvioso, mayo copioso."));
//    EXPECT_TRUE(refran.solveRefran("marzo lluvioso, mayo copioso\n"));
//    EXPECT_TRUE(refran.solveRefran("marzo lluvioso, mayo copioso.\n"));
//    EXPECT_TRUE(refran.solveRefran("marzo lluvioso, mayo copioso."));
//    EXPECT_TRUE(refran.solveRefran("marzo lluvioso, mayo copioso"));
//}
//
//TEST(Refran, findOcurrences)
//{
//    Refran refran;
//
//    EXPECT_EQ(refran.findOcurrences('o'), 7);
//    EXPECT_EQ(refran.findOcurrences('m'), 2);
//    EXPECT_EQ(strcmp(refran.getRefranOculto(), "M___o _____o_o, m__o _o__o_o."), 0);
//}