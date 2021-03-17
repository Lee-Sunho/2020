#include "RootHeader.h"

char * getCurTime(){
    char ret[BUF_SIZE];
    time_t t = time(NULL);
    struct tm curTime = *localtime(&t);
    sprintf(ret, "%d.%d.%d %d:%d:%d", curTime.tm_year + 1900, curTime.tm_mon + 1, curTime.tm_mday,
            curTime.tm_hour, curTime.tm_min, curTime.tm_sec);
    return ret;
}