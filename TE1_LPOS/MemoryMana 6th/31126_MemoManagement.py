"""Program for Memory allocation
1) First Fit
2) Best Fit
3) Worst Fit
4) Next Fit"""

class FirstFit:
    def __init__(self):  # The method for taking Input for number of Block and processes
        self.m = int(input("Enter the number of Blocks:"))
        self.n = int(input("Enter the number of Process:"))
        self.block = [-1]*self.m
        self.process = [-1]*self.n
        self.allocation = [-1]*self.n

    def TakeInput(self): # The method for taking Input for the size of block and processes
        print("Enter the Block sizes")
        for i in range(self.m):
            print("Enter the size of Block with block no."+str(i+1)+":",end="")
            a = int(input())
            self.block[i] = a

        print("Enter the size of Processes")
        for j in range(self.n):
            print("Enter the size of P"+str(j+1),":",end="")
            b = int(input())
            self.process[j] = b

        print("*********************************************")
        print(" Empty Blocks with size")
        print("%10s%12s" % ("Block no.", "Block size"))
        for i in range(self.m):
            print("%6d%12d" % (i + 1, self.block[i]))
        print("*********************************************")
        print()

    def Method(self): # Method for First Fit Algorithm
        for i in range(self.n):
            for j in range(self.m):
                if self.process[i]<=self.block[j]:
                    self.allocation[i] = j
                    self.block[j]-=self.process[i]
                    break

    def SetMethod(self): # Method for Next Fit Algorithm
        self.allocation = [-1] * self.n
        j = 0
        for i in range(self.n):
            while j < self.m:
                if self.block[j] >= self.process[i]:
                    self.allocation[i] = j
                    self.block[j] -= self.process[i]
                    break
                j = (j + 1) % self.m

    def ShowOutput(self): # Method for output of the given algorithm
        print("*********************************************")
        print("Processes after allocation")
        print("%11s%14s%12s"%("Process no.","Process size","Block no."))
        for j in range(self.n):
            print("%5d%14d%14d"%(j+1,self.process[j],self.allocation[j]+1))
        print("*********************************************")
        print()

        print("*********************************************")
        print(" After Memory allocation")
        print("%10s%12s" % ("Block no.", "Block size"))
        for i in range(self.m):
            print("%6d%12d" % (i + 1, self.block[i]))
        print("**********************************************")
        print()

class BestFit:
    def __init__(self):# The method for taking Input for number of Block and processes
        self.m = int(input("Enter the number of Blocks:"))
        self.n = int(input("Enter the number of Process:"))
        self.block = [-1]*self.m
        self.process = [-1]*self.n
        self.allocation = [-1]*self.n

    def TakeInput(self):# The method for talking Input for the size of block and processes
        print("Enter the Block sizes")
        for i in range(self.m):
            print("Enter the size of Block with block no."+str(i+1)+":",end="")
            a = int(input())
            self.block[i] = a

        print("Enter the size Of Processes")
        for j in range(self.n):
            print("Enter the size of P"+str(j+1),":",end="")
            b = int(input())
            self.process[j] = b

        print("*********************************************")
        print(" Empty Blocks with size")
        print("%10s%12s" % ("Block no.", "Block size"))
        for i in range(self.m):
            print("%6d%12d" % (i + 1, self.block[i]))
        print("*********************************************")
        print()

    def Method(self):# Method for Best Fit Algorithm
        # minimum block size that can be assigned to current process
        self.allocation = [-1] * self.n
        for i in range(self.n):
            var = -1
            for j in range(self.m):
                if self.block[j] >= self.process[i]:
                    if var == -1:
                        var = j
                    elif self.block[var] > self.block[j]:
                        var = j    #index of min size block greater than process size
            if var != -1:
                self.allocation[i] = var
                self.block[var] -= self.process[i]

    def ShowOutput(self): # Method for output of the given algorithm
        print("*********************************************")
        print("Processes after allocation")
        print("%11s%14s%12s"%("Process no.","Process size","Block no."))
        for j in range(self.n):
            print("%5d%14d%14d"%(j+1,self.process[j],self.allocation[j]+1))
        print("*********************************************")
        print()

        print("*********************************************")
        print(" After Memory allocation")
        print("%10s%12s" % ("Block no.", "Block size"))
        for i in range(self.m):
            print("%6d%12d" % (i + 1, self.block[i]))
        print("**********************************************")
        print()

