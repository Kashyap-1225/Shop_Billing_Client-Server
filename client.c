#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
	int sockfd,len,result;
	struct sockaddr_in address;
	char name[100], ser[100];
	int i=0, num=0;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	address.sin_family=AF_INET;
	address.sin_port=9007;
	address.sin_addr.s_addr=inet_addr("127.0.0.1");
	len=sizeof (address);
	result=connect(sockfd,(struct sockaddr *)&address,len);
	if(result == -1)
	{
		perror("Unable to connect!\n");
		exit(1);
	}
	while(1)
	{
		num = 0;
		printf("\nEnter the request\n");
		gets(name);
		write(sockfd,name,sizeof(name));
		if(name[0]=='1')
		{
			write(sockfd,name,sizeof(name));
			read(sockfd,ser,sizeof(ser));
			puts(ser);
			return 0;
		}
		else if(name[0]=='0')
		{
			printf("\nEnter the UPC no\n");
			gets(name);
			write(sockfd,name,sizeof(name));
			printf("\nEnter the quantity\n");
			gets(name);
			write(sockfd,name,sizeof(name));
			i=0;
			while(name[i]!='\0')
			{
				num = num*10+((int)name[i])-48;
				i++;
			}
			printf("Item name\t");
			read(sockfd,ser,sizeof(ser));
			if(strcmp(ser,"NF"))
			{
				puts(ser);
				printf("Rate of the item is:\t");
				read(sockfd,ser,sizeof(ser));
				puts(ser);
				printf("Price of the item for %d pieces is:\t",num);
				read(sockfd,ser,sizeof(ser));
				puts(ser);
			}
			else 
			{
				printf("UPC not found\n");
				continue;
			}
			
		}
		else printf("Invalid Input\n");
	}
	return 0;
}

