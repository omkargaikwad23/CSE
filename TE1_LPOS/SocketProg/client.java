// Name: Sanchit Kripalani
// Roll no: 31145
// Batch: M1

import java.io.*;
import java.net.*;
import java.util.*;

public class client {
	public static void main(String[] args) throws IOException {
		try {

			Scanner sc = new Scanner(System.in);

			// Get the IP of any localhost
			InetAddress ip = InetAddress.getByName("localhost");

			Socket socket = new Socket(ip, 5000);

			// Input Stream from socket
			DataInputStream input = new DataInputStream(socket.getInputStream());

			// OUtput Stream from socket
			DataOutputStream output = new DataOutputStream(socket.getOutputStream());

			while (true) {
				// Print response of server
				System.out.println(input.readUTF());

				// Store data to be sent to server
				String tosend = sc.nextLine();
				// Write data
				output.writeUTF(tosend);

				// Exit condition
				if (tosend.equalsIgnoreCase("Exit")) {
					socket.close();
					System.out.println("Connection Closed");
					break;
				}

				String received = input.readUTF();
				System.out.println("Server: " + received);
			}
			sc.close();
			input.close();
			output.close();
		} catch (Exception e) {
			System.out.println(e);
		}
	}
}