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
#ifndef FLOW_SYNC_H
#define FLOW_SYNC_H

#include "ceammc_message.h"
#include "ceammc_object.h"

#include <vector>

using namespace ceammc;
typedef std::vector<Message> MessageList;

class FlowSync : public BaseObject {
    MessageList msg_list_;

public:
    FlowSync(const PdArgs& a);

    void onInlet(size_t n, const AtomList& l);
    void onList(const AtomList& l);
    void onFloat(float v);
    void onSymbol(t_symbol* s);

private:
    void sync();
};

#endif // FLOW_SYNC_H
