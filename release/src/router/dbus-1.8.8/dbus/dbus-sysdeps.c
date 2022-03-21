/* -*- mode: C; c-file-style: "gnu"; indent-tabs-mode: nil; -*- */
/* dbus-sysdeps.c Wrappers around system/libc features shared between UNIX and Windows (internal to D-Bus implementation)
 * 
 * Copyright (C) 2002, 2003, 2006  Red Hat, Inc.
 * Copyright (C) 2003 CodeFactory AB
 *
 * Licensed under the Academic Free License version 2.1
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include <config.h>
#include "dbus-internals.h"
#include "dbus-sysdeps.h"
#include "dbus-threads.h"
#include "dbus-protocol.h"
#include "dbus-string.h"
#include "dbus-list.h"
#include "dbus-misc.h"

/* NOTE: If you include any unix/windows-specific headers here, you are probably doing something
 * wrong and should be putting some code in dbus-sysdeps-unix.c or dbus-sysdeps-win.c.
 *
 * These are the standard ANSI C headers...
 */
#if HAVE_LOCALE_H
#include <locale.h>
#endif
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifdef HAVE_ERRNO_H
#include <errno.h>
#endif

#ifdef DBUS_WIN
  #include <stdlib.h>
#elif (defined __APPLE__)
# include <crt_externs.h>
# define environ (*_NSGetEnviron())
#else
extern char **environ;
#endif

/**
 * @defgroup DBusSysdeps Internal system-dependent API
 * @ingroup DBusInternals
 * @brief Internal system-dependent API available on UNIX and Windows
 *
 * The system-dependent API has a dual purpose. First, it encapsulates
 * all usage of operating system APIs for ease of auditing and to
 * avoid cluttering the rest of the code with bizarre OS quirks and
 * headers. Second, it abstracts different operating system APIs for
 * portability.
 * 
 * @{
 */

/**
 * Aborts the program with SIGABRT (dumping core).
 */
void
_dbus_abort (void)
{
  const char *s;
  
  _dbus_print_backtrace ();
  
  s = _dbus_getenv ("DBUS_BLOCK_ON_ABORT");
  if (s && *s)
    {
      /* don't use _dbus_warn here since it can _dbus_abort() */
      fprintf (stderr, "  Process %lu sleeping for gdb attach\n", _dbus_pid_for_log ());
      _dbus_sleep_milliseconds (1000 * 180);
    }
  
  abort ();
  _dbus_exit (1); /* in case someone manages to ignore SIGABRT ? */
}

/**
 * @ingroup DBusMisc
 *
 * Wrapper for setenv(). If the value is #NULL, unsets
 * the environment variable.
 *
 * There is an unfixable memleak in that it is unsafe to
 * free memory malloced for use with setenv. This is because
 * we can not rely on internal implementation details of
 * the underlying libc library.
 *
 * This function is not thread-safe, because altering the environment
 * in Unix is not thread-safe in general.
 *
 * @param varname name of environment variable
 * @param value value of environment variable, or #NULL to unset
 * @returns #TRUE on success, #FALSE if not enough memory.
 */
dbus_bool_t
dbus_setenv (const char *varname,
             const char *value)
{
  _dbus_assert (varname != NULL);
  
  if (value == NULL)
    {
#ifdef HAVE_UNSETENV
      unsetenv (varname);
      return TRUE;
#else
      char *putenv_value;
      size_t len;

      len = strlen (varname);

      /* Use system malloc to avoid memleaks that dbus_malloc
       * will get upset about.
       */
      
      putenv_value = malloc (len + 2);
      if (putenv_value == NULL)
        return FALSE;

      strcpy (putenv_value, varname);
#if defined(DBUS_WIN)
      strcat (putenv_value, "=");
#endif
      
      return (putenv (putenv_value) == 0);
#endif
    }
  else
    {
#ifdef HAVE_SETENV
      return (setenv (varname, value, TRUE) == 0);
#else
      char *putenv_value;
      size_t len;
      size_t varname_len;
      size_t value_len;

      varname_len = strlen (varname);
      value_len = strlen (value);
      
      len = varname_len + value_len + 1 /* '=' */ ;

      /* Use system malloc to avoid memleaks that dbus_malloc
       * will get upset about.
       */
      
      putenv_value = malloc (len + 1);
      if (putenv_value == NULL)
        return FALSE;

      strcpy (putenv_value, varname);
      strcpy (putenv_value + varname_len, "=");
      strcpy (putenv_value + varname_len + 1, value);
      
      return (putenv (putenv_value) == 0);
#endif
    }
}

