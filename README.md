# Recommendation ITU-R P.2108 - U.S. Reference Implementation #

<!-- TODO on v1.0 release created: add updated DOI badge -->
[![GitHub Actions Unit Tests Status][gh-actions-test-badge]][gh-actions-test-link]
[![C++ API Reference][gh-actions-docs-badge]][gh-actions-docs-link]
![GitHub Release](https://img.shields.io/github/v/release/NTIA/P2108)
![GitHub Issues](https://img.shields.io/github/issues/NTIA/P2108)
<!-- [![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.7114033.svg)](https://doi.org/10.5281/zenodo.7114033) -->

[gh-actions-test-link]: https://github.com/NTIA/p2108/actions/workflows/ctest.yml
[gh-actions-test-badge]: https://github.com/NTIA/p2108/actions/workflows/ctest.yml/badge.svg?branch=main
[gh-actions-docs-link]: https://github.com/NTIA/p2108/actions/workflows/doxygen.yml
[gh-actions-docs-badge]: https://github.com/NTIA/p2108/actions/workflows/doxygen.yml/badge.svg?branch=main

This code repository contains the U.S. Reference Software Implementation of
Recommendation ITU-R P.2108. This Recommendation contains three methods for the
prediction of clutter loss: the Height Gain Terminal Correction Model, the
Terrestrial Statistical Model, and the Aeronautical Statistical Model. The software
implements Section 3 of Annex 1 of the Recommendation.

## Getting Started ##

To get started using this model, refer to
[its page on the **NTIA/ITS Propagation Library Wiki**](https://ntia.github.io/propagation-library-wiki/models/P2108/).
There, you will find installation instructions, usage information, and code
examples for all supported languages.

If you're a developer and would like to contribute to or extend this repository,
you will find comprehensive documentation of this C++ code
[here](https://ntia.github.io/P2108), and a guide for contributors
[here](CONTRIBUTING.md).

## Configure and Build ##

The software is designed to be built into a DLL (or corresponding `.so` or `.dylib`
library for non-Windows systems). A CMake build configuration and presets are
provided for cross-platform builds, which can be carried out, for example, by:

```cmd
# From this repository's root directory, try one of the following command pairs:

# "Release" configurations compile the library, build docs, and configure tests:
cmake --preset release64
cmake --build --preset release64

# "Debug" configurations skip building the docs:
cmake --preset debug64
cmake --build --preset debug64

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
git submodule init extern/googletest           # Required to run tests
git submodule init extern/doxygen-awesome-css  # Required to build docs
git submodule update                           # Clones the initialized submodules
```

## Running Tests ##

If you've configured tests when building the project, for example by using one of
the "Release" or "Debug" CMake presets, you can run the included unit tests as follows:

```cmd
ctest --preset release64
```

Additionally, the [Study Group Clutter Excel Workbook](https://www.itu.int/en/ITU-R/study-groups/rsg3/ionotropospheric/Clutter%20and%20BEL%20workbook_V2.xlsx)
contains an extensive set of example values which are useful as validation cases.

## References ##

* [ITS Propagation Library Wiki](https://ntia.github.io/propagation-library-wiki)
* [`ITS.ITU.PSeries.P2108` C++ API Reference](https://ntia.github.io/P2108)
* [Recommendation ITU-R P.2108](https://www.itu.int/rec/R-REC-P.2108/en)
* [Report ITU-R P.2402](https://www.itu.int/pub/R-REP-P.2402)

## Contact ##

For technical questions, contact <code@ntia.gov>.
