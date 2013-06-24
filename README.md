[License]: LICENSE.md

[CMake]: http://www.cmake.org/

[Travis CI]: https://travis-ci.org/timothy-shields/pgm-cpp
[Build Status]: https://api.travis-ci.org/timothy-shields/pgm-cpp.png?branch=master
[.travis.yml]: .travis.yml

[Visual Studio 2012]: http://www.microsoft.com/visualstudio/eng/downloads#d-express-windows-desktop

[Probabilistic Graphical Models]: http://en.wikipedia.org/wiki/Graphical_model

# pgm-cpp: PGMs for C++11 done right

If you're interested in using or contributing to this library, or if you just have questions, **I'd really like to hear from you!**<br>
Contact me at timothy.shields@live.com.

## introduction

[Probabilistic Graphical Models][] provide a framwork for modelling and reasoning about probabilistic environments.

**pgm-cpp** brings the power of [Probabilistic Graphical Models][] to the C++11 environment - and in a way that's **"done right."**

### portability
[portability]: README.md#portability

**pgm-cpp** is written to be cross-platform and fully compliant with the C++11 standard. It currently **has no dependencies** outside of the C++11 standard library. It can be compiled and built using any of the following:

- [Visual Studio 2012][]
- gcc 4.6
- clang 3.1

### build system: [CMake][]

**pgm-cpp** is configured to build using the [CMake][] build system. For other projects already using [CMake][], integrating **pgm-cpp** as a dependency is a simple procedure.

### continuous integration: [Travis CI][] ![Build Status][]

**pgm-cpp** is built automatically by [Travis CI][]. Each time this GitHub repository updates, [Travis CI][] clones and builds the repository using the Linux compilers it provides (see the **[portability][]** section for the list of compilers). The Windows compilers (namely [Visual Studio 2012][]) have to be run manually outside of Travis.

*(coming soon)* Automated testing using Travis CI

The Travis configuration file is [.travis.yml][].

### licensing

**pgm-cpp** is licensed under the Apache License, Version 2.0. You can view the license file [here][License].

## [concepts][]

[Concepts]: http://en.cppreference.com/w/cpp/concept
[DefaultConstructible]: http://en.cppreference.com/w/cpp/concept/DefaultConstructible
[MoveConstructible]: http://en.cppreference.com/w/cpp/concept/MoveConstructible
[MoveAssignable]: http://en.cppreference.com/w/cpp/concept/MoveAssignable

The **linq-cpp** library is built on top of two foundation [concepts][], [`Enumerable<T>`][] and [`Enumerator<T>`][], mimicking the [`IEnumerable<T>`][] and [`IEnumerator<T>`][] interfaces from .NET, respectively. The definitions of these two concepts follow.

### `Factor`
[`Factor`]: README.md#enumerablet

*TODO*
