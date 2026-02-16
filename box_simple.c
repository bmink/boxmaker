#include <stdio.h>
#include <errno.h>
#include "bstr.h"

int
box_simple_outdim(
	bstr_t *out, const float width, const float depth,
	const float height, const float stock)
{
	if(out == NULL)
		return EINVAL;

	bstrcat(out, "<svg xmlns='http://www.w3.org/2000/svg' ");
	bstrcat(out, " width='49in' height='25in'>\n");



	bstrcat(out, "</svg>\n");

	return 0;

	
}
