#include <stdio.h>
#include <time.h>
#include "packet.h"
#include "extern.h"
#define SYS_ID 2

void makeCmdInfo(TYPE_PACKET* tempPack, char *tData,int sensor){
  int i;
  tempPack->sen_id=sensor;
  tempPack->flag=CMD_INFO;
  tempPack->sys_id=SYS_ID;
  tempPack->timestamp=(time(NULL));
  for(i=0;i<4;i++){
	tempPack->data[i]=tData[i];
  }
}
void viewCMD(TYPE_PACKET dtPacket){
	char *p = (char *)&dtPacket.flag;
	int i=0;
	for(i=0; i < sizeof(TYPE_PACKET) ; i++)	printf(" %x", p[i]);
	printf("\n");
	printf("complete: %d %d %d %d %s",dtPacket.flag,dtPacket.sys_id,dtPacket.sen_id,dtPacket.timestamp,dtPacket.data);

}
void makeCmdControl(){}
void makeCmdInterval(){}
/*
int main(){
  int i;
  TYPE_PACKET dtPacket;
  int sensor=1;
  makeCmdInfo(&dtPacket,"22",sensor);

  printf("complete: %d %d %d %lf ",dtPacket.flag,dtPacket.sys_id,dtPacket.sen_id,dtPacket.timestamp);
  for(i=0; i<4; i++) printf("%c",dtPacket.data[i]);
  printf("\n");
  return 0;
}
*/
