#ifndef cdll_h_included
#define cdll_h_included

/* 
 * When building the DLL code, you should define BUILDING_DLL so that
 * the variables/functions are exported correctly. When using the DLL,
 * do NOT define BUILDING_DLL, and then the variables/functions will
 * be imported correctly.
 *
 * You need to be using egcs-1.1.1 or newer.
 *
 * Building the DLL:
 *  - define BUILDING_DLL, which defines DLLIMPORT __attribute__((dllexport))
 * Building the client code:
 *  - DO NOT define BUILDING_DLL, which defines DLLIMPORT to be one 
 *    __attribute__((dllimport))
 */

#if BUILDING_DLL
# define DLLIMPORT __declspec (dllexport)
#else /* Not BUILDING_DLL */
# define DLLIMPORT __declspec (dllimport)
#endif /* Not BUILDING_DLL */

DLLIMPORT int dll_int_square (int) ;
DLLIMPORT double dll_double_square (double);
DLLIMPORT float dll_float_square (float);

DLLIMPORT int dll_global_int_var;

DLLIMPORT void dll_set_global_int_var (int);
DLLIMPORT int dll_get_global_int_var ();

#endif /* cdll_h_included */

