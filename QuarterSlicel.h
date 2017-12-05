#ifndef XDLCOREGEN_QUARTERSLICEL_H
#define XDLCOREGEN_QUARTERSLICEL_H

#include <string>
#include <map>
#include <sstream>

/*!
 * This class groups LUTs and registers of a Slicel together which exist in four exact copies in each Slicel.
 */
class QuarterSlicel {
private:
    std::string _name; /**< Name of this quarter slice. */
    std::map<std::string, std::string> _attributes; /**< Attribute map. */

public:
    QuarterSlicel(const std::string &_name);

    friend std::ostream& operator<<(std::ostream& os, QuarterSlicel const& rhs);
    const std::string & get_name() const;
    void set_name(const std::string &_name);
    void set_attribute(const std::string attr, const std::string val);
    const std::string get_attribute(std::string &attr) const;
};


#endif //XDLCOREGEN_QUARTERSLICEL_H
