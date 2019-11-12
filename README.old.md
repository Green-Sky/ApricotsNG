# Apricots-0.2.6

## Overview

        Apricots is a game I've been writing in my spare time.
        Despite the name, it has nothing to do with apricots.
        It's a game where you fly a little plane around the
        screen and shoot things and drop bombs on enemy targets,
        and it's meant to be quick and fun.

## History

        The original version of the game dates back to around
        1991. The very first version of the game was written on
        an Amiga, using the AMOS language, and the game was
        called 'Planegame'. This was a very simple affair with
        simplistic landscapes, no guns or shrapnel, and very
        limited computer AI. It was also dreadfully slow. The
        AMOS compiler improved things somewhat at a later date. A
        couple of years later I obtained the BLITZ language for
        the Amiga, and ported 'Planegame' carefully over to that,
        resulting in a huge speedup. Impressed by the capabilites
        of BLITZ, in 1995 I proceeded to rewrite the game
        entirely from scratch, even using completely new graphics
        and sound. The result was 'Planegame2', which, for
        various reasons also got dubbed 'Apricots'. This new
        version of the game added anti-aircraft guns, shrapnel,
        trees, towers, water, better airbases and a huge
        improvement on graphics, sound, and intelligent computer
        AI. Slightly later, in 1996, the Draks were added as a
        bit of amusement. The result was a highly playable game,
        which I distributed to a few of my friends. A few years
        later and I now use a PC, which can run Linux. Having
        learnt C++ by this time, at the beginning of 2002 I felt
        ready enough to port 'Apricots' cross platform from BLITZ
        on the Amiga to C++ on a Linux PC. What you see here is
        work in progress on that port. The game has been tweaked
        slightly while being ported over, so is not identical to
        the Amiga version.

## Authors

        Project Leader: Mark Snellgrove (Original concept and game
                        coding)
        Co-author: Mark Harman (First Windows port and SDL conversion)
        Additional contributor: Judebert (Configuration file)
                                           
## Status
        The game is still under development. Apricots-0.2.6 is a 
        beta release using the SDL library. Despite this, it
        is highly playable. Please mail apricots@fishies.org.uk
        any bug reports, upgrades or comments.

## C++ Compilers

        Apricots is known to successfully build under the following
        OS/Compiler configurations
        
        Linux - gcc (reported by Mark Snellgrove)
        OpenBSD - gcc (reported by Johan Luff)
        Windows - Borland (reported by Mark Harman)
        Windows - Visual C++ 6.0 (reported by Mark Snellgrove)
        Windows/Cygwin - gcc (reported by Judebert)
        
        It may build successfuly on other platforms, but this has
        not been tested. Let me know!
                
## Requirements

            SDL > 1.2.0, download from www.libsdl.org
            OpenAL, download from www.openal.org [optional]

## Compilation options

        -DAP_PATH="datadir" Set directory where apricots looks for
                            its data files. Defaults to current directory
                            if unset.
        -DAP_AUDIO_OPENAL   Turns on audio, using OpenAL. Off by default.
                        
## Instructions

        CONTROLS                      PLAYER 1             PLAYER 2
        -----------------------------------------------------------
        ROTATE LEFT                   CURSOR LEFT          Z
        ROTATE RIGHT                  CURSOR RIGHT         C
        ACCELERATE / STEALTH          CURSOR UP            S
        DROP BOMB                     CURSOR DOWN          X
        FIRE SHOT                     RETURN               LEFT CTRL
        
        Gameplay is fairly common sense to work out.
        Stay alive, and shooting enemy targets gains you points,
        whereas being shot down or shooting the wrong things lose
        you points. You have infinite planes, and are competing
        against the other computer planes (or other player!).
        First to a certain score wins once they land at base.
        Simple!

## Play Options

        At present there is no option screen. Options can be changed by
        editing the configuration file apricots.cfg (on UNIX systems this
        will probably require root access, user configuration files will
        be added soon in a future release). The number and type of planes
        can be varied, along with the airbases, as can 1/2 player game
        be chosen. The number of anti aircraft guns and scenery
        can be selected. Draks can be turned on or off, and a
        different condition for winning the game can be chosen.

## License

        Apricots falls under the GPL. Please read the file COPYING included
        in this distrubution. The sourcecode of apricots-0.2.6 will either
        be included in the distrubution, or can otherwise be downloaded
        from the apricots webpage (see below)

## Webpage

        For updates, bugfixes, binaries, sourcecode and more info please
        visit the apricots webpage at
        http://www.fishies.org.uk/apricots.html (offline)
