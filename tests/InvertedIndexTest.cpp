// InvertedIndexTest.cpp
#include "gtest/gtest.h"
#include "InvertedIndex.h"

TEST(InvertedIndexTest, BasicFunctionality) {
    InvertedIndex index;

    std::vector<std::string> docs = {
        "milk sugar salt",
        "milk milk milk",
        "sugar salt water"
    };

    index.UpdateDocumentBase(docs);

    // Проверяем частоту слова "milk"
    std::vector<Entry> expected_milk = {{0, 1}, {1, 3}};
    EXPECT_EQ(index.GetWordCount("milk"), expected_milk);

    // Проверяем частоту слова "sugar"
    std::vector<Entry> expected_sugar = {{0, 1}, {2, 1}};
    EXPECT_EQ(index.GetWordCount("sugar"), expected_sugar);

    // Проверяем частоту слова "water"
    std::vector<Entry> expected_water = {{2, 1}};
    EXPECT_EQ(index.GetWordCount("water"), expected_water);

    // Проверяем слово, которого нет
    EXPECT_EQ(index.GetWordCount("unknown"), std::vector<Entry>{});
}
