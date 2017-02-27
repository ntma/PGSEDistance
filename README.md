## Squared Euclidean Distance in PostgreSQL ##

This a simple C library to compute the squared euclidean distance between SIFT descriptors in a database.

### Dependencies ###

* PostgreSQL

### How to build ###

```
make
make install
```

Make sure you have permissions to install the library in the PostgreSQL library directory. Careful with multiple installations of PostgreSQL since this makefile relies on pg_config.