/**
 * Wrapper for getenv().
 *
 * @param varname name of environment variable
 * @returns value of environment variable or #NULL if unset
 */
const char*
_dbus_getenv (const char *varname)
{  
  /* Don't respect any environment variables if the current process is
   * setuid.  This is the equivalent of glibc's __secure_getenv().
   */
  if (_dbus_check_setuid ())
    return NULL;
  return getenv (varname);
}

/**
 * Wrapper for clearenv().
 *
 * @returns #TRUE on success.
 */
dbus_bool_t
_dbus_clearenv (void)
{
  dbus_bool_t rc = TRUE;

#ifdef HAVE_CLEARENV
  if (clearenv () != 0)
     rc = FALSE;
#else

  if (environ != NULL)
    environ[0] = NULL;
#endif

  return rc;
}

/**
 * Split paths into a list of char strings
 * 
 * @param dirs string with pathes 
 * @param suffix string concated to each path in dirs
 * @param dir_list contains a list of splitted pathes
 * return #TRUE is pathes could be splittes,#FALSE in oom case 
 */
dbus_bool_t
_dbus_split_paths_and_append (DBusString *dirs, 
                              const char *suffix, 
                              DBusList  **dir_list)
{
   int start;
   int i;
   int len;
   char *cpath;
   DBusString file_suffix;

   start = 0;
   i = 0;

   _dbus_string_init_const (&file_suffix, suffix);

   len = _dbus_string_get_length (dirs);

   while (_dbus_string_find (dirs, start, _DBUS_PATH_SEPARATOR, &i))
     {
       DBusString path;

       if (!_dbus_string_init (&path))
          goto oom;

       if (!_dbus_string_copy_len (dirs,
                                   start,
                                   i - start,
                                   &path,
                                   0))
          {
            _dbus_string_free (&path);
            goto oom;
          }

        _dbus_string_chop_white (&path);

        /* check for an empty path */
        if (_dbus_string_get_length (&path) == 0)
          goto next;

        if (!_dbus_concat_dir_and_file (&path,
                                        &file_suffix))
          {
            _dbus_string_free (&path);
            goto oom;
          }

        if (!_dbus_string_copy_data(&path, &cpath))
          {
            _dbus_string_free (&path);
            goto oom;
          }

        if (!_dbus_list_append (dir_list, cpath))
          {
            _dbus_string_free (&path);              
            dbus_free (cpath);
            goto oom;
          }

       next:
        _dbus_string_free (&path);
        start = i + 1;
    } 
      
  if (start != len)
    { 
      DBusString path;

      if (!_dbus_string_init (&path))
        goto oom;

      if (!_dbus_string_copy_len (dirs,
                                  start,
                                  len - start,
                                  &path,
                                  0))
        {
          _dbus_string_free (&path);
          goto oom;
        }

      if (!_dbus_concat_dir_and_file (&path,
                                      &file_suffix))
        {
          _dbus_string_free (&path);
          goto oom;
        }

      if (!_dbus_string_copy_data(&path, &cpath))
        {
          _dbus_string_free (&path);
          goto oom;
        }

      if (!_dbus_list_append (dir_list, cpath))
        {
          _dbus_string_free (&path);              
          dbus_free (cpath);
          goto oom;
        }

      _dbus_string_free (&path); 
    }

  return TRUE;

 oom:
  _dbus_list_foreach (dir_list, (DBusForeachFunction)dbus_free, NULL); 
  _dbus_list_clear (dir_list);
  return FALSE;
}

