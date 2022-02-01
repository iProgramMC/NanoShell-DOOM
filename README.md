# DOOM for NanoShell

This is an attempt to port DOOM to NanoShell.  Considering that this port is more of a mess than the OS source code,
and that it's licensed under GPLV2 or later, I decided to split it up into its own repository.

To try it out, change the path in `src/d_iwad.c:385` from `"/Fat1/doom1.wad"` to any other path visible to NanoShell's file API.

This serves as more of a stress test of my OS' APIs.

## Building

To build, clone this repository and the NanoShell OS repository.  Make sure you have the OS build setup there.  Copy this directory to the `application`
directory, such that all the files in the repository are visible under `<your OS path>/application/doomnanoshell`.  Then, run `build.bat`.

## Attributions

This port was forked from [Blackend's fork](https://github.com/Blackend/doomgeneric) of DOOM-Generic.
As such it is licensed under the GNU General Public License v2.0.
Check the LICENSE file for details.
