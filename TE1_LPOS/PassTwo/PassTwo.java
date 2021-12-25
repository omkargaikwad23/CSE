//Pass2 of 2 pass assembler
//javac --release 8 PassTwo.java
//java PassTwo

//goal: perform lC processing, generate target code file
//Input: LitTab.txt SYMTAB.txt IC.txt
//Output: PassTwo.txt

import java.io.*;
import java.util.*;

class PassTwo {

	public class Line {
		String symbol;
		int address;
		int index;

		public Line(String symbol, int address) {
			super();
			this.symbol = symbol;
			this.address = address;

		}

		public Line(String symbol, int address, int index) {
			super();
			this.symbol = symbol;
			this.address = address;
			this.index = index;

		}

		public int getIndex() {
			return index;
		}

		public void setIndex(int index) {
			this.index = index;
		}

		public String getSymbol() {
			return symbol;
		}

		public void setSymbol(String symbol) {
			this.symbol = symbol;
		}

		public int getAddress() {
			return address;
		}

		public void setAddress(int address) {
			this.address = address;
		}
	}

	ArrayList<Line> sym_tab, lit_table;

	public PassTwo() {
		sym_tab = new ArrayList<>();
		lit_table = new ArrayList<>();
	}

	public static void main(String[] args) {
		PassTwo passTwo = new PassTwo();

		try {
			passTwo.generateCode("IC.txt");
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	// to read from the SymTab and LitTab tables and store it in sym_tab, lit_tab array
	public void readtables() 
	{
		BufferedReader buffer_read;
		String line;
		try {
			buffer_read = new BufferedReader(new FileReader("SYMTAB.txt")); // read symtab
			while ((line = buffer_read.readLine()) != null) {
				String parts[] = line.split("\\s+"); // extract data and add to Line
				sym_tab.add(new Line(parts[1], Integer.parseInt(parts[2]), Integer.parseInt(parts[0])));
			}
			buffer_read.close();
			buffer_read = new BufferedReader(new FileReader("LitTab.txt")); // read LitTab
			while ((line = buffer_read.readLine()) != null) {
				String parts[] = line.split("\\s+");
				lit_table.add(new Line(parts[1], Integer.parseInt(parts[2]), Integer.parseInt(parts[0]))); // extract
				// data and add to Line
			}
			buffer_read.close();
		} catch (Exception e) {
			System.out.println(e.getMessage());
		}
	}

	// (filename: IC.txt)
	public void generateCode(String filename) throws Exception {
		readtables(); // Tokenize and extract data
		BufferedReader buffer_read = new BufferedReader(new FileReader(filename)); // to read filename file lie by line

		BufferedWriter buffer_write = new BufferedWriter(new FileWriter("PassTwo.txt")); // generate pass 2 code
		String line, code;
		while ((line = buffer_read.readLine()) != null) {
			String parts[] = line.split("\\s+");
			// if AD or DS present don't write anything in output
			if (parts[0].contains("AD") || parts[0].contains("DL,02")) 
			{
				buffer_write.write("\n");
				continue;
			} 
			else if (parts.length == 2) {
				if (parts[0].contains("DL")) // Declaration statement
				{
					parts[0] = parts[0].replaceAll("[^0-9]", ""); // extract machine code
					if (Integer.parseInt(parts[0]) == 1) {
						int constant = Integer.parseInt(parts[1].replaceAll("[^0-9]", "")); // extract machine code
						code = "00\t0\t" + String.format("%03d", constant) + "\n";
						buffer_write.write(code);
					}
				} 
				else if (parts[0].contains("IS")) {
					int opcode = Integer.parseInt(parts[0].replaceAll("[^0-9]", "")); // extract machine code

					if (opcode == 10 || opcode == 9) {
						if (parts[1].contains("S")) {
							int symIndex = Integer.parseInt(parts[1].replaceAll("[^0-9]", "")); // extract machine code
							code = String.format("%02d", opcode) + "\t0\t"
									+ String.format("%03d", sym_tab.get(symIndex - 1).getAddress()) + "\n";
							buffer_write.write(code);
						} 
						else if (parts[1].contains("L")) {
							int symIndex = Integer.parseInt(parts[1].replaceAll("[^0-9]", "")); // extract machine code
							code = String.format("%02d", opcode) + "\t0\t"
									+ String.format("%03d", lit_table.get(symIndex - 1).getAddress()) + "\n";
							buffer_write.write(code);
						}

					}
				}
			} else if (parts.length == 1 && parts[0].contains("IS")) {
				int opcode = Integer.parseInt(parts[0].replaceAll("[^0-9]", ""));
				code = String.format("%02d", opcode) + "\t0\t" + String.format("%03d", 0) + "\n";
				buffer_write.write(code);
			} 
			else if (parts[0].contains("IS") && parts.length == 3) // all other instructions
			{
				int opcode = Integer.parseInt(parts[0].replaceAll("[^0-9]", "")); // extract machine code

				int regcode = Integer.parseInt(parts[1]); // extract code for register

				if (parts[2].contains("S")) {
					int symIndex = Integer.parseInt(parts[2].replaceAll("[^0-9]", "")); // get index of sym_tab to be accessed
					code = String.format("%02d", opcode) + "\t" + regcode + "\t"
							+ String.format("%03d", sym_tab.get(symIndex - 1).getAddress()) + "\n";
					buffer_write.write(code);
				} else if (parts[2].contains("L")) {
					int symIndex = Integer.parseInt(parts[2].replaceAll("[^0-9]", "")); // get index of littab to be accessed
					code = String.format("%02d", opcode) + "\t" + regcode + "\t"
							+ String.format("%03d", lit_table.get(symIndex - 1).getAddress()) + "\n";
					buffer_write.write(code);
				}
			}
		}
		buffer_write.close();
		buffer_read.close();
	}
}