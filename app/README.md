# Command-line Driver # TODO

This document explains the use of the included command-line driver. This is a
supplemental software tool to allow a user to call the compiled propagation library
from the command-line using text files to provide inputs and store outputs.

## Input Files ##

Inputs to the command-line driver are specified in an ASCII text file using
the common `key,value` format. Each line holds a single `key,value` combination,
with the `key` representing the model input variable name and the `value` representing
its value. An example is included in this repository [here](./data/in.txt).
(TODO-TEMPLATE update the above example data info/link)

## Output Files ##

After parsing the inputs and running the software, the command-line driver will
generate an output report file containing the results. This file contains a record
of the input parameters, along with the model outputs, and human-readable supporting
documentation.

## Execution ##

Executing the command-line driver requires specifying input arguments, defined
in the below table:

(TODO-TEMPLATE review and update the flags below)
| Flag   | Type   | Required | Description                                                           |
|--------|--------|----------|-----------------------------------------------------------------------|
| `-i`   | string | True     | File specifying model input parameters in `key,value` format          |
| `-o`   | string | True     | Filename where output results should be written                       |
| `-t`   | string | True     | File containing comma-delimited terrain elevation data along the path |
| `-dbg` | N/A    | False    | If specified, intermediate values will be written to the output file  |

Additional arguments are available to print help text and version information:

| Flag | Description                                            |
|------|--------------------------------------------------------|
| `-h` | Display help text                                      |
| `-v` | Display version information for the library and driver |

Input arguments are not case sensitive and do not have to be specified in a certain
order. A generic example of calling the command-line driver on Windows is:

(TODO-TEMPLATE: update example driver command below)
```cmd
<Driver>.exe -i <input_file> -o <output_file>
```

### Examples ###

| Input File                          | Output File                         | Arguments                       |
|-------------------------------------|-------------------------------------|---------------------------------|
| [`i_asm.txt`](./data/i_asm.txt)     | [`o_asm.txt`](./data/o_asm.txt)     | `-i i_asm.txt -o o_asm.txt`     |
| [`i_hgtcm.txt`](./data/i_hgtcm.txt) | [`o_hgtcm.txt`](./data/o_hgtcm.txt) | `-i i_hgtcm.txt -o o_hgtcm.txt` |
| [`i_tsm.txt`](./data/i_tsm.txt)     | [`o_tsm.txt`](./data/o_tsm.txt)     | `-i i_tsm.txt -o o_tsm.txt`     |

## Command-line Driver Errors ##

(TODO-TEMPLATE: Update the below tables with your driver errors. Align with app/Errors.h)

In addition to the return codes defined by the library itself, the command-line
driver implements the following return codes.

### General Errors ###

| Value | Const Name                     | Description                                |
|-------|--------------------------------|--------------------------------------------|
| 1000  | `DRVR__RETURN_SUCCESS`         | Internal driver success code               |
| 1001  | `DRVRERR__MISSING_OPTION`      | No value provided for given argument       | 
| 1002  | `DRVRERR__INVALID_OPTION`      | Unknown option specified                   |
| 1003  | `DRVRERR__OPENING_INPUT_FILE`  | Failed to open the input file for reading  |
| 1004  | `DRVRERR__OPENING_OUTPUT_FILE` | Failed to open the output file for writing |

### Input File Parsing Errors ###

| Value | Const Name                    | Description                               |
|-------|-------------------------------|-------------------------------------------|
| 1100  | `DRVRERR__PARSE`              | General input file parsing error          |
| 1101  | `DRVRERR__PARSE_FREQ`         | Error parsing frequency value             |
| 1102  | `DRVRERR__PARSE_THETA`        | Error parsing theta value                 |
| 1103  | `DRVRERR__PARSE_PERCENTAGE`   | Error parsing percentage value            |
| 1104  | `DRVRERR__PARSE_HEIGHT`       | Error parsing antenna height value        |
| 1105  | `DRVRERR__PARSE_STREET_WIDTH` | Error parsing street width value          |
| 1106  | `DRVRERR__PARSE_REPR_HEIGHT`  | Error parsing representative height value |
| 1107  | `DRVRERR__PARSE_CLUTTER_TYPE` | Error parsing clutter type value          |
| 1108  | `DRVRERR__PARSE_PATH_DIST`    | Error parsing path distance value         |

### Validation Errors ###

Driver validation errors occur when required command line arguments are missing.
These validation errors are distinct from any defined within the library itself,
which may include, e.g., parameter out-of-range errors.

| Value | Const Name                         | Description                      |
|-------|------------------------------------|----------------------------------|
| 1200  | `DRVRERR__VALIDATION_IN_FILE`      | Input file not specified         |
| 1201  | `DRVRERR__VALIDATION_OUT_FILE`     | Output file  not specified       |
| 1202  | `DRVRERR__VALIDATION_MODEL`        | Model not specified              |