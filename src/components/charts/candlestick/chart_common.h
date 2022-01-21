#ifndef CHART_COMMON_H
#define CHART_COMMON_H


namespace candlestick {
enum INTERVAL {
    m_15,
    h_1,
    h_4,
    d_1,
    w_1,
    M_1,
};

inline qint64 getChartIntervalValue(INTERVAL i) {
    switch(i){
        case INTERVAL::m_15:
            return 900;
        case INTERVAL::h_1:
            return 3600;
        case INTERVAL::h_4:
            return 14400;
        case INTERVAL::d_1:
            return 86400;
        case INTERVAL::w_1:
            return 604800;
        case INTERVAL::M_1:
            return 2592000;
    }
}
}

#endif