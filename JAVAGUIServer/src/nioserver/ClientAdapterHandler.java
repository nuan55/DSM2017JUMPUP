package nioserver;

import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.ChannelInboundHandlerAdapter;

public class ClientAdapterHandler extends
        ChannelInboundHandlerAdapter {

	/*
    @Override
    public void messageReceived(ChannelHandlerContext context, String message)
            throws Exception {
        System.out.println(message);
        if (message.equals("quit"))
            throw new ServerEndedException("Server is closed");
    }
*/
    @Override
    public void channelRead(ChannelHandlerContext arg0, Object arg1)
            throws Exception {

    }

    @Override
    public void channelReadComplete(ChannelHandlerContext arg0)
            throws Exception {

    }

    @Override
    public void channelWritabilityChanged(ChannelHandlerContext arg0)
            throws Exception {

    }

}