  
    CC     = gcc -std=c11 -g 
    CFLAGS = -Wall \
	  		 -Wbad-function-cast \
			 -Wmissing-prototypes \
	  		 -Wnested-externs
    LFLAGS =

      PROG = escalona
      OBJS = grafos.o \
	  		 transacoes.o \
             $(PROG).o

.PHONY: limpa faxina clean distclean purge all

%.o: %.c %.h utils.h
	$(CC) -c $(CFLAGS) $<

$(PROG):  $(OBJS)
	$(CC) -o $@ $^ $(LFLAGS)

clean:
	@rm -f *~ *.bak

purge:   clean
	@rm -f *.o core a.out
	@rm -f $(PROG)