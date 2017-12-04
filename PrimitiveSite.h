
#ifndef XDLCOREGEN_PRIMITIVESITE_H
#define XDLCOREGEN_PRIMITIVESITE_H


#include <string>
#include <iostream>

class Tile;

class PrimitiveSite {
protected:
    std::string _name; /**< Name of the primitive site. */
    std::string _type; /**< Type of the primitive site. */
    Tile* _parent; /**< Pointer to the Tile containing this primitive site. */
    int _pos_x; /**< X coordinate of the primitive site. */
    int _pos_y; /**< Y coordinate of the primitive site. */
    bool _used; /**< True if something is placed on this primitive site, false if not. */

public:
    Tile *get_parent() const;
    void set_parent(Tile *_parent);
    const std::string &get_name() const;
    void set_name(const std::string &_name);
    const std::string &get_type() const;
    void set_type(const std::string &_type);
    int get_pos_x() const;
    void set_pos_x(int _pos_x);
    int get_pos_y() const;
    void set_pos_y(int _pos_y);
    bool is_used() const;
    void set_used(bool _used);
    PrimitiveSite(const std::string &_name, const std::string &_type, int _pos_x, int _pos_y, Tile* _parent);
    friend std::ostream& operator<<(std::ostream& os, PrimitiveSite const& rhs);
};


#endif //XDLCOREGEN_PRIMITIVESITE_H
