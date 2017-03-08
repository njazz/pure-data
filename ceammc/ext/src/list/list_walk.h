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
#ifndef LIST_WALK_H
#define LIST_WALK_H

#include "ceammc_factory.h"
#include "ceammc_fn_list.h"
#include "ceammc_object.h"

namespace ceammc {

class ListWalk : public BaseObject {
    AtomList lst_;
    SymbolEnumProperty* walk_mode_;
    t_symbol* m_single_;
    t_symbol* m_clip_;
    t_symbol* m_wrap_;
    t_symbol* m_fold_;
    int current_pos_;
    int length_;
    bool forward_;
    bool single_done_;

public:
    ListWalk(const PdArgs& a);

    void onBang();
    void onList(const AtomList& l);

    void m_current(t_symbol*, const AtomList&);
    void m_next(t_symbol*, const AtomList& l);
    void m_prev(t_symbol*, const AtomList& l);
    void m_reset(t_symbol*, const AtomList&);

    AtomList p_size() const;
    AtomList p_index() const;

private:
    void next(int step = 1);
    void prev(int step = 1);
    void toPosition(int pos);
    void current();
};
}

#endif // LIST_WALK_H
