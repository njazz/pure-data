/*

————————————————————————————————————————————————————————————————
collatz - © Copyright sier 2002
		
		collatz conjecture output
————————————————————————————————————————————————————————————————
*/

#include "cicm_wrapper.h"

#include <math.h>
#include <stdbool.h>

typedef struct
{
    t_object c_ob;
    t_outlet* c_out;
    long c_value;
    long c_offset;
    bool c_mode, om;
} atz;

static void* atz_new(t_symbol* msg, int argc, t_atom* argv);
static void atz_offset(atz* x, long offset);
static void atz_bang(atz* x);
static void atz_int(atz* x, t_float number);
static void atz_mode(atz* x, t_float number);
static void atz_om(atz* x, t_float number);
static int atz_calc(atz* x, int number);

static t_eclass* atz_class;

void atz_mode(atz* x, t_float number)
{
    x->c_mode = (number > 0);
    // ?
    //    if (atz_om)
    //        atz_bang(x);
}

void* atz_new(t_symbol* msg, int argc, t_atom* argv)
{
    long inputarg = 0, offset = 0;

    atz* x;
    x = (atz*)eobj_new(atz_class);
    x->c_out = floatout(x);

    if (argc) {
        if (argc > 1)
            offset = atom_getfloat(&argv[1]);

        if (argc > 0)
            inputarg = atom_getfloat(&argv[0]);
    }

    x->c_value = x->c_offset = 0; //init
    x->c_mode = x->om = 0;
    x->c_value = inputarg;

    if (!inputarg)
        x->c_value = 71; //seed it

    x->c_offset = offset;

    if (!offset)
        x->c_offset = 0;

    return (x); ///the obj, nice and clean, ready to use
}

int atz_calc(atz* x, int number)
{
    short int stub;
    stub = number % 2; //par ou impar

    if (!x->c_mode) { // L.Collatz collatz mode
        if (!stub)
            number /= 2; //par ]e metade
        else
            number = 3 * number + 1; //impar ]e 3n+1
        return (number);
    } else if (x->c_mode) { // Terras collatz mode
        if (!stub)
            number /= 2; //par ]e metade
        else
            number = 0.5 * (3 * number + 1); //impar ]e 1/2(3n+1)
        return (number);
    }

    // ?
    return -1;
}

void atz_offset(atz* x, long offset)
{
    x->c_offset = offset;
    // ?
    //if (atz_om)
    atz_bang(x);
}

void atz_om(atz* x, t_float number)
{
    x->om = (number > 0);
}

void atz_int(atz* x, t_float number)
{
    x->c_value = atz_calc(x, (int)number - 1); //guardar dentro do objecto calculado
    // ?
    //if (atz_om)
    atz_bang(x);
}

void atz_bang(atz* x)
{
    outlet_int(x->c_out, x->c_value + x->c_offset);

    x->c_value = atz_calc(x, (int)x->c_value); //run again
}

void atz_free(atz* x)
{
    outlet_free(x->c_out);
}

void setup_noise0x2ecollatz()
{

    atz_class = eclass_new(("noise.collatz"),
        (t_typ_method)(atz_new),
        (t_typ_method)(atz_free),
        sizeof(atz), 0, A_GIMME, 0);

    eclass_addmethod(atz_class, (method)atz_bang, "bang", A_NULL, 0);
    eclass_addmethod(atz_class, (method)atz_int, "float", A_DEFFLOAT, 0);
    eclass_addmethod(atz_class, (method)atz_offset, "offset", A_DEFFLOAT, 0);
    eclass_addmethod(atz_class, (method)atz_mode, "mode", A_DEFFLOAT, 0);
    eclass_addmethod(atz_class, (method)atz_om, "om", A_DEFFLOAT, 0);
}
