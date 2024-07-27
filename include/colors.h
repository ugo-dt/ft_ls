/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:48:08 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/07/27 13:50:12 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# include "state.h"

// Attributes
# define COLOR_0		"\033[0m"
# define COLOR_RESET	COLOR_0
# define COLOR_1		"\033[1m"
# define COLOR_2		"\033[2m"
# define COLOR_3		"\033[3m"
# define COLOR_4		"\033[4m"
# define COLOR_5		"\033[5m"
# define COLOR_6		"\033[6m"
# define COLOR_7		"\033[7m"
# define COLOR_8		"\033[8m"

// Colors
# define COLOR_39		"\033[39m"
# define COLOR_DEFAULT	COLOR_39
# define COLOR_31		"\033[31m"
# define COLOR_32		"\033[32m"
# define COLOR_33		"\033[33m"
# define COLOR_34		"\033[34m"
# define COLOR_35		"\033[35m"
# define COLOR_36		"\033[36m"
# define COLOR_37		"\033[37m"

// Backgrounds
# define COLOR_40		"\033[40m"
# define COLOR_41		"\033[41m"
# define COLOR_42		"\033[42m"
# define COLOR_43		"\033[43m"
# define COLOR_44		"\033[44m"
# define COLOR_45		"\033[45m"
# define COLOR_46		"\033[46m"
# define COLOR_47		"\033[47m"

// Extra colors	
# define COLOR_90		"\033[90m"
# define COLOR_91		"\033[91m"
# define COLOR_92		"\033[92m"
# define COLOR_93		"\033[93m"
# define COLOR_94		"\033[94m"
# define COLOR_95		"\033[95m"
# define COLOR_96		"\033[96m"
# define COLOR_97		"\033[97m"
# define COLOR_100		"\033[100m"
# define COLOR_101		"\033[101m"
# define COLOR_102		"\033[102m"
# define COLOR_103		"\033[103m"
# define COLOR_104		"\033[104m"
# define COLOR_105		"\033[105m"
# define COLOR_106		"\033[106m"
# define COLOR_107		"\033[107m"

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
ex	*.extension	 	Every file using this extension e.g. *.jpg
*/

typedef struct LS_Colors LS_Colors;

void	parse_dircolors(LS_Colors *colors, const char *dircolors);

#endif // COLORS_H
