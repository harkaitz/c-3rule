# 3rule

Small command line rule of three calculator.

## Usage

```
3rule A-B C-D
```

Solves the proportion `A / B = C / D`. Exactly one of `A`, `B`, `C`,
`D` must be replaced with `x` (or `X`), the unknown to solve for; the
other three must be numbers.

### Examples

```
$ 3rule 100-50 50-x
25
$ 3rule x-50 50-100
25
```

## Building

```
make
make install   # installs to $DESTDIR$PREFIX/bin, PREFIX=/usr/local by default
```

## Style guide

Standard C99, `-Wall`. Keep functions small and documented with a
short comment on what they do and why.

## Collaborating

Patches and bug reports are welcome.