/** @} */

/**
 * @addtogroup DBusString
 *
 * @{
 */
/**
 * Appends an integer to a DBusString.
 * 
 * @param str the string
 * @param value the integer value
 * @returns #FALSE if not enough memory or other failure.
 */
dbus_bool_t
_dbus_string_append_int (DBusString *str,
                         long        value)
{
  /* this calculation is from comp.lang.c faq */
#define MAX_LONG_LEN ((sizeof (long) * 8 + 2) / 3 + 1)  /* +1 for '-' */
  int orig_len;
  int i;
  char *buf;
  
  orig_len = _dbus_string_get_length (str);

  if (!_dbus_string_lengthen (str, MAX_LONG_LEN))
    return FALSE;

  buf = _dbus_string_get_data_len (str, orig_len, MAX_LONG_LEN);

  snprintf (buf, MAX_LONG_LEN, "%ld", value);

  i = 0;
  while (*buf)
    {
      ++buf;
      ++i;
    }
  
  _dbus_string_shorten (str, MAX_LONG_LEN - i);
  
  return TRUE;
}

/**
 * Appends an unsigned integer to a DBusString.
 * 
 * @param str the string
 * @param value the integer value
 * @returns #FALSE if not enough memory or other failure.
 */
dbus_bool_t
_dbus_string_append_uint (DBusString    *str,
                          unsigned long  value)
{
  /* this is wrong, but definitely on the high side. */
#define MAX_ULONG_LEN (MAX_LONG_LEN * 2)
  int orig_len;
  int i;
  char *buf;
  
  orig_len = _dbus_string_get_length (str);

  if (!_dbus_string_lengthen (str, MAX_ULONG_LEN))
    return FALSE;

  buf = _dbus_string_get_data_len (str, orig_len, MAX_ULONG_LEN);

  snprintf (buf, MAX_ULONG_LEN, "%lu", value);

  i = 0;
  while (*buf)
    {
      ++buf;
      ++i;
    }
  
  _dbus_string_shorten (str, MAX_ULONG_LEN - i);
  
  return TRUE;
}

/**
 * Parses an integer contained in a DBusString. Either return parameter
 * may be #NULL if you aren't interested in it. The integer is parsed
 * and stored in value_return. Return parameters are not initialized
 * if the function returns #FALSE.
 *
 * @param str the string
 * @param start the byte index of the start of the integer
 * @param value_return return location of the integer value or #NULL
 * @param end_return return location of the end of the integer, or #NULL
 * @returns #TRUE on success
 */
dbus_bool_t
_dbus_string_parse_int (const DBusString *str,
                        int               start,
                        long             *value_return,
                        int              *end_return)
{
  long v;
  const char *p;
  char *end;

  p = _dbus_string_get_const_data_len (str, start,
                                       _dbus_string_get_length (str) - start);

  end = NULL;
  _dbus_set_errno_to_zero ();
  v = strtol (p, &end, 0);
  if (end == NULL || end == p || errno != 0)
    return FALSE;

  if (value_return)
    *value_return = v;
  if (end_return)
    *end_return = start + (end - p);

  return TRUE;
}

/**
 * Parses an unsigned integer contained in a DBusString. Either return
 * parameter may be #NULL if you aren't interested in it. The integer
 * is parsed and stored in value_return. Return parameters are not
 * initialized if the function returns #FALSE.
 *
 * @param str the string
 * @param start the byte index of the start of the integer
 * @param value_return return location of the integer value or #NULL
 * @param end_return return location of the end of the integer, or #NULL
 * @returns #TRUE on success
 */
