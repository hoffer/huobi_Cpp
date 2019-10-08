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

int main(int argc, char** argv) {
    SubscriptionOptions options;
    options.url = "wss://api.huobi.pro";
    SubscriptionClient* client = createSubscriptionClient(options); 
    client->subscribePriceDepthEvent("btcusdt", [](PriceDepthEvent priceDepthEvent) {
        time(&timer);
        cout << "Local: " << timer << "  Server: " << priceDepthEvent.timestamp << endl;
        cout << "Symbol: " << priceDepthEvent.symbol << endl;
        cout << "Bid price: " << priceDepthEvent.data.bids[0].price<< endl;
        cout << "Ask price: " << priceDepthEvent.data.asks[0].price << endl;
    });
    client->startService();

}

