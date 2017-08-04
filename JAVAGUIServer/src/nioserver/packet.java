package nioserver;
import java.io.IOException;
import java.io.*;

class packet {
	int flag;
	int sys_id;
	int sen_id;
	long timestamp;
	String data=new String();
	public String tString(){
		String sys,sensor = null;
		sys="라즈베리파이"+sys_id;
		if(sen_id==4){
			sensor="touch sensor";
		}else if(sen_id==5){
			sensor="infraredray sensor";
		}
		return(sys+" "+sensor+" "+timestamp+" "+data);
	}
   
}
