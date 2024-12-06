// "arg->i" stores the number of tags to shift right (positive value)
//          or left (negative value)
void
shiftview(const Arg *arg)
{
	Arg a;
	Client *c;
	bool visible = false;
	int i = arg->i;
	int count = 0;
	int nextseltags, curseltags = selmon->tagset[selmon->seltags];

	do {
		if (i > 0) // left circular shift
            nextseltags = (curseltags << i) | (curseltags >> ((int)LENGTH(tags) - i));
        else // right circular shift
			nextseltags = curseltags >> (-i) | (curseltags << ((int)LENGTH(tags) + i));

        // Check if the tag is visible
        wl_list_for_each(c, &clients, link) {
            if (c->mon == selmon && nextseltags & c->tags) {
                visible = true;
                break;
            }
        }

		i += arg->i;
    } while (!visible && ++count <= (int)LENGTH(tags));

    if (count <= (int)LENGTH(tags)) {
        a.i = nextseltags;
        view(&a);
    }
}
