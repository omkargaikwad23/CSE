import java.util.concurrent.BlockingQueue;
import java.util.concurrent.TimeUnit;

public class Clock implements Runnable {
	String name;
	private final BlockingQueue<Event> eventQueue;
	int clockTime = 0;
	int interval = 0;

	public Clock(String name, BlockingQueue<Event> queue, int interval) {
		this.name = name;
		this.eventQueue = queue;
		this.interval = interval;
	}

	public void run() {
		System.out.println("Thread " + this.name + " started");

		int ts;
		// timestamps at which an event is triggered
		if (this.name.equals("C1")) {
			ts = 50;
		} else {
			ts = 30;
		}

		while (true) {
			System.out.println("clock time " + this.name + " " + this.clockTime);
			Event msg;

			// check if the event at the head is for this process
			if (!eventQueue.isEmpty() && eventQueue.peek().getTo().equals(this.name)
					&& (msg = eventQueue.poll()) != null) {
				// sent event log
				System.out.println("\n  ==> Thread " + msg.getFrom() + " sent event to " + msg.getTo() + " at "
						+ msg.getCurrentTime() + "\n");

				// received event log
				System.out.println("\n  ==> Thread " + this.name + " received event from " + msg.getFrom() + " at "
						+ this.clockTime + "\n");

				// updating current clock
				this.clockTime = Math.max(this.clockTime + interval, msg.getCurrentTime() + 1);

				// clock updated log
				System.out.println("\n  ==> Thread " + this.name + " updated its clock to " + this.clockTime + "\n");
			} else {
				// normal clock increment with default interval
				this.clockTime += interval;
			}

			// Events added in queue for clocks to process
			if (this.name.equals("C1")) {
				if (this.clockTime >= ts && ts != 0) {
					this.eventQueue.add(new Event(this.name, "C2", this.clockTime));
					ts = 0;
				}
			} else if (this.name.equals("C3")) {
				if (this.clockTime >= ts && ts != 0) {
					this.eventQueue.add(new Event(this.name, "C1", this.clockTime));
					ts = 0;
				}
			}

			try {
				// sleep thread for 1 sec
				TimeUnit.SECONDS.sleep(1);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}

}
