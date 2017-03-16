#include "flt_bpf24.h"

static void* faust_new(t_symbol* s, int argc, t_atom* argv)
{
    t_faust* x = reinterpret_cast<t_faust*>(pd_new(faust_class));
    PdArgParser p(x, argc, argv);
    p.initFloatArg("freq", 1);
    p.initFloatArg("q", 2);
    return p.pd_obj();
}

extern "C" void setup_flt0x2ebpf24_tilde()
{
    internal_setup(gensym("flt.bpf24~"));
}

