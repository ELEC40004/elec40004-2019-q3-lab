ELEC40004 Quarter 3, Lab3
=========================

Aims of this lab
================

Context
-------

In the previous lab we looked at the idea of representing real-world
things as objects, and in particular coming up with a way of representing
a simulated EEBug as an object. By defining a single `Rover` class
we were able to have multiple users and implementations of the class:

- Two implementations of the `Rover` class, which captured transient
  behaviour over time or integrated behaviour over all of time.

- Three controllers of the `Rover` class, which could drive any instance
  of the class (no matter how it is implemented) to achieve specific
  patterns.

By seperating the implementations out into different source files
(rather than keeping them in header files), we were able to create
six different programmes, representing each possible combination of
controller and implementation. Each controller was completely independent of the
implementation, and each implementation is independent of the controller; all
we need to do is to select which versions get compiled in.

While this allowed us to seperate user and implementation, it has two
key disadvantages:

- If we have $n$ controllers and $m$ implementations, we have to compile $n*m$
  different programs. If we had 20 controllers and 6 different implementations,
  we need to compile 120 programs to cover all combinations.

- It is not possible to combine multiple implementations in one programme, nor
  can we have multiple controllers. In both cases we'll get linker errors, which are errors
  that come after the source code has been compiled but before it has linked
  the definitions into a program. Here they' come
  either from the multiple definitions of the `Rover` methods, or the 
  multiple definitions of `main`.

The goal now is to use basic inheritance to allows us to select between
multiple Rover implementations at run-time, without re-compiling.

Aims
----

The main aims of this lab are to:

- Convert an existing class with two definitions into a class heirarchy
  with a shared abstract base-class.

- Exploit shared functionality between different classes.

- Use command-line parameters to choose different functionality.

The steps in the lab are mirrored by simpler versions of the same steps in the portfolio.

Standard Tasks
==============

This lab starts at the end of the previous lab, so it is reccommended that you
do that lab first. However, this directory contains a snapshot of the
source files at the end point of the previous lab, so you can start from
here as well if you want to. 

You should start by merging this specification into your local working copy
of the repository. This directory is completely seperate from the previous
`lab2` directory, so it should merge without any conflicts.

There are three controller sources, which means you'll need to do certain
things three times. The idea here is that they are relatively simple
to do once you've done it once (it's mostly changing a couple of lines
of code), plus the quick repetition means that it is more likely to sink in.

We're going to be refactoring this code, which means we want it to have
the same function aferwards as before. As a matter of habit you should
think about capturing the output of the programs in their initial state,
so that at the end you can check that it hasn't changed (and ideally
also check whenever you get a stable version). You
also want to double-check the code all actually compiles... If you have
already done the previous lab, then you should have this test
infrastructure already in the `lab2` directory, and can copy it here.

If you haven't done the previous lab, the files in here can be built
using variations of the following compilation command:
```
$ g++ controller_CONTROLLER.cpp rover_IMPLEMENTATION.cpp vector2d.cpp
```
Where CONTROLLER is one of "brownian", "circle", "spiral", and
IMPLEMENTATION is one of "action_writer", "svg_writer". Each
combination of CONTROLLER and IMPLEMENTATION gives a different
program, and you should ideally capture the output of each (you'll
need them in step 10).


1 - Create two new classes: `RoverSVGWriter` and `RoverActionWriter`
--------------------------------------------------------------------

At the moment the SVG writer and action writer implementations share
exactly the same declaration of `Rover` in `Rover.hpp`. This is why
you can't compile both `rover_action_writer.cpp` and `rover_SVG_writer.cpp`
into the same program, as they both attempt to provide definitions of
the same `Rover` methods.

We are first going to seperate the classes up so that they have completely
seperate types `RoverActionWriter` and `RoverSVGWriter`, and then later
we will join them back up via a shared base class `Rover`.

**Task**: Make the two classes distinct, with one class called `RoverActionWriter`
with header `rover_action_writer.hpp`, the other class called `RoverSVGWriter`
with header `rover_svg_writer.hpp`.

To do this you should:

1. Copy the `Rover.hpp` file to create the two new header files (leaving `Rover.hpp`
  unmodified)
2. Change the `#ifndef rover_hpp` at the top of each new header to use something other
   than `rover_hpp`.
3. Change the `Rover` class name in the two new headers to match the new class names
  (`RoverActionWriter` and `RoverSVGWriter`).
4. Change the `#include "Rover.hpp"` in the source files `rover_action_writer.cpp` and
   `rover_svg_writer.cpp` to include the specific header file associated with the source
   file.
5. Change the uses of `Rover` in `rover_action_writer.cpp` and `rover_svg_writer.cpp`
   to match the new class names.


Once this is complete, you should be able to _almost_ compile either `rover_action_writer.cpp`
or `rover_svg_writer.cpp` by themselves, but it will fail to link into a
full program due to the lack of a `main` function. You should also be able to 
_almost_ compile the controllers as before, but they will also fail to link
due to the lack of an implementation of the `Rover` member functions.

2 - Convert `Rover` into an abstract base class
-------------------------------------

