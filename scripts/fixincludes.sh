#!/bin/sh

function fixinclude {
    for file in $1/*
    do
        if [ -d $file ] 
            then
                fixinclude $file
        fi

        if [ -f $file ] 
            then
                echo "Handeling $file"
                sed -i s,#include\ \"mongo/base/string_data.h,#include\ \"mongo/string_data.h, $file
                sed -i s,#include\ \"mongo/client/redef_macros.h,#include\ \"mongo/redef_macros.h, $file
                sed -i s,#include\ \"mongo/client/undef_macros.h,#include\ \"mongo/undef_macros.h, $file
                sed -i s,#include\ \"mongo/db/nonce.h,#include\ \"mongo/nonce.h, $file                
                sed -i s,#include\ \"mongo/platform/atomic_intrinsics.h,#include\ \"mongo/atomic_intrinsics.h, $file
                sed -i s,#include\ \"mongo/platform/atomic_intrinsics_gcc.h,#include\ \"mongo/atomic_intrinsics_gcc.h, $file
                sed -i s,#include\ \"mongo/platform/atomic_intrinsics_win32.h,#include\ \"mongo/atomic_intrinsics_win32.h, $file
                sed -i s,#include\ \"mongo/platform/atomic_word.h,#include\ \"mongo/atomic_word.h, $file
                sed -i s,#include\ \"mongo/platform/basic.h,#include\ \"mongo/basic.h, $file
                sed -i s,#include\ \"mongo/platform/compiler.h,#include\ \"mongo/compiler.h, $file
                sed -i s,#include\ \"mongo/platform/compiler_gcc.h,#include\ \"mongo/compiler_gcc.h, $file
                sed -i s,#include\ \"mongo/platform/compiler_msvc.h,#include\ \"mongo/compiler_msvc.h, $file
                sed -i s,#include\ \"mongo/platform/cstdint.h,#include\ \"mongo/cstdint.h, $file
                sed -i s,#include\ \"mongo/platform/float_utils.h,#include\ \"mongo/float_utils.h, $file
                sed -i s,#include\ \"mongo/platform/windows_basic.h,#include\ \"mongo/windows_basic.h, $file
                      
                sed -i s,#include\ \"mongo/util/assert_util.h,#include\ \"mongo/assert_util.h, $file
                sed -i s,#include\ \"mongo/util/exit_code.h,#include\ \"mongo/exit_code.h, $file
                sed -i s,#include\ \"mongo/util/hex.h,#include\ \"mongo/hex.h, $file
                sed -i s,#include\ \"mongo/util/md5.h,#include\ \"mongo/md5.h, $file
                sed -i s,#include\ \"mongo/util/md5.hpp,#include\ \"mongo/md5.hpp, $file
                sed -i s,#include\ \"mongo/util/time_support.h,#include\ \"mongo/time_support.h, $file
        fi
    done
}

fixinclude ../src
