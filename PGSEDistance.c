#include <math.h>
#include "postgres.h"
#include "utils/array.h"

PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(distance_to_bytea);

Datum
distance_to_bytea(PG_FUNCTION_ARGS)
{
    ArrayType *arrL;

    double *al;
    bytea *b1;

    unsigned char *bytesr;
    double ed = 0.0;

    arrL = PG_GETARG_ARRAYTYPE_P(0);
    b1 = PG_GETARG_BYTEA_P(1);

    al = (double *) ARR_DATA_PTR(arrL);
    bytesr = (unsigned char*) VARDATA(b1);

    for(int j = 0; j < 128; j+= 4){
        ed += pow(*(al + j    ) - (((double)*(bytesr + j    )) / 512.0), 2.0);
        ed += pow(*(al + j + 1) - (((double)*(bytesr + j + 1)) / 512.0), 2.0);
        ed += pow(*(al + j + 2) - (((double)*(bytesr + j + 2)) / 512.0), 2.0);
        ed += pow(*(al + j + 3) - (((double)*(bytesr + j + 3)) / 512.0), 2.0);
    }

    //ed = sqrt(ed);

    PG_RETURN_FLOAT8(ed);
}
