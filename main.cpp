#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "matrix.h"

TEST(AMatrixTest, DefaultConstructorTest) {
    amatrix::AMatrix<int> m1;
    EXPECT_EQ(m1.size1(), 0);
    EXPECT_EQ(m1.size2(), 0);
    EXPECT_EQ(m1.data(), nullptr);

    amatrix::AMatrix<double> m2;
    EXPECT_EQ(m2.size1(), 0);
    EXPECT_EQ(m2.size2(), 0);
    EXPECT_EQ(m2.data(), nullptr);
}

TEST(AMatrixTest, SizeConstructorTest) {
    amatrix::AMatrix<double> m1(2,2);
    EXPECT_EQ(m1.size1(), 2);
    EXPECT_EQ(m1.size2(), 2);
    EXPECT_NE(m1.data(), nullptr);
}

TEST(AMatrixTest, ConstructorDefValTest) {
    amatrix::AMatrix<int> m1(2, 2, 3);
    EXPECT_EQ(m1.size1(), 2);
    EXPECT_EQ(m1.size2(), 2);
    EXPECT_NE(m1.data(), nullptr);
    auto ptr = m1.data();
    EXPECT_EQ(*ptr, 3);
    ++ptr;
    EXPECT_EQ(*ptr, 3);
    ++ptr;
    EXPECT_EQ(*ptr, 3);
    ++ptr;
    EXPECT_EQ(*ptr, 3);
}

TEST(AMatrixTest, ConstructorInitListTest) {
    amatrix::AMatrix<double> m1({ 1.0, 2.0, 3.0 }, 2);
    EXPECT_EQ(m1.size1(), 2);
    EXPECT_EQ(m1.size2(), 3);
    EXPECT_NE(m1.data(), nullptr);
    auto ptr = m1.data();
    EXPECT_EQ(*ptr, 1.0);
    ++ptr;
    EXPECT_EQ(*ptr, 2.0);
    ++ptr;
    EXPECT_EQ(*ptr, 3.0);
    ++ptr;
    EXPECT_EQ(*ptr, 1.0);
    ++ptr;
    EXPECT_EQ(*ptr, 2.0);
    ++ptr;
    EXPECT_EQ(*ptr, 3.0);

    amatrix::AMatrix<double> m2({ 1.0, 2.0, 3.0 });
    EXPECT_EQ(m2.size1(), 1);
    EXPECT_EQ(m2.size2(), 3);
    EXPECT_NE(m2.data(), nullptr);
    ptr = m2.data();
    EXPECT_EQ(*ptr, 1.0);
    ++ptr;
    EXPECT_EQ(*ptr, 2.0);
    ++ptr;
    EXPECT_EQ(*ptr, 3.0);
    ++ptr;
    EXPECT_NE(*ptr, 1.0);
}

TEST(AMatrixTest, ConstructorInitListTwoSizeTest) {
    amatrix::AMatrix<int> m1(4, 2, { 0,1,2,3,4,5,6,7 });
    EXPECT_EQ(m1.size1(), 4);
    EXPECT_EQ(m1.size2(), 2);
    EXPECT_NE(m1.data(), nullptr);
    for (std::size_t i = 0; i < m1.size1()*m1.size2(); ++i)
        EXPECT_EQ(m1(i), i);

    amatrix::AMatrix<int> m2(4, 0, { 0,1,2,3,4,5,6,7 });
    EXPECT_EQ(m2.size1(), 0);
    EXPECT_EQ(m2.size2(), 0);
    EXPECT_EQ(m2.data(), nullptr);

    amatrix::AMatrix<int> m3(4, 3, { 0,1,2,3,4,5,6,7 });
    EXPECT_EQ(m3.size1(), 0);
    EXPECT_EQ(m3.size2(), 0);
    EXPECT_EQ(m3.data(), nullptr);
}

