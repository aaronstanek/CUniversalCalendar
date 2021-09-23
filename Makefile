CUniversalCalendar.so: */*.c */*.h
	gcc -std=c99 -shared -O3 -o CUniversalCalendar.so */*.c
