/* -*-comment-start: "//";comment-end:""-*-
 * GNU Mes --- Maxwell Equations of Software
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

#include <linux/syscall.h>
#include <arch/syscall.h>
#include <fcntl.h>
#include <sys/stat.h>

int
mkfifo (char const *file_name, mode_t mode)
{
  long flagged = (long) (mode | S_IFIFO);
#if defined (SYS_mknod)
  return _sys_call3 (SYS_mknod, (long) file_name, flagged, 0);
#elif defined (SYS_mknodat)
  return _sys_call4 (SYS_mknodat, AT_FDCWD, (long) file_name, flagged, 0);
#else
#error No usable mknod syscall
#endif
}
