// Name: Omkar Gaikwad
// Roll No: 31126
// javac --release 8 pass1.java
// java pass1

//input: macro1.txt
//output: MNT, MDT, KPDT, PNTAB
// IC.txt is empty because macro is not called

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.Iterator;
import java.util.LinkedHashMap;

public class pass1 {
    public static void main(String[] args) throws Exception {

        BufferedReader br = new BufferedReader(new FileReader("macro1.txt"));

        FileWriter MNT = new FileWriter("MNT.txt"); // Macro Name Table
        FileWriter MDT = new FileWriter("MDT.txt"); // Macro Definition Table(index, label, opcode, operands)
        FileWriter KPDT = new FileWriter("KPDT.txt"); // Keyword Parameter Default Table
        FileWriter PNT = new FileWriter("PNTAB.txt"); // Parameter Name Table
        FileWriter INTER = new FileWriter("IC.txt"); // Intermediate Code File

        LinkedHashMap<String, Integer> pntab = new LinkedHashMap<>();
        String curr_line;  // To read each curr_line 
        String macro_name = null;
        int mdtp = 1, kpdtp = 0, param_no = 1, pp = 0, kp = 0, flag = 0; // Pointers to access table rows

        while ((curr_line = br.readLine()) != null) {
            String tokens[] = curr_line.split("\\s+");
            if (tokens[0].equalsIgnoreCase("MACRO")) // If token is MACRO
            {
                flag = 1; // Macro definition is found
                curr_line = br.readLine();  // Read next curr_line
                tokens = curr_line.split("\\s+"); // Split whitespaces
                macro_name = tokens[0]; // First token is the name of the macro
                if (tokens.length <= 1) //case: Macro without any parameters
                {
                    MNT.write(tokens[0] + "\t" + pp + "\t" + kp + "\t" + mdtp + "\t" + (kp == 0 ? kpdtp : (kpdtp + 1))
                            + "\n"); // Add entry in MNT and continue with next curr_line
                    continue;
                }
                for (int i = 1; i < tokens.length; i++) // Macro with positional and keyword parameters
                {
                    tokens[i] = tokens[i].replaceAll("[&,]", ""); // Replace '&' and ',' with empty character
                    if (tokens[i].contains("=")) // If token contains '=', then it is keyword parameter
                    {
                        kp++;    // Increment counter of Keyword Parameters
                        String keyword_param[] = tokens[i].split("=");   // Split keyword parameter
                        pntab.put(keyword_param[0], param_no++);
                        if (keyword_param.length == 2)
                            KPDT.write(keyword_param[0] + "\t" + keyword_param[1] + "\n");
                        else // KP without default value
                            KPDT.write(keyword_param[0] + "\t-\n");
                    } else // Else it is a positional parameter
                    {
                        pntab.put(tokens[i], param_no++);
                        pp++;
                    }
                }
                MNT.write(tokens[0] + "\t" + pp + "\t" + kp + "\t" + mdtp + "\t" + (kp == 0 ? kpdtp : (kpdtp + 1))
                        + "\n"); // Add corresponding data in MNT
                kpdtp = kpdtp + kp;
            } else if (tokens[0].equalsIgnoreCase("MEND")) // Process MEND statement
            {
                MDT.write(curr_line + "\n"); // Add entry to the MDT and reset all pointers
                flag = kp = pp = 0;
                mdtp++;
                param_no = 1;
                PNT.write(macro_name + ":\t"); // Store macro_name in PNT
                Iterator<String> itr = pntab.keySet().iterator();
                while (itr.hasNext())
                    PNT.write(itr.next() + "\t");
                PNT.write("\n");
                pntab.clear();  // Clear PNT table
            } else if (flag == 1) // Process definition of Macro
            {
                for (int i = 0; i < tokens.length; i++) // Loop through tokens
                {
                    if (tokens[i].contains("&")) // Find occurrence of '&'
                    {
                        tokens[i] = tokens[i].replaceAll("[&,]", ""); // Replace '&' and ',' with empty character
                        MDT.write("(P," + pntab.get(tokens[i]) + ")\t"); // Write into MDT file
                    } else
                        MDT.write(tokens[i] + "\t"); // Write token as it is to MDT file
                }
                MDT.write("\n");
                mdtp++; // Increment MDT pointer
            } else
                INTER.write(curr_line + "\n"); // Process statements other than Macro Definitions here
        }

        br.close();
        MDT.close();
        MNT.close();
        INTER.close();
        PNT.close();
        KPDT.close();
    }
}
