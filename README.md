# XDLCoreGen
XDLCoreGen provides a framework for creating FPGA hard macros in XDL (Xilinx Design Language) for Xilinx Virtex 6 and 7 devices.
It also implements a multiplier described in the paper "An Efficient Softcore Multiplier Architecture for Xilinx FPGAs" by Martin Kumm, Shahid Abbas and Peter Zipf.

## Usage
### Creating a hard macro
You can create a hard macro by adding configured `Slicel`/`Slicem` objects to a `Module`, connecting them and adding ports.
For more complex hard macros it is recommended to create a class that is derived from `Module` which also gives you the ability
to override the `place()` method for a specialized placing algorithm.

The `Module` class contains slices, nets, and ports and is added to a `Design`. The `Slicel` class contains all configurable attributes of a Slicel and nets describe connections between slice inputs and outputs.

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
This creates two Slices with a basic configuration and adds them to the module. For a more information about attributes read the *Slicel Configuration* section below.

Connections can be added with the `add_interconnect(<netname>)` method.

```
m.add_interconnect("net1")->set_outpin("testslicel1", "AMUX")->add_inpin("testslicel2", "B5");
```
This creates a new `Net` or uses the existing one with the name "net1", sets an output pin, and adds an input pin.
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


To create an XDL file the module has to be added to a `Design`. The `Design` object needs a `Device` to place the slices onto.
```
Device d = Device("./devices/xc6vlx75tff484-3.xdl");
Design test_design = Design(d);
test_design.add_module(m);
test_design.place(0, 0);
```

Now you can output the XDL source to any stream.

```
cout << test_design;
```

For an example of a hard macro implemented as a class derived from `Module` with a custom placing algorithm see examples/ExampleModule.cpp.

#### Creating a carry chain
To create a carry chain the *PRECYINIT* attribute of the first slice in the chain has to be set to *0, 1* or *AX*. This is the initial value.
For every slice in the chain except the last *COUTUSED* has to be set to `0` (active). For the last slice it has to be set to `#OFF`.
For the next slices the COUT pin of the previous slice has to be connected to the CIN pin.

```
Module m = Module("testmodule");

Slicel s = Slicel("testslicel1");
s.set_attribute("PRECYINIT", "0");
m.set_attribute("COUTUSED", "0");
m.add_slice(s);

s = Slicel("testslicel2");
m.set_attribute("COUTUSED", "#OFF");
m.add_slice(s);

m.add_interconnect("carry<0-1>")->set_outpin("testslicel1", "COUT")->add_inpin("testslicel2", "CIN");
```

If you are using the build-in placing algorithm the slices have to be added to the module in the correct order.

## Using a hard macro
To use the hard macro in VHDL you need to convert the *\*.xdl* file to a *\*.nmc* file using the *xdl* tool with the *-xdl2ncd* parameter and a *\*.nmc* file as output.

```
xdl -xdl2ncd 32x32_pipelined.xdl 32x32_pipelined.nmc
```

This file can then be instanced as a component in VHDL with the file name as the component name. You have to add a location constraint by adding

```
attribute LOC : string;
attribute LOC of <instance> : label is "SLICE_X0Y0";
```
 to the declaration block of the architecture where `<instance>` is the
 name of the hard macro component instance and `SLICE_X0Y0` contains the placing offsets of your hard macro (default is X0Y0).
 The macro also has `vcc` and `gnd` inputs which have to be connected to `1` and `0`;


Here is an example of a VHDL wrapper for the integrated multiplier macro.
```
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity Mutliplier_32_pipelined is
    generic(word_size   : integer := 32);
    Port ( a : in  STD_LOGIC_VECTOR (word_size-1 downto 0);
           b : in  STD_LOGIC_VECTOR (word_size-1 downto 0);
           p : out  STD_LOGIC_VECTOR (word_size+word_size-1 downto 0);
           clk : in  STD_LOGIC);
end Mutliplier_32_pipelined;

architecture Behavioral of Mutliplier_32_pipelined is
component 32x32_pipelined is
    Port ( a : in  STD_LOGIC_VECTOR (word_size-1 downto 0);
            b : in  STD_LOGIC_VECTOR (word_size-1 downto 0);
            p : out  STD_LOGIC_VECTOR (word_size+word_size-1 downto 0);
            clk : in  STD_LOGIC;
            gnd : in  STD_LOGIC;
            vcc : in  STD_LOGIC);
end component;
   attribute LOC : string;
   attribute LOC of M1 : label is "SLICE_X0Y0";
begin
    M1: component 32x32_pipelined
        port map(p=>p,
                  a=>a,
                  b=>b,
                  clk=>clk,
                  gnd=>'0',
                  vcc=>'1');
end Behavioral;
```

### Simulating the output
Since hard macros can't be used in a simulation, a VHDL representation has to be created first. To get this you have to generate a *\*.ncd* file using the *xdl* tool with the *-xdl2ncd* parameter and an output file with the *\*.ncd* ending.

```
xdl -xdl2ncd 32x32_pipelined.xdl 32x32_pipelined.ncd
```

This *\*.ncd* file can then be converted to VHDL with the *netgen* tool.

```
netgen -ofmt vhdl -sim -w 32x32_pipelined.ncd 32x32_pipelined.vhd
```
This VHDL output can then be used like any other VHDL entity and has the same configuration as the XDL macro.


## Creating device description files
Device description files can be created with the xdl tool using the `-report` switch.

