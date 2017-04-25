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
#ifndef ARRAY_BASE_H
#define ARRAY_BASE_H

#include "ceammc_factory.h"
#include "ceammc_object.h"

using namespace ceammc;

class ArrayBase : public BaseObject {
public:
    ArrayBase(const PdArgs& a);

protected:
    t_symbol* name_;
    t_garray* findArray(t_symbol* s) const;
    long arraySize() const;
};

#endif // ARRAY_BASE_H
