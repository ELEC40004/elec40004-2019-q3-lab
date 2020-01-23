ELEC40004 Quarter 3, Lab1
=========================

Aims of this lab
================

Context
-------

This lab uses the example of an image rendering application to show how to
[refactor](https://en.wikipedia.org/wiki/Code_refactoring) it into  a plain
object. To avoid the need to either write large amounts or work with completely
trivial programs, we'll start with an existing library and set of programs,
and convert it to a class.

The source consists of three source files:

- `drawing.hpp` : A header file that contains a type `Drawing`, plus a number of functions for working with it.

- `house.cpp` : A program that draws a picture of a house.

- `spiral.cpp` : A program that draws a pretty spiral.

The drawing library allows programs to construct images using polygons, and then
render the resulting images as an [SVG](https://en.wikipedia.org/wiki/Scalable_Vector_Graphics)
file. If you do the following:
```
$ g++ house.cpp -o house
$ ./house > house.svg
```
Then you should end up with an SVG file which can be opened in any web-browser.

Aims
----

The main aims of this lab are to be able do a number of tasks with basic 
objects, by re-factoring an existing image rendering library and programs
to use classes. The ability to perform these tasks are directly tested in a simpler
context in the portfolio. The components, plus the portfolio exercise they
are related to are:

1 - [e1] Pull source code from a remote repository to a local repository.

2 - [e2] Create and use test infrastructure to support re-factoring of a program.

3 - [e3] Capture the state of the repository using a commit.

4 - [e4] Convert a handle-based type to a class.

5 - [e5] Convert a program that uses a handle-based API on a pointer to use a class-based API.

6 - [e6] Convert a program that uses a handle-based API on a local variable to use a class-based API.

7 - [e7,e10] Commit and push changes in a local repository to a remote repository.

8 - [e8] Apply access modifiers to protect member variables of a class.

9 - [e9] Fix a program that uses direct access to member variables.



Standard Tasks
==============

To do two of these steps you'll need to have created a github account and registered it via
[this form](https://forms.office.com/Pages/ResponsePage.aspx?id=B3WJK4zudUWDC0-CZ8PTB07FeicCPhVAsezU-PfpjRxUMEdHVDc0Q0s0SU5URTBONUtZOU5JWkdRWi4u). Eventually
this information will be used to create the private repository that is mentioned here.
Note that you can do almost all the steps except the final *push*, so if you haven't got
a private repository yet then it doesn't need to stop you getting started during lab.

These are the tasks that everyone is expected to be able to do, and directly link
to the exercises in the portfolio.

1 - Pull source code from remote repository
-------------------------------------------

You are probably reading this readme at [https://github.com/ELEC40004/elec40004-2019-q3-lab/tree/master/lab1].

*Task*: Get a local copy of this repository by performing the command:
```
$ git clone https://github.com/ELEC40004/elec40004-2019-q3-lab.git
```
You should now have a complete copy of the repository on your local machine
in the directory `elec40004-2019-q3-lab`. Note that this is not just a snapshot of the files,
it also contains the history of changes to the files. If you move into
the directory and use `git log`, you'll see the history of commits to
the repository:
```
$ cd elec40004-2019-q3-lab/lab1
$ git log
commit 1ebb2007e09d4860c8caaf2e4f4402d014efe813 (HEAD -> master)
Author: David Thomas <dt10@imperial.ac.uk>
Date:   Tue Jan 14 12:56:16 2020 +0000

    Adding xmlns for SVG.

commit 5828d1b826b3ad26a38d80bfe16f828b5c52b1c0
Author: David Thomas <dt10@imperial.ac.uk>
Date:   Tue Dec 24 12:07:38 2019 +0000

    Initial import from dev repo.
```
(You'll probably see more commits than this).


2 - Create test infrastructure
------------------------------

We want to refactor this code, which means we want to change the structure, while
maintaining existing functionality. To do this reliably, we need to be able to
easily check that the behaviour before is the same as the behaviour afterwards.

*Task*: Create a test script called `test_drawing.sh` which will:

1. Compile `house.cpp` and `spiral.cpp`.
2. Run the programs and collect the outputs as `house.got.svg` and `spiral.got.svg`.
3. Compare the outputs against pre-generated reference outputs `house.ref.svg` and `spiral.ref.svg`.

If any of the steps fail, then the script should fail.

The two files `house.ref.svg` and `spiral.ref.svg` should be the outputs of the
two programs _right now_, i.e. before you start changing the code. These files
should be checked into source control, as they represent the reference against
which any future modified version of the code will be compared. The idea is that
as you transform the code you will ensure that the current code always produces
the same output as the original code.

3 - Capture the state of the repository using a commit
------------------------------------------------------

Your repository is now in a state where you are just about to start modifying
the code. This is the point at which you should capture the state of the
repository, as it is the best point to go back to if anything goes wrong in 
the next stage.

Before doing this, you should specify your local git user-name to
be your login, and your email address to be `login@imperial.ac.uk`. You
can do this using `git config`, with the following pattern:
```
$ git config --global user.name "MY_LOGIN"
$ git config --global user.email "MY_LOGIN@imperial.ac.uk" 
```
For example, David Thomas's login is `dt10`, so the commands would be:
```
$ git config --global user.name "dt10"
$ git config --global user.email "dt10@imperial.ac.uk"
```
Your's will depend on your login.

*Task*: Add the files `test_drawing.sh`, `house.ref.svg` and `spiral.ref.svg` to
    source control, and create a commit containing the string "wk1T3PreReFactor".

Recall that we can add files to a repo using `git add [filenames]`, and can
commit with the command `git commit -a -m 'MY COMMIT MESSAGE'`.

You can use a longer commit message if you want as long as it contains the
string `wk1T3PreReFactor`. If there are more than one commit contining the
string, the most recent one is chosen.

4 - Convert the Drawing object into a class
-------------------------------------------

*Task*: modify `drawing.hpp` so that `Drawing` is converted into a structure with member functions.

The main steps involved are:

1.  Moving the `Drawing_*` functions inside the `Drawing` structure.
2.  Removing the redundant `Drawing_` prefix from the functions.
3.  Converting the `Drawing_create` function into a constructor with no parameters.
4.  Converting the methods so that the object is either explicitly or implicitly accessed
    via `this`, rather than explicitly via the `d` parameter.

While you can't compile the programs yet, you can attempt to compile the
header file by itself, for example:
```
$ g++ drawing.hpp
```
This will let you know if you have any basic syntactic problems from the conversion.

5 - Converting uses of the type via a pointer
---------------------------------------------------------

The program `house.cpp` uses the `Drawing` type "properly", as it relies only on
the functions in the API.

*Task*: modify `house.cpp` so that it compiles and executes against the modified
class-based `drawing.hpp` header. 

The main changes required are:

1.  ```c++
    Drawing *d=Drawing_create();
    ```
    becomes
    ```c++
    Drawing *d=new Drawing;
    ```

2.  ```c++
    Drawing_destroy(d);
    ```
    becomes
    ```c++
    delete d;
    ```
    as we are relying on the destructor to release the object when it is deallocated.

3.  Each function call to `Drawing_*` becomes a method call, so for example
        ```c++
        Drawing_add_square(d, ...);
        ```
        becomes:
        ```c++
        d->add_square(...);
        ```

6 - Converting a program that uses a local variable
---------------------------------------------------

The program `spiral.cpp` is a bit cheeky, as it instantiates an instance
of `Drawing` on the stack, and bypasses the `Drawing_create` function.
Once we apply accessors modifiers this will cause problems, but the main
goal during refactoring is to get back to the point where all tests pass as
soon as possible.

*Task*: modify `spiral.cpp` so that it compiles and executes against the modified
class-based `drawing.hpp` header. You should keep the stack-allocated
`Drawing d` and the direct access and manipulation of member variables, as we need to
retain it so that step 9 make sense. 

7 - Commit and push changes
---------------------------

You should now be in a position where you have modified the header and both
programs, and are back in a position where `test_drawing.sh` returns a success
code.

*Task*: commit the updated files with the message `wk1T7PlainClass`, and **push** the
repository to your private remote repository at `https://github.com/ELEC40004/elec40004-2019-q3-lab-${LOGIN}`.

Here the string `${LOGIN}` should be replaced with your _Imperial_ login.

The site you pulled the initial version of this repository from is a shared
"master", and you do not have push access rights to it. However, the repository
at `https://github.com/ELEC40004/elec40004-2019-q3-lab-${LOGIN}` is your own private repository, and has some extra properties:

- Only you and instructors can view (read from) the repository.

- Only you can push (write to) the repository.

Your local repository will currently be set up with one **remote**, which is a place that
you can push and pull your repository to. You can list the current remotes using:
```
$ git remote -v
origin  https://github.com/ELEC40004/elec40004-2019-q3-lab.git (fetch)
origin  https://github.com/ELEC40004/elec40004-2019-q3-lab.git (push)
```
The two "remotes" listed for `origin` point back to the
master repository at `https://github.com/ELEC40004/elec40004-2019-q3-lab.git`.

Add a new remote called `private` which points at your private repository at `https://github.com/ELEC40004/elec40004-2019-q3-lab-${LOGIN}.git`:
```
$ git remote add private https://github.com/ELEC40004/elec40004-2019-q3-lab-${LOGIN}.git
```
Remember that you need to replace `${LOGIN}` with your Imperial login id.
If you list remotes again, there should now be a new remote called `private`:
```
$ git remote -v
origin  https://github.com/ELEC40004/elec40004-2019-q3-lab.git (fetch)
origin  https://github.com/ELEC40004/elec40004-2019-q3-lab.git (push)
private https://github.com/ELEC40004/elec40004-2019-q3-lab-dt10.git (fetch)
private https://github.com/ELEC40004/elec40004-2019-q3-lab-dt10.git (push)
```

Now the remote is set up, you should be able to *push* to that remote, which will
mirror your local repository to your private remote:
```
$ git push --set-upstream private master
```
You are likely to be asked for your credentials (username and password) when doing this.
These should be the credentials for your github account, not your Imperial credentials.
You may be asked for your credentials every time you push and pull from your private
remote, though some operating systems (such as macOS) may cache it for future attempts.

If the push succeeds, you can browse to `https://github.com/ELEC40004/elec40004-2019-q3-lab-${LOGIN}`, and should see your modified repository is now visible there, including your two commits.

8 - Apply access modifiers to protect member variables
------------------------------------------------------

The program `spiral.cpp` is being bad, and is directly reaching into the
structure and modifying the `min_x`, `max_x` variables. This is quite fragile,
as it means that:

1 - The program is modifying the state of the object without the knowledge of
    the class, which could violate constraints and class invariants.

2 - The program is now intimately linked to the implementation of the class, so
    it becomes impossible to change the internal implementation of `Drawing` to
    add new features.

*Task*: convert `Drawing` to a `class`, and add `private` and `public` modifiers
to the `Drawing` class to make sure that member variables are not accessible, but
member functions are.

After this step you should find that `house.cpp` compiles and executes correctly,
but `spiral.cpp` will no longer compile. This is completely the fault of the
writer of `spiral.cpp`, as they have no right to reach in and tinker with the
state of the object - they're not even doing it right!

9 - Fix the program
-------------------

*Task*: Fix `spiral.cpp`.

The compiler should tell you exactly where the problem is with `spiral.cpp`. The
attempt to manually set the min/max x/y in `spiral.cpp` is not necessary
and doesn't work, so remove it.

Check that the program still passes your original tests with `test_drawing.sh`.

10 - Commit and push the re-factored code
------------------------------------------

At this point you should now have a header and pair of programs that have
been completely re-factored to use classes, while preserving the same
functionality.

*Task*: Create a final commit called `wk1T10RefactorComplete` and push the
repository to your private remote.

Final checks
------------

It is strongly suggested that whenever you have finished a unit of work that
you clone the repository into a new directory, and then test that the
code works in the target environment. This avoids problems where you forgot
to check in certain files, or over-wrote particular files. For those of you
who are doing most of your work in macOS, cygwin, WSL, ... this is also the
chance to check that it works in Ubuntu.

For this particular lab it should be sufficient to move to a new directory
and do:
```
$ git clone https://github.com/ELEC40004/elec40004-2019-q3-lab-${LOGIN}.git
$ cd elec40004-2019-q3-lab-${LOGIN}
$ cd lab1
$ ./test_drawing.sh
```

Extra Tasks
===========

If you're interested in extra improvements, then some possible extensions are:

Compositional
-------------

It is common to want to re-use a drawing in another drawing. Add a method:
```
void Drawing::add_drawing(const Drawing &src, float x, float y);
```
which embeds the contents of the polygons contained in `src`, but translated by `x` and `y`.

To test this you could attempt to draw the house multiple times within a larger drawing,
or modify the spiral code to draw a house instead of a circle at each point.

Animation
---------

The `spiral` program has a number of command-line parameters which can be varied in order to
get different effects. If these parameters are slowly varied, then the spiral will change
shape and colour.

At the moment the spiral program generates one svg file for each set of parameters,
but if you can find a way to call the program hundreds of times with slightly
changing parameters, you can generate hundreds of SVG frames. From an SVG
file you can generate a `png` bitmap file using `convert` from Imagemagick.

So for example, if you can somehow generate a script looking like:
```
#!/bin/bash

./spiral 64.0 > out00001.svg
convert out00001.svg out00001.png 

./spiral 65.0 > out00002.svg
convert out00002.svg out00002.png 

./spiral 66.0 > out00003.svg
convert out00003.svg out00003.png 

...
```
and so on, you would end up with large numbers of slightly varying bitmaps.
It would take a long time to run (well minutes for a few hundred frames),
but you can go and do something else while it happens.

Hrmm, what could be used to print lots of lines of text with slightly changing
numbers?

The `ffmpeg` command then knows how to turn those png images into a movie `out.mp4`:
```
$ ffmpeg -r 25 -i out%06d.png -c:v libx264 -crf 10  -pix_fmt yuv420p out.mp4
```

This is mainly for fun, but it is the start of being able to do large
scale exploration of big problem spaces, including using parallel machines.


Genuine circles
--------------

The SVG specification actually supports [real circles](https://developer.mozilla.org/en-US/docs/Web/SVG/Element/circle), but in this code we're generating polygonal approximations to circles. Using
genuine circles would both result in better figures, and also smaller file sizes.

You'll need to think about how to represent circles, as currently there is only the polygon
struct for representing shapes. This is actually quite a difficult problem without using
inheritance, though it is possible. Some possibilities are:

- Creating a `Circle` struct, and having a vector of Polygons and a separate vector of Circles. 
- Add a flag to the `Polygon` struct, indicating whether the data should be treated as a polygon
  or a circle. Even better: rename it to `Shape`.

The act of trying to solve the problem will actually set you up quite well for the
solution that inheritance provides later on.
