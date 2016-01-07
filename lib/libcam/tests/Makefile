# $FreeBSD: head/share/examples/tests/tests/atf/Makefile 263161 2014-03-14 08:56:19Z jmmv $

.include <bsd.own.mk>

# Directory into which the Kyuafile provided by this directory will be
# installed.
#
# This is always a subdirectory of ${TESTSBASE}/.  The remainder of the
# path has to match the relative path within the source tree in which
# these files are found modulo the tests/ component at the end.
#
# For example: if this Makefile were in src/bin/cp/tests/, its TESTSDIR
# would point at ${TESTSBASE}/bin/cp/.
TESTSDIR=	${TESTSBASE}/lib/libcam

# List of test programs to build.  Note that we can build more than one
# test from a single directory, and this is expected.
ATF_TESTS_C=	libcam_test

# List of libraried to link against
LIBADD.libcam_test+= cam

.include <bsd.test.mk>
