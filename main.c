#include "shell.h"

/**
 *main - main code
 *@ac: argument count
 *@av: array of raguments
 *Return: 0 on success or -1
 */
int main(int ac, char **av)
{
	info_t infor[] = { INFO_INIT };
	int pd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (pd)
			: "r" (pd));

	if (ac == 2)
	{
		pd = open(av[1], O_RDONLY);
		if (pd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		infor->readfd = pd;
	}
	populate_env_list(infor);
	hist_read(infor);
	hsh(infor, av);
	return (EXIT_SUCCESS);
}
