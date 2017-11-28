# XDLCoreGen
XDLCoreGen provides a framework for creating FPGA hard macros in XDL (Xilinx Design Language) for Xilinx VIrtex 6 and 7 devices.
It also implements the multiplier described in the paper "An Efficient Softcore Multiplier Architecture for Xilinx FPGAs" by Kumm et al.

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

## Creating device description files
Device description files can be created with the xdl tool using the `-report` switch.

```
xdl -report xc6vlx75tff784
```


## Slicel Attributes
#### General Slice configuration
| Attribute | Explanation | Value | Default  |
|-----------|-------------|-------|----------|
| PRECYINIT | Carry chain initial value | #OFF, 0, 1, AX | #OFF
|SRUSEDMUX | SR input of the flip-flops used. | #OFF, 0 (used) | #OFF
|SYNC_ATTR | Reset type. | #OFF, SYNC, ASYNC | #OFF
|COUTUSED | Carry chain output used. | #OFF (not used) / 0 (used) | #OFF
|CLKINV | Clock inverted | #OFF (not used) / 0 (used) | #OFF

#### Slicel LUT(?) configuration
These attributes are prefixed by *A, B, C* or *D* and configure one logic unit in a slice.

| Attribute | Explanation | Value | Default |
|-----------|-------------|-------|----------|
| 5FFINIT | 5FF register initial value. | #OFF, <p>INIT0, INIT1 | #OFF
| 5FFMUX | 5FF register input selection. | #OFF, A5Q (5FF output), F7, CY(carry), XOR (previous carry XOR O6), O5 (5LUT output), O6 (6LUT output) | #OFF
| 5FFSR |
| 5LUT |
| 5LUTNAME |
| 6LUT |
| 6LUTNAME |
| CY0 | Select carry *propagate* (DI) input. | #OFF, O5, (A-D)X
| FF | Latch/register | #OFF, #FF, #LATCH
| FFNAME | Latch/register name | either empty or string
| FFINIT | Latch/register initial value. | #OFF, INIT0, INIT1
| FFMUX | Latch/register input selection. | #OFF, F7, CY, XOR, AX, O5, O6
| FFSR
| OUTMUX |
| USED | O6 pass through output used. | #OFF, 0 (active)

##### LUT configuration
LUT configurations use variables A1-A5 for 5LUTs and A1-A6 for 6LUTs and the boolean operators from the table below. All LUTs use A for variables regardless of their name.

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