```
xdl -report xc6vlx75tff784
```


## Slicel Configuration
#### General Slicel configuration
| Attribute | Explanation | Value | Default  |
|-----------|-------------|-------|----------|
| PRECYINIT | Carry chain initial value. | #OFF (not used) <br>0 <br>1 <br>AX (AX input pin) | #OFF |
| SRUSEDMUX | SR input of the flip-flops used. | #OFF (not used) <br>0 (used) | #OFF |
| SYNC_ATTR | Reset type. | #OFF (not used) <br>SYNC <br>ASYNC | #OFF |
| COUTUSED | Carry chain output used. | #OFF (not used) <br>0 (used) | #OFF |
| CLKINV | Clock inverter. | #OFF (not used) <br>0 (used) | #OFF |

#### Slicel LUT/Register configuration
These attributes are prefixed by *A, B, C* or *D* and configure one logic unit in a slice.

| Attribute | Explanation | Value | Default |
|-----------|-------------|-------|----------|
| 5FFINIT | 5FF register initial value. | #OFF (not used)<br>INIT0<br>INIT1 | #OFF |
| 5FFMUX | 5FF register input selection. | #OFF (not used)<br>O5 <br>(A-D)X | #OFF |
| 5FFSR | 5FF register initial SR value. | #OFF (not used)<br>SRLOW <br>SRHIGH | #OFF |
| 5LUT | O5 function. | string (see below) | |
| 5LUTNAME | O5 LUT name. | string | |
| 6LUT | O6 function. | string (see below) | |
| 6LUTNAME | O6 LUT name. | string | |
| CY0 | Select carry *propagate* (DI) input. | #OFF (not used)<br>O5 <br>(A-D)X | #OFF |
| FF | Latch/register | #OFF (not used)<br>#FF <br>#LATCH | #OFF |
| FFNAME | Latch/register name | string | |
| FFINIT | Latch/register initial value. | #OFF (not used)<br>INIT0 <br>INIT1 | #OFF |
| FFMUX | Latch/register input selection. | #OFF (not used)<br>F7 <br>CY (carry) <br>XOR (previous carry XOR O6)<br>(A-D)X (X input pass through) <br>O5 (5LUT output) <br>O6 (6LUT output)| #OFF |
| FFSR | Latch/register initial SR value. | #OFF (not used)<br>SRLOW <br>SRHIGH | #OFF |
| OUTMUX | OUTMUX output selection | #OFF (not used)<br>A5Q (5FF output) <br>F7 <br>CY (carry) <br>XOR (previous carry XOR O6) <br>O5 (5LUT output) <br>O6 (6LUT output) | #OFF |
| USED | O6 pass through output used. | #OFF (not used)<br>0 (active) | #OFF |


##### LUT configuration
LUT configurations use variables A1-A5 for 5LUTs or A1-A6 for 6LUTs and the boolean operators from the table below. All LUTs use A for variables regardless of their name.

| Operator | Symbol |
|----------|--------|
| NOT      | ~      |
| AND      | *      |
| OR       | +      |
| XOR      | @      |

Examples:
```
s1.set_attribute("B6LUT", "(A5*A6)");
s2.set_attribute("D6LUT", "(A6+~A6)*(((~A2*(A3*(A4@A5)))+(A2*(A3+(A4@A5)))))");
s3.set_attribute("C5LUT", "(((~A2*(A3*(A4@A5)))+(A2*(A3+(A4@A5)))))");
```

## Generating a Multiplier hard macro
To customize the multiplier you can use the following parameters:

```
  XDLCoreGen [OPTION...]

  -d, --device_file <path>  Device file path.
      --multiplier          Generate a mutliplier macro.
  -o, --output <path>       Output file path. If omitted the output will be
                            printed.
  -p, --pipelined           Generate pipelined macro. Default: not pipelined
  -x, --x_offset N          X offset for the placer. Default: 0
  -y, --y_offset N          Y offset for the placer. Default: 0
  -h, --help                Print help

 multiplier options:
  -a, --a_length N  A input length. Default: 8
  -b, --b_length N  B input length. Default: 8
```

To display a list of possible parameters use *-h* or *--help*.

Example:
```
xdlcoregen --multiplier --a_length 32 --b_length 32 --pipelined --device_file "./device/xc6vlx75tff484-3.xdl" --output 32x32_pipelined.xdl
```
This creates a pipelined mutliplier with 32x32 inputs using the device described in *xc6vlx75tff484-3.xdl* and writes it to *32x32_pipelined.xdl*.

## Limitations
This framework currently only supports the creation of hard macros. This means a design must contain a single module with ports and no further nets or instances.

## Credits
* Martin Kumm, Shahid Abbas and Peter Zipf: An Efficient Softcore Multiplier Architecture for Xilinx FPGAs In: 22nd IEEE Symposium on Computer Arithmetic (ARITH 22), 2015 ([preprint](http://www.uni-kassel.de/eecs/fileadmin/datas/fb16/Fachgebiete/Digitaltechnik/preprints/2015_ARITH_kumm.pdf), copyright IEEE, http://dx.doi.org/10.1109/ARITH.2015.17)
* Ghosh, Subhrashankha, "XDL-Based Hard Macro Generator" (2011). All Theses and Dissertations. 2507. https://scholarsarchive.byu.edu/etd/2507
* Option parser library [cxxopts](https://github.com/jarro2783/cxxopts)
