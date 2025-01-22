// SearchServerTest.cpp
#include "gtest/gtest.h"
#include "InvertedIndex.h"
#include "SearchServer.h"

TEST(SearchServerTest, SimpleQuery) {
    InvertedIndex index;
    index.UpdateDocumentBase({
        "london is the capital of great britain",
        "paris is the capital of france",
        "berlin is the capital of germany"
    });

    SearchServer server(index);
    std::vector<std::string> queries = {"london", "capital"};
    auto results = server.search(queries);

    EXPECT_EQ(results.size(), 2);
    EXPECT_EQ(results[0][0].doc_id, 0);  // Лондон найден в первом документе
    EXPECT_EQ(results[1].size(), 3);     // Все документы содержат слово "capital"
}
