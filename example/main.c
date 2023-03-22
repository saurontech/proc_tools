#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "proc_tools.h"

//#define LOOP

#ifdef LOOP
struct _cmd_info{
	int active;
	char cmd[1024];
};
#endif

int main(int argc, char *argv[])
{
	int i;
	int ret;
	pid_t pid;
	char ifname[1024];
	char cmd[1024];
	int cmdlen;
	struct stat sb;	
#ifdef LOOP
	struct _cmd_info * cmds;

	cmds = malloc(sizeof(struct _cmd_info)*(argc - 1));
	memset(cmds, 0, sizeof(struct _cmd_info)*(argc - 1));

	do{
#endif
	for(i = 1; i < argc; i++){
		if(stat(argv[i], &sb) == 0){
		}else if(__search_port_inode(atoi(argv[i]), 10, &sb.st_ino) == 0){
		}else{
			printf("no inode %s\n", argv[i]);
#ifdef LOOP
			if(cmds[i - 1].active){
				printf("reactivate %s\n", cmds[i - 1].cmd);
			}
#endif
			continue;
		}

		if(__cmd_inode_search_pid(0, sb.st_ino, 
					cmd, sizeof(cmd), &cmdlen, 
					&pid)){
			printf("no ps operating %s\n", argv[i]);
#ifdef LOOP
			if(cmds[i - 1].active){
				printf("reactivate %s\n", cmds[i -1].cmd);
			}
#endif
			continue;
		}
#ifdef LOOP
		int j;
		cmds[i -1].active = 1;
		memcpy(cmds[i-1].cmd, cmd, cmdlen);
		for(j = 0; j < cmdlen; j++){
			if(cmds[i - 1].cmd[j] == '\0'){
				cmds[i - 1].cmd[j] = ' ';
			}
		}
		cmds[i -1].cmd[cmdlen] = '\0';
//		printf("after adjust %s\n", cmds[i -1].cmd);
#endif	
		printf("%s operating %s\n", cmd, argv[i]);
	}

#ifdef LOOP
	sleep(10);
	}while(1);
#endif


	return 0;
}
