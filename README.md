#duelshock
duelshock enables a SIXAXIS controller connnected via USB to be used in linux based systems.

##Features.
* Optimised mapping for maximum usablility.
* Stand-by mode to handle Dualshock's buggy R2/L2 triggers.
* Handy notifications.
* Mouse pointer sensitivity can be changed by tweaking POINTERSENSITIVITY in duelshock.h.

##Dependecies.
xdotool is the only dependency.

    sudo apt-get install xdotool

More info [here](http://www.semicomplete.com/projects/xdotool/).

##Usage.
Compile duelshock.c and execute it with root permission (needed to access /dev/hidrawX). 

    gcc -o duelshock duelshock.c  
    sudo ./duelshock

Plug in the controller and enjoy!

## Default Mapping.
Button                |  Default Mapping
----------------------|-------------------
Left Stick            |  Mouse pointer.
Right Stick           |  Scrolling.
X Action key          |  Left-click.
O Action key          |  Right-click.
T Action key          |  Media Play/Pause. (XF86AudioPlay)
S Action key          |  Backspace.
D-pad keys            |  Arrow keys.
L1                    |  Media Previous. (XF86AudioPrev)
L2                    |  Ctrl.
L3                    |  Middle-click.
R1                    |  Media Next. (XF86AudioNext)
R2                    |  Shift.
R3                    |  Escape.
Start                 |  Enter/Return.
Select                |  Alt.
PS                    |  Toggles Standby mode.

##Changing Default Mapping.
Mapping of all buttons (D-pad, Action keys, \[LR\]\[1-3\]) can be changed via duelshock.h by changing the corresponding symbol's value. For example, to change X Action key\'s map from left-click to enter/return, change AXMAP in duelshock.h to "Return". Map values are similar to xdotool's keystrokes. Read the man page of xdotool to know keystroke values of different keys.

Scrolling and mouse movement can be swapped between the sticks by changing the value of LEFTSTICKMOUSE to 0.

Mouse-click map values are "RClick" for right-click, "LClick" for left-click and "MClick" for middle-click.

##TODO
* CLI to create profiles and to change mapping.
* Bluetooth capability.
* ~~Windows port?~~

##Notes.
1. Media controls can be used to handle both default music player (rythmbox/banshee) as well as video players (totem/vlc). [Read](http://askubuntu.com/a/424847).
2. Scrolling is a little buggy. Expect a fix soon.
3. Working on a experimental, totally mental way to type. Might implement it later if it is usable.
4. Icon paths for notify-send can be configured via duelshock.h
5. Default mapping can now be changed in duelshock.h.
