#!/bin/sh
: ${srcdir=.}
. "$srcdir/init.sh"; path_prepend_ .

# Test NULL prefix. Result should not contain a number.
test-perror 2>&1 >/dev/null | LC_ALL=C tr -d '\r' > t-perror.tmp
grep '[0-9]' t-perror.tmp > /dev/null \
  && fail_ "result should not contain a number"

# Test empty prefix. Result should be the same.
test-perror '' 2>&1 >/dev/null | LC_ALL=C tr -d '\r' > t-perror1.tmp
diff t-perror.tmp t-perror1.tmp \
  || fail_ "empty prefix should behave like NULL argument"

# Test non-empty prefix.
test-perror foo 2>&1 >/dev/null | LC_ALL=C tr -d '\r' > t-perror3.tmp
sed -e 's/^/foo: /' < t-perror.tmp > t-perror2.tmp
diff t-perror2.tmp t-perror3.tmp || fail_ "prefix applied incorrectly"

# Test exit status.
test-perror >out 2>/dev/null || fail_ "unexpected exit status"
test -s out && fail_ "unexpected output"

Exit 0
