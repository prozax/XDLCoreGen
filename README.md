# XDLCoreGen
XDLCoreGen provides a framework for creating FPGA hard macros in XDL (Xilinx Design Language).
It implements the multiplier described in the paper "An Efficient Softcore Multiplier Architecture for Xilinx FPGAs" by Kumm et al.

## Usage
### Creating a hard macro
You can create a hard macro by adding configured `Slicel`/`Slicem` objects to a `Module`, connecting them and adding ports.
For more complex hard macros it is recommended to create a class that is derived from `Module` which also gives you the ability
to override the `place()` method for a specialized placing algorithm.

The `Module` class contains slices, nets, and ports and is added to a `Design`.

```
Module m = Module("testmodule");

Slicel s = Slicel("testslicel1");
s.set_attribute("A6LUT", "A1*A2+A3");
s.set_attribute("AOUTMUX", "O6");
m.add_slice(s);

s = Slicel("testslicel2");
s.set_attribute("B5LUT", "A5");
s.set_attribute("BOUTMUX", "O5");
m.add_slice(s);
```
For a more information about attributes look at the *Slicel Attributes* section below.
LUT configurations always use *A1* through *A6* regardless of their actual input names.

Connections can be added with the `add_interconnect(<netname>)` method.

```
m.add_interconnect("net1")->set_outpin("testslicel1", "AMUX")->add_inpin("testslicel2", "B5");
```
This call creates a new `Net` or uses the existing one with the name "net1", sets an output pin, and adds an input pin.
A net can have one outpin and multiple inpins.
`add_inpin()` method calls can be chained together because it returns a pointer to the `Net` object.


Ports can be added with the `add_port()` method. Every port pin has to be used in a net. If it hasn't been used in a net previously you have to create a net with only that pin.
```
m.add_port("in(0)", "testslicel1", "A1");
m.add_interconnect("inpin<0>")->add_inpin("testslicel1", "A1");

m.add_port("out(0)", s, "BMUX");
m.add_interconnect("outpin<0>")->set_outpin(s.get_name(), "BMUX");
```

Since hard macros can't contain power nets they have to be replaced by a port. You can use the convenience methods
`add_vcc_connection()` and `add_ground_connection()` which add the pins to ground or vcc and create a port.
```
m.add_vcc_connection("testslicel1", "A2");
m.add_ground_connection("testslicel1", "A3");
```


To create a XDL file the module has to be added to a `Design`. The `Design` object needs a `Device` to place the slices onto.
```
Device d = Device("xc6vlx75tff484-3", "./devices/xc6vlx75tff484-3.xdl");
Design test_design = Design(d);
test_design.add_module(m);
test_design.place();
```

Now you can output the XDL source to any stream.

```
cout << test_design;
```

#### Creating a Design


### Generating a Multiplier hard macro
To customize the multiplier you can use the following parameters:

```
  -a, --a_length N     A input length. Default: 8
  -b, --b_length N     B input length. Default: 8
  -o, --output <path>  Output file path. If omitted the output will be printed.
  -p, --pipelined      Generate pipelined multiplier. Default: not pipelined
```

To display a list of possible parameters use *-h* or *--help*.

Example:
```
xdlcoregen -a 32 -b 32 -p -o 32x32_pipelined.xdl
```

The devices folder must be in the same directory as the executable.

## Using a hard macro
To use the hard macro in VHDL you need to convert the **.xdl* file to a **.nmc* file using the *xdl* tool with the *-xdl2ncd* parameter and a **.nmc* file as output.

```
xdl -xdl2ncd 32x32_pipelined.xdl 32x32_pipelined.nmc
```

This file can then be instanced as a component in VHDL. You also have to add a location constraint by adding

```
attribute LOC : string;
attribute LOC of <instance> : label is "SLICE_X0Y0";
```
 to the declaration block of the architecture where `<instance>` is the name of the hard macro component instance and `SLICE_X0Y0` contains the placing offsets of your hard macro (default is X0Y0).

### Simulating the output
To simulate the XDL output you need to generate a VHDL representation of the multiplier. To get this you have to generate a **.ncd* file first using the *xdl* tool with the *-xdl2ncd* parameter and an output file with the **.ncd* ending.

```
xdl -xdl2ncd 32x32_pipelined.xdl 32x32_pipelined.ncd
```

This **.ncd* file can then be converted to VHDL with the *netgen* tool.

```
netgen -ofmt vhdl -sim -w 32x32_pipelined.ncd
```

## Slicel Attributes
