#!/bin/sh

installpkg() {
	pacman --noconfirm --needed -S "$1" >/dev/null 2>&1
}

aurinstall() {
	sudo yay -S --noconfirm "$1" >/dev/null 2>&1
}

maininstall() {
	installpkg "$1"
}

total=$(wc -l < progs.csv)
while IFS=, read -r tag program; do
	n=$((n + 1))
	case "$tag" in
	"A") aurinstall "$program" ;;
	*) maininstall "$program" ;;
	esac
done < progs.csv
