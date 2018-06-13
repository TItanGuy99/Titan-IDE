#!/bin/bash
find . -name '*.class' | xargs jlint -not_overridden \
-redundant -weak_cmp -bounds -zero_operand -string_cmp -shadow_local | \
grep -v 'Field .class\$' | grep -v 'can be .*ed from different threads' | \
grep -v 'Method.*Runnable.*synch'

