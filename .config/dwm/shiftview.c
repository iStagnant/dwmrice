/* Sends a window to the next/prev tag */
void
shifttag(const Arg *arg)
{
	Arg shifted;
	shifted.ui = selmon->tagset[selmon->seltags] & ~SPTAGMASK;


	if (arg->i > 0)	/* left circular shift */
		shifted.ui = ((shifted.ui << arg->i) | (shifted.ui >> (LENGTH(tags) - arg->i))) & ~SPTAGMASK;
	else		/* right circular shift */
		shifted.ui = (shifted.ui >> (- arg->i) | shifted.ui << (LENGTH(tags) + arg->i)) & ~SPTAGMASK;
	tag(&shifted);
}
/* Navigate to the next/prev tag */
void
shiftview(const Arg *arg)
{
	Arg shifted;
	shifted.ui = selmon->tagset[selmon->seltags] & ~SPTAGMASK;

	if (arg->i > 0) {/* left circular shift */
		shifted.ui = (shifted.ui << arg->i) | (shifted.ui >> (LENGTH(tags) - arg->i));
		shifted.ui &= ~SPTAGMASK;
	} else {	/* right circular shift */
		shifted.ui = (shifted.ui >> (- arg->i) | shifted.ui << (LENGTH(tags) + arg->i));
		shifted.ui &= ~SPTAGMASK;
	}
	view(&shifted);
}
/* move the current active window to the next/prev tag and view it. More like following the window */
void
shiftboth(const Arg *arg)
{
	Arg shifted;
	shifted.ui = selmon->tagset[selmon->seltags] & ~SPTAGMASK;

	if (arg->i > 0)	/* left circular shift */
		shifted.ui = ((shifted.ui << arg->i) | (shifted.ui >> (LENGTH(tags) - arg->i))) & ~SPTAGMASK;
	else		/* right circular shift */
		shifted.ui = ((shifted.ui >> (- arg->i) | shifted.ui << (LENGTH(tags) + arg->i))) & ~SPTAGMASK;
	tag(&shifted);
	view(&shifted);
}
