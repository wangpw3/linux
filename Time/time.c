#include <stdio.h>
#include <time.h>

char buf[110];

int main() {
    time_t t = time(NULL);
    
    //本地时间
    struct tm * local = localtime(&t);
    printf("%d-%d-%d   %d:%d:%d\n",\
    local->tm_year+1900, local->tm_mon+1, local->tm_mday,\
    local->tm_hour, local->tm_min, local->tm_sec);

    char * c = ctime(&t);
    printf("%s", c);


    //国际时间
    struct tm * gm = gmtime(&t);
    printf("%d-%d-%d   %d:%d:%d\n",\
    gm->tm_year+1900, gm->tm_mon+1, gm->tm_mday,\
    gm->tm_hour, gm->tm_min, gm->tm_sec);

    char * asc = asctime(local);
    printf("%s", asc);

    
    strftime(buf, 100, "%H:%M:%S", local);
    printf("%s", buf);/*  */

    return 0;
}