As it stands, the `Rover` class is left as a "normal" class declaration,
though it now lacks a definition for its methods.

**Task**: Convert `Rover` into an abstract base class by:

1. Removing the default constructor. This is no longer needed, as the
  concrete inheritors will provide any constructor functionality.

2. Marking the destructor as `virtual` and give it an empty body.

3. Marking the other methods as pure virtual by:

    a. Prefixing the method declarations with `virtual`; and
    b. Adding the `=0` suffix at the end of the declarations.

4. Remove the data members, as they are not contained in the concrete classes.

For example, if we had the class:
```c++
class X
{
public:
  X();
  
  ~X();

  void f(int z);
};
```
we would turn it into an abstract base-class:
```c++
class X
{
public:
  virtual ~X()
  {}

  virtual void f(int z) =0;
};
```

The idea of this process is to indicate that there will never be
an actual instance of the `Rover` class, as it is abstract. Instead,
it provides an API that will be implemented by other classes that
inherit from the `Rover` class.

3 - Make `RoverActionWriter` and `RoverSVGWriter` inherit from `Rover`
----------------------------------------------------------------------

We now have three classes:

- The abstract class `Rover`, which declares an API, but explicitly does
  not provide an implementation.

- The two classes `RoverActionWriter` and `RoverSVGWriter`, which implement
  the same API as `Rover`, but are not explicitly related to it.

We want to explicitly join these together, so that `Rover` is the abstract
base class for the two concrete implementations `RoverActionWriter` and `RoverSVGWriter`.

**Task**: Make `RoverActionWriter` and `RoverSVGWriter` concrete implementations of `Rover`:

1.  Add a `#include "Rover.hpp"` to the headers of the two concrete classes. 
2.  Explicitly add `Rover` as a public base class of the two concrete classes.

If you try to compile either of the two concrete class's source files, they
should still compile correctly, but will fail to link into a program due to
the lack of a `main` function.

4 - Explicitly use the `RoverSVGWriter` class
---------------------------------------------

At this point in time the controller programs all try to directly
instantiate `Rover`. However, this will not compile because `Rover`
is an abstract base-class - it exists only to provide an API for
concrete derived classes, and there can never be an instance of the `Rover` type.
Note the subtle distinction: there can never be an instance of the abstract type `Rover`,
but there can be instances of concrete types which _inherit_ from the abstract type `Rover`.

In each of the controllers there is currently a line where the `Rover`
instance is declared:
```c++
Rover r;
```
from that point on the variable `r` is used to access the member functions of `Rover`.

**Task**: Rewrite the controller sources to directly instantiate
  `RoverSVGWriter`, but to use it through a reference of type `Rover`:

1.  Include the file `RoverSVGWriter.hpp` at the start of each controller source.
2.  Create a local variable of type `RoverSVGWriter`.
3.  Turn the instance `r` into a _reference_ to the `RoverSVGWriter` instance.

The 2nd and 3rd steps mean that we turn this:
```
Rover r;
```
into this:
```
RoverSVGWriter concrete_r;
Rover &r = concrete_r;
```
You should not need to change or modify any of the code in any controller that
_uses_ the variable `r`. Previously they used an instance of the concrete class
`Rover`, while now they are using a _reference_ of the abstract class `Rover`,
but in terms of API `r` looks exactly the same.

After this step you should find that each of the controllers can be compiled
and executed, as long as you compile them alongside the `vector2d.cpp` and
`rover_svg_writer.cpp` sources.
However, unlike before you should find that they also compile if you add
the `rover_action_writer.cpp` into the program too, as there is now
no conflict between the two implementations - they are two separate classes.

You should be back at the point where the three controllers can compile
and execute, albeit they are now fixed to use just one implementation
again. Add any new files, and commit the repository with a message
containing the string `s4ExplicitSVGWriter`.

Here we're using a reference to the base class rather than a pointer,
but the principle is the same - calls to virtual methods through
a reference will resolve the actual method at run-time, just like
calling through a pointer.


5 - Declare a factory function for `Rover` implementations
--------------------------------------------------------

You can manually select between rover implementations by editing
the controller sources, but this is no better than the original
state of affairs at the start of the previous lab. We now want
to add the ability to select which implementation is used when
the program starts, rather than when it is compiled. To do that
we will create a _factory_, which is a function or class whose
only job is to create object instances at run-time.

Our factory function will have the following prototype:
```
/* Create an instance of Rover, using the given string to select the concrete type.
   The type of instance will depend on the string:
   - "svg" : returns a new instance of RoverSVGWriter
   - "action" : returns a new instance of RoverActionWriter
*/
Rover *rover_factory(const string &type);
```
The purpose of this function is to provide a layer of indirection: callers of
the function don't need to know exactly how the Rover instances are created,
they just know that it will turn a string describing an implementation into
a pointer to a concrete type.

**Task**: Add a header file called `rover_factory.hpp` which declares the
`rover_factory` function.

Note that you'll need to include `Rover.hpp` into this header, as you need
access to the declaration of `Rover`.

6 - Implement a function that returns an implementation
-------------------------------------------------------

**Task**: Create a source file called `rover_factory.cpp` which provides
an definition of `rover_factory`. The function should look at the value
of the input argument `type` and return an instance of a new rover type accordingly:

