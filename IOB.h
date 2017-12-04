
#ifndef XDLCOREGEN_IOB_H
#define XDLCOREGEN_IOB_H

#include <string>
#include <map>
#include "PrimitiveSite.h"
#include <sstream>

class IOB {
protected:
    std::string _name; /**< Name of the instance */
    std::map<std::string, std::string> _attributes; /**< attribute map */
    bool _placed; /**< True if placed, false if unplaced. */
    PrimitiveSite* _primitive_site; /**< pointer to the primitive site the instance is placed on. */

public:
    IOB(const std::string &_name);
    friend std::ostream& operator<<(std::ostream& os, IOB const& rhs);
    bool is_placed()const;
    void set_attribute(std::string attr, std::string val);
};


#endif //XDLCOREGEN_IOB_H