dbus_bool_t
_dbus_string_parse_uint (const DBusString *str,
                         int               start,
                         unsigned long    *value_return,
                         int              *end_return)
{
  unsigned long v;
  const char *p;
  char *end;

  p = _dbus_string_get_const_data_len (str, start,
                                       _dbus_string_get_length (str) - start);

  end = NULL;
  _dbus_set_errno_to_zero ();
  v = strtoul (p, &end, 0);
  if (end == NULL || end == p || errno != 0)
    return FALSE;

  if (value_return)
    *value_return = v;
  if (end_return)
    *end_return = start + (end - p);

  return TRUE;
}

/** @} */ /* DBusString group */

/**
 * @addtogroup DBusInternalsUtils
 * @{
 */

void
_dbus_generate_pseudorandom_bytes_buffer (char *buffer,
                                          int   n_bytes)
{
  long tv_usec;
  int i;
  
  /* fall back to pseudorandom */
  _dbus_verbose ("Falling back to pseudorandom for %d bytes\n",
                 n_bytes);
  
  _dbus_get_real_time (NULL, &tv_usec);
  srand (tv_usec);
  
  i = 0;
  while (i < n_bytes)
    {
      double r;
      unsigned int b;
          
      r = rand ();
      b = (r / (double) RAND_MAX) * 255.0;

      buffer[i] = b;

      ++i;
    }
}

/**
 * Fills n_bytes of the given buffer with random bytes.
 *
 * @param buffer an allocated buffer
 * @param n_bytes the number of bytes in buffer to write to
 */
void
_dbus_generate_random_bytes_buffer (char *buffer,
                                    int   n_bytes)
{
  DBusString str;

  if (!_dbus_string_init (&str))
    {
      _dbus_generate_pseudorandom_bytes_buffer (buffer, n_bytes);
      return;
    }

  if (!_dbus_generate_random_bytes (&str, n_bytes))
    {
      _dbus_string_free (&str);
      _dbus_generate_pseudorandom_bytes_buffer (buffer, n_bytes);
      return;
    }

  _dbus_string_copy_to_buffer (&str, buffer, n_bytes);

  _dbus_string_free (&str);
}

/**
 * Generates the given number of random bytes, where the bytes are
 * chosen from the alphanumeric ASCII subset.
 *
 * @param str the string
 * @param n_bytes the number of random ASCII bytes to append to string
 * @returns #TRUE on success, #FALSE if no memory or other failure
 */
