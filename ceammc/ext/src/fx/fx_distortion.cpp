#include "fx_distortion.h"

EXTERNAL_NEW
{
    FAUST_EXT* x = reinterpret_cast<FAUST_EXT*>(pd_new(FAUST_EXT_CLASS));
    PdArgParser p(x, argc, argv);
    p.initFloatArg("drive", 1);
    p.initFloatArg("offset", 2);
    return p.pd_obj();
}

EXTERNAL_SETUP(fx);
