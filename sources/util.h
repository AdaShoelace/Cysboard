/*Copyright 2016 Michael Osei

This file is part of Cysboard.

Cysbaord is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Cysboard is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Cysboard.  If not, see <http://www.gnu.org/licenses/>.*/

/*
 * Contains MACROs and functions for handling common or repetitive tasks
 */

#ifndef UTIL_H
#define UTIL_H

#include <sciter/sciter-x-window.hpp>

template<class T>
static inline void NUM_TO_DOM_TEXT(T source, sciter::dom::element destination){
    std::string val = std::to_string(source);
    val.erase(val.find_last_not_of(".0") + 1);
    if(destination.is_valid()) {
        destination.set_text((const WCHAR*)aux::utf2w(val));
    }
}

static inline void STR_TO_DOM_TEXT(std::string source, sciter::dom::element destination) {
    if(destination.is_valid()) { \
        destination.set_text((const WCHAR*)aux::utf2w(source)); \
    }
}

#define DOM_TEXT_TO_NUM(source, destination) \
            destination = aux::wtoi(source.c_str()) \

#define DOM_TEXT_TO_STR(source, destination)\
            destination = aux::w2utf(source.c_str()) \

#define DOM_TEXT_TO_CSTR(source)\
            aux::w2utf(source.c_str()).c_str()\


#endif // UTIL_H
