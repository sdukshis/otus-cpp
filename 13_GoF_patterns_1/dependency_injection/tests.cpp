#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <iostream>
#include <memory>

#include "HTTPClient.h"
#include "healthchecker.h"

using ::testing::_;
using ::testing::Return;
using ::testing::Throw;

class MockHTTPClient : public HTTPClient {
  public:
    MOCK_METHOD(void, connect, (const std::string_view &), (override));
    MOCK_METHOD(HTTPResponse, request, (const HTTPRequest &), (override));
};

TEST(healthcheck, positive) {
    std::string_view host = "example.com";
    HTTPResponse response;
    response.status_code = 200;

    auto client = std::make_shared<MockHTTPClient>();
    EXPECT_CALL(*client, connect(_))
        .Times(1);

    EXPECT_CALL(*client, request(_))
        .Times(1)
        .WillOnce(Return(response));

    Healthchecker checker{client};
    ASSERT_TRUE(checker.check(host));
}

TEST(healthcheck, negative_status_code) {
    std::string_view host = "example.com";
    HTTPResponse response;
    response.status_code = 404;

    auto client = std::make_shared<MockHTTPClient>();
    EXPECT_CALL(*client, connect(_))
        .Times(1);

    EXPECT_CALL(*client, request(_))
        .Times(1)
        .WillOnce(Return(response));

    Healthchecker checker{client};
    ASSERT_FALSE(checker.check(host));
}

TEST(healthcheck, negative_connection_error) {
    std::string_view host = "example.com";
    HTTPResponse response;
    response.status_code = 404;

    auto client = std::make_shared<MockHTTPClient>();
    EXPECT_CALL(*client, connect(_))
        .Times(1)
        .WillOnce(Throw(std::exception{}));

    Healthchecker checker{client};
    ASSERT_FALSE(checker.check(host));
}
