#ifndef XDLCOREGEN_QUARTERSLICEL_H
#define XDLCOREGEN_QUARTERSLICEL_H

#include <string>

class QuarterSlicel {
private:
    static int slicel_count = 0;

    std::string _name;

    std::string _5FFINIT;
    std::string _5FFMUX;
    std::string _5FFSR;
    std::string _5LUT;
    std::string _5LUTNAME;
    std::string _6LUT;
    std::string _6LUTNAME;
    std::string _CY0;
    std::string _FF;
    std::string _FFINIT;
    std::string _FFMUX;
    std::string _FFSR;
    std::string _OUTMUX;
    std::string _USED;

public:
    QuarterSlicel(const std::string &_name);
    QuarterSlicel(const std::string &_name, const std::string &_5FFINIT, const std::string &_5FFMUX,
                  const std::string &_5FFSR, const std::string &_5LUT, const std::string &_5LUTNAME,
                  const std::string &_6LUT, const std::string &_6LUTNAME, const std::string &_CY0,
                  const std::string &_FF, const std::string &_FFINIT, const std::string &_FFMUX,
                  const std::string &_FFSR, const std::string &_OUTMUX, const std::string &_USED);

    const std::string to_string() const;

    const std::string & get_name() const;
    void set_name(const std::string &_name);
    const std::string & get_5FFINIT() const;
    void set_5FFINIT(const std::string &_5FFINIT);
    const std::string & get_5FFMUX() const;
    void set_5FFMUX(const std::string &_5FFMUX);
    const std::string & get_5FFSR() const;
    void set_5FFSR(const std::string &_5FFSR);
    const std::string & get_5LUT() const;
    void set_5LUT(const std::string &_5LUT);
    const std::string & get_5LUTNAME() const;
    void set_5LUTNAME(const std::string &_5LUTNAME);
    const std::string & get_6LUT() const;
    void set_6LUT(const std::string &_6LUT);
    const std::string & get_6LUTNAME() const;
    void set_6LUTNAME(const std::string &_6LUTNAME);
    const std::string & get_CY0() const;
    void set_CY0(const std::string &_CY0);
    const std::string & get_FF() const;
    void set_FF(const std::string &_FF);
    const std::string & get_FFINIT() const;
    void set_FFINIT(const std::string &_FFINIT);
    const std::string & get_FFMUX() const;
    void set_FFMUX(const std::string &_FFMUX);
    const std::string & get_FFSR() const;
    void set_FFSR(const std::string &_FFSR);
    const std::string & get_OUTMUX() const;
    void set_OUTMUX(const std::string &_OUTMUX);
    const std::string & get_USED() const;
    void set_USED(const std::string &_USED);
};


#endif //XDLCOREGEN_QUARTERSLICEL_H
