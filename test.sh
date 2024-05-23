#!/bin/bash

set -e
verbose=false
bonus=false

run_bonus()
{
	diff <(./ft_ls -A) <(ls -A) || (echo "BONUS KO" && exit 1)
	diff <(./ft_ls -f) <(ls -f) || (echo "BONUS KO" && exit 1)
	diff <(./ft_ls --format=long) <(ls --format=long) || (echo "BONUS KO" && exit 1)
	diff <(./ft_ls -g) <(ls -g) || (echo "BONUS KO" && exit 1)
	diff <(./ft_ls -o) <(ls -o) || (echo "BONUS KO" && exit 1)
	diff <(./ft_ls -log) <(ls -log) || (echo "BONUS KO" && exit 1)
	diff <(./ft_ls -s) <(ls -s) || (echo "BONUS KO" && exit 1)
	diff <(./ft_ls -S) <(ls -S) || (echo "BONUS KO" && exit 1)
	diff <(./ft_ls -U) <(ls -U) || (echo "BONUS KO" && exit 1)

	diff <(./ft_ls --all) <(ls --all) || (echo "BONUS KO" && exit 1)
	diff <(./ft_ls --almost-all) <(ls --almost-all) || (echo "BONUS KO" && exit 1)
	diff <(./ft_ls --reverse) <(ls --reverse) || (echo "BONUS KO" && exit 1)
	diff <(./ft_ls --recursive) <(ls --recursive) || (echo "BONUS KO" && exit 1)
	diff <(./ft_ls --size) <(ls --size) || (echo "BONUS KO" && exit 1)
	diff <(./ft_ls --sort=none) <(ls --sort=none) || (echo "BONUS KO" && exit 1)
	diff <(./ft_ls --sort=size) <(ls --sort=size) || (echo "BONUS KO" && exit 1)
	diff <(./ft_ls --sort=time) <(ls --sort=time) || (echo "BONUS KO" && exit 1)

	diff <(./ft_ls --format=long) <(ls --format=long) || (echo "KO" && exit 1)
	diff <(./ft_ls --format=verbose) <(ls --format=verbose) || (echo "KO" && exit 1)
	diff <(./ft_ls --format long) <(ls --format long) || (echo "KO" && exit 1)
	diff <(./ft_ls --format verbose) <(ls --format verbose) || (echo "KO" && exit 1)
	diff <(./ft_ls --forma=long) <(ls --forma=long) || (echo "KO" && exit 1)
	diff <(./ft_ls --forma=verbose) <(ls --forma=verbose) || (echo "KO" && exit 1)
	diff <(./ft_ls --forma long) <(ls --forma long) || (echo "KO" && exit 1)
	diff <(./ft_ls --forma verbose) <(ls --forma verbose) || (echo "KO" && exit 1)
	diff <(./ft_ls --fo=long) <(ls --fo=long) || (echo "KO" && exit 1)
	diff <(./ft_ls --fo=verbose) <(ls --fo=verbose) || (echo "KO" && exit 1)
	diff <(./ft_ls --fo long) <(ls --fo long) || (echo "KO" && exit 1)
	diff <(./ft_ls --fo verbose) <(ls --fo verbose) || (echo "KO" && exit 1)
	diff <(./ft_ls --fo=l) <(ls --fo=l) || (echo "KO" && exit 1)
	diff <(./ft_ls --fo=verb) <(ls --fo=verb) || (echo "KO" && exit 1)
	diff <(./ft_ls --fo l) <(ls --fo l) || (echo "KO" && exit 1)
	diff <(./ft_ls --fo verb) <(ls --fo verb) || (echo "KO" && exit 1)

	diff <(./ft_ls --format=long /bin) <(ls --format=long /bin) || (echo "KO" && exit 1)
	diff <(./ft_ls --format=verbose /bin) <(ls --format=verbose /bin) || (echo "KO" && exit 1)
	diff <(./ft_ls --format long /bin) <(ls --format long /bin) || (echo "KO" && exit 1)
	diff <(./ft_ls --format verbose /bin) <(ls --format verbose /bin) || (echo "KO" && exit 1)
	diff <(./ft_ls --forma=long /bin) <(ls --forma=long /bin) || (echo "KO" && exit 1)
	diff <(./ft_ls --forma=verbose /bin) <(ls --forma=verbose /bin) || (echo "KO" && exit 1)
	diff <(./ft_ls --forma long /bin) <(ls --forma long /bin) || (echo "KO" && exit 1)
	diff <(./ft_ls --forma verbose /bin) <(ls --forma verbose /bin) || (echo "KO" && exit 1)
	diff <(./ft_ls --fo=long /bin) <(ls --fo=long /bin) || (echo "KO" && exit 1)
	diff <(./ft_ls --fo=verbose /bin) <(ls --fo=verbose /bin) || (echo "KO" && exit 1)
	diff <(./ft_ls --fo long /bin) <(ls --fo long /bin) || (echo "KO" && exit 1)
	diff <(./ft_ls --fo verbose /bin) <(ls --fo verbose /bin) || (echo "KO" && exit 1)
	diff <(./ft_ls --fo=l /bin) <(ls --fo=l /bin) || (echo "KO" && exit 1)
	diff <(./ft_ls --fo=verb /bin) <(ls --fo=verb /bin) || (echo "KO" && exit 1)
	diff <(./ft_ls --fo l /bin) <(ls --fo l /bin) || (echo "KO" && exit 1)
	diff <(./ft_ls --fo verb /bin) <(ls --fo verb /bin) || (echo "KO" && exit 1)

	echo "BONUS OK"
}

