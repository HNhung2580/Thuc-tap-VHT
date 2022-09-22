#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<sched.h>
#include<time.h>



static struct timespec rtc, rqst;

static struct timespec ot;

 FILE *file1;
 FILE *file2;


long T =100000;

void * sample_func(void *arg) {
        struct sched_param sp;
        sp.sched_priority = 70;
        pthread_setschedparam(pthread_self(), SCHED_FIFO, &sp);

        clock_gettime(CLOCK_MONOTONIC, &rqst);
        
        while(1) {
      
        rqst.tv_nsec += T;
       
        if(rqst.tv_nsec > 1000*1000*1000) {
                rqst.tv_nsec -= 1000*1000*1000;
                rqst.tv_sec++;
        }

        clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &rqst, NULL);
        
        clock_gettime(CLOCK_MONOTONIC, &rtc);
        }
        
   return NULL;

}
void * input_func(void *arg) {
        struct sched_param sp;
        sp.sched_priority = 10;
        pthread_setschedparam(pthread_self(), SCHED_FIFO, &sp);

        file2 = fopen("freq.txt","r");
       while(1) {
     
        char buff[100];
        fgets(buff,sizeof(buff),file2);
        char *eptr;
        T = strtol(buff,&eptr,10);  

       }
        fclose(file2);
        return NULL;

}
void    *logging_func(void* arg) {    
        struct sched_param sp;
        sp.sched_priority = 40;
        pthread_setschedparam(pthread_self(), SCHED_FIFO, &sp);


         file1 = fopen("time_and_interval.txt","a+");
        while(1) {

                if(rtc.tv_nsec != ot.tv_nsec ||rtc.tv_sec != ot.tv_sec ) {
        
                        if(file1 == NULL) {
                                printf("Unable to open file\n");
                                return NULL;
                        }

                        long diff_sec = (long)rtc.tv_sec - (long)ot.tv_sec ;
                        long diff_nsec;
                        
                        if(rtc.tv_nsec > ot.tv_nsec) {
                                diff_nsec = rtc.tv_nsec - ot.tv_nsec;
                        }
                        
                        else {
                                diff_nsec = 1000000000 - ot.tv_nsec + rtc.tv_nsec;
                                diff_sec = diff_sec - 1;
                        }        
                        
                        if(ot.tv_nsec != 0) {

                                fprintf(file1, "%ld\n",diff_nsec);
                        }
                
                        ot.tv_nsec = rtc.tv_nsec;
                        ot.tv_sec = rtc.tv_sec;
                }
        }
        fclose(file1);
        return NULL;
}
int main(int argc, char** argv)
{

        pthread_t SAMPLE,INPUT,LOGGING;
        rqst.tv_sec = 0;
        rqst.tv_nsec = 0;


        pthread_create(&INPUT, NULL, &input_func, NULL); 
        pthread_create(&SAMPLE,  NULL,&sample_func, NULL); 
        pthread_create(&LOGGING, NULL, &logging_func, NULL); 

        pthread_join(INPUT,NULL);
        pthread_join(SAMPLE,NULL);
        pthread_join(LOGGING,NULL);

        return 0;
}