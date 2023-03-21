#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "proc_tools.h"

int main(int argc, char *argv[])
{
	int i;
	int ret;
	pid_t pid;
	char ifname[1024];
	char cmd[1024];
	int cmdlen;
	struct stat sb;	
		
	for(i = 1; i < argc; i++){
		if(stat(argv[i], &sb) == 0){
		}else if(__search_port_inode(atoi(argv[i]), 10, &sb.st_ino) == 0){
		}else{
			printf("no inode %s", argv[i]);
		}

		if(__cmd_inode_search_pid(0, sb.st_ino, 
					cmd, sizeof(cmd), &cmdlen, 
					&pid)){
			printf("no ps operating %s\n", argv[i]);
			continue;
		}
		
		printf("%s operating %s\n", cmd, argv[i]);
	}

/*	if(__search_port_inode(atoi(argv[1]), 10, &sb.st_ino) == 0 &&
				__cmd_inode_search_pid(0, sb.st_ino, 
					cmd, sizeof(cmd), &cmdlen, 
					&pid) == 0){
			printf("ret 2 = %d cmd %s\n", ret, cmd);
	}else{
		printf("no ps operating %s\n", argv[1]);
	}

*/


	return 0;

}
