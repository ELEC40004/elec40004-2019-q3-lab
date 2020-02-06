ELEC40004 Quarter 3, Lab4
=========================

Note that this lab is not associated with an portfolio exercise set, so
is a bit more freeform with less clearly defined outcomes.

Aims of this lab
================

The main aim of this lab is to get you to read and modify existing code,
and look at some more sophisticated ways of using objects.

The actual modifications are more suggestions of things to do - this
is essentially a framework, and allows lots of things to be dropped in.
The main benefit comes from reading somewhat complex code.

1 - Building and running the code
---------------------------------

The code consists of a base class for representing waves, plus another class
for operating on waves. The idea is that we can seperate producers and
consumers of waves, and add new implementations as necessary.

You can compile the program by compiling together all the source files apart from
`test_factory_parameters.cpp`:
```
$ g++ process_wave.cpp  factory_parameters.cpp wave_factory.cpp  sink_factory.cpp -o process_wave
```

By default the program will use the following waves and sinks:

- Wave : a unit square wave
- Sink : a csv writer

The first argument to the program will control the wave, and the second argument
will control the sink. You can try different combinations and see how they vary:
For example:

```
# Default square waves
$ ./process_wave "square" "csv"

# Square wave with half the frequency
$ ./process_wave "[ square 0.5 ]" "csv"

# Square wave with twice the frequency
$ ./process_wave "[ square 2 ]" "csv"

# Square wave with twice the frequency and amplitude of 10
$ ./process_wave "[ square 2 10 ]" "csv"

# Sum of two square waves
$ ./process_wave "[ sum [ square 0.5 10 ] [ square 2 1 ] ]" "csv"

# Change the start and finish time of csv plot
$ ./process_wave "[ sum [ square 0.5 10 ] [ square 2 1 ] ]" "[ csv 1 10 ]"
```

2 - Understanding the code
--------------------------

It is always worth following the code to try to work out how this happens:

- What are the classes involved?
- How does the `factory_parameters` class work?
- How are parameters passed to the factory?
- How is the sum of two waves achieved?

There is a lot of complexity, so following the classes and logic may take some time.

3 - Adding a sin wave
---------------------

There is an example of a square wave, so try to add in an equivalent sin wave using
square wave as a template.

Once it is complete, trying adding together a square wave and a sin wave:
```
$ ./process_wave "[ sum [ square 0.5 10 ] [ sin 2 1 ] ]" "[ csv 1 10 ]"
```
Ideally you'll see a superposition of a sin and a square wave.
You might like to try importing the data into excel and plotting it.

4 - Adding a multiplication wave
--------------------------------

It is often very useful for multiply waves together (this is used in modulation).
Using `SumWave` as an example, add a new class which can multiple waves.

5 - Adding an SVG writer
------------------------

You know how to generate SVG using lines, so a nice graphical view would
be ideal. Use the SVG writer as a template, and try to create something
that will render the points as a sequence of lines. You can copy and
paste SVG parts from previous labs as needed.
