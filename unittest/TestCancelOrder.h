/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestCancelOrder.h
 * Author: yuanxueqi
 *
 * Created on 2019年3月25日, 上午10:44
 */

#ifndef TESTCANCELORDER_H
#define TESTCANCELORDER_H

#include <gtest/gtest.h>
#include <../src/RestApiImpl.h>
#include "../include/Huobi/HuobiApiException.h"
#include "../include/Huobi/Decimal.h"
#include "../src/Utils/JsonDocument.h"


using namespace Huobi;

TEST(TestCancelOrder, Request) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");

    auto request = impl->cancelOrder("htbtc", 12345L);
    ASSERT_EQ("POST", request->method);
    ASSERT_TRUE(request->path.find("/v1/order/orders/12345/submitcancel") != std::string::npos);
    ASSERT_TRUE(request->path.find("Signature") != std::string::npos);
}

TEST(TestCancelOrder, CancelOrders) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    std::list<long> longList;
    longList.push_back(12443l);
    longList.push_back(2344l);
    auto request = impl->cancelOrders("htbtc", longList);
    ASSERT_EQ("POST", request->method);
    ASSERT_TRUE(request->path.find("Signature") != std::string::npos);
    JsonDocument doc;
    JsonWrapper querier = doc.parseFromString(request->postbody);
    ASSERT_STREQ("12443", querier.getJsonObjectOrArray("order-ids").getStringAt(0));
    ASSERT_STREQ("2344", querier.getJsonObjectOrArray("order-ids").getStringAt(1));
}

TEST(TestCancelOrder, InvalidSymbolInCancelOrder) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    EXPECT_THROW(impl->cancelOrder("$$$$", 100L), HuobiApiException);
}

TEST(TestCancelOrder, InvalidSymbolInCancelOrders) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    std::list<long> longList;
    longList.push_back(12443l);
    longList.push_back(2344l);
    EXPECT_THROW(impl->cancelOrders("$$$$", longList), HuobiApiException);
}

TEST(TestCancelOrder, NullOrderList) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    std::list<long> longList;
    EXPECT_THROW(impl->cancelOrders("btcusdt", longList), HuobiApiException);
}

TEST(TestCancelOrder, HugeOrderList) {
    RestApiImpl* impl = new RestApiImpl("12345", "67890");
    std::list<long> longList;
    for (int i = 0; i <= 50; i++) {
        longList.push_back((long)i);
    }
    EXPECT_THROW(impl->cancelOrders("btcusdt", longList), HuobiApiException);
}

#endif /* TESTCANCELORDER_H */

