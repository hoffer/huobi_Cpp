/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <time.h>
#include <iostream>
#include "Huobi/HuobiClient.h"

using namespace Huobi;
using namespace std;
time_t timer;

#if 1
    #define SERVER_URL "wss://www.hbdm.com/ws"
    #define SYMBOL "BTC_CQ"
#else
    #define SERVER_URL "wss://api.huobi.pro"
    #define SYMBOL "btcusdt"
#endif

int main(int argc, char** argv) {
    SubscriptionOptions options;
    options.url = SERVER_URL;
    Logger::setlogMode(1);
    SubscriptionClient* client = createSubscriptionClient(options);
    client->subscribePriceDepthEvent(SYMBOL, [](PriceDepthEvent priceDepthEvent) {
        time(&timer);
        cout << "Local: " << timer << "  Server: " << priceDepthEvent.timestamp << endl;
        cout << "Symbol: " << priceDepthEvent.symbol << endl;
        cout << "Bid price: " << priceDepthEvent.data.bids[0].price<< endl;
        cout << "Ask price: " << priceDepthEvent.data.asks[0].price << endl;
    });
    client->startService();

}

