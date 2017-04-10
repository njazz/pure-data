#include "mod_path.h"

extern "C" void setup_path0x2ebasename();
extern "C" void setup_path0x2edirname();
extern "C" void setup_path0x2ehome();
extern "C" void setup_path0x2elistdir();

void ceammc_path_setup()
{
#ifdef WITH_GLIB
    setup_path0x2ebasename();
    setup_path0x2edirname();
    setup_path0x2ehome();
    setup_path0x2elistdir();
#endif
}
