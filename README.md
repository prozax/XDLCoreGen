# XDLCoreGen
This program generates an efficient multiplier hard macro in XDL (Xilinx Design Language).
It implements the multiplier described in the paper "An Efficient Softcore Multiplier Architecture for Xilinx FPGAs" by Kumm et al.

## Usage
### Generating a XDL hard macro
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


### Using the hard macro
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
