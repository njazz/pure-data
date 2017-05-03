/*****************************************************************************
 * Copyright 2017 Serge Poltavsky. All rights reserved.
 *
 * This file may be distributed under the terms of GNU Public License version
 * 3 (GPL v3) as defined by the Free Software Foundation (FSF). A copy of the
 * license should have been included with this file, or the project in which
 * this file belongs to. You may also find the details of GPL v3 at:
 * http://www.gnu.org/licenses/gpl-3.0.txt
 *
 * If you have any questions regarding the use of this file, feel free to
 * contact the author of this file, or the owner of the project in which
 * this file belongs to.
 *****************************************************************************/
#include "math_and.h"
#include "ceammc_factory.h"

#include <algorithm>

MathAnd::MathAnd(const PdArgs& a)
    : MathBool(a)
{
}

int MathAnd::check() const
{
    return (std::find(vars_.begin(), vars_.begin() + long(arg_num_), false) == vars_.end()) ? 1 : 0;
}

extern "C" void setup_math0x2eand()
{
    ObjectFactory<MathAnd> obj("math.and");
    obj.addAlias("and");
    obj.addMethod("reset", &MathAnd::m_reset);
}
