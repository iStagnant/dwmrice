if [[ -z "$DISPLAY" ]] && [[ $(tty) = /dev/tty1 ]]; then
	startx "$XDG_CONFIG_HOME/X11/xinitrc"
fi
