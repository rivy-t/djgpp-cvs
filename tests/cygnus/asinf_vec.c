#include "test.h"
 one_line_type asinf_vec[] = {
{34, 0, 0,__LINE__, 0xbff921fb, 0x60000000, 0xbff00000, 0x00000000, },	/* -1.5708E+00=F(      -1) */
{34, 0, 0,__LINE__, 0xbff7de14, 0x60000000, 0xbfefe666, 0x60000000, },	/* -1.4917E+00=F( -0.9969) */
{34, 0, 0,__LINE__, 0xbff757cb, 0xa0000000, 0xbfefcccc, 0xc0000000, },	/* -1.4589E+00=F( -0.9937) */
{34, 0, 0,__LINE__, 0xbff6f0ac, 0x80000000, 0xbfefb333, 0x20000000, },	/* -1.4338E+00=F( -0.9906) */
{34, 0, 0,__LINE__, 0xbff699ab, 0x60000000, 0xbfef9999, 0x80000000, },	/* -1.4125E+00=F( -0.9875) */
{34, 0, 0,__LINE__, 0xbff64cf5, 0x00000000, 0xbfef7fff, 0xe0000000, },	/* -1.3938E+00=F( -0.9844) */
{34, 0, 0,__LINE__, 0xbff6078c, 0x80000000, 0xbfef6666, 0x40000000, },	/* -1.3768E+00=F( -0.9812) */
{34, 0, 0,__LINE__, 0xbff5c7ab, 0xc0000000, 0xbfef4ccc, 0xa0000000, },	/* -1.3612E+00=F( -0.9781) */
{34, 0, 0,__LINE__, 0xbff58c2a, 0xe0000000, 0xbfef3333, 0x00000000, },	/* -1.3467E+00=F(  -0.975) */
{34, 0, 0,__LINE__, 0xbff5543c, 0xa0000000, 0xbfef1999, 0x60000000, },	/* -1.3331E+00=F( -0.9719) */
{34, 0, 0,__LINE__, 0xbff51f4b, 0x60000000, 0xbfeeffff, 0xc0000000, },	/* -1.3201E+00=F( -0.9687) */
{34, 0, 0,__LINE__, 0xbff4ece6, 0x20000000, 0xbfeee666, 0x20000000, },	/* -1.3078E+00=F( -0.9656) */
{34, 0, 0,__LINE__, 0xbff4bcb5, 0x60000000, 0xbfeecccc, 0x80000000, },	/* -1.2961E+00=F( -0.9625) */
{34, 0, 0,__LINE__, 0xbff48e73, 0x60000000, 0xbfeeb332, 0xe0000000, },	/* -1.2848E+00=F( -0.9594) */
{34, 0, 0,__LINE__, 0xbff461e7, 0xa0000000, 0xbfee9999, 0x40000000, },	/* -1.2739E+00=F( -0.9562) */
{34, 0, 0,__LINE__, 0xbff436e3, 0xa0000000, 0xbfee7fff, 0xa0000000, },	/* -1.2634E+00=F( -0.9531) */
{34, 0, 0,__LINE__, 0xbff10c06, 0x60000000, 0xbfec0000, 0x00000000, },	/* -1.0654E+00=F(  -0.875) */
{34, 0, 0,__LINE__, 0xbfee5985, 0x60000000, 0xbfea0000, 0x00000000, },	/* -9.4843E-01=F( -0.8125) */
{34, 0, 0,__LINE__, 0xbfeb2353, 0x20000000, 0xbfe80000, 0x00000000, },	/* -8.4806E-01=F(   -0.75) */
{34, 0, 0,__LINE__, 0xbfe841de, 0xc0000000, 0xbfe60000, 0x00000000, },	/* -7.5804E-01=F( -0.6875) */
{34, 0, 0,__LINE__, 0xbfe59aad, 0x80000000, 0xbfe40000, 0x00000000, },	/* -6.7513E-01=F(  -0.625) */
{34, 0, 0,__LINE__, 0xbfe31df4, 0x00000000, 0xbfe20000, 0x00000000, },	/* -5.9741E-01=F( -0.5625) */
{34, 0, 0,__LINE__, 0xbfe0c152, 0x40000000, 0xbfe00000, 0x00000000, },	/* -5.2360E-01=F(    -0.5) */
{34, 0, 0,__LINE__, 0xbfe31df4, 0x00000000, 0xbfe20000, 0x00000000, },	/* -5.9741E-01=F( -0.5625) */
{34, 0, 0,__LINE__, 0xbfe1ec23, 0x00000000, 0xbfe10000, 0x00000000, },	/* -5.6008E-01=F( -0.5312) */
{34, 0, 0,__LINE__, 0xbfe0c152, 0x40000000, 0xbfe00000, 0x00000000, },	/* -5.2360E-01=F(    -0.5) */
{34, 0, 0,__LINE__, 0xbfdf3958, 0xa0000000, 0xbfde0000, 0x00000000, },	/* -4.8788E-01=F( -0.4688) */
{34, 0, 0,__LINE__, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },	/* +0.0000E+00=F(      +0) */
{34, 0, 0,__LINE__, 0x3fb002ab, 0xe0000000, 0x3fb00000, 0x00000000, },	/* +6.2541E-02=F( +0.0625) */
{34, 0, 0,__LINE__, 0x3fc00abe, 0x00000000, 0x3fc00000, 0x00000000, },	/* +1.2533E-01=F(  +0.125) */
{34, 0, 0,__LINE__, 0x3fc82494, 0xe0000000, 0x3fc80000, 0x00000000, },	/* +1.8862E-01=F( +0.1875) */
{34, 0, 0,__LINE__, 0x3fd02be9, 0xc0000000, 0x3fd00000, 0x00000000, },	/* +2.5268E-01=F(   +0.25) */
{34, 0, 0,__LINE__, 0x3fd45739, 0x40000000, 0x3fd40000, 0x00000000, },	/* +3.1782E-01=F( +0.3125) */
{34, 0, 0,__LINE__, 0x3fd899f4, 0xe0000000, 0x3fd80000, 0x00000000, },	/* +3.8440E-01=F(  +0.375) */
{34, 0, 0,__LINE__, 0x3fdcfaf2, 0x80000000, 0x3fdc0000, 0x00000000, },	/* +4.5282E-01=F( +0.4375) */
{34, 0, 0,__LINE__, 0x3fe0c152, 0x40000000, 0x3fe00000, 0x00000000, },	/* +5.2360E-01=F(    +0.5) */
{34, 0, 0,__LINE__, 0x3fe1ec23, 0x00000000, 0x3fe10000, 0x00000000, },	/* +5.6008E-01=F( +0.5312) */
{34, 0, 0,__LINE__, 0x3fe31df4, 0x00000000, 0x3fe20000, 0x00000000, },	/* +5.9741E-01=F( +0.5625) */
{34, 0, 0,__LINE__, 0x3fe59aad, 0x80000000, 0x3fe40000, 0x00000000, },	/* +6.7513E-01=F(  +0.625) */
{34, 0, 0,__LINE__, 0x3fe841de, 0xc0000000, 0x3fe60000, 0x00000000, },	/* +7.5804E-01=F( +0.6875) */
{34, 0, 0,__LINE__, 0x3feb2353, 0x20000000, 0x3fe80000, 0x00000000, },	/* +8.4806E-01=F(   +0.75) */
{34, 0, 0,__LINE__, 0x3fee5985, 0x60000000, 0x3fea0000, 0x00000000, },	/* +9.4843E-01=F( +0.8125) */
{34, 0, 0,__LINE__, 0x3ff10c06, 0x60000000, 0x3fec0000, 0x00000000, },	/* +1.0654E+00=F(  +0.875) */
{34, 0, 0,__LINE__, 0x3ff40d41, 0x00000000, 0x3fee6666, 0x60000000, },	/* +1.2532E+00=F(   +0.95) */
{34, 0, 0,__LINE__, 0x3ff436e4, 0x40000000, 0x3fee8000, 0x00000000, },	/* +1.2634E+00=F( +0.9531) */
{34, 0, 0,__LINE__, 0x3ff461e8, 0x40000000, 0x3fee9999, 0xa0000000, },	/* +1.2739E+00=F( +0.9563) */
{34, 0, 0,__LINE__, 0x3ff48e74, 0x00000000, 0x3feeb333, 0x40000000, },	/* +1.2848E+00=F( +0.9594) */
{34, 0, 0,__LINE__, 0x3ff4bcb6, 0x00000000, 0x3feecccc, 0xe0000000, },	/* +1.2961E+00=F( +0.9625) */
{34, 0, 0,__LINE__, 0x3ff4ece6, 0xe0000000, 0x3feee666, 0x80000000, },	/* +1.3078E+00=F( +0.9656) */
{34, 0, 0,__LINE__, 0x3ff64cf5, 0x60000000, 0x3fef8000, 0x00000000, },	/* +1.3938E+00=F( +0.9844) */
{34, 0, 0,__LINE__, 0x3ff721a5, 0xe0000000, 0x3fefc000, 0x00000000, },	/* +1.4457E+00=F( +0.9922) */
{34, 0, 0,__LINE__, 0x3ff921fb, 0x60000000, 0x3ff00000, 0x00000000, },	/* +1.5708E+00=F(      +1) */
{34, 1, 0,__LINE__, 0x7ff80000, 0x00000000, 0xbff19999, 0xa0000000, },	/* +NaN       =F(    -1.1) */
{34, 1, 0,__LINE__, 0x7ff80000, 0x00000000, 0x3ff19999, 0xa0000000, },	/* +NaN       =F(    +1.1) */
{34, 0, 0,__LINE__, 0x7ff80000, 0x00000000, 0x7ff80000, 0x00000000, },	/* +NaN       =F(    +NaN) */
{34, 1, 0,__LINE__, 0x7ff80000, 0x00000000, 0x7ff00000, 0x00000000, },	/* +NaN       =F(    +Inf) */
{34, 0, 0,__LINE__, 0x3ff92091, 0x40000000, 0x3fefffff, 0xe0000000, },	/* +1.5705E+00=F(      +1) */
0,};
void
test_asinf(int m)	{ run_vector_1(m, asinf_vec,(char *)(asinf),"asinf","ff");}