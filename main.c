#include <stdio.h>
#include <libgen.h>
#include <unistd.h>
#include <errno.h>
#include "bstr.h"


void usage(const char *);
 
typedef int (*typefunc_t)(bstr_t *, float, float, float, float);

typedef struct boxtype {
	char		*bt_name;
	typefunc_t	bt_genfunc_outdim;
	typefunc_t	bt_genfunc_indim;
} boxtype_t;

int box_simple_outdim(bstr_t *, float, float, float, float);


boxtype_t	boxtype_table[] = {
	{ "simple",	box_simple_outdim, NULL },
	{ 0 }
};


int
parse_dims(const char *str, float *width, float *depth, float *height)
{
	int	cnt;

	if(xstrempty(str))
		return EINVAL;

	cnt = sscanf(str, "%f:%f:%f", width, depth, height);
	if(cnt != 3)
		return ENOENT;

	return 0;
}





int
main(int argc, char **argv)
{
	char		*execn;
	int		err;
	int		ret;
	int		c;
	char		*type;
	bstr_t		*out;
	char		*indims;
	char		*outdims;
	float		width;
	float		depth;
	float		height;
	float		stock;
	boxtype_t	*bt;

	err = 0;
	type = NULL;
	out = NULL;
	indims = NULL;
	outdims = NULL;
	width = depth = height = stock = 0;

        execn = basename(argv[0]);
        if(xstrempty(execn)) {
                fprintf(stderr, "Can't get executable name\n");
                err = -1;
                goto end_label;
        }

	while ((c = getopt (argc, argv, "ht:s:i:o:")) != -1) {
		switch (c) {

		case 'h':
			usage(execn);
			goto end_label;

		case 't':
			type = optarg;
			break;

		case 'i':
			indims = optarg;
			break;

		case 'o':
			outdims = optarg;
			break;

		case 's':
			if(xstrempty(optarg)) {
				fprintf(stderr,
				    "Invalid stock width specified.\n");
				err = -1;
				goto end_label;
			}

			stock = atof(optarg);
			if(stock <= 0) {
				fprintf(stderr,
				    "Invalid stock thickness specified.\n");
				err = -1;
				goto end_label;
			}
			break;

		case '?':
			fprintf (stderr, "Unknown option `-%c'\n", optopt);
			err = -1;
			goto end_label;

		default:
			fprintf (stderr, "Error while parsing options");
			err = -1;
			goto end_label;
		}
	}

	if(type == NULL) {
		fprintf(stderr, "No type specified.\n");
		err = -1;
		goto end_label;
	}

	if(indims == NULL && outdims == NULL) {
		fprintf(stderr, "Either inside or outside dimensions"
		    " are requied.\n");
		err = -1;
		goto end_label;
	}

	if(indims != NULL && outdims != NULL) {
		fprintf(stderr, "Can't specify both inside and outside"
		    " dimensions.\n");
		err = -1;
		goto end_label;
	}

	if(outdims != NULL)
		ret = parse_dims(outdims, &width, &depth, &height);
	else
		ret = parse_dims(indims, &width, &depth, &height);

	if(ret != 0) {
		fprintf(stderr, "Invalid dimensions speficied: %s.\n",
		    strerror(ret));
		err = -1;
		goto end_label;
	}

	out = binit();
	if(out == NULL) {
		fprintf(stderr, "Couldn't allocate out\n");
		err = -1;
		goto end_label;
	}

	for(bt = boxtype_table; bt->bt_name != NULL; ++bt) {
		if(!xstrcmp(bt->bt_name, type))
			break;
	}

	if(bt == NULL) {
		fprintf(stderr, "Type not found: %s.\n", type);
		err = -1;
		goto end_label;
	}

	if(outdims != NULL) {
		if(bt->bt_genfunc_outdim == NULL) {
			fprintf(stderr, "Type '%s' does not support"
			    " outside dimensions\n", type);
			err = -1;
			goto end_label;
		}
		ret = bt->bt_genfunc_outdim(out, width, depth, height, stock);
		if(ret != 0) {
			fprintf(stderr, "Error while generating output: %s\n",
			    strerror(ret));
			err = -1;
			goto end_label;
		}
	} else {
		if(bt->bt_genfunc_indim == NULL) {
			fprintf(stderr, "Type '%s' does not support"
			    " inside dimensions\n", type);
			err = -1;
			goto end_label;
		}
		ret = bt->bt_genfunc_indim(out, width, depth, height, stock);
		if(ret != 0) {
			fprintf(stderr, "Error while generating output: %s\n",
			    strerror(ret));
			err = -1;
			goto end_label;
		}
	}

	btofilep(stdout, out);


end_label:

	if(out)
		buninit(&out);


	return err;
}


void
usage(const char *execn)
{
        printf("usage:\n");
        printf("\n");
        printf("  Tail live comments on post:\n");
        printf("\n");
        printf("      %s [options] <reddit_post_url>\n", execn);
        printf("\n");
        printf("  To exit, press Ctrl-C or send SIGTERM (eg. 'kill <pid>')\n");
        printf("\n");
        printf("  Supported options:\n");
        printf("\n");
        printf("      -d <delaysec>\n");
        printf("              Delay comment display by this many seconds\n");
        printf("\n");
        printf("      -f      Full comment display mode  (default is compact"
            " display)\n");
        printf("\n");
        printf("      -n <instance cnt>\n");
        printf("              Number of concurrent processes\n");
        printf("\n");
        printf("\n");
        printf("      -u <usrcredsfile>\n");
        printf("              Alternate user credentials file\n");
        printf("\n");
        printf("      -a <appcredsfile>\n");
        printf("              Alternate app credentials file\n");
        printf("\n");
        printf("      -h      Print this help text and exit\n");
        printf("\n");
}

