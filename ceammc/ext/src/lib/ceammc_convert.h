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
#ifndef CEAMMC_CONVERT_H
#define CEAMMC_CONVERT_H

#include <string>

namespace ceammc {
namespace convert {
    namespace time {
        /**
         * @brief converts time in seconds to formatted time string: "00:00:00"
         */
        std::string sec2str(int sec);

        float str2sec(const std::string& str, float def = 0.f);
    }
}
}

#endif // CEAMMC_CONVERT_H
