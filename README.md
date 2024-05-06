# Recommendation ITU-R P.2108-1 - U.S. Reference Implementation #

Persistent Identifier: [![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.7114033.svg)](https://doi.org/10.5281/zenodo.7114033)

This code repository contains the U.S. Reference Software Implementation of
Recommendation ITU-R P.2108. This Recommendation contains three methods for the
prediction of clutter loss: [Height Gain Terminal Correction Model](README.md#height-gain-terminal-correction-model),
[Terrestrial Statistical Model](README.md#terrestrial-statistical-model),
[Aeronautical Statistical Model](README.md#aeronautical-statistical-model).
The software implements Section 3 of Annex 1 of the Recommendation.

## Height Gain Terminal Correction Model ##

The height gain terminal correction model is described in Section 3.1.
This end-point clutter method gives the median loss due to different terminal
surroundings for terrestrial paths for frequencies between 0.3 to 3 GHz. This
model can be applied to both transmitting and receiving ends of the path.

### Inputs (Height Gain Terminal Correction Model) ###

| Variable       | Type   | Units | Limits               | Description                   |
|----------------|--------|-------|----------------------|-------------------------------|
| `f__ghz`       | double | GHz   | 0.3 <= `f__ghz` <= 3 | Frequency                     |
| `h__meter`     | double | meter | 0 <= `h__meter`      | Antenna height                |
| `w_s__meter`   | double | meter | 0 < `w_s__meter`     | Street width                  |
| `R__meter`     | double | meter | 0 < `R__meter`       | Representative clutter height |
| `clutter_type` | int    |       |                      | Clutter type <ul><li>1 = Water/sea</li><li>2 = Open/rural</li><li>3 = Suburban</li><li>4 = Urban</li><li>5 = Trees/forest</li><li>6 = Dense urban</li></ul> |

Where site-specific values for the representative clutter height are not available,
the following default values are recommended.

| Clutter Type | `R__meter` |
|--------------|:----------:|
| Water/sea    |         10 |
| Open/rural   |         10 |
| Suburban     |         10 |
| Urban        |         15 |
| Trees/forest |         15 |
| Dense urban  |         20 |

### Outputs (Height Gain Terminal Correction Model) ###

| Variable   | Type   | Units | Description |
|------------|--------|-------|-------------|
| `A_h__db`  | double | dB    | Additional loss (clutter loss) |

### Return Codes (Height Gain Terminal Correction Model) ###

Possible return codes, including the corresponding defined constant name as
defined in [`Errors.h`](include/Errors.h):

| Value | Const Name                | Description                                        |
|-------|---------------------------|----------------------------------------------------|
| 0     | `SUCCESS`                 | Successful execution                               |
| 3100  | `ERROR31__FREQUENCY`      | Frequency must be between 0.3 and 3 GHz, inclusive |
| 3101  | `ERROR31__ANTENNA_HEIGHT` | Antenna height must be >= 0 meters                 |
| 3102  | `ERROR31__STREET_WIDTH`   | Street width must be > 0 meters                    |
| 3103  | `ERROR31__CLUTTER_HEIGHT` | Representative clutter height must be > 0 meters   |
| 3104  | `ERROR31__CLUTTER_TYPE`   | Invalid value for clutter type                     |

## Terrestrial Statistical Model ##

The statistical clutter loss model for terrestrial paths as described in Section
3.2. This model is valid for urban and suburban clutter environments. For paths
between 0.25 and 1 km, this model can only be applied to one end of the path.
For paths greater than 1 km, the model can be applied to both terminals, if desired.

### Inputs (Terrestrial Statistical Model) ###

| Variable | Type   | Units | Limits              | Description   |
|----------|--------|-------|---------------------|---------------|
| `f__ghz` | double | GHz   | 2 <= `f__ghz` <= 67 | Frequency     |
| `d__km`  | double | km    | 0.25 <= `d__km`     | Path distance |
| `p`      | double | %     | 0 < `p` < 100       | Percentage of locations clutter loss not exceeded |

### Outputs (Terrestrial Statistical Model) ###

| Variable   | Type   | Units | Description |
|------------|--------|-------|-------------|
| `L_ctt__db` | double | dB   | Clutter loss |

### Return Codes (Terrestrial Statistical Model) ###

Possible return codes, including the corresponding defined constant name as
defined in [`Errors.h`](include/Errors.h):

| Value | Const Name            | Description                                       |
|-------|-----------------------|---------------------------------------------------|
| 0     | `SUCCESS`             | Successful execution                              |
| 3200  | `ERROR32__FREQUENCY`  | Frequency must be between 2 and 67 GHz, inclusive |
| 3201  | `ERROR32__DISTANCE`   | Path distance must be >= 0.25 km                  |
| 3202  | `ERROR32__PERCENTAGE` | Percentage must be between 0 and 100              |

## Aeronautical Statistical Model ##

The Earth-space and aeronautical statistical clutter loss model as described in
Section 3.3. This model is applicable when one end of the path is within man-made
clutter and the other end is a satellite, aeroplane, or other platform above the
Earth. This model is valid for urban and suburban clutter environments.

### Inputs (Aeronautical Statistical Model) ###

| Variable     | Type   | Units | Limits                  | Description     |
|--------------|--------|-------|-------------------------|-----------------|
| `f__ghz`     | double | GHz   | 10 <= `f__ghz` <= 100   | Frequency       |
| `theta__deg` | double | deg   | 0 <= `theta__deg` <= 90 | Elevation angle |
| `p`          | double | %     | 0 < `p` < 100 | Percentage of locations clutter loss not exceeded |

### Outputs (Aeronautical Statistical Model) ###

| Variable   | Type   | Units | Description |
|------------|--------|-------|-------------|
| `L_ces__db` | double | dB    | Clutter loss |

### Return Codes (Aeronautical Statistical Model) ###

Possible return codes, including the corresponding defined constant name as defined
in [`Errors.h`](include/Errors.h):

| Value | Const Name            | Description                                              |
|-------|-----------------------|----------------------------------------------------------|
| 0     | `SUCCESS`             | Successful execution                                     |
| 3300  | `ERROR33__FREQUENCY`  | Frequency must be between 10 and 100 GHz, inclusive      |
| 3301  | `ERROR33__THETA`      | Elevation angle must be between 0 and 100 GHz, inclusive |
| 3302  | `ERROR33__PERCENTAGE` | Percentage must be between 0 and 100, inclusive          |

## Example Values ##

The [Study Group Clutter Excel Workbook](https://www.itu.int/en/ITU-R/study-groups/rsg3/ionotropospheric/Clutter%20and%20BEL%20workbook_V2.xlsx)
contains an extensive set of validation example values.

## Notes on Code Style ##

* In general, variables follow the naming convention in which a single underscore
denotes a subscript (pseudo-LaTeX format), where a double underscore is followed
by the units, i.e. `h_1__meter`.
* Variables are named to match their corresponding mathematical variables in the
underlying Recommendation text.
* Wherever possible, equation numbers are provided. It is assumed that a user
reviewing this source code would have a copy of the Recommendation's text available
as a primary reference.

## Configure and Build ##

### C++ Software ###

The software is designed to be built into a DLL (or corresponding library for
non-Windows systems). The source code can be built for any OS that supports the
standard C++ libraries. A Visual Studio 2019 project file is provided for Windows
users to support the build process and configuration.

### C#/.NET Wrapper Software ###

The .NET support of P.2108 consists of a simple pass-through wrapper around the
native DLL. It is compiled to target .NET Framework 4.8.1. Distribution and updates
are provided through the published [NuGet package](https://github.com/NTIA/p2108/packages).

## References ##

* [Recommendation ITU-R P.2108](https://www.itu.int/rec/R-REC-P.2108/en)
* [Report ITU-R P.2402](https://www.itu.int/pub/R-REP-P.2402)

## Contact ##

For questions, contact Billy Kozma, (303) 497-6082, <wkozma@ntia.gov>
