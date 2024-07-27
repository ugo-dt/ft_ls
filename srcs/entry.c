/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:14:56 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/07/27 15:05:13 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entry.h"
# include "file.h"

/*
lc	LEFTCODE, LEFT	Opening terminal code
rc	RIGHTCODE, RIGHT	Closing terminal code
ec	ENDCODE, END	Non-filename text
ex	*.extension	 	Every file using this extension e.g. *.jpg
*/

const char	*get_entry_color(struct Entry *entry)
{
	struct stat s;

	if (entry->is_link)
	{
		char	target_path[PATH_MAX];
		ssize_t len;
		len = readlink(entry->full_path, target_path, sizeof(target_path) - 1);
		if (len == -1)
			return state.colors.mi;
		target_path[len] = '\0';
		if (stat(target_path, &s) != 0)
		{
			if (errno == ENOENT)
				// return COLOR_40 COLOR_91;
				return state.colors.or;
			else
				return state.colors.mi;
		}
		return state.colors.ln;
	}

	switch (entry->statbuf.st_mode & S_IFMT)
	{
	case S_IFREG: // Normal file
		if (entry->statbuf.st_mode & S_ISUID) // setuid
			return state.colors.su;
		if (entry->statbuf.st_mode & S_ISGID) // setgid
			return state.colors.sg;
		if (entry->statbuf.st_mode & S_IXUSR) // executable
			return state.colors.ex;
		return state.colors.fi;
	case S_IFBLK: // Block device
		return state.colors.bd;
	case S_IFCHR: // Character device
		return state.colors.cd;
	case S_IFDIR: // Directory
		if (entry->statbuf.st_mode & S_IWOTH && entry->statbuf.st_mode & S_ISVTX) // other-writable and sticky
			return state.colors.tw;
		if (entry->statbuf.st_mode & S_IWOTH && !(entry->statbuf.st_mode & S_ISVTX)) // other-writable and not sticky
			return state.colors.ow;
		if (!(entry->statbuf.st_mode & S_IWOTH) && entry->statbuf.st_mode & S_ISVTX) // not other-writable sticky
			return state.colors.st;
		return state.colors.di;
	case S_IFLNK: // Symbolic link
		if (stat(entry->full_path, &s) != 0)
			return state.colors.or;
		return state.colors.ln;
	case S_IFSOCK: // Socket
		return state.colors.so;
	case S_IFIFO: // Named pipe
		return state.colors.pi;
	default:
		return state.colors.no;
	}
	return state.colors.no;
}

void	entry_print(struct Entry *entry)
{
	if (!entry || !entry->name)
		return;
	if (SHOULD_SKIP_HIDDEN(entry->name))
		return;
	if (state.options & OPTION_PRINT_SIZE)
		ft_printf("%*ld ", state.width.file_blocks, (long)entry->statbuf.st_blocks >> BLOCKS_SHIFT_BY);
	if (state.options & OPTION_LONG)
	{
		struct passwd *pwd;
		struct group *grp;

		print_file_type(entry->statbuf.st_mode);
		print_owner_permissions(entry->statbuf.st_mode);
		print_group_permissions(entry->statbuf.st_mode);
		print_other_permissions(entry->statbuf.st_mode);
		ft_printf(" %*ld ", state.width.nlink, (long)entry->statbuf.st_nlink);

		if (!(state.options & OPTION_HIDE_OWNER))
		{
			if ((pwd = getpwuid(entry->statbuf.st_uid)) != NULL)
				ft_printf("%-*s ", state.width.owner, pwd->pw_name);
			else
				ft_printf("%-*u ", state.width.owner, entry->statbuf.st_uid);
		}

		if (!(state.options & OPTION_HIDE_GROUP))
		{
			if ((grp = getgrgid(entry->statbuf.st_gid)) != NULL)
				ft_printf("%-*s ", state.width.group, grp->gr_name);
			else
				ft_printf("%-*u ", state.width.group, entry->statbuf.st_gid);
		}

		if (S_ISCHR(entry->statbuf.st_mode) || S_ISBLK(entry->statbuf.st_mode))
            ft_printf("%*u, %*u ", state.width.major_device_number, major(entry->statbuf.st_rdev),
			                         state.width.minor_device_number, minor(entry->statbuf.st_rdev));
		else
			ft_printf("%*ld ", state.width.file_size, (long)entry->statbuf.st_size);

		print_date(&entry->statbuf);
		ft_putchar(' ');
	}
	if (state.show_colors)
	{
		bool first = !state.current_color;
		state.current_color = get_entry_color(entry);
		if (first && state.current_color)
			ft_putstr(COLOR_RESET);
		if (state.current_color)
			ft_printf("%s%s%s", state.current_color, entry->name, COLOR_RESET);
		else
			ft_putstr(entry->name);
	}
	else
		ft_putstr(entry->name);
	if (state.options & OPTION_LONG && is_entry_symbolic_link(entry))
	{
		char buffer[1024];
		ssize_t len = readlink(entry->full_path, buffer, (sizeof(buffer) - 1));
		if (len != -1)
		{
			buffer[len] = '\0';
			ft_printf(" -> %s", buffer);
		}
	}
	ft_putchar('\n');
}

