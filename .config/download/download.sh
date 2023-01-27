#!/bin/sh

installpkg() {
	pacman --noconfirm --needed -S "$1" >/dev/null 2>&1
}

aurinstall() {
	sudo -u "$USER" yay -S --noconfirm "$1" >/dev/null 2>&1
}

maininstall() {
	installpkg "$1"
}

pipinstall() {
	[ -x "$(command -v "pip")" ] || installpkg python-pip >/dev/null 2>&1
	yes | pip install "$1"
}

installationloop() {
	total=$(wc -l < progs.csv)
	while IFS=, read -r tag program; do
		n=$((n + 1))
		case "$tag" in
		"A") aurinstall "$program" ;;
		"P") pipinstall "$program" ;;
		*) maininstall "$program" ;;
		esac
	done < progs.csv
}

## THE ACTUAL SCRIPT ##

# Allow user to run sudo without password. Since AUR programs must be installed
# in a fakeroot environment, this is required for all builds with AUR.
trap 'rm -f /etc/sudoers.d/larbs-temp' HUP INT QUIT TERM PWR EXIT
echo "%wheel ALL=(ALL) NOPASSWD: ALL" >/etc/sudoers.d/larbs-temp

# Make pacman colorful, concurrent downloads and Pacman eye-candy.
grep -q "ILoveCandy" /etc/pacman.conf || sed -i "/#VerbosePkgLists/a ILoveCandy" /etc/pacman.conf
sed -Ei "s/^#(ParallelDownloads).*/\1 = 5/;/^#Color$/s/#//" /etc/pacman.conf

# Use all cores for compilation.
sed -i "s/-j2/-j$(nproc)/;/^#MAKEFLAGS/s/^#//" /etc/makepkg.conf

# The command that does all the installing. Reads the progs.csv file and installs each needed program.
installationloop

# Moving github files to their places
parentdir="$(dirname $(dirname $(pwd)))"
[ -d /home/$USER/.config ] && rm -rf /home/$USER/.config
[ -d /home/$USER/.local ] && rm -rf /home/$USER/.local
sudo -u "$USER" cp -r "$parentdir/.*" "/home/$USER"
[ -d /home/$USER/.config ] && cd /home/$USER/.config/dwm && sudo make clean install && cd ../st && sudo make clean install && cd ../slstatus && sudo make clean install && cd ../slock && sudo make clean install

# Making sure that abook has a storage directory
[ -d /home/$USER/.local/share/abook ] || sudo -u "$USER" mkdir -p "/home/$USER/.local/share/abook"

# Make zsh the default shell for the user.
chsh -s /bin/zsh "$USER" >/dev/null 2>&1
sudo -u "$USER" mkdir -p "/home/$USER/.cache/zsh/"

# Generating completion script for mangal
mangal completion zsh > /usr/share/zsh/site-functions/_mangal

# Making neomutt work with my abook configuration
sed -Ei "s/set query_command =.*/set query_command = \"abook --config ~\/.config\/abook\/abookrc --datafile ~\/.local\/share\/abook\/addressbook --mutt-query '%s'\"/" /usr/share/mutt-wizard/mutt-wizard.muttrc
sed -Ei "s/abook --add-email/abook --config ~\/.config\/abook\/abookrc --datafile ~\/.local\/share\/abook\/addressbook --add-email/" /usr/share/mutt-wizard/mutt-wizard.muttrc
