package nioserver;

import java.util.concurrent.*;

import io.netty.bootstrap.Bootstrap;
import io.netty.channel.Channel;
import io.netty.channel.EventLoopGroup;
import io.netty.channel.nio.NioEventLoopGroup;
import io.netty.channel.socket.nio.NioSocketChannel;

public class ContainerClient extends Thread{
	static String server;
	static int port;
	int containerPort;
	static int flag=0;
	static EventLoopGroup group;
	Bootstrap bootstrap;
	static NioSocketChannel channel;
	
	public ContainerClient(String server, int port, int containerPort){
		this.server=server;
		this.port=port;
		this.containerPort=containerPort;
	}
	@Override
	public void run(){
		new ContainerClient(server,port,containerPort).start();
	}
	public void start() {
	    group = new NioEventLoopGroup();
	    try {
	        bootstrap = new Bootstrap().group(group).channel(NioSocketChannel.class).handler(new ClientAdapterInitializer());
	        channel = (NioSocketChannel)bootstrap.connect(server, port).sync().channel();
	        
	        while(true){
	        	synchronized(getCacheSyncObject(this.flag)){
	        	if(this.flag==103||this.flag==105){
	        		channel.writeAndFlush(Integer.toString(this.flag));
	        		System.out.println(this.flag);
	        		flag=0;
	        	}else if(this.flag==110){
	        		channel.writeAndFlush(Integer.toString(this.flag));
	        		System.out.println(Integer.toString(this.flag));
	        		this.flag=0;
	        		}
	        	
	        }
	        }
	        /*while(true){
	        channel.write("Hi\n");
	        channel.flush();
	        Thread.sleep(750);
	        
	        }
	        */
	    } catch (Exception e) {
	        e.printStackTrace();
	    } finally {
	        group.shutdownGracefully();
	    }
	}
	
	private ConcurrentMap<Integer, Integer> locks = new ConcurrentHashMap<Integer, Integer>();

	private Object getCacheSyncObject(final Integer id) {
		  locks.putIfAbsent(id, id);
		  return locks.get(id);
		}
	
	}

