#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <pthread.h>
#include "packet.h"
#include "LinuxSc.h"
#include "Lsense.h"

int main(){
   pthread_t thread[3];
   int status;
   pthread_create(&thread[0],NULL,(void*)&Lserver,NULL);
   pthread_create(&thread[1],NULL,(void*)&Lclient,NULL);
   pthread_create(&thread[2],NULL,(void*)&sensorsample,NULL);

   pthread_join(thread[3],(void **)&status);
   pthread_join(thread[0],(void **)&status);
   pthread_join(thread[1],(void **)&status);
   return 0;
}