TEST(AMatrixTest, CopyConstructorTest) {
    amatrix::AMatrix<double> m1({ 1.0, 2.0, 3.0 }, 2);
    amatrix::AMatrix<double> m2(m1);
    EXPECT_EQ(m2.size1(), 2);
    EXPECT_EQ(m2.size2(), 3);
    EXPECT_NE(m2.data(), nullptr);
    auto ptr = m2.data();
    EXPECT_EQ(*ptr, 1.0);
    ++ptr;
    EXPECT_EQ(*ptr, 2.0);
    ++ptr;
    EXPECT_EQ(*ptr, 3.0);
    ++ptr;
    EXPECT_EQ(*ptr, 1.0);
    ++ptr;
    EXPECT_EQ(*ptr, 2.0);
    ++ptr;
    EXPECT_EQ(*ptr, 3.0);

    amatrix::AMatrix<double> m3 = m1;
    EXPECT_EQ(m3.size1(), 2);
    EXPECT_EQ(m3.size2(), 3);
    EXPECT_NE(m3.data(), nullptr);
    ptr = m3.data();
    EXPECT_EQ(*ptr, 1.0);
    ++ptr;
    EXPECT_EQ(*ptr, 2.0);
    ++ptr;
    EXPECT_EQ(*ptr, 3.0);
    ++ptr;
    EXPECT_EQ(*ptr, 1.0);
    ++ptr;
    EXPECT_EQ(*ptr, 2.0);
    ++ptr;
    EXPECT_EQ(*ptr, 3.0);
}

TEST(AMatrixTest, AssignOperatorTest) {
    amatrix::AMatrix<double> m1({ 1.0, 2.0, 3.0 }, 2);
    amatrix::AMatrix<double> m2;
    m2 = m1;
    EXPECT_EQ(m2.size1(), m1.size1());
    EXPECT_EQ(m2.size2(), m1.size2());
    EXPECT_NE(m2.data(), m1.data());
    auto ptr = m2.data();
    EXPECT_EQ(*ptr, 1.0);
    ++ptr;
    EXPECT_EQ(*ptr, 2.0);
    ++ptr;
    EXPECT_EQ(*ptr, 3.0);
    ++ptr;
    EXPECT_EQ(*ptr, 1.0);
    ++ptr;
    EXPECT_EQ(*ptr, 2.0);
    ++ptr;
    EXPECT_EQ(*ptr, 3.0);

    amatrix::AMatrix<double> m3(5,5,0);
    m3 = m1;
    EXPECT_EQ(m3.size1(), m1.size1());
    EXPECT_EQ(m3.size2(), m1.size2());
    EXPECT_NE(m3.data(), m1.data());
    ptr = m3.data();
    EXPECT_EQ(*ptr, 1.0);
    ++ptr;
    EXPECT_EQ(*ptr, 2.0);
    ++ptr;
    EXPECT_EQ(*ptr, 3.0);
    ++ptr;
    EXPECT_EQ(*ptr, 1.0);
    ++ptr;
    EXPECT_EQ(*ptr, 2.0);
    ++ptr;
    EXPECT_EQ(*ptr, 3.0);
}

TEST(AMatrixTest, MoveConstructorTest) {
    amatrix::AMatrix<double> m1({ 1.0, 2.0, 3.0 }, 2);
    amatrix::AMatrix<double> m2(std::move(m1));
    EXPECT_EQ(m2.size1(), 2);
    EXPECT_EQ(m2.size2(), 3);
    EXPECT_NE(m2.data(), m1.data());
    EXPECT_EQ(m1.size1(), 0);
    EXPECT_EQ(m1.size2(), 0);
    EXPECT_EQ(m1.data(), nullptr);
    auto ptr = m2.data();
    EXPECT_EQ(*ptr, 1.0);
    ++ptr;
    EXPECT_EQ(*ptr, 2.0);
    ++ptr;
    EXPECT_EQ(*ptr, 3.0);
    ++ptr;
    EXPECT_EQ(*ptr, 1.0);
    ++ptr;
    EXPECT_EQ(*ptr, 2.0);
    ++ptr;
    EXPECT_EQ(*ptr, 3.0);
}

TEST(AMatrixTest, MoveOperatorTest) {
    amatrix::AMatrix<double> m1({ 1.0, 2.0, 3.0 }, 2);
    amatrix::AMatrix<double> m2;
    m2 = std::move(m1);
    EXPECT_EQ(m2.size1(), 2);
    EXPECT_EQ(m2.size2(), 3);
    EXPECT_NE(m2.data(), m1.data());
    EXPECT_EQ(m1.size1(), 0);
    EXPECT_EQ(m1.size2(), 0);
    EXPECT_EQ(m1.data(), nullptr);
    auto ptr = m2.data();
    EXPECT_EQ(*ptr, 1.0);
    ++ptr;
    EXPECT_EQ(*ptr, 2.0);
    ++ptr;
    EXPECT_EQ(*ptr, 3.0);
    ++ptr;
    EXPECT_EQ(*ptr, 1.0);
    ++ptr;
    EXPECT_EQ(*ptr, 2.0);
    ++ptr;
    EXPECT_EQ(*ptr, 3.0);

    amatrix::AMatrix<double> m3(5, 5, 0);
    m3 = std::move(m2);
    EXPECT_EQ(m3.size1(), 2);
    EXPECT_EQ(m3.size2(), 3);
    EXPECT_NE(m3.data(), m2.data());
    EXPECT_EQ(m2.size1(), 0);
    EXPECT_EQ(m2.size2(), 0);
    EXPECT_EQ(m2.data(), nullptr);
    ptr = m3.data();
    EXPECT_EQ(*ptr, 1.0);
    ++ptr;
    EXPECT_EQ(*ptr, 2.0);
    ++ptr;
    EXPECT_EQ(*ptr, 3.0);
    ++ptr;
    EXPECT_EQ(*ptr, 1.0);
    ++ptr;
    EXPECT_EQ(*ptr, 2.0);
    ++ptr;
    EXPECT_EQ(*ptr, 3.0);
}

