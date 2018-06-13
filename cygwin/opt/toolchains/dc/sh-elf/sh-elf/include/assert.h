/*
	assert.h
*/

#ifdef __cplusplus
extern "C" {
#endif

#include "_ansi.h"

#undef assert

#ifdef NDEBUG           /* required by ANSI standard */
# define assert(__e) ((void)0)
#else
# define assert(__e) ((__e) ? (void)0 : __assert (__FILE__, __LINE__, \
						       #__e, (char *)0, __ASSERT_FUNC))

# ifndef __ASSERT_FUNC
  /* Use g++'s demangled names in C++.  */
#  if defined __cplusplus && defined __GNUC__
#   define __ASSERT_FUNC __PRETTY_FUNCTION__

  /* C99 requires the use of __func__.  */
#  elif __STDC_VERSION__ >= 199901L
#   define __ASSERT_FUNC __func__

  /* Older versions of gcc don't have __func__ but can use __FUNCTION__.  */
#  elif __GNUC__ >= 2
#   define __ASSERT_FUNC __FUNCTION__

  /* failed to detect __func__ support.  */
#  else
#   define __ASSERT_FUNC ((char *) 0)
#  endif
# endif /* !__ASSERT_FUNC */
#endif /* !NDEBUG */

void _EXFUN(__assert, (const char *, int, const char *, const char *,
                       const char *) _ATTRIBUTE ((__noreturn__)));

#if __STDC_VERSION__ >= 201112L && !defined __cplusplus
# define static_assert _Static_assert
#endif

#ifdef __cplusplus
}
#endif
