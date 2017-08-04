#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include "packet.h"
#include "Lsense.h"
#include "extern.h"

#define MAXBUF 1024

int Lserver ()
{
	int result, maxfd,n,status;
	int server_sockfd, client_sockfd;
	int client_len,i;
	int max_client=-1;
	char buf[MAXBUF];
	char recvdata[4];
	struct sockaddr_in clientaddr,serveraddr;
	client_len=sizeof(clientaddr);
	int client[5];
	cyclenum=3;

	fd_set readfds, allfds;


/*
	if(argc<2)
	{
		printf("Help : server portno");
		return 1;
	}
*/
	if((server_sockfd=socket(AF_INET, SOCK_STREAM,0))==-1)
	{
		printf("socket error : ");
		exit(0);
	}
printf("point1\n");
	memset(&serveraddr,0,sizeof(serveraddr));
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_addr.s_addr=htonl(INADDR_ANY);
	serveraddr.sin_port=htons(5259);

	bind(server_sockfd,(struct sockaddr *)&serveraddr, sizeof(serveraddr));
	listen(server_sockfd,5);
	maxfd=server_sockfd;
	FD_ZERO(&readfds);
	FD_SET(server_sockfd,&readfds);
	printf("point2\n");
	for(i=0;i<5;i++){
		client[i]=0;
	}

	while(1){
		struct timeval tval;
		tval.tv_sec = 0;
		tval.tv_usec= 500;
		FD_ZERO(&readfds);
		FD_SET(server_sockfd,&readfds);
		for(i=0;i<5;i++){
			// printf("%d \n", client[i]);
			if(client[i]>0){
				FD_SET(client[i],&readfds);
			}
		}
		allfds=readfds;
		memset(buf,0x00,MAXBUF);
		//printf("..... %d .......\n", maxfd);
		result=select (maxfd+1,&allfds,0,0,&tval);
		if(result==-1)
		{
			puts("select : error");
			exit(1);
		}
		else if(result==0)
		{
			//puts("select : time over\n");
			continue;
		}
		else
		{

			if(FD_ISSET(server_sockfd,&allfds)){
			   client_sockfd=accept(server_sockfd,(struct sockaddr *)&clientaddr,&client_len);  
			   printf("New Client Connect: %s\n",inet_ntoa(clientaddr.sin_addr));


			   for(i=0;i<5;i++){
				if(client[i]<=0){
					client[i]=client_sockfd;
					printf("\nclientNum = %d\n clientFD=%d\n",i+1,client_sockfd);
					break;
				}
			   }

			
			   FD_SET(client_sockfd,&readfds);

			   if(client_sockfd>maxfd)
				maxfd=client_sockfd;
			   if(i<max_client)
				max_client=i;

			   continue;
			}
				
			for(i=0;i<5;i++){
				
				if(FD_ISSET(client[i],&allfds)){
					if(n=recv(client_sockfd,recvdata,sizeof(recvdata),0)){
							result=atoi(recvdata);
							printf("receive data : %d \n",result);
					}else printf("NOPE");

					if(n==-1){
					   puts("recverror!");
					   return(1);
					}
					switch(result){
						case 103: cyclenum=3; break;
						case 105: cyclenum=5; break;
						case 110: cyclenum=10; break;
					}
				}
			}
		    }

		}
	
	}
		
		



