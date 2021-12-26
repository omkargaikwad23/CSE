// Used to define an event. Contains info about current time and incoming and outgoing processes
public class Event {
	String from;
	String to;
	int currentTime;

	Event(String from, String to, int currentTime) {
		this.currentTime = currentTime;
		this.from = from;
		this.to = to;
	}

	public String getFrom() {
		return from;
	}

	public void setFrom(String from) {
		this.from = from;
	}

	public String getTo() {
		return to;
	}

	public void setTo(String to) {
		this.to = to;
	}

	public int getCurrentTime() {
		return currentTime;
	}

	public void setCurrentTime(int currentTime) {
		this.currentTime = currentTime;
	}

}
