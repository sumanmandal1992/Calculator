objects = main.o calculation.o stack.o

calculate : $(objects)
	cc -o calculate $(objects)

main.o : Calculation.h
calculation.o : Stack.h Calculation.h Error.h
stack.o : Stack.h

.PHONY : clean
clean :
	rm $(objects)