- "svg" : returns a new instance of RoverSVGWriter
- "action" : returns a new instance of RoverActionWriter

If the input string is any other value then we don't know how to
deal with it. Sensible choices would be to use `assert(0)` to
indicate there is a problem, or to print a message to `cerr` and
`exit` with an error code. Returning `nullptr` is probably not
a good idea, as it relies on the caller checking it. However,
we will not specify the error behaviour here, and instead assume
all inputs are value.

This source file will need to include the header files of the
two implementations, as it needs to know their declarations
so that it can instantiate them.

7 - Modify the controllers to use the factory function
------------------------------------------------------

Currently we are instantiating the controller as a local variable, 
so something like:
```c++
RoverSVGWriter concrete_r;
Rover &r = concrete_r;
```
We are happy the with the reference `r`, but want to change the
direct instantiation of `concrete_r` to instead use the factory function.

**Task**: Modify the controllers so that they use `rover_factory("svg")` to
create a pointer to an SVG writer instance, and make `r` a reference to that instance.

By analogy with integer references and variables, if we had the following code:
```c++
int x = 5;
int &r = x; // Form reference to the variable x
```
we could convert it to use a dynamically allocated integer as follows:
```c++
int *px = new int(3);
int &r = *px; // Form reference to the instance that px is pointer at
```
If we had a function `int_factory`, we could modify it as follows:
```c++
int *px = int_factory();
int &r = *px;
```
You want to do exactly the same, but with `Rover` instead of `int`, and
`rover_factory("svg")` instead of `int_factory()`.

You should be able to get this to compile and run, and it may appear
as if the output is roughly correct, compared to the original program.
However, if you open the resulting SVG in a web browser you may
find that nothing comes up, or the program complains that the
file is corrupted. Here is where it would have been _really_
useful to have maintained some test scripts.

It's important to think about lifetimes here:

- The `RoverSVGWriter` class actually prints the end of the SVG output in its destructor.
- The result of the factory function is dynamically allocated.
- A dynamically allocated instance is only destroyed if `delete` is called.
- The reference `r` is only an alias or new name for the thing returned from
  the factory function; it does not control it's lifetime.

**Task**: Make sure you call `delete` on the rover instance. This must happen
  _after_ the last use of the instance via the reference `r`.

8 - Make the implementation a run-time choice
---------------------------------------------

The controllers are still fixed to using the "svg" implementation, but
we want to select at run-time.

**Task**: Modify the controllers so that the program takes a
single argument that describes the rover implementation to use. If
there is no argument, a default of "svg" should be chosen.

After you have done this, you should be able to do the following:
```
$ ./controller_circle svg > circle.svg
$ ./controller_circle action > circle.action
```
So you can now select the implementation without re-compiling.

_Hint: the parameter will come in via `argv[1]`_.

**Task**: Add files to the repo as necessary, and create a commit with the string
`s8RunTimeImplementation`.

9 - Merging common functions
----------------------------

If you look at the methods of `Rover`, you can see that almost
all of them are exactly the same, and they are also all very
short "getter" and "setter" functions. These methods are important
to stop users corrupting the state of our rover, but we could
avoid repetition by moving the shared functionality into the
base class. That way we reduce the amount of code, and only
need to provide overrides for the differences between the derived classes.

**Task**: Add definitions for all the `get_` and `set_` methods
to the `Rover` class, and remove them from the two concrete implementation
classes. 

When you add a definition of a member to the base class, then that method
is no longer a pure virtual function, so you need to remove the `=0`
suffix. However, it is still a virtual method, as derived classes might
want to augment or change the functionality.

Note that the `advance_time` methods are different in each concrete
implementation, so must remain as overrides. Similarly, the constructor
and destructors are different in the concrete classes, so should
remain seperate.

10 - Create/update test scripts to test the three controllers
-------------------------------------------------------------

We've done a lot of refactoring here, and changed the API of
the rover programs at the command-line level, so should create
testing scripts that reflect this new interface.

**Task**: Create a script called `compile_and_run_controllers.sh`
which will:
- compile each of the controllers, including the appropriate source files
- run each controller with the both the "svg" and "action" implementations and capture the output
- compare the output against reference outputs included in the repository


**Task**: finally, add any new files, commit with a message `s10RoverDynamic`, and push
to your private repo in github.

Extensions
==========

Turning the controllers into classes
------------------------------------

Just as we turned the rover into a class with multiple implementations,
it would make sense to turn the controllers into classes. For example,
you could create a base class with the following declaration:
```c++
class Controller
{
public:
  ~virtual Controller()
  {}

 // Not const, as the controller may change its state
  void run(Rover &r);
};
```

You can then use the same techniques to allow both the controller
and the rover implementation to be chosen at the same time, with
just one executable for all of them.

Creating composite controllers
------------------------------

Once you have the ability to create represent controllers
as objects, you gain the ability to create collections of
controllers. For example, you can create a sequence
controller, which is given a vector of controller instances,
and then runs each controller in turn. This opens up
the ability to create more complex behaviour, with
fractal paths and sub-controllers. 

