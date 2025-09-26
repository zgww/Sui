package OrcLang

#include <stdio.h>

extern void Time_sleepMs(int milliSecond)

extern long long Time_unixMs()
long long Time_unixSec(){
    long long ms = Time_unixMs()
    long long sec = ms / 1000;
    return sec;
}
/*
long long Time_unixMinute(){
    long long ms = Time_unixMs()
    long long sec = ms / 1000 / 3600;
    return sec;
}
long long Time_unixHour(){
    long long ms = Time_unixMs()
    long long sec = ms / 1000 / 3600;
    return sec;
}
long long Time_unixDay(){
    long long ms = Time_unixMs()
    long long sec = ms / 1000 / 86400;
    return sec;
}
*/


void Time_test(){

    printf("now ms:%lld\n", Time_unixMs());
    Time_sleepMs(1000);
    printf("中文now ms:%lld\n", Time_unixMs());
}