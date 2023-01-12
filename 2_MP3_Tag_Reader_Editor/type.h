#ifndef TYPES_H
#define TYPES_H

typedef unsigned int uint;

typedef enum
{
    failure,
    success
} Status;

typedef enum
{
    view,
    edit
} OperationType;

typedef enum
{
    TPE1,
    TIT2,
    TALB,
    TYER,
    TCON,
    TCOM
} Tag;
#endif
