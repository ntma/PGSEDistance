#include <math.h>
#include "postgres.h"
#include "utils/array.h"
#include "catalog/pg_type.h"

PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(sed_float_to_bytea);

Datum
sed_float_to_bytea(PG_FUNCTION_ARGS)
{
    ArrayType *arrL;

    float *al;
    bytea *b1;

    unsigned char *bytesr;
    float ed = 0.0;

    arrL = PG_GETARG_ARRAYTYPE_P(0);
    b1 = PG_GETARG_BYTEA_P(1);

    al = (float *) ARR_DATA_PTR(arrL);
    bytesr = (unsigned char*) VARDATA(b1);

    for(int j = 0; j < 128; j+= 4){
        ed += powf(*(al + j    ) - (((float)*(bytesr + j    )) / 512.0), 2.0);
        ed += powf(*(al + j + 1) - (((float)*(bytesr + j + 1)) / 512.0), 2.0);
        ed += powf(*(al + j + 2) - (((float)*(bytesr + j + 2)) / 512.0), 2.0);
        ed += powf(*(al + j + 3) - (((float)*(bytesr + j + 3)) / 512.0), 2.0);
    }

    //ed = sqrt(ed);

    PG_RETURN_FLOAT4(ed);
}

PG_FUNCTION_INFO_V1(sed_int_to_bytea);

Datum
sed_int_to_bytea(PG_FUNCTION_ARGS)
{
    ArrayType *arrL;

    int *al;
    bytea *b1;

    unsigned char *bytesr;
    int ed = 0;

    arrL = PG_GETARG_ARRAYTYPE_P(0);
    b1 = PG_GETARG_BYTEA_P(1);

    al = (int *) ARR_DATA_PTR(arrL);
    bytesr = (unsigned char*) VARDATA(b1);

    for(int j = 0; j < 128; j+= 4){
        ed += pow(*(al + j    ) - ((int)*(bytesr + j    )), 2);
        ed += pow(*(al + j + 1) - ((int)*(bytesr + j + 1)), 2);
        ed += pow(*(al + j + 2) - ((int)*(bytesr + j + 2)), 2);
        ed += pow(*(al + j + 3) - ((int)*(bytesr + j + 3)), 2);
    }

    //ed = sqrt(ed);

    PG_RETURN_INT32((int) ed);
}

PG_FUNCTION_INFO_V1(bytea_to_int128);

Datum
bytea_to_int128(PG_FUNCTION_ARGS)
{
    bytea *b;
    unsigned char *bytesr;
    Datum *d;
    size_t size = 128;
    ArrayType *out_array;

    b = PG_GETARG_BYTEA_P(0);

    bytesr = (unsigned char*) VARDATA(b);

    d = (Datum *) palloc(sizeof(Datum) * size);

    for(int j = 0; j < 128; j++){
        d[j] = ((int)*(bytesr + j));
    }

    out_array = construct_array(d, size, INT4OID, sizeof(int), true, 'i');

    PG_RETURN_ARRAYTYPE_P(out_array);
}