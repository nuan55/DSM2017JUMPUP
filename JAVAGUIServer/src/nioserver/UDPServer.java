package nioserver;
import java.io.*;
import java.net.*;
import java.nio.*;
public class UDPServer extends Thread
{
	@Override
   public void run()
      {
	   	 try{
	   	 int port=6258;
         DatagramSocket serverSocket = new DatagramSocket(port);
	   	 packet pack=new packet();
	   	 int readsize;
            while(true)
               {
            	byte[] buf=new byte[30];
            	
            	DatagramPacket receivePacket=new DatagramPacket(buf,buf.length);
            	serverSocket.receive(receivePacket);
            	
            	
            	byte[] data=new byte[receivePacket.getLength()];
            	data=receivePacket.getData();
            	
            	byte[] tarr=new byte[4];
            	System.arraycopy(data, 0, tarr, 0, 4);
            	pack.flag=java.nio.ByteBuffer.wrap(tarr).order(java.nio.ByteOrder.LITTLE_ENDIAN).getInt();
            	
            	tarr=new byte[4];
            	System.arraycopy(data, 4, tarr, 0, 4);
            	pack.sys_id=java.nio.ByteBuffer.wrap(tarr).order(java.nio.ByteOrder.LITTLE_ENDIAN).getInt();
            	
            	tarr=new byte[4];
            	System.arraycopy(data, 8, tarr, 0, 4);
            	pack.sen_id=java.nio.ByteBuffer.wrap(tarr).order(java.nio.ByteOrder.LITTLE_ENDIAN).getInt();
            	
            	tarr=new byte[8];
            	System.arraycopy(data, 12, tarr, 0, 8);
            	pack.timestamp=java.nio.ByteBuffer.wrap(tarr).order(java.nio.ByteOrder.LITTLE_ENDIAN).getLong();		
            	
            	tarr=new byte[4];
            	System.arraycopy(data, 20, tarr, 0, 4);
            	String text1=new String(tarr,"UTF-8");
            	pack.data=text1;
            	String msgpacket=pack.tString();
            	System.out.println("д╖ют : "+msgpacket);
            	NewJFrame.detectjLabel();
            	saveFile(msgpacket);
            	Thread.sleep(1000);
            	NewJFrame.nodetectjLabel();
            	
               }
	   	 }catch(Exception e){e.printStackTrace();}
	   	 
      }
	
	
	public int getInt(byte[] bt){
		int temp = 0;
		int[] bt2 = new int[4];
		for(int i=0; i<4; i++)
		{
			bt2[i] = bt[i] < 0 ? ((Byte.MAX_VALUE + 1) * 2) + bt[i] : bt[i];
			temp |= (bt2[i] << (8*(3-i)));
		}
		return temp;
	}
	
	public long getLong(byte[] bt){
		
		ByteBuffer buf=ByteBuffer.allocate(8);
		final byte[] change=new byte[8];
		
		for(int i=0;i<8;i++)   change[i]=(byte)0x00;
		for(int i=0;i<bt.length;i++) change[7-i]=bt[bt.length-1-i];
		
		buf=ByteBuffer.wrap(change);
		buf.order(ByteOrder.BIG_ENDIAN);
		
		return buf.getLong();
		
		
	}
	 public void saveFile(String data) throws IOException {
	        FileWriter fw = new FileWriter("d:/storefile.txt", true);
	        fw.write(data+"\r \n");
	        fw.close();
	    }
}