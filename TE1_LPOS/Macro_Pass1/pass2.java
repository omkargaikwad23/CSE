//javac --release 8 pass2.java
//java pass2

// expand the macro call, link actual parameters with formal parameters


import java.io.*;
import java.util.*;

public class pass2 {

	// Helper class to store data into MNT table
    public static class TableRow {
        String name;
        int pp,kp,mdtp,kpdtp;
        
        // Constructors along with setter and getter methods
        public TableRow(String name, int pp, int kp, int mdtp, int kpdtp) {
            super();
            this.name = name;
            this.pp = pp;
            this.kp = kp;
            this.mdtp = mdtp;
            this.kpdtp = kpdtp;
        }
        public String getName() {
            return name;
        }
        public void setName(String name) {
            this.name = name;
        }
        public int getPp() {
            return pp;
        }
        public void setPp(int pp) {
            this.pp = pp;
        }
        public int getKp() {
            return kp;
        }
        public void setKp(int kp) {
            this.kp = kp;
        }
        public int getMdtp() {
            return mdtp;
        }
        public void setMdtp(int mdtp) {
            this.mdtp = mdtp;
        }
        public int getKpdtp() {
            return kpdtp;
        }
        public void setKpdtp(int kpdtp) {
            this.kpdtp = kpdtp;
        }
    }
    public static void main(String[] args) throws Exception {

		// Open all the files generated from macro pass1
		BufferedReader IC = new BufferedReader(new FileReader("intermediate.txt"));
		BufferedReader MDTF = new BufferedReader(new FileReader("mdt.txt"));
		BufferedReader KPDTF = new BufferedReader(new FileReader("kpdt.txt"));
		BufferedReader MNTF = new BufferedReader(new FileReader("mnt.txt"));
		
		// Create expanded file
		FileWriter expanded_file = new FileWriter("expanded_file.txt");
		FileWriter APT = new FileWriter("aptab.txt");  // Actual parameter table
		
		HashMap<String, TableRow> MNT = new HashMap<>();				// Hashmap to store data from MNT table
		HashMap<Integer, String> APTAB = new HashMap<>();			// Actual parameter table
		HashMap<String, Integer> Inverse_APTAB = new HashMap<>();	// Inverse Actual parameter table
		
		Vector<String> MDT = new Vector<String>();		// To store MDT table
		Vector<String> KPDT = new Vector<String>();		// To store KPDT table
		
		int pp, kp, mdtp, kpdtp, param_no;	//kpd = keyword parameter
		String curr_line;

		// Read MDT table
		while((curr_line = MDTF.readLine())!=null)
			MDT.addElement(curr_line);
		
		// Read KPDT table
		while((curr_line = KPDTF.readLine())!=null)
			KPDT.addElement(curr_line);
		
		// Read MNT table
		while((curr_line = MNTF.readLine())!=null)
		{
			String tokens[] = curr_line.split("\\s+");
			MNT.put(tokens[0], new TableRow(tokens[0], Integer.parseInt(tokens[1]), Integer.parseInt(tokens[2]), Integer.parseInt(tokens[3]), Integer.parseInt(tokens[4])));
		}

		while((curr_line = IC.readLine())!=null)
		{
			String tokens[] = curr_line.split("\\s+");						// Tokenize the string 
			if(MNT.containsKey(tokens[0]))									// Check for the name of Macro in MNT
			{
				pp = MNT.get(tokens[0]).getPp();
				kp = MNT.get(tokens[0]).getKp();
				kpdtp = MNT.get(tokens[0]).getKpdtp();
				mdtp = MNT.get(tokens[0]).getMdtp();
				param_no = 1;

				for(int i=0; i<pp; i++)										// Process positional parameters
				{ 
					tokens[param_no] = tokens[param_no].replace(",", "");
					APTAB.put(param_no, tokens[param_no]);					// Put parameter index and name in APTAB
					Inverse_APTAB.put(tokens[param_no], param_no);
					param_no++;												// Increment the parameter index
				}

				int j = kpdtp-1;
				for(int i=0; i<kp; i++)										// Process keyword parameters
				{
					String temp[] = KPDT.get(j).split("\t");
					APTAB.put(param_no,temp[1]);							// Put parameter index and name in APTAB
					Inverse_APTAB.put(temp[0],param_no);					// Put reverse entry in Inverse_APTAB
					j++;
					param_no++;
				}
				
				// Check if default values of keyword parameters are changed
				for(int i=pp+1; i<tokens.length; i++)
				{
					tokens[i] = tokens[i].replace(",", "");
					String splits[] = tokens[i].split("=");		
					String name = splits[0].replaceAll("&", "");
					APTAB.put(Inverse_APTAB.get(name),splits[1]);			// Get its index from Inverse_APTAB and insert into APTAB
				}
				
				// Write into APT file
				APT.write("Macro: " + tokens[0] + "\nIndex\tValue\n");
				for (Integer i : APTAB.keySet())
					APT.write(i + "\t\t" + APTAB.get(i) + "\n");

				System.out.print("Macro: " + tokens[0] + " (APTAB)\nIndex\tValue\n");
				for (Integer i : APTAB.keySet())
					System.out.print(i + "\t" + APTAB.get(i) + "\n");
				System.out.print("Macro: " + tokens[0] + " (Inverse_APTAB)\nIndex\tValue\n");
				for (String i : Inverse_APTAB.keySet())
					System.out.print(i + "\t" + Inverse_APTAB.get(i) + "\n");

				int i = mdtp-1;												// MDT pointer for that Macro
				while(!MDT.get(i).equalsIgnoreCase("MEND"))
				{
					String splits[] = MDT.get(i).split("\\s+");
					for(int k=0; k<splits.length; k++)
					{
						if(splits[k].contains("(P,"))						// Check for parameter
						{
							splits[k] = splits[k].replaceAll("[^0-9]", "");			// Extract the index of the parameter
							String value = APTAB.get(Integer.parseInt(splits[k]));	// Get value from APTAB
							expanded_file.write(value+"\t");								// Write into expanded_file file
						}
						else
							expanded_file.write(splits[k]+"\t");							// Write as it is
					}
					expanded_file.write("\n");									// Expansion of one line from Macro Definition is done
					i++;													// Increment MDT pointer
				}

				// Clear both AP Tables
				APTAB.clear();
				Inverse_APTAB.clear();
			}
			else								
				expanded_file.write(curr_line+"\n");
		}
	
		// Close respective files
		expanded_file.close();
		MNTF.close();
		MDTF.close();
		KPDTF.close();
		IC.close();
		APT.close();
	}
}
