#!/usr/bin/env python

import sys
import cffi

ffi = cffi.FFI()

cfile = sys.argv[1]
ctype = sys.argv[2]

cdefs = open(cfile).read().replace('__attribute((aligned(8)))', '').replace('__attribute__((aligned(8)))','')
ffi.cdef(cdefs)

ty = ffi.typeof(ctype)

tymaps = {
        'int32_t': '%ld',
        'uint16_t': '%hu',
        'uint32_t': '%lu',
        'uint64_t': '%llu',
        'uint8_t': '%hhu'
}

def formats(var):
    for name, etype in ty.fields:
        yield '    {} = {}'.format(name, tymaps[etype.type.cname])
        yield '{}->{}'.format(var, name)


l = list(formats('var'))

print '''\
#include <sys/types.h>
#include <stdint.h>
#include <stdio.h>
#include "tcpinfo.h"

char *
{name}_str({ty} *var)
{{
\tchar *buf = NULL;
\tasprintf(&buf,
\t\t"{fmts}",
\t\t{args});
\treturn buf;
}}
'''.format(ty=ty.cname, name=ty.cname.split()[-1], fmts='\\n"\n\t\t"'.join(l[::2]), args=',\n\t\t'.join(l[1::2]))
