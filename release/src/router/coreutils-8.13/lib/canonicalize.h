/* Return the canonical absolute name of a given file.
   Copyright (C) 1996-2007, 2009-2011 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#ifndef CANONICALIZE_H_
# define CANONICALIZE_H_

#include <stdlib.h> /* for canonicalize_file_name */

enum canonicalize_mode_t
  {
    /* All components must exist.  */
    CAN_EXISTING = 0,

    /* All components excluding last one must exist.  */
    CAN_ALL_BUT_LAST = 1,

    /* No requirements on components existence.  */
    CAN_MISSING = 2
  };
typedef enum canonicalize_mode_t canonicalize_mode_t;

/* Return a malloc'd string containing the canonical absolute name of
   the named file.  This acts like canonicalize_file_name, except that
   whether components must exist depends on the canonicalize_mode_t
   argument.  */
char *canonicalize_filename_mode (const char *, canonicalize_mode_t);

#endif /* !CANONICALIZE_H_ */
