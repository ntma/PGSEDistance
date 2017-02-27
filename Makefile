MODULES = PGSEDistance

PG_CONFIG = pg_config
PGXS = $(shell $(PG_CONFIG) --pgxs)
INCLUDEDIR = $(shell $(PG_CONFIG) --includedir-server)
include $(PGXS)

PGSEDistance.so: PGSEDistance.o
	gcc -shared -o PGSEDistance.so PGSEDistance.o

PGSEDistance.o: PGSEDistance.c
	gcc -o PGSEDistance.o -c -fPIC -Wall PGSEDistance.c $(CFLAGS) -I$(INCLUDEDIR)
