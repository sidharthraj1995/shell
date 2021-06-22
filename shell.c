#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#define WHITESPACE " \t\n"      // We want to split our command line up into tokens
                                // so we need to define what delimits our tokens.
                                // In this case  white space
                                // will separate the tokens on our command line

#define MAX_COMMAND_SIZE 255    // The maximum command-line size

#define MAX_NUM_ARGUMENTS 10     // Mav shell only supports ten arguments


int main()
{	int j=0, status;
	char cmd[255], *para[255], command[255];
  char * cmd_str = (char*) malloc( MAX_COMMAND_SIZE );
  memset(cmd, 0, 255);
  
  char * binpath[255];
  char * usrlocalbinpath[255];
  char * usrlocalpath[255];
  //char * cwdpath[255];
  
  memset(binpath, 0 ,255);
  memset(usrlocalbinpath, 0 ,255);
  memset(usrlocalpath, 0 ,255);
 // memset(cwdpath, 0 ,255);  
  
 //char *envp[] = { (char *) "PATH=/bin" , 0};

  while(1)
  {
    // Print out the msh prompt
    printf ("msh> ");
    
    read_command(command, para);
    
	// Read the command from the commandline.  The
    // maximum command that will be read is MAX_COMMAND_SIZE
    // This while command will wait here until the user
    // inputs something since fgets returns NULL when there
    // is no input
 /*   while( !fgets (cmd_str, MAX_COMMAND_SIZE, stdin) );

    // Parse input 
    char *token[MAX_NUM_ARGUMENTS];

    int   token_count = 0;                                 
                                                           
    // Pointer to point to the token
    // parsed by strsep
    char *arg_ptr;                                         
                                                           
    char *working_str  = strdup( cmd_str );                

    // we are going to move the working_str pointer so
    // keep track of its original value so we can deallocate
    // the correct amount at the end
    char *working_root = working_str;

    // Tokenize the input strings with whitespace used as the delimiter
    while ( ( (arg_ptr = strsep(&working_str, WHITESPACE ) ) != NULL) && 
              (token_count<MAX_NUM_ARGUMENTS))
    {
      token[token_count] = strndup( arg_ptr, MAX_COMMAND_SIZE );
      if( strlen( token[token_count] ) == 0 )
      {
        token[token_count] = NULL;
      }
        token_count++;
    }
    
     strcpy( cmd , token[0]); //first word is the command-> copy that to cmd
     
	 
	 for(j=0; j< token_count; j++)
     {
     	para[j]=token[j];
     	
     }
*/
     
     
      if( strcmp(cmd, "exit") == 0 || strcmp(cmd, "quit") == 0)
	    
		   exit(0);
	    
	  /*  else
	    {
    		strcmp(cmd, NULL);
	        printf("msh>");
		}
    		
    	 */
    	
    	
    pid_t pid;
    pid=fork();
    
        
    if( pid != 0)
    {
    		wait(&status);
    		
    }
    else{	strncpy(binpath , "/bin/", strlen( "/bin" ));
			strncpy(usrlocalbinpath , "/usr/local/bin/", strlen( "/usr/local/bin/" ));
			strncpy(usrlocalpath , "/usr/local/", strlen( "/usr/local/" ));
			//strncpy(cwdpath , "/bin/", strlen( "/bin" ));
			
			strncpy(cmd, binpath, strlen(binpath));
			strncpy(cmd, usrlocalbinpath, strlen(usrlocalbinpath));
			strncpy(cmd, usrlocalpath, strlen(usrlocalpath));
		//	strncpy(cmd, binpath, strlen(binpath));
		
		
			execl(usrlocalpath,cmd,(char*)NULL );
			execl(usrlocalbinpath,cmd,(char*)NULL );
			execl(binpath,cmd,(char*)NULL );
			//execl(cwdpath+cmd, );
			
			printf("Command not found\n");
	
//			strcmp (cmd , "/bin/");
// 			strcat (cmd , command);
//  		execve (cmd , para ,envp);
	    }
	    
	   
    

//    int token_index  = 0;
//    for( token_index = 0; token_index < token_count; token_index ++ ) 
//    {
//      printf("token[%d] = %s\n", token_index, token[token_index] );  
//    }

//     free( working_root );

  }
  return 0;

}


void read_command ( char commands[], char *parameterss[])
{	
	char line[1024];
	int count = 0, i = 1, j = 0;
	char *array[100], *pch;
	
	//read onr line
	for( ;; )
	{
		int c = fgetc(stdin);
		line[count++] = (char) c;
		if( c == '\n')
		{
			break;
		}
	}
	
	if(count == 1) return;
	pch = strtok( line, "\n");
	
	//parse the line into words
	while(pch != NULL)
	{
		array[i++]=strdup(pch);
		pch=strtok(NULL, " \n");
	}
	//command
	strcpy(commands,array[0]);
	
	//parameters
	for(j=0;j<i;j++)
	{
		parameterss[j]=array[j];
		parameterss[i]=NULL;
	}
	
}