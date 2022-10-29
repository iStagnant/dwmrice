#!/bin/zsh
typeset -U path PATH

# Setting Defaults
export EDITOR=nvim
export VISUAL=nvim
export BROWSER=firefox

# Adding XDG paths
export XDG_DATA_HOME=${XDG_DATA_HOME:="$HOME/.local/share"}
export XDG_CACHE_HOME=${XDG_CACHE_HOME:="$HOME/.cache"}
export XDG_CONFIG_HOME=${XDG_CONFIG_HOME:="$HOME/.config"}

# Disable files
export LESSHISTFILE=-

# Fixing Paths
export XINITRC="$XDG_CONFIG_HOME"/X11/xinitrc
export XAUTHORITY="$XDG_RUNTIME_DIR"/Xauthority
export ZDOTDIR=$HOME/.config/zsh
export PASSWORD_STORE_DIR=$HOME/.config/.password-store

# Other program settings
export SUDO_ASKPASS="$HOME/.local/bin/dmenupass"

# Adding user scripts to PATH
path=(~/.local/bin $path)
export PATH
