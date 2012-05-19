/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */


#ifndef EFL_CONFIG_H__
#define EFL_CONFIG_H__


/* Define to one of `_getb67', `GETB67', `getb67' for Cray-2 and Cray-YMP
   systems. This function is required for `alloca.c' support on those systems.
   */
/* #undef CRAY_STACKSEG_END */

/* Define to 1 if using `alloca.c'. */
/* #undef C_ALLOCA */

/* support old eet file format */
#define EET_OLD_EET_FILE_FORMAT 1

/* use gnutls_x509_crt_verify_hash */
/* #undef EET_USE_NEW_GNUTLS_API */

/* Define to 1 if you have `alloca', as a function or macro. */
#define HAVE_ALLOCA 1

/* Define to 1 if you have <alloca.h> and it should be used (not on Ultrix).
   */
#define HAVE_ALLOCA_H 1

/* Have cipher support built in eet */
/* #undef HAVE_CIPHER */

/* Define to 1 if you have the <dlfcn.h> header file. */
/* #undef HAVE_DLFCN_H */

/* Set to 1 if Evil library is installed */
/* #undef HAVE_EVIL */

/* Define to 1 if you have the `fmemopen' function. */
#define HAVE_FMEMOPEN 1

/* Have Gnutls support */
/* #undef HAVE_GNUTLS */

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the <memory.h> header file. */
/* #undef HAVE_MEMORY_H */

/* Define to 1 if you have the <netinet/in.h> header file. */
#define HAVE_NETINET_IN_H 1

/* Have Openssl support */
/* #undef HAVE_OPENSSL */

/* Define to 1 if you have the `open_memstream' function. */
#define HAVE_OPEN_MEMSTREAM 1

/* Define to 1 if you have the `realpath' function. */
/* #undef HAVE_REALPATH */

/* Have signature support for eet file */
/* #undef HAVE_SIGNATURE */

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if your compiler has __attribute__ */
#define HAVE___ATTRIBUTE__ 1

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
#define LT_OBJDIR ".libs/"

/* Define to 1 if your C compiler doesn't accept -c and -o together. */
/* #undef NO_MINUS_C_MINUS_O */

/* Name of package */
#define PACKAGE "eet"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "enlightenment-devel@lists.sourceforge.net"

/* Define to the full name of this package. */
#define PACKAGE_NAME "eet"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "eet 1.5.99.esportato"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "eet"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "1.5.99.esportato"

/* default value since PATH_MAX is not defined */
#define PATH_MAX 4096

/* If using the C implementation of alloca, define if you know the
   direction of stack growth for your system; otherwise it will be
   automatically deduced at runtime.
	STACK_DIRECTION > 0 => grows toward higher addresses
	STACK_DIRECTION < 0 => grows toward lower addresses
	STACK_DIRECTION = 0 => direction of growth unknown */
/* #undef STACK_DIRECTION */

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Version number of package */
#define VERSION "1.5.99.esportato"

/* Major version */
#define VMAJ 1

/* Micro version */
#define VMIC 99

/* Minor version */
#define VMIN 5

/* Revison */
#define VREV esportato

/* Enable GNU extensions */
#define _GNU_SOURCE /**/

/* Macro declaring a function argument to be unused */
#define __UNUSED__ __attribute__((unused))

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

/* Define to `__inline__' or `__inline' if that's what the C compiler
   calls it, or to nothing if 'inline' is not supported under any name.  */
#ifndef __cplusplus
/* #undef inline */
#endif


#endif /* EFL_CONFIG_H__ */
