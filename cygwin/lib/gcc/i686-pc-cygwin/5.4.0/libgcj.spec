#
# This spec file is read by gcj when linking.
# It is used to specify the standard libraries we need in order
# to link with libgcj.
#
%rename startfile startfileorig
*startfile:  %(startfileorig)

%rename lib liborig
*lib: %{static-libgcj:-non_shared} %{s-bc-abi:} -lgcj-noncore -lgcj %{static-libgcj:-call_shared} -lm  -liconv    -lrt -lz   -ldl %(libgcc)  %(liborig)

*jc1:  -fuse-divide-subroutine -fcheck-references -fuse-boehm-gc      -fkeep-inline-functions
