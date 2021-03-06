package bgu.spl.net.impl.BGRSServer;
import bgu.spl.net.api.BGRSEncoderDecoder;
import bgu.spl.net.api.Protocol;
import bgu.spl.net.srv.BaseServer;
import bgu.spl.net.srv.BlockingConnectionHandler;

public class TPCMain {

    public static void main(String args[]) {
//        int port = Integer.decode(args[0]).intValue();
        int port = 7777;
        BaseServer b = new BaseServer(port, ()->new Protocol(), ()->new BGRSEncoderDecoder()) {
            @Override
            protected void execute(BlockingConnectionHandler handler) {
                handler.run();
            }
        };
        b.serve();
    }
}
