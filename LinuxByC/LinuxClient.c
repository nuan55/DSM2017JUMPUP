#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include "packet.h"
#include "variables.h"
#include "extern.h"

int Lclient(){
   int client_sfd;
   struct sockaddr_in serveradr;
   int i;

   memset(&realPack,0,sizeof(TYPE_PACKET));

   if((client_sfd=socket(AF_INET,SOCK_DGRAM,0))==-1){
	printf("socket error: \n");
	exit(0);
   }
   printf("point1 \n");
   memset(&serveradr,0,sizeof(serveradr));
   serveradr.sin_family=AF_INET;
   serveradr.sin_addr.s_addr=inet_addr("192.168.137.1");
   serveradr.sin_port=htons(6258);
   while(1){
	if(flag==1){
	if(sendto(client_sfd,(char *)&realPack,24,0,(struct sockaddr *)&serveradr,sizeof(serveradr))<0){
		puts("sendto failed \n");
		flag=0;
		break;
	   }
		viewCMD(realPack);
   		printf("success! \n");
		flag=0;
  	 }else if(flag==2){
		if(sendto(client_sfd,(char *)&realPack,24,0,(struct sockaddr *)&serveradr,sizeof(serveradr))<0){
		puts("sendto failed \n");
		flag=0;
		break;
	   }
   		printf("success! \n");
		flag=0;
	 }

}
}