class WorstFit:
    def __init__(self):# The method for taking Input for number of Block and processes
        self.m = int(input("Enter the number of Blocks:"))
        self.n = int(input("Enter the number of Process:"))
        self.block = [-1]*self.m
        self.process = [-1]*self.n
        self.allocation = [-1]*self.n

    def Input(self):# The method for talking Input for the size of block and processes
        print("Enter the Block sizes")
        for i in range(self.m):
            print("Enter the size of Block with block no."+str(i+1)+":",end="")
            a = int(input())
            self.block[i] = a

        print("Enter the size Of Processes")
        for j in range(self.n):
            print("Enter the size of P"+str(j+1),":",end="")
            b = int(input())
            self.process[j] = b

        print("*********************************************")
        print(" Empty Blocks with size")
        print("%10s%12s" % ("Block no.", "Block size"))
        for i in range(self.m):
            print("%6d%12d" % (i + 1, self.block[i]))
        print("*********************************************")
        print()

    def SetMethod(self):# Method for Worst Fit Algorithm
        self.allocation = [-1] * self.n
        for i in range(self.n):
            var1 = -1
            for j in range(self.m):
                if self.block[j] >= self.process[i]:
                    if var1 == -1:
                        var1 = j
                    elif self.block[var1] < self.block[j]:
                        var1 = j  #index of max size block greater than process size
            if var1 != -1:
                self.allocation[i] = var1
                self.block[var1] -= self.process[i]


    def Output(self):# Method for output of the given algorithm
        print("*********************************************")
        print("Processes after allocation")
        print("%11s%14s%12s"%("Process no.","Process size","Block no."))
        for j in range(self.n):
            print("%5d%14d%14d"%(j+1,self.process[j],self.allocation[j]+1))
        print("*********************************************")
        print()

        print("*********************************************")
        print(" After Memory allocation")
        print("%10s%12s" % ("Block no.", "Block size"))
        for i in range(self.m):
            print("%6d%12d" % (i + 1, self.block[i]))
        print("**********************************************")
        print()
        
while True: # The menu Driven Part for the program
    print("***************Menu******************")
    print("1.First Fit \n2.Best Fit \n3.Worst Fit\n4.Next Fit\n0.For Exit ")
    print("Enter the Choice : ",end="")
    choice = int(input())
    if choice == 0:
        print("Thank You")
        print("*************************************")
        break

    if choice == 1:
        ffalgo = FirstFit()
        ffalgo.TakeInput()
        ffalgo.Method()
        ffalgo.ShowOutput()

    elif choice == 2:
        bfalgo = BestFit()
        bfalgo.TakeInput()
        bfalgo.Method()
        bfalgo.ShowOutput()

    elif choice == 3:
        wfalgo = WorstFit()
        wfalgo.Input()
        wfalgo.SetMethod()
        wfalgo.Output()

    elif choice == 4:
        nfalgo = FirstFit()
        nfalgo.TakeInput()
        nfalgo.SetMethod()
        nfalgo.ShowOutput()

    else:
        print("Enter proper choice")


