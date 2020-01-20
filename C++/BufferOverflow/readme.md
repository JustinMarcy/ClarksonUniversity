# simple buffer overflow example

## summary
* a simple example to show a stack buffer overflow
* course: EE 363 (Fall 2017), Clarkson University

## list of files required
* mys.c

## instructions:
* compile: `gcc mys.c -o mys.out`

## notes:
* follow the instructions above to generate the executable `mys.out`
* `mys.out` is a program that intends to do simple password validation; three attempts are allowed
* open `mys.c` to look at the correct password

## normal functioning
* at one of the three attempts,  enter the correct password
* on entering the correct password, the message "Root priviliges granted' is displayed
* on entering the wrong password three times, the message "Multiple login failures; this will be reported." is displayed

## anomalous functioning
* run `mys.out` and enter the wrong password twice
* the third time, enter a wrong password that is very long e.g. asadjkasdnalfnslkjdfnskjdfnskjn234234rjknsldfnskdjfn
	* you will likely observe that there is a segmentation fault; more importantly, you will get the message "Root priviliges granted" which seems to suggest that the wrong password has been accepted 
* note: in one instance on my machine, entering the string "sdfksmldfsasdksalkmdlkndfldlf" after two wrong passwords causes the program to give a privilige granted message, without any segmentation fault

## analysis
* obviously, the most interesting (and worrisome!) thing is why a very long password seems to be accepted, even when it is incorrect
* the reason is that our compilation process has ensured that the compiler doesn't check for buffer stack overflows
* this allows any string entered by the user to be copied into the array `buff`,  even when the string's size exceeds the the capacity of `buff`
* copying of such a large string causes the memory location of the variable `flag` to be overwritten; this is what causes the privilige to be granted even though the 
(long) password string was wrong

## end


