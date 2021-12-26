// Name: Sanchit Kripalani
// Roll no: 31145
// Batch: M1

import java.io.*;
import java.net.*;

public class server {
	public static void main(String[] args) throws IOException {

		// Initialize the socket with port number
		ServerSocket serverSocket = new ServerSocket(5000);

		System.out.println("Server started");
		System.out.println("Waiting for the client...");

		while (true) {
			Socket socket = null;
			try {
				// Accept a connection request from a client
				socket = serverSocket.accept();

				System.out.println("A new Client is connected: " + socket);

				// Used to read input stream
				DataInputStream input = new DataInputStream(socket.getInputStream());

				// Used to write an output stream
				DataOutputStream output = new DataOutputStream(socket.getOutputStream());

				System.out.println("Assigning a new thread for this Client!");

				// Each client will its own thread
				Thread t = new clientHandler(socket, input, output);
				t.start();

			} catch (Exception e) {
				socket.close();
				System.out.println(e);
			}
		}
	}
}

class clientHandler extends Thread {

	final DataInputStream input;
	final DataOutputStream output;
	final Socket socket;

	public clientHandler(Socket socket, DataInputStream input, DataOutputStream output) {
		this.socket = socket;
		this.input = input;
		this.output = output;
	}

	public void run() {

		String received;
		while (true) {
			try {
				output.writeUTF("Send message to server (Type Exit to terminate connection)");
				// Read data from client
				received = input.readUTF();

				// If client wants to exit the connection
				if (received.equalsIgnoreCase("Exit")) {
					System.out.println("Client " + this.socket + " sends exit...");
					System.out.println("Closing the connection");
					this.socket.close();
					System.out.println("Connection Closed");
					break;
				}
				output.writeUTF(received);

				System.out.println("Response of client: " + received);
			} catch (Exception e) {
				System.out.println(e);
			}
		}

		try {
			this.input.close();
			this.output.close();
		} catch (IOException e) {
			System.out.println(e);
		}
	}
}