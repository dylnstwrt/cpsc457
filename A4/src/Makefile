all: deadlock.o testdeadlock verify

deadlock.o:
	g++ -O2 deadlock.cpp -o deadlock

testdeadlock:
	time ./deadlock < deadlock-input.txt > output.txt

verify:
	diff deadlock-output.txt output.txt