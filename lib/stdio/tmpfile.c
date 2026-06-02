/* -*-comment-start: "//";comment-end:""-*-
 * GNU Mes --- Maxwell Equations of Software
 * Copyright © 2026 Harmen Stoppels <harmen@stoppels.ch>
 *
 * This file is part of GNU Mes.
 *
 * GNU Mes is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or (at
 * your option) any later version.
 *
 * GNU Mes is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Mes.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

FILE *
tmpfile (void)
{
  char name[] = "/tmp/mesXXXXXX";
  int fd;
  FILE *f;

  if (mktemp (name) == 0 || name[0] == '\0')
    return 0;

  fd = open (name, O_RDWR | O_CREAT | O_EXCL, 0600);
  if (fd < 0)
    return 0;

  /* Unlink now; the open fd keeps the file alive until fclose.  */
  unlink (name);

  f = fdopen (fd, "wb+");
  if (f == 0)
    {
      close (fd);
      return 0;
    }
  return f;
}
