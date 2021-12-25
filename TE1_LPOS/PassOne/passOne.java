// To design and implement Pass-1 of a Two pass assembler
//cd PassOne
//javac --release 8 PassOne.java
//java PassOne

import java.io.*;

class PassOne {

    public static void main(String args[]) throws Exception {

		// Variables to keep track of indices in the tables
		int line_count = 0, LC = 0, symTabLine = 0, opTabLine = 0, litTabLine = 0, poolTabLine = 0;
		
		// To read Machine code from text file line by line
		FileReader FP = new FileReader("input2.txt");
		BufferedReader bufferedReader = new BufferedReader(FP);

		// line represents the current line which will be read
		String line = null;
		
		final int MAX = 200;

		// data structures, storing in Table as 2-d Arrays
		String SymbolTab[][] = new String[MAX][3];
		String OpTab[][] = new String[MAX][3];
		String LitTab[][] = new String[MAX][2];
		int PoolTab[] = new int[MAX];

		System.out.println("Reading the Assembly Code\n");
		while ((line = bufferedReader.readLine()) != null) {
			String[] tokens = line.split("\t");					// Tokenizing input file
			if (line_count == 0) {
				for (int i = 0; i < tokens.length; i++)
					System.out.print(tokens[i] + "\t");
				System.out.print("\n");
				if(tokens[1]!="") LC = Integer.parseInt(tokens[1]);
			} 
			else {
				for (int i = 0; i < tokens.length; i++)
					System.out.print(tokens[i] + "\t");

				// Symbol table (symbol, address, length)
				System.out.println("");
				if (!tokens[0].equals("")) {

					SymbolTab[symTabLine][0] = tokens[0];
					SymbolTab[symTabLine][1] = Integer.toString(LC);
					SymbolTab[symTabLine][2] = Integer.toString(1);
					symTabLine++;
				} 
				else if (tokens[1].equalsIgnoreCase("DS") || tokens[1].equalsIgnoreCase("DC")) {
					SymbolTab[symTabLine][0] = tokens[0];
					SymbolTab[symTabLine][1] = Integer.toString(LC);
					SymbolTab[symTabLine][2] = Integer.toString(1);
					symTabLine++;
				}
				
				// Literal Table (Provides address of each literal)
				if (tokens.length == 3 && tokens[2].charAt(0) == '=') {
					LitTab[litTabLine][0] = tokens[2];
					LitTab[litTabLine][1] = Integer.toString(LC);
					litTabLine++;
				}
				
				// Mnemonic Table (Stores mnemonics along with it's class and info)
				else if (tokens[1] != null) {
					OpTab[opTabLine][0] = tokens[1];

					if (tokens[1].equalsIgnoreCase("START") || tokens[1].equalsIgnoreCase("END")
							|| tokens[1].equalsIgnoreCase("ORIGIN") || tokens[1].equalsIgnoreCase("EQU")
							|| tokens[1].equalsIgnoreCase("LTORG")) // if Assembler Directive
					{
						OpTab[opTabLine][1] = "AD";			// AD is assembly directive
						OpTab[opTabLine][2] = "R11";
					} else if (tokens[1].equalsIgnoreCase("DS") || tokens[1].equalsIgnoreCase("DC")) {
						OpTab[opTabLine][1] = "DL";			// DL: Declarative Statement, DS: Declare Storage, DC: Declare Constant
						OpTab[opTabLine][2] = "R7";
					} else {
						OpTab[opTabLine][1] = "IS";			// IS: Imperative Statement
						OpTab[opTabLine][2] = "(04,1)";
					}
					opTabLine++;
				}
			}
			line_count++;
			LC++;
		}
		
		// Printing tables
		System.out.println("----------------------All Tables----------------------");

		System.out.println("\n\n	SYMBOL TABLE		");
		System.out.println("--------------------------");
		System.out.println("SYMBOL\tADDRESS\tLENGTH");
		System.out.println("--------------------------");
		for (int i = 0; i < symTabLine; i++)
			System.out.println(SymbolTab[i][0] + "\t" + SymbolTab[i][1] + "\t" + SymbolTab[i][2]);
		System.out.println("--------------------------");

		System.out.println("\n\n	OPCODE TABLE		");
		System.out.println("----------------------------");
		System.out.println("MNEMONIC\tCLASS\tINFO");
		System.out.println("----------------------------");
		for (int i = 0; i < opTabLine; i++)
			System.out.println(OpTab[i][0] + "\t\t" + OpTab[i][1] + "\t" + OpTab[i][2]);
		System.out.println("----------------------------");

		System.out.println("\n\n   LITERAL TABLE		");
		System.out.println("-----------------");
		System.out.println("LITERAL\tADDRESS");
		System.out.println("-----------------");
		for (int i = 0; i < litTabLine; i++)
			System.out.println(LitTab[i][0] + "\t" + LitTab[i][1]);
		System.out.println("------------------");

		for (int i = 0; i < litTabLine; i++) {
			if (LitTab[i][0] != null && LitTab[i + 1][0] != null) // if literals are present
			{
				if (i == 0) {
					PoolTab[poolTabLine] = i + 1;
					poolTabLine++;
				} else if (Integer.parseInt(LitTab[i][1]) < (Integer.parseInt(LitTab[i + 1][1])) - 1) {
					PoolTab[poolTabLine] = i + 2;
					poolTabLine++;
				}
			}
		}
		
		// Print the pool Table
		System.out.println("\n\n   POOL TABLE		");
		System.out.println("-----------------");
		System.out.println("LITERAL NUMBER");
		System.out.println("-----------------");
		for (int i = 0; i < poolTabLine; i++)
			System.out.println(PoolTab[i]);
		System.out.println("------------------");

		bufferedReader.close();
	}
}



// Reading the Assembly Code!!!

// START   100
//         READ    A   
// LABLE   MOVER   A,B 
//         LTORG       
//                 ='2'
//                 ='1'
//                 ='5'
//                 ='7'
//         MOVEM   A,B
//         LTORG
//                 ='2'
// LOOP    READ    B
// A       DS      1
// B       DC      '1'
//                 ='1'
//         END
// ----------------------All Tables----------------------


//         SYMBOL TABLE
// --------------------------
// SYMBOL  ADDRESS LENGTH
// --------------------------
// LABLE   2       1
// LOOP    11      1
// A       12      1
// B       13      1
// --------------------------


//         OPCODE TABLE
// ----------------------------
// MNEMONIC        CLASS   INFO
// ----------------------------
// READ            IS      (04,1)
// MOVER           IS      (04,1)
// LTORG           AD      R11
// MOVEM           IS      (04,1)
// LTORG           AD      R11
// READ            IS      (04,1)
// DS              DL      R7
// DC              DL      R7
// END             AD      R11
// ----------------------------


//    LITERAL TABLE
// -----------------
// LITERAL ADDRESS
// -----------------
// ='2'    4
// ='1'    5
// ='5'    6
// ='7'    7
// ='2'    10
// ='1'    14
// ------------------


//    POOL TABLE
// -----------------
// LITERAL NUMBER
// -----------------
// 1
// 5
// 6
// ------------------