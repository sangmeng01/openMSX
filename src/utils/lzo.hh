// $Id$

/* minilzo.hh -- mini subset of the LZO real-time data compression library

   This file is part of the LZO real-time data compression library.

   Copyright (C) 2008 Markus Franz Xaver Johannes Oberhumer
   Copyright (C) 2007 Markus Franz Xaver Johannes Oberhumer
   Copyright (C) 2006 Markus Franz Xaver Johannes Oberhumer
   Copyright (C) 2005 Markus Franz Xaver Johannes Oberhumer
   Copyright (C) 2004 Markus Franz Xaver Johannes Oberhumer
   Copyright (C) 2003 Markus Franz Xaver Johannes Oberhumer
   Copyright (C) 2002 Markus Franz Xaver Johannes Oberhumer
   Copyright (C) 2001 Markus Franz Xaver Johannes Oberhumer
   Copyright (C) 2000 Markus Franz Xaver Johannes Oberhumer
   Copyright (C) 1999 Markus Franz Xaver Johannes Oberhumer
   Copyright (C) 1998 Markus Franz Xaver Johannes Oberhumer
   Copyright (C) 1997 Markus Franz Xaver Johannes Oberhumer
   Copyright (C) 1996 Markus Franz Xaver Johannes Oberhumer
   All Rights Reserved.

   The LZO library is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of
   the License, or (at your option) any later version.

   The LZO library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with the LZO library; see the file COPYING.
   If not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

   Markus F.X.J. Oberhumer
   <markus@oberhumer.com>
   http://www.oberhumer.com/opensource/lzo/
 */

/*
 * NOTE:
 *   the full LZO package can be found at
 *   http://www.oberhumer.com/opensource/lzo/
 */


#ifndef LZO_HH
#define LZO_HH

#include "lzoconf.hh"


/* Memory required for the wrkmem parameter.
 * When the required size is 0, you can also pass a NULL pointer.
 */

#define LZO1X_MEM_COMPRESS      LZO1X_1_MEM_COMPRESS
#define LZO1X_1_MEM_COMPRESS    ((lzo_uint32) (16384L * lzo_sizeof_dict_t))


namespace openmsx {

/* compression */
int lzo1x_1_compress(const lzo_bytep src, lzo_uint  src_len,
                     lzo_bytep dst, lzo_uintp dst_len,
                     lzo_voidp wrkmem);

/* decompression */
int lzo1x_decompress(const lzo_bytep src, lzo_uint  src_len,
                     lzo_bytep dst, lzo_uintp dst_len);

} // namespace openmsx

#endif // LZO_HH
