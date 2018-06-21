all: application


INCLUDE=/usr/include
# LIBS=gdbm
# On some distrbutions you may need to change the above line to include 
# the compatability you may need to change the above line to include 
LIBS= -lgdbm_compat -lgdbm
CFLAGS=
api_ui.o: api_ui.c cd_data.h
	gcc $(CFLAGS) -c api_ui.c

access.o: access.c cd_data.h
	gcc $(CFLAGS) -I$(INCLUDE) -c access.c

application: api_ui.o access.o
	gcc $(CFLAGS) -o application api_ui.o access.o $(LIBS)


clean:
	rm -f application *.o

nodbmfiles:
	rm -f	*.dir *.pag 
