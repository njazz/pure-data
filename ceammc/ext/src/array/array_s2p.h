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
#ifndef ARRAY_S2P_H
#define ARRAY_S2P_H

#include "array_base.h"

class ArraySampleToPhase : public ArrayBase {
public:
    ArraySampleToPhase(const PdArgs& a);

    /**
     * @brief converts sample position to phase [0..1]
     * @param sample position
     */
    void onFloat(t_float sample);
    void onList(const AtomList& lst);

private:
    t_object* sr_;
};

#endif // ARRAY_S2P_H
