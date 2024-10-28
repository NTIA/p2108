# GitHub Repository Public Release Approval

**Project Name:** NTIA/OSM Research and Development

**Software Name:** Recommendation ITU-R P.2108 - U.S. Reference Implementation

The project identified above, which is contained within the repository this
document is stored in, has met the following criteria for public release:

1. [x] The project, including the test criteria, meets the requirements defined
in the ITS Software Development Publication Policy for making a repository public.
The major pre-established criteria for publication are listed below, and the check
mark next to each attests that the criterion has been met.
    * [x] The repository contains unit tests and test data, and the software has
    been tested against these.
    * [x] The C++ header files required for this software are located in a folder
    which is named for their location within the ITS Propagation Library namespace,
    e.g. `include/ITS.Propagation.ITM`.
    * [x] The repository contains a top-level `CMakeLists.txt` which can be used
    to compile the software on Windows, Linux, and macOS.
    * [x] A GitHub action is provided in `.github/workflows` which compiles and
    tests the software on each of these operating systems.
    * [x] Any wrappers which provide bindings for this software in languages other
    than C++ are included as Git submodules.
    * [x] The repository includes the ITS Propagation Library `.clang-format` file,
    and all C++ source code has been auto-formatted using ClangFormat and this file.
    * [x] The repository includes the appropriate `LICENSE.md` file
2. [x] Any test data necessary for the code to function is included in this GitHub
repository.
3. [x] The README.md file is complete.
4. [x] The project complies with the ITS Code Style Guide or an appropriate style
guide as agreed to by the sponsor, project lead, or Supervising Division Chief.
5. [x] Approved disclaimer and licensing language has been included.

In order to complete this approval, please create a new branch, upload and commit
your version of this Markdown document to that branch, then create a pull request
for that branch. The following must login to GitHub and approve that pull request
before the pull request can be merged and this repo made public:

* Project Lead
* Supervising Division Chief or Release Authority
