# Recommendation ITU-R P.2108 #

[![NTIA/ITS PropLib][proplib-badge]][proplib-link]
[![GitHub Release][gh-releases-badge]][gh-releases-link]
[![GitHub Actions Unit Test Status][gh-actions-test-badge]][gh-actions-test-link]
[![C++ API Reference][gh-actions-docs-badge]][gh-pages-docs-link]
[![GitHub Issues][gh-issues-badge]][gh-issues-link]
[![DOI][doi-badge]][doi-link]

[proplib-badge]: https://img.shields.io/badge/PropLib-badge?label=%F0%9F%87%BA%F0%9F%87%B8%20NTIA%2FITS&labelColor=162E51&color=D63E04
[proplib-link]: https://ntia.github.io/propagation-library-wiki
[gh-actions-test-badge]: https://img.shields.io/github/actions/workflow/status/NTIA/p2108/ctest.yml?branch=main&logo=cmake&label=Build%2FTests&labelColor=162E51
[gh-actions-test-link]: https://github.com/NTIA/p2108/actions/workflows/ctest.yml
[gh-actions-docs-badge]: https://img.shields.io/github/actions/workflow/status/NTIA/p2108/doxygen.yml?branch=main&logo=c%2B%2B&label=Docs&labelColor=162E51
[gh-pages-docs-link]: https://ntia.github.io/p2108
[gh-releases-badge]: https://img.shields.io/github/v/release/NTIA/p2108?logo=github&label=Release&labelColor=162E51&color=D63E04
[gh-releases-link]: https://github.com/NTIA/p2108/releases
[gh-issues-badge]: https://img.shields.io/github/issues/NTIA/p2108?logo=github&label=Issues&labelColor=162E51
[gh-issues-link]: https://github.com/NTIA/p2108/issues
[doi-badge]: https://zenodo.org/badge/384267941.svg
[doi-link]: https://zenodo.org/badge/latestdoi/384267941

This repository contains the NTIA/ITS implementation of Recommendation ITU-R
P.2108. This Recommendation contains three methods for the prediction of clutter
loss: the Height Gain Terminal Correction Model, the Terrestrial Statistical Model,
and the Aeronautical Statistical Model. The software implements Section 3 of Annex 1
of the Recommendation.

Additional bindings to the shared library built from this repository are provided
for .NET, MATLAB, and Python in the following repositories:

- [NTIA/p2108-dotnet](https://github.com/NTIA/p2108-dotnet)
- [NTIA/p2108-matlab](https://github.com/NTIA/p2108-matlab)
- [NTIA/p2108-python](https://github.com/NTIA/p2108-python)

## Getting Started ##

To get started using this library, refer to
[its page on the **NTIA/ITS Propagation Library Wiki**](https://ntia.github.io/propagation-library-wiki/models/P2108/).
There, you will find installation instructions, usage information, and code
examples for all supported languages.

An executable is also provided which can be used to run the functions provided
by this library using plain text input and output files. Installation and usage
details for the command-line driver are also provided on
[the wiki](https://ntia.github.io/propagation-library-wiki/models/P2108/driver).

If you're a developer and would like to contribute to or extend this repository,
you will find comprehensive documentation of this C++ code
[here](https://ntia.github.io/P2108), and a guide for contributors
[here](CONTRIBUTING.md).

## Configure and Build ##

The software is designed to be built into a DLL (or corresponding `.so` or `.dylib`
library for non-Windows systems). A CMake build configuration and presets are
provided for cross-platform builds. Presets provide default sets of compiler flags,
and additional set default CMake options to control which parts of the project are
build. Below are a few examples of how this project can be built using provided presets.

```cmd
# From this repository's root directory, try one of the following command pairs:

# "Release" configurations compile the library and driver, build docs, and configure tests:
cmake --preset release64
cmake --build --preset release64

# "Debug" configurations skip building the docs, driver, and driver tests:
cmake --preset debug64
cmake --build --preset debug64

# Additional options can override presets:
cmake --preset debug64 -DBUILD_DRIVER=ON

# "DocsOnly" configurations only build the docs:
cmake --preset docsOnly
cmake --build --preset docsOnly
```

Note that this repository makes use of several
[Git submodules](https://git-scm.com/book/en/v2/Git-Tools-Submodules)
to reference dependencies used for running unit tests and building documentation.
In order to do either, ensure the required submodules are cloned by running:

```cmd
# From this repository's root directory
git submodule init
git submodule update
```

## Running Tests ##

If you've configured tests when building the project, for example by using one of
the "Release" or "Debug" CMake presets, you can run the included unit tests as follows:

```cmd
ctest --preset release
```

Additionally, the [Study Group Clutter Excel Workbook](https://www.itu.int/en/ITU-R/study-groups/rsg3/ionotropospheric/Clutter%20and%20BEL%20workbook_V2.xlsx)
contains an extensive set of example values which are useful as validation cases.

## References ##

- [ITS Propagation Library Wiki](https://ntia.github.io/propagation-library-wiki)
- [P2108 Wiki Page](https://ntia.github.io/propagation-library-wiki/models/P2108)
- [`ITS.ITU.PSeries.P2108` C++ API Reference](https://ntia.github.io/P2108)
- [Recommendation ITU-R P.2108](https://www.itu.int/rec/R-REC-P.2108/en)
- [Report ITU-R P.2402](https://www.itu.int/pub/R-REP-P.2402)

## Contact ##

For technical questions, contact <code@ntia.gov>.
