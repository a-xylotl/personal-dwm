# my take on Derek Taylor's dwm (Dynamic Window Manager) build

![Screenshot of his desktop](https://gitlab.com/dwt1/dotfiles/raw/master/.screenshots/dotfiles04.png) 
dwm is an extremely fast, small, and dynamic window manager for X.

# Keybindings

The MODKEY is set to the `Super` key (aka the `Windows` key)

| Keybinding | Action |
| :--- | :--- |
| `MODKEY + P` | opens run launcher (dmenu is the run launcher but can be easily changed) |
| `MODKEY + Enter` | opens terminal (st is the terminal but can be easily changed) |
| `MODKEY + c` | kills the client |
| `MODKEY + b` | toggles the top bar |
| `MODKEY + SHIFT + c` | closes window with focus |
| `MODKEY + SHIFT + q` | quits dwm |
| `MODKEY + d` | incnmaster -1 |
| `MODKEY + i` | incnmaster +1 |
| `MODKEY + j` | focus stack +1 (switches focus between windows in the stack) 
| `MODKEY + k` | focus stack -1 (switches focus between windows in the stack)|
| `MODKEY + SHIFT + n` | rotates stack +1 (rotates the windows in the stack)|
| `MODKEY + SHIFT + m` | rotates stack -1 (rotates the windows in the stack)|
| `MODKEY + SHIFT + j` | move stack +1 (moves the windows in the stack) |
| `MODKEY + SHIFT + k` | move stack -1 (moves the windows in the stack) |
| `MODKEY + h` | setmfact -0.05 (decreases window width) |
| `MODKEY + l` | setmfact +0.05 (increases window width) |
| `MODKEY + ,` | focusmon -1 (switches focus between monitors) |
| `MODKEY + .` | focusmon +1 (switches focus between monitors) |
| `MODKEY + CTRL + ,` | cyclelayout -1 (cycles onto previous layout) |
| `MODKEY + CTRL + .` | cyclelayout +1 (cycles onto next layout) |
| `MODKEY + SHIFT + [number]` | (sends window to specified tag)

# Requirements

In order to build dwm you need the Xlib header files.


# Installation

Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

    make clean install


# Running dwm

Add the following line to your .xinitrc to start dwm using startx:

    exec dwm

In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

    DISPLAY=foo.bar:1 exec dwm

(This will start dwm on display :1 of the host foo.bar.)

In order to display status info in the bar, you can do something
like this in your .xinitrc:

    while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
    do
    	sleep 1
    done &
    exec dwm


# Configuration

The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.


# Patches

Here is a list of patches for my build (this repo) of dwm:
- dwm-alpha - Makes dwm have translucent bars, while keeping text opaque
- dwm-attachaside - Makes new clients get attached and focused in stacking area instead of becoming the new master
- dwm-autostart - Adds program autostart functionality when dwm starts up
- dwm-centeredmaster - Adds two layouts, centeredmaster and centeredfloatingmaster
- dwm-cyclelayouts - Adds functionality to cycle through all available layouts
- dwm-fancybar - Shows titles of every visible window instead of just selected one
- dwm-fibonacci - Adds a layout where windows are arranged in a fibonacci-style layout
- dwm-gridmode - Adds a layout where windows are arranged in a grid layout
- dwm-movestack - Adds functionality to move clients around in stack and swap them with the master
- dwm-pertag - Makes each tag have their own layout, mwfact, barpos and nmaster
- dwm-selfrestart - Restart dwm without using an external script
- dwm-rotatestack- Adds functionality to move a client from bottom to top of stack
- dwm-statuspadding - Adds configurability to horizontal and vertical padding in the status bar
- dwm-uselessgap - Adds useless gap around windows for aesthetics
