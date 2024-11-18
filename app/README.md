# Command-line Driver #

This document explains the use of the included command-line driver. This is a
supplemental software tool to allow a user to call the compiled propagation library
from the command-line using text files to provide inputs and store outputs.

## Input Files ##

Inputs to the command-line driver are specified in an ASCII text file using
the common `key,value` format. Each line holds a single `key,value` combination,
with the `key` representing the model input variable name and the `value` representing
its value.

## Output Files ##

After parsing the inputs and running the software, the command-line driver will
generate an output report file containing the results. This file contains a record
of the input parameters, along with the model outputs, and human-readable supporting
documentation.

## Execution ##

Executing the command-line driver requires specifying input arguments, defined
in the below table:

| Flag     | Type   | Required | Description                                                  |
|----------|--------|----------|--------------------------------------------------------------|
| `-i`     | string | true     | File specifying model input parameters in `key,value` format |
| `-model` | string | true     | Which model to run, one of `HGTCM`, `TSM`, or `ASM`          |
| `-o`     | string | true     | Filename where output results should be written              |

Additional arguments are available to print help text and version information:

| Flag | Description                                            |
|------|--------------------------------------------------------|
| `-h` | Display help text                                      |
| `-v` | Display version information for the library and driver |

Input arguments are not case sensitive and do not have to be specified in a certain
order. A generic example of calling the command-line driver on Windows is:

```cmd
P2108Driver.exe -i input.txt -model ASM -o output.txt
```

### Examples ###

The following files are included as references for the functionality of this software.
Using these input files and the commands specified should produce outputs identical
to the provided corresponding output files.

| Input File                          | Output File                         | Arguments                                    |
|-------------------------------------|-------------------------------------|----------------------------------------------|
| [`i_hgtcm.txt`](./data/i_hgtcm.txt) | [`o_hgtcm.txt`](./data/o_hgtcm.txt) | `-i i_hgtcm.txt -model HGTCM -o o_hgtcm.txt` |
| [`i_tsm.txt`](./data/i_tsm.txt)     | [`o_tsm.txt`](./data/o_tsm.txt)     | `-i i_tsm.txt -model TSM -o o_tsm.txt`       |
| [`i_asm.txt`](./data/i_asm.txt)     | [`o_asm.txt`](./data/o_asm.txt)     | `-i i_asm.txt -model ASM -o o_asm.txt`       |

## Command-line Driver Errors ##

In addition to the return codes defined by the library itself, the command-line
driver implements its own set of return codes in [`app/include/ReturnCodes.h`](./include/ReturnCodes.h).
A helper function to map human-readable status messages to these codes in
[`app/src/ReturnCodes.cpp`](./src/ReturnCodes.cpp).
