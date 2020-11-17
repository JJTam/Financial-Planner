# Note: the following is just an option to make sure Make won't automatically delete any object files after every build; don't worry about that
.PRECIOUS: %.o 

all: test1 test2 test3

test%: main%.o ledger.o account.o transactions.o expenses.o income.o
	g++ -std=c++11 -o $@ $^ 
# Note: $^ is not covered in lab1. It basically denotes all depended files, i.e., all 6 files "main%.o ledger.o account.o transactions.o expenses.o income.o"

ledger.o: ledger.cpp ledger.h
	g++ -std=c++11 -c $< -o $@ 
    
account.o: account.cpp account.h
	g++ -std=c++11 -c $< -o $@     

transactions.o: transactions.cpp transactions.h
	g++ -std=c++11 -c $< -o $@ 

expenses.o: expenses.cpp expenses.h
	g++ -std=c++11 -c $< -o $@ 

income.o: income.cpp income.h
	g++ -std=c++11 -c $< -o $@

%.o: %.cpp
	g++ -std=c++11 -c $< -o $@ 
# Note: this meta rule (see lab 1) is to generate rules for main1.o, ..., main3.o 

clean:
	del *.o *.exe
# On most Windows, use: del *.o *.exe
# On Linux or MacOS or some Windows (just try which command works for you), use: rm -f *.o *.exe