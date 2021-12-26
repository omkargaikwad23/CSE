import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicBoolean;
import java.lang.Thread;

class ReaderWriter implements Runnable {

    // Semaphore for reader and writer
    Semaphore semWrite = new Semaphore(1);
    Semaphore semRead = new Semaphore(1);

    // Number of readers in the buffer
    private int readerCounter;

    // Type of object, ie. reader or writer 
    private boolean type;

    // A common status flag. Will be set to true if all the work is done
    public static AtomicBoolean status = new AtomicBoolean(false);
    
    // Name of object 
    public String name;

    // Constructor
    public ReaderWriter(String rw, String name) {
        readerCounter = 0;
        type = rw.equals("reader");
        this.name = name;
    }

    // Check the type and call a function accordingly
    public void RunMethod(){
        if (type) Reader();
        else Writer();
    }

    @Override
    public void run() {}

    // Critical section (Common shared part) of the code
    private static void critical_section(String name){
        System.out.println("Thread currently occupied by: " + name);
    }

    // Reader function
    public void Reader(){
        while (!status.get()){

            // Acquire the right to read.
            semRead.tryAcquire();
            readerCounter++;

            if (readerCounter == 1) semWrite.tryAcquire();          // Writer should not be able to write while reading. 
            semRead.release();

            // Enter the critical section.
            critical_section(name);
            semRead.tryAcquire();
    
            // release after reading is done. Other readers may read from here
            readerCounter--;
            if (readerCounter == 0) semWrite.release();
    
            semRead.release();
        }
    }

    public void Writer(){
        while (!status.get()){
            // Acquire the right to write. Enter the critical section.
            semWrite.tryAcquire();
            critical_section(name);
            semWrite.release();
        }
    }

};

class Main {
    public static void main(String args[]){

        // Creating Readers and Writers with threads
        ReaderWriter r1 = new ReaderWriter("reader", "R1");
        Thread t1 = new Thread(new Runnable() {
            @Override
            public void run() {
                r1.RunMethod();
            }
        });
        t1.setPriority(7);

        ReaderWriter w1 = new ReaderWriter("writer", "W1");
        Thread t2 = new Thread(new Runnable() {
            @Override
            public void run() {
                w1.RunMethod();
            }
        });
        t2.setPriority(6);

        ReaderWriter r2 = new ReaderWriter("reader", "R2");
        Thread t3 = new Thread(new Runnable() {
            @Override
            public void run() {
                r2.RunMethod();
            }
        });
        t3.setPriority(5);

        t1.start();
        t2.start();
        t3.start();

        Thread t4 = new Thread(new Runnable(){
            @Override
            public void run(){
                ReaderWriter.status.set(true);
            } 
        });

        t4.setPriority(4);
        t4.start();
    }  
};