dbus_bool_t
_dbus_generate_random_ascii (DBusString *str,
                             int         n_bytes)
{
  static const char letters[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz";
  int i;
  int len;
  
  if (!_dbus_generate_random_bytes (str, n_bytes))
    return FALSE;
  
  len = _dbus_string_get_length (str);
  i = len - n_bytes;
  while (i < len)
    {
      _dbus_string_set_byte (str, i,
                             letters[_dbus_string_get_byte (str, i) %
                                     (sizeof (letters) - 1)]);

      ++i;
    }

  _dbus_assert (_dbus_string_validate_ascii (str, len - n_bytes,
                                             n_bytes));

  return TRUE;
}

/**
 * Converts a UNIX errno, or Windows errno or WinSock error value into
 * a #DBusError name.
 *
 * @todo should cover more errnos, specifically those
 * from open().
 * 
 * @param error_number the errno.
 * @returns an error name
 */
const char*
_dbus_error_from_errno (int error_number)
{
  switch (error_number)
    {
    case 0:
      return DBUS_ERROR_FAILED;
      
#ifdef EPROTONOSUPPORT
    case EPROTONOSUPPORT:
      return DBUS_ERROR_NOT_SUPPORTED;
#elif defined(WSAEPROTONOSUPPORT)
    case WSAEPROTONOSUPPORT:
      return DBUS_ERROR_NOT_SUPPORTED;
#endif
#ifdef EAFNOSUPPORT
    case EAFNOSUPPORT:
      return DBUS_ERROR_NOT_SUPPORTED;
#elif defined(WSAEAFNOSUPPORT)
    case WSAEAFNOSUPPORT:
      return DBUS_ERROR_NOT_SUPPORTED;
#endif
#ifdef ENFILE
    case ENFILE:
      return DBUS_ERROR_LIMITS_EXCEEDED; /* kernel out of memory */
#endif
#ifdef EMFILE
    case EMFILE:
      return DBUS_ERROR_LIMITS_EXCEEDED;
#endif
#ifdef EACCES
    case EACCES:
      return DBUS_ERROR_ACCESS_DENIED;
#endif
#ifdef EPERM
    case EPERM:
      return DBUS_ERROR_ACCESS_DENIED;
#endif
#ifdef ENOBUFS
    case ENOBUFS:
      return DBUS_ERROR_NO_MEMORY;
#endif
#ifdef ENOMEM
    case ENOMEM:
      return DBUS_ERROR_NO_MEMORY;
#endif
#ifdef ECONNREFUSED
    case ECONNREFUSED:
      return DBUS_ERROR_NO_SERVER;
#elif defined(WSAECONNREFUSED)
    case WSAECONNREFUSED:
      return DBUS_ERROR_NO_SERVER;
#endif
#ifdef ETIMEDOUT
    case ETIMEDOUT:
      return DBUS_ERROR_TIMEOUT;
#elif defined(WSAETIMEDOUT)
    case WSAETIMEDOUT:
      return DBUS_ERROR_TIMEOUT;
#endif
#ifdef ENETUNREACH
    case ENETUNREACH:
      return DBUS_ERROR_NO_NETWORK;
#elif defined(WSAENETUNREACH)
    case WSAENETUNREACH:
      return DBUS_ERROR_NO_NETWORK;
#endif
#ifdef EADDRINUSE
    case EADDRINUSE:
      return DBUS_ERROR_ADDRESS_IN_USE;
#elif defined(WSAEADDRINUSE)
    case WSAEADDRINUSE:
      return DBUS_ERROR_ADDRESS_IN_USE;
#endif
#ifdef EEXIST
    case EEXIST:
      return DBUS_ERROR_FILE_EXISTS;
#endif
#ifdef ENOENT
    case ENOENT:
      return DBUS_ERROR_FILE_NOT_FOUND;
#endif
    }

  return DBUS_ERROR_FAILED;
}

/**
 * Converts the current system errno value into a #DBusError name.
 *
 * @returns an error name
 */
const char*
_dbus_error_from_system_errno (void)
{
  return _dbus_error_from_errno (errno);
}

/**
 * Assign 0 to the global errno variable
 */
void
_dbus_set_errno_to_zero (void)
{
#ifdef DBUS_WINCE
  SetLastError (0);
#else
  errno = 0;
#endif
}

/**
 * See if errno is set
 * @returns #TRUE if errno is not 0
 */
dbus_bool_t
_dbus_get_is_errno_nonzero (void)
{
  return errno != 0;
}

/**
 * See if errno is ENOMEM
 * @returns #TRUE if errno == ENOMEM
 */
dbus_bool_t
_dbus_get_is_errno_enomem (void)
{
  return errno == ENOMEM;
}

/**
 * See if errno is EINTR
 * @returns #TRUE if errno == EINTR
 */
dbus_bool_t
_dbus_get_is_errno_eintr (void)
{
  return errno == EINTR;
}

/**
 * See if errno is EPIPE
 * @returns #TRUE if errno == EPIPE
 */
dbus_bool_t
_dbus_get_is_errno_epipe (void)
{
  return errno == EPIPE;
}

/**
 * See if errno is ETOOMANYREFS
 * @returns #TRUE if errno == ETOOMANYREFS
 */
dbus_bool_t
_dbus_get_is_errno_etoomanyrefs (void)
{
#ifdef ETOOMANYREFS
  return errno == ETOOMANYREFS;
#else
  return FALSE;
#endif
}

/**
 * Get error message from errno
 * @returns _dbus_strerror(errno)
 */
const char*
_dbus_strerror_from_errno (void)
{
  return _dbus_strerror (errno);
}

/** @} end of sysdeps */

/* tests in dbus-sysdeps-util.c */
