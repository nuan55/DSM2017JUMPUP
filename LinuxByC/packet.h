typedef struct packet{
	int flag;
	int sys_id;	//SYSTEM ID
	int sen_id;	//SENSOR ID
	long long int timestamp;
	char data[4];
}__attribute__((packed)) TYPE_PACKET;
//typedef struct packet __attribute__((packed)) TYPE_PACKET;



#define CMD_INFO 1
#define CMD_CONTROL 2
#define CMD_INTERVAL 3
