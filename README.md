# TrackNTrade
desktop application to Track Cryptocurrency prices
## Third-party
- Qt 5.12.8
- QMake

The prices are fetched from <a href="https://cryptowat.ch/">api.cryptowat.ch</a>. The free version of API with limited number of request per day is used.

<p style="text-align: justify">
<strong>NOTE:</strong> if you live in Iran, then you may have problems using cryptowatch. make sure you have activated <a href="https://shecan.ir">shecan</a> before running the app.
</p>

## Build
```
git clone https://github.com/fatemehkarimi/Track-N-Trade.git
cd Track-N-Trade
mkdir build
cd bulid
qmake ../TrackNTrade.pro
make
```

use the command `./TrackNTrade` to run the app.
