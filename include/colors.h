/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:48:08 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/07/26 13:25:50 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# include "file.h"
# include "state.h"

// RESET 0 
// DIR 01;34 
// LINK 01;36 
// MULTIHARDLINK 00 
// FIFO 40;33 
// SOCK 01;35 
// DOOR 01;35 
// BLK 40;33;01 
// CHR 40;33;01 
// ORPHAN 40;31;01 
// MISSING 00 
// SETUID 37;41 
// SETGID 30;43 
// CAPABILITY 30;41 
// STICKY_OTHER_WRITABLE 30;42 
// OTHER_WRITABLE 34;42 
// STICKY 37;44 
// EXEC 01;32

# define COLOR_DEFAULT	"\033[039m"

/*
no	NORMAL, NORM	Global default, although everything should be something
fi	FILE	Normal file
di	DIR	Directory
ln	SYMLINK, LINK, LNK	Symbolic link. If you set this to 'target' instead of a numerical value, the colour is as for the file pointed to.
pi	FIFO, PIPE	Named pipe
do	DOOR	Door
bd	BLOCK, BLK	Block device
cd	CHAR, CHR	Character device
or	ORPHAN	Symbolic link pointing to a non-existent file
so	SOCK	Socket
su	SETUID	File that is setuid (u+s)
sg	SETGID	File that is setgid (g+s)
tw	STICKY_OTHER_WRITABLE	Directory that is sticky and other-writable (+t,o+w)
ow	OTHER_WRITABLE	Directory that is other-writable (o+w) and not sticky
st	STICKY	Directory with the sticky bit set (+t) and not other-writable
ex	EXEC	Executable file (i.e. has 'x' set in permissions)
mi	MISSING	Non-existent file pointed to by a symbolic link (visible when you type ls -l)
lc	LEFTCODE, LEFT	Opening terminal code
rc	RIGHTCODE, RIGHT	Closing terminal code
ec	ENDCODE, END	Non-filename text
*.extension	 	Every file using this extension e.g. *.jpg
*/

const char *get_entry_color(mode_t mode);

void		parse_dircolors(const char *dircolors);

#endif // COLORS_H