#define GET_NUMBER_LENGTH(len_ptr_, nb_, base_) \
	do                                          \
	{                                           \
		(*(len_ptr_)) = 1;                      \
		typeof(nb_) tmp_ = nb_;                 \
		if (tmp_ < 0)                           \
		{                                       \
			(*(len_ptr_))++;                    \
			tmp_ = -tmp_;                       \
		}                                       \
		while (tmp_ >= base_)                   \
		{                                       \
			tmp_ /= base_;                      \
			(*(len_ptr_))++;                    \
		}                                       \
	} while (0)

# define _SET_WIDTH(_width, _number) \
	do \
	{ \
		long len_; \
		GET_NUMBER_LENGTH(&len_, _number, 10); \
		if (_width < len_) \
			_width = len_; \
	} while (0)

struct Entry *entry_create(const char *name, const char *full_path)
{
	struct Entry *_new_entry = ft_xcalloc(sizeof(struct Entry));

	if (name)
		_new_entry->name = ft_xstrdup(name);
	if (full_path)
	{
		_new_entry->full_path = ft_xstrdup(full_path);
		long len;
		if (do_stat(full_path, &_new_entry->statbuf, &_new_entry->is_link) != 0)
		{
			show_errno_error(_new_entry->name);
			entry_destroy(_new_entry);
			return (NULL);
		}
		else
		{
			_SET_WIDTH(state.width.file_blocks, _new_entry->statbuf.st_blocks >> BLOCKS_SHIFT_BY);
			if (state.options & OPTION_LONG)
			{
				if ((_new_entry->pwd = getpwuid(_new_entry->statbuf.st_uid)) != NULL)
					len = ft_strlen(_new_entry->pwd->pw_name);
				else
					GET_NUMBER_LENGTH(&len, _new_entry->statbuf.st_uid, 10);
				if (state.width.owner < len)
					state.width.owner = len;

				if ((_new_entry->grp = getgrgid(_new_entry->statbuf.st_gid)) != NULL)
					len = ft_strlen(_new_entry->grp->gr_name);
				else
					GET_NUMBER_LENGTH(&len, _new_entry->statbuf.st_gid, 10);
				if (state.width.group < len)
					state.width.group = len;
				
				_SET_WIDTH(state.width.nlink, _new_entry->statbuf.st_nlink);
				_SET_WIDTH(state.width.file_size, _new_entry->statbuf.st_size);

				if (S_ISCHR(_new_entry->statbuf.st_mode) || S_ISBLK(_new_entry->statbuf.st_mode))
				{
					_SET_WIDTH(state.width.major_device_number, major(_new_entry->statbuf.st_rdev));
					_SET_WIDTH(state.width.minor_device_number, minor(_new_entry->statbuf.st_rdev));
					if (state.width.file_size < state.width.major_device_number + state.width.minor_device_number + 2)
						state.width.file_size = state.width.major_device_number + state.width.minor_device_number + 2;
				}
			}
		}
	}
	return (_new_entry);
}

void entry_destroy(void *self)
{
	struct Entry *entry = (struct Entry *)self;

	if (!entry)
		return;
	if (entry->name)
		free(entry->name);
	if (entry->full_path)
		free(entry->full_path);
	free(entry);
}

int compare_entries_by_size(const struct Entry *a, const struct Entry *b)
{
	int diff = (a->statbuf.st_size - b->statbuf.st_size);
	// We sort by largest first
	return diff ? -diff : ft_strcmp(a->name, b->name);
}

int compare_entries_by_name(const struct Entry *a, const struct Entry *b)
{
	return (ft_strcmp(a->name, b->name));
}

int compare_entries_by_time(const struct Entry *a, const struct Entry *b)
{
	int diff = timespec_cmp(a->statbuf.st_mtim, b->statbuf.st_mtim);
	// We sort by newest first
	return diff ? -diff : ft_strcmp(a->name, b->name);
}

bool is_entry_symbolic_link(struct Entry *entry)
{
	return (S_ISLNK(entry->statbuf.st_mode));
}

bool is_entry_regular(struct Entry *entry)
{
	return (S_ISREG(entry->statbuf.st_mode));
}

bool is_entry_directory(struct Entry *entry)
{
	return (S_ISDIR(entry->statbuf.st_mode));
}