TEST(AMatrixTest, SwapTest) {
    amatrix::AMatrix<double> m1({ 1.0, 2.0, 3.0 }, 2);
    amatrix::AMatrix<double> m2({ 3.0, 2.0 }, 3);
    m1.swap(m2);
    EXPECT_EQ(m2.size1(), 2);
    EXPECT_EQ(m2.size2(), 3);
    EXPECT_NE(m2.data(), nullptr);
    EXPECT_NE(m2.data(), m1.data());
    EXPECT_EQ(m1.size1(), 3);
    EXPECT_EQ(m1.size2(), 2);
    EXPECT_NE(m1.data(), nullptr);
    auto ptr = m2.data();
    EXPECT_EQ(*ptr, 1.0);
    ++ptr;
    EXPECT_EQ(*ptr, 2.0);
    ++ptr;
    EXPECT_EQ(*ptr, 3.0);
    ++ptr;
    EXPECT_EQ(*ptr, 1.0);
    ++ptr;
    EXPECT_EQ(*ptr, 2.0);
    ++ptr;
    EXPECT_EQ(*ptr, 3.0);
    ptr = m1.data();
    EXPECT_EQ(*ptr, 3.0);
    ++ptr;
    EXPECT_EQ(*ptr, 2.0);
    ++ptr;
    EXPECT_EQ(*ptr, 3.0);
    ++ptr;
    EXPECT_EQ(*ptr, 2.0);
    ++ptr;
    EXPECT_EQ(*ptr, 3.0);
    ++ptr;
    EXPECT_EQ(*ptr, 2.0);
}

TEST(AMatrixTest, ElementTest) {
    amatrix::AMatrix<int> m1(4, 2, { 1,2,3,4,5,6,7,8 });    
    EXPECT_EQ(m1(0, 0), 1);
    EXPECT_EQ(m1(2,1), 6);
    EXPECT_EQ(m1(3,1), 8);
    EXPECT_EQ(m1(0), 1);
    EXPECT_EQ(m1(4), 5);
    EXPECT_EQ(m1(7), 8);
    EXPECT_ANY_THROW({
        m1(8);
    });
    EXPECT_THROW({
        try {
            m1(5,3);
        }
        catch (std::out_of_range const& err) {
            EXPECT_STREQ("index is out of the range", err.what());
            throw;
        }
    }, std::out_of_range);
}

TEST(AMatrixTest, AdditionMatrixTest) {
    amatrix::AMatrix<int> m1(4, 2, { 1,2,3,4,5,6,7,8 });
    amatrix::AMatrix<int> m2(4, 2, { 8,7,6,5,4,3,2,1 });
    amatrix::AMatrix<int> m3(4, 2, { -1,-2,-3,-4,-5,-6,-7,-8 });

    auto res1 = m1 + m2;
    EXPECT_EQ(res1.size1(), m1.size1());
    EXPECT_EQ(res1.size2(), m1.size2());
    EXPECT_EQ(res1.size1(), m2.size1());
    EXPECT_EQ(res1.size2(), m2.size2());
    for (std::size_t i = 0; i < res1.size1()*res1.size2(); ++i)
        EXPECT_EQ(res1(i), 9);

    auto res2 = m1 + m3;
    EXPECT_EQ(res2.size1(), m1.size1());
    EXPECT_EQ(res2.size2(), m1.size2());
    EXPECT_EQ(res2.size1(), m2.size1());
    EXPECT_EQ(res2.size2(), m2.size2());
    for (std::size_t i = 0; i < res2.size1() * res2.size2(); ++i)
        EXPECT_EQ(res2(i), 0);

    res1 += m3;
    EXPECT_EQ(res1.size1(), m3.size1());
    EXPECT_EQ(res1.size2(), m3.size2());
    for (std::size_t i = 0; i < res1.size1() * res1.size2(); ++i)
        EXPECT_EQ(res1(i), m2(i));

    m1 += m3;
    EXPECT_EQ(m1.size1(), m3.size1());
    EXPECT_EQ(m1.size2(), m3.size2());
    for (std::size_t i = 0; i < m1.size1() * m1.size2(); ++i)
        EXPECT_EQ(m1(i), 0);
}

