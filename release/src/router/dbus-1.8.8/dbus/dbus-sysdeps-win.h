/* -*- mode: C; c-file-style: "gnu"; indent-tabs-mode: nil; -*- */
/* dbus-sysdeps.c Wrappers around system/libc features (internal to D-BUS implementation)
 * 
 * Copyright (C) 2002, 2003  Red Hat, Inc.
 * Copyright (C) 2003 CodeFactory AB
 * Copyright (C) 2005 Novell, Inc.
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

#ifndef DBUS_SYSDEPS_WIN_H
#define DBUS_SYSDEPS_WIN_H

extern void *_dbus_win_get_dll_hmodule (void);
#define WIN32_LEAN_AND_MEAN

#include "dbus-hash.h"
#include "dbus-string.h"
#include <ctype.h>
#include <malloc.h>
#include <windows.h>
#undef interface

#define DBUS_CONSOLE_DIR "/var/run/console/"


void _dbus_win_set_errno (int err);
const char* _dbus_win_error_from_last_error (void);

dbus_bool_t _dbus_win_startup_winsock (void);
void _dbus_win_warn_win_error  (const char *message,
                                unsigned long code);
                                
char * _dbus_win_error_string (int error_number);
void _dbus_win_free_error_string (char *string);

extern const char* _dbus_lm_strerror  (int error_number);


dbus_bool_t _dbus_win_account_to_sid (const wchar_t *waccount,
                                      void         **ppsid,
                                      DBusError     *error);

dbus_bool_t
_dbus_win32_sid_to_name_and_domain (dbus_uid_t  uid,
                                    wchar_t   **wname,
                                    wchar_t   **wdomain,
                                    DBusError  *error);


/* Don't define DBUS_CONSOLE_DIR on Win32 */

wchar_t    *_dbus_win_utf8_to_utf16 (const char  *str,
                                     DBusError   *error);
char       *_dbus_win_utf16_to_utf8 (const wchar_t *str,
                                     DBusError *error);

void        _dbus_win_set_error_from_win_error (DBusError *error, int code);

dbus_bool_t
_dbus_win_sid_to_name_and_domain (dbus_uid_t uid,
                                  wchar_t  **wname,
                                  wchar_t  **wdomain,
                                  DBusError *error);

dbus_bool_t _dbus_file_exists (const char *filename);

dbus_bool_t _dbus_get_config_file_name(DBusString *config_file, 
                                       char *s);

dbus_bool_t _dbus_get_install_root(char *prefix, int len);

void        _dbus_threads_windows_init_global (void);
void        _dbus_threads_windows_ensure_ctor_linked (void);

#endif

/** @} end of sysdeps-win.h */
