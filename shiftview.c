// "arg->i" stores the number of tags to shift right (positive value)
//          or left (negative value)
void
shiftview(const Arg *arg)
{
	Arg a;
	bool visible = true;
	int i = arg->i;
	int count = 0;
	int nextseltags, curseltags = selmon->tagset[selmon->seltags];

	do {
		if (i > 0) // left circular shift
            nextseltags = (curseltags << i) | (curseltags >> ((int)LENGTH(tags) - i));
        else // right circular shift
			nextseltags = curseltags >> (-i) | (curseltags << ((int)LENGTH(tags) + i));

		i += arg->i;
    } while (!visible && ++count <= (int)LENGTH(tags));

    if (count <= (int)LENGTH(tags)) {
        a.i = nextseltags;
        view(&a);
    }
}
