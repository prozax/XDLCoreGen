
#ifndef XDLCOREGEN_PRIMITIVESITE_H
#define XDLCOREGEN_PRIMITIVESITE_H


#include <string>
#include <iostream>

class Tile;

class PrimitiveSite {
protected:
    std::string _name; /**<  */
    std::string _type; /**<  */
    Tile* _parent; /**<  */
    int _pos_x; /**<  */
    int _pos_y; /**<  */
    bool _used; /**<  */

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
