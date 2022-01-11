#ifndef _STDINT_H
#define _STDINT_H

#ifndef _SIGNED_INTS
#define _SIGNED_INTS
typedef signed char                 int8_t;
typedef short int                   int16_t;
typedef int                         int32_t;
typedef long long int               int64_t;  // this is set for 64 bit system currently. long int is 8 bits on 32 bit machines
#endif

#ifndef _UNSIGNED_INTS
#define _UNSIGNED_INTS
typedef unsigned char               uint8_t;
typedef unsigned short int          uint16_t;
typedef unsigned int                uint32_t;
typedef unsigned long long int      uint64_t;  // this is set for 64 bit system currently. long int is 8 bits on 32 bit machines
#endif


#endif