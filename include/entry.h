/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:15:46 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/07/25 19:11:48 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTRY_H
# define ENTRY_H

# include "colors.h"
# include "file.h"
# include "state.h"
# include "ft_xmalloc.h"
# include <errno.h>
# include <grp.h>
# include <libft.h>
# include <pwd.h>
# include <stdbool.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <time.h>

# ifdef __linux__
#  include <sys/sysmacros.h>
# endif

#ifdef __GNUC__
# if __has_warning("-Wgnu-statement-expression-from-macro-expansion")
#  pragma GCC diagnostic ignored	"-Wgnu-statement-expression-from-macro-expansion"
# endif
# if __has_warning("-Wgnu-statement-expression")
#  pragma GCC diagnostic ignored	"-Wgnu-statement-expression"
# endif
# if __has_warning("-Wlanguage-extension-token")
#  pragma GCC diagnostic ignored	"-Wlanguage-extension-token"
# endif
#endif // __GNUC

# define _SKIP_IMPLIED(_name) \
	(state.options & OPTION_ALMOST_ALL && (!ft_strcmp(_name, ".") || !ft_strcmp(_name, "..")))

# define SHOULD_SKIP_HIDDEN(_name) \
	(_name[0] == '.' && !(state.options & (OPTION_ALL | OPTION_ALMOST_ALL)) || _SKIP_IMPLIED(_name))

struct Entry
{
	char          *name;
	char          *full_path;
	struct stat   statbuf;
	struct group  *grp;
	struct passwd *pwd;
};

struct Entry *entry_create(const char *name, const char *full_path);
void          entry_print(struct Entry *entry);
void          entry_destroy(void *entry);

int           compare_entries_by_name(const struct Entry *a, const struct Entry *b);
int           compare_entries_by_time(const struct Entry *a, const struct Entry *b);
int           compare_entries_by_size(const struct Entry *a, const struct Entry *b);

bool          is_entry_symbolic_link(struct Entry *entry);
bool          is_entry_regular(struct Entry *entry);
bool          is_entry_directory(struct Entry *entry);

#endif // ENTRY_H
