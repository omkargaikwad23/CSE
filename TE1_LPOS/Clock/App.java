import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

public class App {
    public static void main(String[] args) throws Exception {

        // Thread safe queue
        BlockingQueue<Event> q = new LinkedBlockingQueue<Event>();

        // Declare clocks 
        Thread c1 = new Thread(new Clock("C1", q, 3));
        Thread c2 = new Thread(new Clock("C2", q, 10));
        Thread c3 = new Thread(new Clock("C3", q, 20));

        // start clocks
        c1.start();
        c2.start();
        c3.start();
    }
}
