#include "noise_lfreq.h"

static void* faust_new(t_symbol* s, int argc, t_atom* argv)
{
    t_faust* x = reinterpret_cast<t_faust*>(pd_new(faust_class));
    PdArgParser p(x, argc, argv);
    return p.pd_obj();
}

extern "C" void setup_noise0x2elfreq_tilde()
{
    internal_setup(gensym("noise.lfreq~"));
}