TEST(AMatrixTest, SubtractionMatrixTest) {
    amatrix::AMatrix<int> m1(4, 2, { 1,2,3,4,5,6,7,8 });
    amatrix::AMatrix<int> m2(4, 2, { -8,-7,-6,-5,-4,-3,-2,-1 });
    amatrix::AMatrix<int> m3(4, 2, { 1,2,3,4,5,6,7,8 });

    auto res1 = m1 - m2;
    EXPECT_EQ(res1.size1(), m1.size1());
    EXPECT_EQ(res1.size2(), m1.size2());
    EXPECT_EQ(res1.size1(), m2.size1());
    EXPECT_EQ(res1.size2(), m2.size2());
    for (std::size_t i = 0; i < res1.size1() * res1.size2(); ++i)
        EXPECT_EQ(res1(i), 9);

    auto res2 = m1 - m3;
    EXPECT_EQ(res2.size1(), m1.size1());
    EXPECT_EQ(res2.size2(), m1.size2());
    EXPECT_EQ(res2.size1(), m3.size1());
    EXPECT_EQ(res2.size2(), m3.size2());
    for (std::size_t i = 0; i < res2.size1() * res2.size2(); ++i)
        EXPECT_EQ(res2(i), 0);

    m1 -= m3;
    EXPECT_EQ(m1.size1(), m3.size1());
    EXPECT_EQ(m1.size2(), m3.size2());
    for (std::size_t i = 0; i < m1.size1() * m1.size2(); ++i)
        EXPECT_EQ(m1(i), 0);

    m3 -= res1;
    EXPECT_EQ(m3.size1(), res1.size1());
    EXPECT_EQ(m3.size2(), res1.size2());
    for (std::size_t i = 0; i < m3.size1() * res1.size2(); ++i)
        EXPECT_EQ(m3(i), m2(i));
}

TEST(AMatrixTest, MultiplicationMatrixTest) {
    amatrix::AMatrix<int> m1(2,2,2);
    amatrix::AMatrix<int> m2(2,2,3);

    auto res1 = m1 * m2;
    EXPECT_EQ(res1.size1(), m1.size1());
    EXPECT_EQ(res1.size2(), m2.size2());
    for (std::size_t i = 0; i < res1.size1() * res1.size2(); ++i)
        EXPECT_EQ(res1(i), 12);

    amatrix::AMatrix<int> m3(2, 3, {0,2,2,1,3,1});
    amatrix::AMatrix<int> m4(3, 2, { 1,4,2,5,3,6 });
    auto res2 = m3 * m4;
    EXPECT_EQ(res2.size1(), m3.size1());
    EXPECT_EQ(res2.size2(), m4.size2());
    EXPECT_EQ(res2(0), 10);
    EXPECT_EQ(res2(0,1), 22);
    EXPECT_EQ(res2(1,0), 10);
    EXPECT_EQ(res2(3), 25);
}

TEST(AMatrixTest, IncrPrefixTest) {
    amatrix::AMatrix<int> m1(4, 2, 1);
    ++m1;
    EXPECT_EQ(m1.size1(), 4);
    EXPECT_EQ(m1.size2(), 2);
    EXPECT_NE(m1.data(), nullptr);
    for (std::size_t i = 0; i < m1.size1() * m1.size2(); ++i)
        EXPECT_EQ(m1(i), 2);
}

TEST(AMatrixTest, IncrPostfixTest) {
    amatrix::AMatrix<int> m1(4, 2, 1);
    m1++;
    EXPECT_NE(m1.data(), nullptr);
    for (std::size_t i = 0; i < m1.size1() * m1.size2(); ++i)
        EXPECT_EQ(m1(i), 2);
}

TEST(AMatrixTest, DecrPrefixTest) {
    amatrix::AMatrix<int> m1(4, 2, 1);
    --m1;

    for (std::size_t i = 0; i < m1.size1() * m1.size2(); ++i)
        EXPECT_EQ(m1(i), 0);
}

TEST(AMatrixTest, DecrPostfixTest) {
    amatrix::AMatrix<int> m1(4, 2, 1);
    m1--;
    for (std::size_t i = 0; i < m1.size1() * m1.size2(); ++i)
        EXPECT_EQ(m1(i), 0);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}