run_tests()
{
	rm -f __ft_ls_test_fifo__
	mkfifo __ft_ls_test_fifo__

	diff <(./ft_ls) <(ls) || (echo "KO" && exit 1)
	diff <(./ft_ls -a) <(ls -a) || (echo "KO" && exit 1)
	diff <(./ft_ls -aA) <(ls -aA) || (echo "KO" && exit 1)
	diff <(./ft_ls -Aa) <(ls -Aa) || (echo "KO" && exit 1)
	diff <(./ft_ls -R) <(ls -R) || (echo "KO" && exit 1)
	diff <(./ft_ls -r) <(ls -r) || (echo "KO" && exit 1)
	diff <(./ft_ls -aR) <(ls -aR) || (echo "KO" && exit 1)
	diff <(./ft_ls -rR) <(ls -rR) || (echo "KO" && exit 1)
	diff <(./ft_ls -ar) <(ls -ar) || (echo "KO" && exit 1)
	diff <(./ft_ls -aRr) <(ls -arR) || (echo "KO" && exit 1)

	diff <(./ft_ls -a . libft/srcs srcs include) <(ls -a . libft/srcs srcs include) || (echo "KO" && exit 1)
	diff <(./ft_ls -aA . libft/srcs srcs include) <(ls -aA . libft/srcs srcs include) || (echo "KO" && exit 1)
	diff <(./ft_ls -Aa . libft/srcs srcs include) <(ls -Aa . libft/srcs srcs include) || (echo "KO" && exit 1)
	diff <(./ft_ls -R . libft/srcs srcs include) <(ls -R . libft/srcs srcs include) || (echo "KO" && exit 1)
	diff <(./ft_ls -r . libft/srcs srcs include) <(ls -r . libft/srcs srcs include) || (echo "KO" && exit 1)
	diff <(./ft_ls -aR . libft/srcs srcs include) <(ls -aR . libft/srcs srcs include) || (echo "KO" && exit 1)
	diff <(./ft_ls -rR . libft/srcs srcs include) <(ls -rR . libft/srcs srcs include) || (echo "KO" && exit 1)
	diff <(./ft_ls -ar . libft/srcs srcs include) <(ls -ar . libft/srcs srcs include) || (echo "KO" && exit 1)
	diff <(./ft_ls -aRr . libft/srcs srcs include) <(ls -arR . libft/srcs srcs include) || (echo "KO" && exit 1)

	diff <(./ft_ls -a *) <(ls -a *) || (echo "KO" && exit 1)
	diff <(./ft_ls -aA *) <(ls -aA *) || (echo "KO" && exit 1)
	diff <(./ft_ls -Aa *) <(ls -Aa *) || (echo "KO" && exit 1)
	diff <(./ft_ls -R *) <(ls -R *) || (echo "KO" && exit 1)
	diff <(./ft_ls -r *) <(ls -r *) || (echo "KO" && exit 1)
	diff <(./ft_ls -aR *) <(ls -aR *) || (echo "KO" && exit 1)
	diff <(./ft_ls -rR *) <(ls -rR *) || (echo "KO" && exit 1)
	diff <(./ft_ls -ar *) <(ls -ar *) || (echo "KO" && exit 1)
	diff <(./ft_ls -aRr *) <(ls -arR *) || (echo "KO" && exit 1)

	diff <(./ft_ls -la *) <(ls -la *) || (echo "KO" && exit 1)
	diff <(./ft_ls -lR *) <(ls -lR *) || (echo "KO" && exit 1)
	diff <(./ft_ls -lr *) <(ls -lr *) || (echo "KO" && exit 1)
	diff <(./ft_ls -laR *) <(ls -laR *) || (echo "KO" && exit 1)
	diff <(./ft_ls -lrR *) <(ls -lrR *) || (echo "KO" && exit 1)
	diff <(./ft_ls -lar *) <(ls -lar *) || (echo "KO" && exit 1)
	diff <(./ft_ls -laRr *) <(ls -larR *) || (echo "KO" && exit 1)

	diff <(./ft_ls /bin) <(ls /bin) || (echo "KO" && exit 1)
	diff <(./ft_ls /usr/bin) <(ls /usr/bin) || (echo "KO" && exit 1)
	diff <(./ft_ls /dev) <(ls /dev) || (echo "KO" && exit 1)

	diff <(./ft_ls -R /bin) <(ls -R /bin) || (echo "KO" && exit 1)
	diff <(./ft_ls -R /usr/bin) <(ls -R /usr/bin) || (echo "KO" && exit 1)

	diff <(./ft_ls -laR /bin) <(ls -laR /bin) || (echo "KO" && exit 1)
	diff <(./ft_ls -laR /usr/bin) <(ls -laR /usr/bin) || (echo "KO" && exit 1)

	diff <(./ft_ls -ta *) <(ls -ta *) || (echo "KO" && exit 1)
	diff <(./ft_ls -taA *) <(ls -taA *) || (echo "KO" && exit 1)
	diff <(./ft_ls -tAa *) <(ls -tAa *) || (echo "KO" && exit 1)
	diff <(./ft_ls -tR *) <(ls -tR *) || (echo "KO" && exit 1)
	diff <(./ft_ls -tr *) <(ls -tr *) || (echo "KO" && exit 1)
	diff <(./ft_ls -taR *) <(ls -taR *) || (echo "KO" && exit 1)
	diff <(./ft_ls -trR *) <(ls -trR *) || (echo "KO" && exit 1)
	diff <(./ft_ls -tar *) <(ls -tar *) || (echo "KO" && exit 1)
	diff <(./ft_ls -taRr *) <(ls -tarR *) || (echo "KO" && exit 1)

	diff <(./ft_ls -lta *) <(ls -lta *) || (echo "KO" && exit 1)
	diff <(./ft_ls -ltaA *) <(ls -ltaA *) || (echo "KO" && exit 1)
	diff <(./ft_ls -ltAa *) <(ls -ltAa *) || (echo "KO" && exit 1)
	diff <(./ft_ls -ltR *) <(ls -ltR *) || (echo "KO" && exit 1)
	diff <(./ft_ls -ltr *) <(ls -ltr *) || (echo "KO" && exit 1)
	diff <(./ft_ls -ltaR *) <(ls -ltaR *) || (echo "KO" && exit 1)
	diff <(./ft_ls -ltrR *) <(ls -ltrR *) || (echo "KO" && exit 1)
	diff <(./ft_ls -ltar *) <(ls -ltar *) || (echo "KO" && exit 1)
	diff <(./ft_ls -ltaRr *) <(ls -ltarR *) || (echo "KO" && exit 1)

	# These take longer to complete
	# diff <(./ft_ls -artRl /usr/lib) <(ls -artRl /usr/lib) || (echo "KO" && exit 1)
	# diff <(./ft_ls -artRl /usr) <(ls -artRl /usr) || (echo "KO" && exit 1)

	set +x
	echo "OK"
}

for var in "$@"
do
	case $var in
		-v|--verbose)
			verbose=true
			shift
			;;
		-b|--bonus)
			bonus=true
			shift
			;;
		*)
			;;
	esac
done

if [ "$verbose" = true ]; then
	set -x
	run_tests
	if [ "$bonus" = true ]; then
		run_bonus
	fi
else
	run_tests 2> /dev/null
	if [ "$bonus" = true ]; then
		run_bonus  2> /dev/null
	fi
fi


rm -f __ft_ls_test_fifo__
