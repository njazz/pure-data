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
#include "conv_bpm2sec.h"
#include "ceammc_factory.h"

static t_float bpm2sec(t_float v)
{
    return 60 / v;
}

BpmToSec::BpmToSec(const PdArgs& a)
    : BaseObject(a)
{
    createOutlet();
}

void BpmToSec::onFloat(t_float v)
{
    floatTo(0, bpm2sec(v));
}

void BpmToSec::onList(const AtomList& lst)
{
    listTo(0, lst.map(bpm2sec));
}

extern "C" void setup_conv0x2ebpm2sec()
{
    ObjectFactory<BpmToSec> obj("conv.bpm2sec");
    obj.addAlias("bpm->sec");
}
