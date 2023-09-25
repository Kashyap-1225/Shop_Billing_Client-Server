#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>

void fetch(char *upc, char *val, char*nam)
{
 	strcpy(val,"NF");
 	strcpy(nam,"NF");
    	char buf[100];
	FILE* ptr = fopen("database.txt", "r");
    	FILE* red = ptr;
    	FILE* name = fopen("database.txt", "r");
    	if (ptr!= NULL)
    	while (fscanf(ptr, "%s%*s%*s",buf)== 1)
	{
		if(!strcmp(buf,upc))	
        	{
        		fscanf(red, "%*s%s%*s",val);
        		//name = ptr;
        		fscanf(name, "%*s%*s%s",nam);
        	}
        	else
        	{ 
        		red = ptr;
        		name = ptr;
        	}
        	
        }
}

void end(char *b, int total)
{
	int length = 0;
	char total_cost[10];
	char end_msg[] = "Thank You.\nYour total cost is\t";
	length = snprintf( NULL, 0, "%d", total);
	snprintf( total_cost, length+1, "%d", total);
	strncat(end_msg,total_cost,length);
	strcpy(b,end_msg);
}


int costing(char *a, char *b, char *c, char *d)
{
	int num=0, cost=0, length=0,i=0;
	char upc[4];
	char val[10];
	char nam[50];
	strncpy(upc, a, 3);
	upc[3]='\0';
	fetch(upc,val,nam);
	if(strcmp(val,"NF"))
	{
		while(val[i]!='\0')
		{
			cost = cost*10+((int)val[i])-48;
			i++;
		}
	}
	else return 0;
	i = 0;
	while(d[i]!='\0')
		{
			num = num*10+((int)d[i])-48;
			i++;
		}
	length = snprintf( NULL, 0, "%d", cost);
	snprintf( b, length+1, "%d", cost);
	length = snprintf( NULL, 0, "%d", cost*num);
	snprintf( c, length+1, "%d", cost*num);
	strcpy(d,nam);
	return cost*num;
}

int main()
{
	int counter=0;
	int serv_sockfd,serv_len,cli_sockfd,processId;
	int total = 0, cost = 0,x;
	struct sockaddr_in serv_address;
	char a[100], b[100], c[100], d[100];
	serv_sockfd=socket(AF_INET,SOCK_STREAM,0);
	serv_address.sin_family=AF_INET;
	serv_address.sin_port=9007;
	serv_address.sin_addr.s_addr = INADDR_ANY;
	serv_len=sizeof(serv_address);
	bind(serv_sockfd,(struct sockaddr*)&serv_address,serv_len);
	listen(serv_sockfd,5);
	printf("SERVER IS WORKING..\n");

	while(1)
	{
		counter++;
		cli_sockfd = accept(serv_sockfd,(struct sockaddr*)&serv_address,&serv_len);	
		processId = fork();
		if(processId==0)
		{
			
			printf("\nClient %d : Connected\n",counter);
			close(serv_sockfd);
			while(1)
			{
				printf("Request from client %d:\t",counter);	
				read(cli_sockfd,a,sizeof(a));
				printf("%s\n",a);	
				if(a[0]=='1')
				{
					end(b, total);	
					write(cli_sockfd, b, sizeof(b));
					break;
				}
				else if(a[0]=='0')
				{
					printf("UPC_number from client %d:\t",counter);	
					read(cli_sockfd,a,sizeof(a));
					printf("%s\n",a);	
					read(cli_sockfd,d,sizeof(d));	
							
					cost = costing(a,b,c,d);
					if(cost == 0)
					{
						printf("Not found\n");
						strcpy(d,"NF");
						write(cli_sockfd, d, sizeof(d));
						continue;
					}
					else
					{
						total+= cost;	
						printf("Found: Data Sent\n");
					}
				}
				write(cli_sockfd, d, sizeof(d));
				write(cli_sockfd, b, sizeof(b));
				write(cli_sockfd, c, sizeof(c));
			}
			printf("\nClient %d : Connection terminated\n", counter);
			exit(0);
		}
		close(cli_sockfd);
	}
	return 0;
}
