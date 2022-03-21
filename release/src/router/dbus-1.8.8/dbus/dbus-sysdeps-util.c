/* -*- mode: C; c-file-style: "gnu"; indent-tabs-mode: nil; -*- */
/* dbus-sysdeps-util.c Tests for dbus-sysdeps.h API
 * 
 * Copyright (C) 2002, 2003, 2004, 2005  Red Hat, Inc.
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
#include "dbus-sysdeps.h"
#include "dbus-internals.h"
#include "dbus-string.h"
#include "dbus-test.h"

#include <stdlib.h>

#ifdef DBUS_WIN
  /* do nothing, it's in stdlib.h */
#elif (defined __APPLE__)
# include <crt_externs.h>
# define environ (*_NSGetEnviron())
#else
extern char **environ;
#endif

/**
 * Gets a #NULL-terminated list of key=value pairs from the
 * environment. Use dbus_free_string_array to free it.
 *
 * @returns the environment or #NULL on OOM
 */
char **
_dbus_get_environment (void)
{
  int i, length;
  char **environment;

  _dbus_assert (environ != NULL);

  for (length = 0; environ[length] != NULL; length++);

  /* Add one for NULL */
  length++;

  environment = dbus_new0 (char *, length);

  if (environment == NULL)
    return NULL;

  for (i = 0; environ[i] != NULL; i++)
    {
      environment[i] = _dbus_strdup (environ[i]);

      if (environment[i] == NULL)
        break;
    }

  if (environ[i] != NULL)
    {
      dbus_free_string_array (environment);
      environment = NULL;
    }

  return environment;
}

#ifdef DBUS_ENABLE_EMBEDDED_TESTS
static void
check_dirname (const char *filename,
               const char *dirname)
{
  DBusString f, d;
  
  _dbus_string_init_const (&f, filename);

  if (!_dbus_string_init (&d))
    _dbus_assert_not_reached ("no memory");

  if (!_dbus_string_get_dirname (&f, &d))
    _dbus_assert_not_reached ("no memory");

  if (!_dbus_string_equal_c_str (&d, dirname))
    {
      _dbus_warn ("For filename \"%s\" got dirname \"%s\" and expected \"%s\"\n",
                  filename,
                  _dbus_string_get_const_data (&d),
                  dirname);
      exit (1);
    }

  _dbus_string_free (&d);
}

static void
check_path_absolute (const char *path,
                     dbus_bool_t expected)
{
  DBusString p;

  _dbus_string_init_const (&p, path);

  if (_dbus_path_is_absolute (&p) != expected)
    {
      _dbus_warn ("For path \"%s\" expected absolute = %d got %d\n",
                  path, expected, _dbus_path_is_absolute (&p));
      exit (1);
    }
}

/**
 * Unit test for dbus-sysdeps.c.
 * 
 * @returns #TRUE on success.
 */
dbus_bool_t
_dbus_sysdeps_test (void)
{
#ifdef DBUS_WIN
  check_dirname ("foo\\bar", "foo");
  check_dirname ("foo\\\\bar", "foo");
  check_dirname ("foo/\\/bar", "foo");
  check_dirname ("foo\\bar/", "foo");
  check_dirname ("foo//bar\\", "foo");
  check_dirname ("foo\\bar/", "foo");
  check_dirname ("foo/bar\\\\", "foo");
  check_dirname ("\\foo", "\\");
  check_dirname ("\\\\foo", "\\");
  check_dirname ("\\", "\\");
  check_dirname ("\\\\", "\\");
  check_dirname ("\\/", "\\");
  check_dirname ("/\\/", "/");
  check_dirname ("c:\\foo\\bar", "c:\\foo");
  check_dirname ("c:\\foo", "c:\\");
  check_dirname ("c:/foo", "c:/");
  check_dirname ("c:\\", "c:\\");
  check_dirname ("c:/", "c:/");
  check_dirname ("", ".");  
#else  
  check_dirname ("foo", ".");
  check_dirname ("foo/bar", "foo");
  check_dirname ("foo//bar", "foo");
  check_dirname ("foo///bar", "foo");
  check_dirname ("foo/bar/", "foo");
  check_dirname ("foo//bar/", "foo");
  check_dirname ("foo///bar/", "foo");
  check_dirname ("foo/bar//", "foo");
  check_dirname ("foo//bar////", "foo");
  check_dirname ("foo///bar///////", "foo");
  check_dirname ("/foo", "/");
  check_dirname ("////foo", "/");
  check_dirname ("/foo/bar", "/foo");
  check_dirname ("/foo//bar", "/foo");
  check_dirname ("/foo///bar", "/foo");
  check_dirname ("/", "/");
  check_dirname ("///", "/");
  check_dirname ("", ".");  
#endif

#ifdef DBUS_WIN
  check_path_absolute ("c:/", TRUE);
  check_path_absolute ("c:/foo", TRUE);
  check_path_absolute ("", FALSE);
  check_path_absolute ("foo", FALSE);
  check_path_absolute ("foo/bar", FALSE);
  check_path_absolute ("", FALSE);
  check_path_absolute ("foo\\bar", FALSE);
  check_path_absolute ("c:\\", TRUE);
  check_path_absolute ("c:\\foo", TRUE);
  check_path_absolute ("c:", TRUE);
  check_path_absolute ("c:\\foo\\bar", TRUE);
  check_path_absolute ("\\", TRUE);
  check_path_absolute ("/", TRUE);
#else  
  check_path_absolute ("/", TRUE);
  check_path_absolute ("/foo", TRUE);
  check_path_absolute ("", FALSE);
  check_path_absolute ("foo", FALSE);
  check_path_absolute ("foo/bar", FALSE);
#endif
  
  return TRUE;
}
#endif /* DBUS_ENABLE_EMBEDDED_TESTS */
