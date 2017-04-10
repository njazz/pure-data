#include "flt_c_lowshelf.h"

EXTERNAL_NEW
{
    FAUST_EXT* x = reinterpret_cast<FAUST_EXT*>(pd_new(FAUST_EXT_CLASS));
    PdArgParser p(x, argc, argv);
    p.initFloatArg("freq", 1);
    p.initFloatArg("q", 2);
    p.initFloatArg("gain", 3);
    return p.pd_obj();
}

EXTERNAL_SETUP(flt);
