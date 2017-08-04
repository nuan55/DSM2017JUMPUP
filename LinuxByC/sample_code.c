#include <stdio.h>
#include <wiringPi.h>
#include "packet.h"
#include "extern.h"
#include "LinuxSc.h"
#define TOUCH_SENSOR 4
#define DCT_SENSOR 5
#define LED1 1
#define LED2 3

int sensorsample()
{
  flag=0;
  int i=0;
  if(wiringPiSetup()==-1) return 1;
  pinMode(TOUCH_SENSOR,INPUT);
  pinMode(DCT_SENSOR,INPUT);
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  //TYPE_PACKET tempPack;

  for(;;){
  	int res=digitalRead(TOUCH_SENSOR);
	int dres=digitalRead(DCT_SENSOR);
//	printf("TOUCH: %d......\n",res);
//	printf("DETECT: %d......\n",dres);
	digitalWrite(LED1, res);
	digitalWrite(LED2, dres);

	if(res!=0){
		makeCmdInfo(&realPack,res?"YES":"NO",TOUCH_SENSOR);
		//realPack=tempPack;
		flag=1;
	}
	if(dres!=0){
		makeCmdInfo(&realPack,dres?"YES":"NO",DCT_SENSOR);
		//realPack=tempPack;
		flag=1;
	}

//	viewCMD(realPack);
	sleep(1);
	i++;
	if(i==60*cyclenum){
		makeCmdInfo(&realPack,dres?"YES":"NO",TOUCH_SENSOR);
		//realPack=tempPack;
		flag=1;
	}
	}
   return 0;
}
