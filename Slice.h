#ifndef XDLGEN_SLICE_H
#define XDLGEN_SLICE_H


#include <string>
#include "PrimitiveSite.h"
#include "Tile.h"

class Slice {
protected:
    std::string _name;
    bool _placed;
    PrimitiveSite* _primitive_site;
    int _pos_x;
    int _pos_y;
public:
    Slice(const std::string &_name);
    int getPos_x() const;
    void setPos_x(int pos_x);
    int getPos_y() const;
    void setPos_y(int pos_y);
    bool isPlaced() const;
    void setPlaced(bool placed);
    void set_name(const std::string &_name);
    const std::string &get_name() const;
    friend std::ostream& operator<<(std::ostream& os, Slice const& rhs);
    PrimitiveSite *get_primitive_site() const;
    void set_primitive_site(PrimitiveSite *_primitive_site);
};


#endif //XDLGEN_SLICE_H
