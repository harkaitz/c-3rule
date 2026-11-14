#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char HELP[] =
    "Usage: 3rule A-B C-D"                                       "\n"
    ""                                                           "\n"
    "Apply the rule of three, one of A,B,C,D may be 'x' or 'X'." "\n"
    ;

/* Returns 1 if the token is the unknown placeholder ('x' or 'X'). */
static int is_unknown(const char *_s);

/* Splits "LEFT-RIGHT" into two tokens, returns 0 on success. */
static int split_pair(char *_buf, char **_left, char **_right);

int
main(int _argc, char *_argv[])
{
	char  *l1, *r1, *l2, *r2;
	float  a, b, c, d;
	int    unk = -1, e;

	/* Print help. */
	if (_argc == 1 || !strcmp(_argv[1], "--help") || !strcmp(_argv[1], "-h")) {
		printf("%s", HELP);
		return 0;
	}

	/* Parse arguments. */
	if (_argc != 3/*err*/) { goto err_arg; }
	e = split_pair(_argv[1], &l1, &r1) || split_pair(_argv[2], &l2, &r2);
	if (e/*err*/) { goto err_arg; }

	/* Get numbers and the unknown. */
	if (is_unknown(l1)) {
		unk = 0;
		a = 0;
	} else {
		a = (float) atof(l1);
	}
	if (is_unknown(r1)) {
		if (unk != -1/*err*/) { goto err_mulx; }
		unk = 1;
		b = 0;
	} else {
		b = (float) atof(r1);
	}
	if (is_unknown(l2)) {
		if (unk != -1/*err*/) { goto err_mulx; }
		unk = 2;
		c = 0;
	} else {
		c = (float) atof(l2);
	}
	if (is_unknown(r2)) {
		if (unk != -1/*err*/) { goto err_mulx; }
		unk = 3;
		d = 0;
	} else {
		d = (float) atof(r2);
	}
	if (unk == -1/*err*/) { goto err_nox; }

	/* Proportion: a / b = c / d */
	switch (unk) {
	case 0:
		if (d == 0/*err*/) { goto err_div0; }
		printf("%g\n", b * c / d);
		break;
	case 1:
		if (c == 0/*err*/) { goto err_div0; }
		printf("%g\n", a * d / c);
		break;
	case 2:
		if (b == 0/*err*/) { goto err_div0; }
		printf("%g\n", a * d / b);
		break;
	case 3:
		if (a == 0/*err*/) { goto err_div0; }
		printf("%g\n", b * c / a);
		break;
	}

	return 0;
	err_div0:
	fprintf(stderr, "3rule: error: division by zero\n");
	return 1;
	err_mulx:
	fprintf(stderr, "3rule: error: only one unknown allowed\n");
	return 1;
	err_nox:
	fprintf(stderr, "3rule: error: no unknown ('x') given\n");
	return 1;
	err_arg:
	fprintf(stderr, "3rule: error: Invalid arguments.\n");
	return 2;
}

static int
is_unknown(const char *_s)
{
	return (_s[0] == 'x' || _s[0] == 'X') && _s[1] == '\0';
}

static int
split_pair(char *_buf, char **_left, char **_right)
{
	char *dash = strchr(_buf, '-');
	if (!dash)
		return 1;
	*dash   = '\0';
	*_left  = _buf;
	*_right = dash + 1;
	return 0;
}
