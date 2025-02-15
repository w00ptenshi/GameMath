/* s_rintf.c -- float version of s_rint.c.
 * Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
 */

 /*
  * ====================================================
  * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
  *
  * Developed at SunPro, a Sun Microsystems, Inc. business.
  * Permission to use, copy, modify, and distribute this
  * software is freely granted, provided that this notice
  * is preserved.
  * ====================================================
  */

#include <fenv.h>
#include "gmath.h"
#include "math_private.h"

static const float
TWO23[2] = {
  8.3886080000e+06, /* 0x4b000000 */
 -8.3886080000e+06, /* 0xcb000000 */
};

float
gm_nearbyintf(float x)
{
	int exc = fetestexcept(FE_INEXACT);

	int32_t i0, j0, sx;
	volatile float w, t;	/* volatile works around gcc bug */
	GET_FLOAT_WORD(i0, x);
	sx = (i0 >> 31) & 1;
	j0 = ((i0 >> 23) & 0xff) - 0x7f;
	if (j0 < 23) {
		if (j0 < 0) {
			if ((i0 & 0x7fffffff) == 0) return x;
			w = TWO23[sx] + x;
			t = w - TWO23[sx];
			if (!exc) feclearexcept(FE_INEXACT);
			return t;
		}
		w = TWO23[sx] + x;
		t = w - TWO23[sx];
		if (!exc) feclearexcept(FE_INEXACT);
		return t;
	}

	if (j0 == 0x80) return x + x;	/* inf or NaN */
	else return x;			/* x is integral */
}