'''
PS D:\Documents\TE1-SPOS\LPOS coding> python -u "d:\Documents\TE1-SPOS\LPOS coding\MemoryMana\31126_MemoManagement.py"
***************Menu******************
1.First Fit
2.Best Fit
3.Worst Fit
4.Next Fit
0.For Exit
Enter the Choice : 1
Enter the number of Blocks:5
Enter the number of Process:4
Enter the Block sizes
Enter the size of Block with block no.1:100
Enter the size of Block with block no.2:120
Enter the size of Block with block no.3:150
Enter the size of Block with block no.4:190
Enter the size of Block with block no.5:300
Enter the size Of Processes
Enter the size of P1 :70
Enter the size of P2 :230
Enter the size of P3 :80
Enter the size of P4 :170
*********************************************
 Empty Blocks with size
 Block no.  Block size
     1         100
     2         120
     3         150
     4         190
     5         300
*********************************************

*********************************************
Processes after allocation
Process no.  Process size   Block no.        
    1            70             1
    2           230             5
    3            80             2
    4           170             4
*********************************************

*********************************************
 After Memory allocation
 Block no.  Block size
     1          30
     2          40
     3         150
     4          20
     5          70
**********************************************

***************Menu******************
1.First Fit
2.Best Fit
3.Worst Fit
4.Next Fit
0.For Exit
Enter the Choice : 2
Enter the number of Blocks:5
Enter the number of Process:4
Enter the Block sizes
Enter the size of Block with block no.1:100
Enter the size of Block with block no.2:120
Enter the size of Block with block no.3:150
Enter the size of Block with block no.4:190
Enter the size of Block with block no.5:300
Enter the size Of Processes
Enter the size of P1 :70
Enter the size of P2 :230
Enter the size of P3 :80
Enter the size of P4 :170
*********************************************
 Empty Blocks with size
 Block no.  Block size
     1         100
     2         120
     3         150
     4         190
     5         300
*********************************************

*********************************************
Processes after allocation
Process no.  Process size   Block no.
    1            70             1
    2           230             5
    3            80             2
    4           170             4
*********************************************

*********************************************
 After Memory allocation
 Block no.  Block size
     1          30
     2          40
     3         150
     4          20
     5          70
**********************************************

***************Menu******************
1.First Fit
2.Best Fit
3.Worst Fit
4.Next Fit
0.For Exit
Enter the Choice : 3
Enter the number of Blocks:5
Enter the number of Process:4
Enter the Block sizes
Enter the size of Block with block no.1:100
Enter the size of Block with block no.2:120
Enter the size of Block with block no.3:150
Enter the size of Block with block no.4:190
Enter the size of Block with block no.5:300
Enter the size Of Processes
Enter the size of P1 :70
Enter the size of P2 :230
Enter the size of P3 :80
Enter the size of P4 :170
*********************************************
 Empty Blocks with size
 Block no.  Block size
     1         100
     2         120
     3         150
     4         190
     5         300
*********************************************

*********************************************
Processes after allocation
Process no.  Process size   Block no.
    1            70             5
    2           230             5
    3            80             4
    4           170             0
*********************************************

*********************************************
 After Memory allocation
 Block no.  Block size
     1         100
     2         120
     3         150
     4         110
     5           0
**********************************************

***************Menu******************
1.First Fit
2.Best Fit
3.Worst Fit
4.Next Fit
0.For Exit
Enter the Choice : 4
Enter the number of Blocks:5
Enter the number of Process:4
Enter the Block sizes
Enter the size of Block with block no.1:100
Enter the size of Block with block no.2:120
Enter the size of Block with block no.3:150
Enter the size of Block with block no.4:190
Enter the size of Block with block no.5:300
Enter the size Of Processes
Enter the size of P1 :70
Enter the size of P2 :230
Enter the size of P3 :80
Enter the size of P4 :170
*********************************************
 Empty Blocks with size
 Block no.  Block size
     1         100
     2         120
     3         150
     4         190
     5         300
*********************************************

*********************************************
Processes after allocation
Process no.  Process size   Block no.
    1            70             1
    2           230             5
    3            80             2
    4           170             4
*********************************************

*********************************************
 After Memory allocation
 Block no.  Block size
     1          30
     2          40
     3         150
     4          20
     5          70
**********************************************

***************Menu******************
1.First Fit
2.Best Fit
3.Worst Fit
4.Next Fit
0.For Exit
Enter the Choice : 0
Thank You
*************************************
'''