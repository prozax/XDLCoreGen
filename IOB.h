
#ifndef XDLCOREGEN_IOB_H
#define XDLCOREGEN_IOB_H

#include <string>
#include <map>
#include "PrimitiveSite.h"
#include <sstream>

class IOB {
protected:
    std::string _name; /**<  */
    std::map<std::string, std::string> _attributes; /**<  */
    bool _placed; /**<  */
    PrimitiveSite* _primitive_site; /**<  */

public:
    IOB(const std::string &_name);
    friend std::ostream& operator<<(std::ostream& os, IOB const& rhs);
    bool is_placed()const;
    void set_attribute(std::string attr, std::string val);
};


#endif //XDLCOREGEN_IOB_H
