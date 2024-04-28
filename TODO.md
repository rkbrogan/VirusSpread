# notes

## 4/28

- sounds like life’s been good...bro' visit...🎂🎳 w/friends...and even work's been challenging/interesting given your foray into the work of wi-fi networks
- discussed the *ethics of analytics*😎
- once you attempted to share your screen, we ran into a wierd bluriness problem, resolved by switching to Zoom for now...
- a quick review of your implementation (which looked good), and some discussion led to a few recommendations:
  - fully combine `simulate` and `analyze` vs. delineate by `ntrials`
  - normalize console and data (files) formats
  - surface all constants via the command line
  - use `getopt` to parse and UT the command line arguments/options

### 4/28 next

- complete integration such that `ntrials` is just another argument
- complete command line
- complete UTs and implementation of core functions
- consider what's next, *e.g.,* new project or `otp v.next`:
  - concurrrency (threads)
  - client/server
  - I/O GUI:
    - input: window based UI w/widgets, *etc.*
    - output: various plots, dashboards, *etc.*

## 4/12

- unfortunately, more time spent on *configuration* issues:
  - VS Code's *internal* build/debugger:
    - `tasks.json`
    - `launch.json`
    - *etc.*
  - external `Makefile`

### 4/12 next

- [ ] **complete** build/debug workflow for both the `virus` and `virus-test` executables, *or*, return to a single executable w/`test` as a fourth sub-command
- ignoring *visualization*, the PDF describes *features*, that you should combine into a single executable:
  1) command line parsing
  2) mathematical-style `f()`-s - take some input and transform it to some output - no side-effects (*i.e.*, easier to UT)
  3) output - anything from simulation summaries to `CSV` files for post-procerssoing, or...

- [ ] **complete** (i.) using: [getopt(3) - Linux manual page](https://www.man7.org/linux/man-pages/man3/getopt.3.html)

## 4/4

- once again we focused mostly on build/debug config issues:
  - `Makefile`, `task.json`, `launch.json`
  - tools, *e.g.*, `clang` vs. `gcc`...
  - debugger & extensions: `gdb`, `lldb`

### 4/4 next

- double check tools, extensions, *etc.*
- any access to a *clean* Mac? Maybe a virtual one in the cloud:
  - *clean* environment
- **post-lesson** - working on `hello world` repo/app...get it working again on `virus`❗
- how can I help get past this roadblock?

## 3/27

- unfortunately, not a lot of progress this week
- spent most of Lesson working on debugger configuration:
  - `launch.json`
  - appropriate debugger extension
- use the PDF as a set of *guidelines* or a *specification*, rather then an *assignment*:
  - one executable for *all* functionality
    - `simulate`
    - `analyze`
    - `visualize`
  - the latter can be done w/an external utility (ala the PDF), a plotting library or both - your call...be creative...w/o over-engineering😎

### 3/27 next

- get debugger config working
- structure code, `Makefile`, *etc.* to support one application executable

## 3/19

- discussed the 👰🤵 and the timing of the universe - flat 🛞
- you didn't have a chance to review the PDF and so our focus was on the annoying 😎 `Makefile​`
- after some fiddling - to resolve the multiple `main.c​` issue - w/macros/file filtering in the `Makefile​`, followed by some file renaming and...
    > **both the test and main​ executable could both be built❗❗❗**
- finally, we agreed to experiment w/this - `TODO.md​` - for notes, plans, references, *etc.* in lieu of ClickUp

### 3/19 next

- review PDF and put together a go-forward plan of attack😎
- clean up code/repo (as needed) in prep for the *go-forward plan of attack*
