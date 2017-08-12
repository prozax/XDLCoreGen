#ifndef XDLGEN_SLICE_H
#define XDLGEN_SLICE_H


#include <string>
#include <map>
#include "PrimitiveSite.h"
#include "Tile.h"

class Slice {
protected:
    std::string _name;
    std::map<std::string, std::string> _attributes;
    bool _placed;
    PrimitiveSite* _primitive_site;

public:
    Slice(const std::string &_name);
    bool is_placed() const;
    void set_placed(bool placed);
    void set_name(const std::string &_name);
    const std::string &get_name() const;
    friend std::ostream& operator<<(std::ostream& os, Slice const& rhs);
    PrimitiveSite *get_primitive_site() const;
    void set_primitive_site(PrimitiveSite *_primitive_site);
};


#endif //XDLGEN_SLICE_H
