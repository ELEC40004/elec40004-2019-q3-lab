ELEC40004 Quarter 3, Lab2
=========================

Aims of this lab
================

Context
-------

This lab uses the idea of objects to represent real-world things: in the
previous labs we looked at static models of the images; this time we'll
look at objects which evolve over time. We're also looking at how objects
could be used to control things in the real-world, as well as simulating
virtual versions of them.

The main object being considered here is pretty much the EEBug - it is a
rover that can move around a 2D space. The main difference is that we are
operating at a higher-level of abstraction - rather than working out the
low-level details of how to control the motor, we consider the function and
state of the device at a more abstract level. We also don't consider input
in order to keep things simple - there are no light sensors.

An additional feature of our rover model is that it contains a pen, which
can be up or down. If the pen is down, then it leaves a line behind
on the floor; if the pen is up, then no trail is left. This idea is
borrowed from the [LOGO](https://en.wikipedia.org/wiki/Logo_(programming_language))
programming language, which allowed the user to control a "turtle" much
like the rover. The turtle could either by a virtual turtle on-screen,
or if you were lucky enough your school might have a
[physical turtle](https://en.wikipedia.org/wiki/Turtle_(robot)#/media/File:Turtle_draw.jpg)
which drew pictures on the floor (this was a big thing in the late 80s).

We are not going to explicitly connect this object model to your
physical rovers, but conceptually the gap between these abstract
APIs and the concrete Arduino code is small.

The main header files are:

- `rover.hpp` : Contains the declaration of the `Rover` class. Clients can use this to find
    out the current angle, speed and so on, and also to then modify the angle and speed, and to
    move the rover forwards by a certain time step.

- `rover_svg_writer.hpp` : Contains an implementation of the `Rover` class that generates an SVG
    capturing where the rover moved with it's pen down throughout the entire control period.

- `rover_action_writer.hpp` : Contains an implementation of the `Rover` class that captures
    the actions performed on the rover as a stream of action objects that are written to
    `stdout`.

A problem with this current approach is that we can only include one of those files
into a program, which we'll try to fix.

We also have three source files which are able to control a rover:

- `controller_circle.cpp` : Makes the rover drive round the edge of a unit circle.

- `controller_spiral.cpp` : Makes the rover drive in a sort of decreasing square spiral.

- `controller_brownian.cpp` : Makes the rover follow a brownian motion path.

Aims
----

The main aims of this lab are to:
- use practical function and operator overloading;
- use the `const` keyword for parameters and methods;
- allow objects to save and load themselves to files;
- seperate compilation into different source files.

The steps in the lab are mirrored by simpler versions of the same steps in the portfolio.

Standard Tasks
==============

These instructions assume that you have started, and ideally completed, the
previous lab exercise. The idea is that we are modelling incremental changes
and features being added to a codebase over time, so we need to start
thinking about how to merge and reconcile conflicts.

1 - Merging changes in a repository
-----------------------------------

It is expected that you will do these tasks in the _same_ repository as for
lab1, so you are adding new stuff to an existing repository. In this case
the changes are in different directories, which should make it easy. You
can also do this lab in a completely fresh directory if you want, but in
the portfolio you will need to do it all and submit it in one repo to show
you know how to do it.

Check out a local copy of your `elec40004-2019-q3-lab-${LOGIN}` repo from
github, either by:

- Cloning a new copy; or
- Using `git pull YOUR_REMOTE_NAME` to ensure that your existing local repository is up to date.

You are probably reading this on `https://github.com/ELEC40004/elec40004-2019-q3-lab/tree/master/lab2`, which is contained on github. If you're reading this document somewhere else,
then temporarily open a browser and go to that link. You should see the main view onto the
repo, with lots of options and links. Looking down from the top of the page, you'll
see a row of links containing "commits", "branches", "packages", "releases", "contributors",
with a number in front of each one. _Click the "commits" link_.

You'll see a list of rows containing different commits (changes) made to the
repository, from newest to oldest. Each row contains the commit message, information
about the commiter (in this case probably `m8pple`), and on the right-hand side there
is a short hash hexadecimal hash associated with the commit. If you click on the hash
(or the commit message), it will take you to a summary of the differences that
the commit introduced. Towards the right-hand side of the commit summary you'll
see a much longer 40 digit hex string, which is the "full" hash. This hash should
be unique amongst all hashes in the world, and uniquely identifies each commit.
The shorter hash is only unique within the repo, and is more of a short-hand for
humans. The github commit view shows the same information as is returned from `git log`
on the command line, but with fancier formatting.

If you navigate to your own lab repo at `https://github.com/ELEC40004/elec40004-2019-q3-lab-${LOGIN}`
(remember to replace ${LOGIN} with your own Imperial login) you'll also be
able to look at the commits. Up to a certain point these commits will be exactly the
same in both the master and in your repo, but the commits that introduce
lab2 will create a "fork": commits exist in the master repo that aren't in yours, and
commits exist in your repo that aren't in master.

Fortunately, these changes occur in different directories, so there should be no
conflicts between your commits and external commits - effectively you just want to
copy the `lab2` directory from master into your own repo. However, if you copied
it in then you would lost the history of changes associated with `lab2. What
we want to do is *merge* the changes, so that your local repo contains the changes
and history from the master and your own changes, plus detailed information on
who changed what. In that way, if something goes wrong in the code, we can work
out whether the blame should be attributed to you or to `m8pple` based on who
changed the file last.

**Task**: Merge the changes from master into your local repository.

To do this you'll need to:

1. Have your current directory inside your local repository; and
2. Have a remote setup which points at the master repository at
   `https://github.com/ELEC40004/elec40004-2019-q3-lab/`

If you aren't sure which remotes you have, then you can use `git remote`
from last week to check/change them: `git remote -v` to list them, and `git add ...`
to change them.

If the name of the remote pointing at the master repo is `${MASTER_REPO}`, then
the command to merge would be:
```
$ git pull ${MASTER_REPO}
```
For example if the output of `git remote -v` was:
```
origin  git@github.com:ELEC40004/elec40004-2019-q3-lab.git (fetch)
origin  git@github.com:ELEC40004/elec40004-2019-q3-lab.git (push)
private https://github.com/ELEC40004/elec40004-2019-q3-lab-dt10.git (fetch)
private https://github.com/ELEC40004/elec40004-2019-q3-lab-dt10.git (push)
```
you would use:
```
$ git pull origin
```
to merge changes from the `origin` remote.

You _should_ now find that if you do `git log` then you find that your
local repository contains all of your changes, plus all of the changes
from the master repo.

To double-check, it is worth using `git push private` (or equivalent)
to push your changes back up to github, then look at in the github web-site.
You should now see the commits from master intermixed with your own commits. It's also
possible to see the fork and merge graphically; look for the row of
tabs "Code", "Issues", "Pull requests", and click on the tab "Insights".
On the left-hand side there is a tab called "Network", which will
show the commit history as a dependency graph. If you finished lab2
before starting lab1 you should see a branching point in the network
graph, then a merging back together for the most recent commit.

Once the merge is complete, you should have all the code for lab2
available in the `lab2` directory.

2 - Overloading `<<` and `>>`
-----------------------------

The file `vector2d.hpp` contains a very simple struct for representing
2D points. Notice that the author has decided to make it a `struct` with
public member variables. The reason is that any possible state is
valid, as every combination of `x` and `y` is possible. As a consequence,
we don't mind if users modify the members directly.

There are examples of operator overloading already which allow the user to
add, subtract, and multiply vectors with a constant. We also have declarations
for `<<` and `>>`, but they do not have definitions.

**Task**: Add definitions to the declarations of `<<` and `>>` for the
`vector2d` class.

Vectors should be printed as described in the documentation for the `<<` function.
Examples of valid text versions of vectors are given in `test_vector2d_io_in.txt`.

The output format has a strict requirement on the numeric format, as it
requires numbers to be printed with exactly three decimal digits of
accuracy. The `ostream` type has a number of modifiers which can be
applied to control things like this. For example:

- `cout << hex ;` : Print integers in base 16
- `cout << dec ;` : Print integers in base 10
- `cout << setprecision(n) ;` : print floating-point numbers with n digits of precision
- `cout << fixed ;` : Print floating-point numbers in fixed-point format (no exponent)
- `cout << scientific ;` : Print floating-point numbers in scientific format (one digit left of decimal point with exponent)

You can use these inline, like so:
```c++
int main()
{
    cout << 255 << endl;        // Prints "255"
    cout << hex << 255 << endl; // Prints "ff"
    cout << scientific << 1625.0 << endl; // Prints "1.625000e+03"
}
```

In our specific case we need two manipulators to print the numbers
correctly: `fixed`, and `setprecision(3)`.

(For this lab, don't worry about trying to restore the initial format and precision,
though see the following commentary.)

### Commentary on global state

_This is just commentary/explanation, and can be skipped if you are in a rush._

These manipulators are very convenient, but it is worth thinking about their
drawbacks too. If you happen to use `cout<<hex;` in one function, then
the `cout` object will print all integers in hex from that point forwards.
So a function that previously printed values out in decimal could suddenly
start printing out in hex, without that function ever being modified.
This is the danger of global state, and why we try to avoid it - changes
in one function could change the behaviour of other functions, even though
the types of those functions suggest it is impossible for them to affect each other.

A "hygenic" print implementation would try to restrict it's globally visible
changes, so that the state of `cout` is the same after the function as before.
For example, a function that needs to print in hex might try to fix it by doing:
```
void print_hex(int x)
{
    cout << hex << x << dec;
}
```
However, this pre-supposes that the original state was actually to print in decimal.
Imagine if the above function were called from this function:
```
int main()
{
    for(int i=0; i<256; i++){
        cout << dec << " i = " << i ;
        cout << oct << " = 0" << i ;
        print_hex(i);
        cout << endl;
    }
}
```
To be ultra-hygenic the pattern is to save the state before changing it, then
to restore it:
```
void print_hex(int x)
{
    ios::fmtflags flags = cout.flags(); // Save the formatting flags
    cout << hex << x;
    cout.flags(flags); // Restore the flags
}
```
You can see an example of this in the overloads of `<<` and `>>` for `RoverAction`.

Unfortunately there are a number of different pieces of state that
need to be saved and restored, and it can be difficult to remember
to save+restore them all. Despite the elegance of the iostream
overload method of printing, with hindsight this global state is
_probably_ a mistake, and is not something that is seen in the
IO libraries of more recent languages.


3 - Testing `<<` and `>>`
-------------------------

**Task**: Write a script called `test_vector2d_io.sh` which checks that
your implementation of `<<` and `>>` can correctly read and write all the values
from `test_vector2d_io_in.txt`.

Note: You are going to need at least one support `.cpp` file to implement this
functionality, as something needs to be compiled. Feel free to create files
with prefix `test_vector2d_` to support this, though make sure you commit
them in to the repository.

If you want to read and write points within a program it is exactly the same as
reading any other type:
```c++
int main()
{
    vector2d v;
    cin >> v;
    cout << v << endl;

    v={2.5, 6.0};
    cout << v << endl;
}
```

One approach is to have two programs: one that reads the vectors from
`cin` and verifies it reads the same values as the original
file; and another separate program that generates the required value and writes
them to `cout`. In both cases you need to embed the expected vector values
from the file, so that the program can either check the values read in or create
the values to be written.

An alternative approach is to have a single program which reads vectors from
`cin` and then immediately writes them to `cout`. You then need to verify that
the output file matches the expected output using something like `diff` - however
the whitespace in the output might not match the input. A reasonable choice
would be to manually create a new reference output text file from `test_vector2d_io_in.txt`,
where you delete all whitespace and put each value on a different line.

4 - Fix const-correctness
-------------------------

The public API for `Rover` is in `rover.hpp`, with multiple implementations of
the rover methods in different `rover_*.hpp` files. Currently all the
controller files `#include "rover_svg_writer.hpp"`, which means that the Rover
will generate a single SVG as it moves.

However, if you try compiling `controller_circle.cpp`, you'll find there are lots
of errors due to a missing `const` modifiers on the method definitions in `rover_svg_writer.hpp`.

**Task**: Modify `rover_svg_writer.hpp` so that the definitions match the declarations
in `rover.hpp`, by adding `const` where needed.

Once this is done, you should be able to compile each of the controllers.


5 - Compile the controllers
---------------------------

**Task**: Create a script called `compile_and_run_controllers_to_svg_writer.sh`, which
compiles each of the controller source files `X.cpp` into an
executable with the suffix "X_to_svg_writer", and then runs and captures the output
of the program in a file called `X.svg` extensions.

The three controllers are:

- `controller_circle.cpp`
- `controller_brownian.cpp`
- `controller_spiral.cpp`

For example, the outputs for `controller_circle.cpp` should be a program
`controller_circle_to_svg_writer` and an SVG file called `controller_circle.svg`.

**Task**: Capture the state of the respository in a commit with the word `s5FixedSVG`
in the commit message.

The programs and SVG files should _not_ be added to the repository, as
they take up a lot of space - anything that can be recreated is usually
left out of the repo.

6 - Convert the controllers to the action writer
------------------------------------------------

The file `rover_action_writer.hpp` contains an implementation that 
writes the movements of the rover as a textual description, so that
the movement can be save to a file, or transmitted to another program.

**Task**: Modify the three controller files so that they include the
`rover_action_writer.hpp` implementation.

As you do this, you might want to try including both implementations at
the same time, and observe that the compiler won't let you do it due
to multiple definitions of the same function.

7 - Compile the controllers
---------------------------

*Task**: Create a script called `compile_and_run_controllers_to_action_writer.sh`, which
compiles each of the controller source files `X.cpp` into an
executable with the suffix "X_to_action_writer", and captures the output
of the program into a file called `X.actions`.

For example, the outputs for `controller_circle.cpp` should be a program
`controller_circle_to_action_writer` and an SVG file called `controller_circle.actions`.

Note that the actions file format is just text, and is read and written
by `RoverAction` via its `<<` and `>>` operator overloads.

**Task**: Capture the state of the respository in a commit with the word `s7WritingActions`
in the commit message.

8 - Converting the headers to source files
------------------------------------------

We are now in the unhappy situation where we can either choose the
svg writer or the action writer, but not both - to change which method is used
we have to modify the source file and re-compile. Ideally we'd like
to support multiple types of controller from the same client source code,
ideally without needing to compile. We can achieve the first objective now,
and then the second objective with the use of basic inheritance next week.

At the moment the files `rover_log_writer.hpp` and `rover_action_writer.hpp` are
header files, which means they need to be `#include`'d. However, they are
also completely valid source files, except for the fact that they don't have
a main function. 

**Task**: Rename the two rover implementation headers from .hpp to .cpp.

If you try compiling them now they have source file extensions, you should find
the compiler has no problems with them. The only thing stopping it
from creating a program is the lack of a `main` function, which it
flags as an error right at the end.

9 - Compile controllers source against writer source
-----------------------------------------------------

The problem we faced was that we had to modify the controller source to
select a specific rover implementation via `#include`, as the controller
needs the definitions of the `Rover` method. However, we could decide to not include
any definitions into the controller source file, and instead compile them
in from another source file.

**Task**: Completely remove the `#include "rover_action_writer.hpp"` line from
all three controller sources.

If you try compiling the controllers, you should see a lot of linker errors
complaining that it can't find definitions for all the `Rover` methods. So
now we have two sets of source files:

- _controller source files_: can't compile due to missing `Rover` methods.
- _rover implementation files_: can't compile due to missing `main`.

Each file has what the other file needs, and the compiler is capable of
"linking" together two source files so that it can combine definitions from
two sources. You just need to give more than one source file to the compiler.

For example:
```
$ g++ controller_circle.cpp rover_svg_writer.cpp -o controller_circle_to_svg_writer
```
If you try this, you'll find they compile, but now you get multiple linker errors
due to `vector2d`:
```
/tmp/cckM7cQ6.o: In function `operator+(vector2d const&, vector2d const&)':
rover_svg_writer.cpp:(.text+0x0): multiple definition of `operator+(vector2d const&, vector2d const&)'
/tmp/cc5G1gwG.o:controller_circle.cpp:(.text+0x0): first defined here
/tmp/cckM7cQ6.o: In function `operator-(vector2d const&, vector2d const&)':
rover_svg_writer.cpp:(.text+0x66): multiple definition of `operator-(vector2d const&, vector2d const&)'
/tmp/cc5G1gwG.o:controller_circle.cpp:(.text+0x66): first defined here
```

The problem is that both source files include `vector2d.hpp`, so now _both_ source
files have definitions for the operators. To fix this, we can split `vector2d.hpp`
up, by extracting the functions definitions from `vector2d.hpp`, and putting
them in a source file called `vector2d.cpp`.

**Task**: split the file `vector2d.hpp` up, by adding a source file `vector2d.cpp` which
contains the operator overload definitions.

We should now be able to compile the program by specifying all three
source files:
```
$ g++ controller_circle.cpp rover_svg_writer.cpp vector2d.cpp -o controller_circle_to_svg_writer
```

You should _also_ be able to compile a version which combines the circle and action writer
without needing to change the source code:
```
$ g++ controller_circle.cpp rover_action_writer.cpp vector2d.cpp -o controller_circle_to_action_writer
```

10 - Update the two build scripts
---------------------------------

We now have the ability to link different controller implementations
against different Rover implementations, _without_ changing the source
code. All we need to do is to select between different sets of source
files which allows us to bring in different sets of definitions, and
produce programs that combine different implementations.

**Task**: update `compile_and_run_controllers_to_action_writer.sh` and
`compile_and_run_controllers_to_svg_writer.sh` so that they select
the correct functionality by switching between source files.

**Task**: make sure you have added all new files, commit your
final version with the message `s10SeperateSources`, and then push the final results.


Other things to do
==================

The purpose of the action_writer version might be a but unclear.
It is actually there so that we can convert the methods that are
called into a stream that can either be stored for later, moved
to a different program, or sent to a different computer.

Rendering the path of the Rover over time
-----------------------------------------

The program `render_rover_actions_as_rgb32_sequence.cpp` is a simple
program that reads an action stream from input, and then writes a
stream of video frames showing the path of the rover over
time. The output of the video is raw binary data, with four bytes
per pixel to describe red, green, and blue, so the file is massive.

To get it into a form the you can see, you can use `ffmpeg` to turn
it into an mp4 video that most video players can play.

The steps are:

1.  Make sure `ffmpeg` is installed, e.g. using `sudo apt install ffmpeg` in Ubuntu.

2.  Compile the `render_rover_actions_as_rgb32_sequence` program.

3.  Generate an action file from one of the controllers.

4.  Pipe the action file through `render_rover_actions_as_rgb32_sequence` and
    capture the output as `output.rgb32`. Warning, the file might be quite big - it's
    about 1GB for the "spiral" controller.

5.  Pipe the rgb32 file into the command
    `./convert_rgb32_512x512_stdin_to_mp4_file.sh FILE.mp4`, where `FILE.mp4`
    is the video you want to create.

The last three steps could be performed as:
```
$ ./controller_spiral_to_action_writer > tmp.actions
$ <tmp.actions ./render_rover_actions_as_rgb32_sequence >tmp.rgb32
$ <tmp.rgb32 ./convert_rgb32_512x512_stdin_to_mp4_file.sh spiral.mp4
```
Or you could do it in one single command, with no intermediate files, as:
```
$ ./controller_spiral_to_action_writer | ./render_rover_actions_as_rgb32_sequence | ./convert_rgb32_512x512_stdin_to_mp4_file.sh spiral.mp4
```
