#include"httpd.h"

int strtup(const char* _ip, const char* _port)
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0)
	{
		printf_log("socket fail", WARNING);
		exit(3);
	}
	
	int opt = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(atoi(_port));
	local.sin_addr.s_addr = inet_addr(_ip);

	if(bind(sock, (struct sockaddr*)&local, sizeof(local)) < 0)
	{
		printf_log("bind fail",WARNING);
		exit(4);
	}

	if(listen(sock, 5) < 0)
	{
		printf_log("listen fail",WARNING);
		exit(5);
	}

	return sock;
}
void printf_log(const char* mather, int rank)
{
	printf("[%s] [%d]\n",mather, rank);
}
int handle_pthread(void* arg)
{
	int sock = (int)arg;
	char buf[_SIZE_];//存储一行消息
	char method[_SIZE_];//方法，GET/POST
	char url[_SIZE_];//URL 带参的和不带参的（有无？区分）
	char path[_SIZE_];//路径
	char* str = NULL;//GET方法URL中？的后半部分
	
	int cgi = 0;//POST方法cgi=1，GET方法带参cgi=1，其余情况cgi=0
	int ret = -1;//读取一行获取的字符的数量
	int i = 0;
	int j = 0;
	int errno = 0;//退出码

	ret = get_line(sock, buf, sizeof(buf));
	if(ret < 0)
	{
		printf_log("get_line fail", FATAL);
		errno = 6;
		goto end;
	}
	printf("%s\n",buf);

	//GET xxx/yyy/zzz/?xxx=CCC
	//i->buf index    j->method index   -1是为了在装满的情况下最后一个位置放‘\0’
	while((i < sizeof(buf)) && (j < sizeof(method)-1) && !isspace(buf[i]))
	{
		method[j] = buf[i];
		++i;
		++j;
	}
	method[j] = '\0';

	if((strcasecmp(method, "GET") != 0) && (strcasecmp(method, "POST") != 0))
	{
		//这里我们写的http服务器只处理GET/POST请求，其余请求不处理
		errno = 7;
		goto end;
	}
	
	if(strcasecmp(method, "POST") == 0)
	{
		cgi = 1;//POST请求方法必须cgi=1
	}

	//过滤掉多余的空格
	while(isspace(buf[i]))//出了while循环以后，i一定指向URL的第一个字符
	{
		++i;
	}

	//i->buf index   j->url index   -1是为了在装满的情况下最后一个位置放‘\0’
	j = 0;
	while((i < sizeof(buf)) && (j < sizeof(url)) && (!isspace(buf[i])))
	{
		url[j] = buf[i];
		++i;
		++j;
	}
	url[j] = '\0';
	
	if(strcasecmp(method, "GET") == 0)
	{
		str = url;

		while(*str != '\0' && *str != '?')
		{
			++str;
		}

		//GET为带参的请求方法，cgi需要置为1
		if(*str == '?')
		{
			cgi = 1;
			*str = '\0';
			++str;//将url切分成两部分，一部分是？前的数据，由url指向，另外一部分是？后的数据，由str指向
		}
	}
	
	sprintf(path,"wwwroot%s",url);//将第三个参数的内容拼接到第二个参数中，然后得到的数据在放入第一个参数（缓冲区）中
	//url有可能是一个/也有可能是一串资源路径
	if(path[strlen(path)-1] == '/')//查看path路径此时是文件还是文件夹，如果是文件夹，那么直接将缺省页面加进去
	{
		//处理不给路径情况下的缺省页面
		strcat(path,"index.html");//字符串拼接
	}

	struct stat st;
	//stat(path,&st),在st中查找path，看path是否存在
	if( stat(path, &st) < 0 )
	{
		errno = 8;
		goto end;
	}
	else//路径确实存在
	{
		if( S_ISDIR(st.st_mode) )
		{
			//这个路径是一个文件夹
			strcpy(path, "wwroot/index.html");
		}
		else if((st.st_mode & S_IXUSR) || (st.st_mode & S_IXGRP) || (st.st_mode & S_IXOTH))
		{
			//st.st_mode是path路径下的文件的模式
			// (& S_IXUSR)==1 那么表明拥有者具有可执行权限，反之。
			// (& S_IXGRP)==1 那么表明所属组具有可执行权限，反之。
			// (& S_IXOTH)==1 那么表明其他具有可执行权限，反之。
			//走到这里至少拥有一个可执行权限，此时cgi需要置成1
			cgi = 1;
		}

		if(cgi == 1)
		{
			//
		}
		else
		{
			//走到这里一定是GET请求方法的无参类型的请求
			clear_hander(sock);//清空头部消息
			echo_www(sock, path, st.st_size);//回显响应内容
		}
	}

end:
	close(sock);
	return errno;
}

void clear_hander(int sock)
{
	int ret = -1;
	char buf[_SIZE_];

	do{
		ret = get_line(sock, buf, sizeof(buf));
	}while((ret != 1) && (strcmp(buf, "\n") != 0));
}

void echo_www(int sock, const char* path, int size)
{
	int ret = -1;
	int fd = open(path, O_RDONLY);//将该路径（path）下的文件已只读的方式打开
	if(fd < 0)
	{
		echo_errno();
		return;
	}
	
	char line[_SIZE_];
	sprintf(line, "HTTP/1.0 200 OK\r\n\r\n");//将响应行内容写进缓冲区中，多了一个\r\n代表着一个空行
	send(sock, line, strlen(line), 0);//将line缓冲区里面的内容放到sock文件描述符当中

	ret = sendfile(sock, fd, NULL, size);//将fd文件描述符的内容写进sock文件描述符当中，写size大小的字节数字
	if(ret < 0)
	{
		echo_errno();
		return;
	}

	close(fd);
}

void echo_errno()
{
	//noting
}

int get_line(int sock, char* buf, int len)
{
	assert(buf);

	char c = '\0';
	int i = 0;
	int ret = 0;

	//-1是为了不读取‘\0’
	while((i < len - 1) && (c != '\n'))
	{
		ret = recv(sock, &c, 1, 0);//从sock中读进c中，每次读1个，0默认表示为读取（读成功后取走字符）
		if(ret < 0)
		{
			c = '\n';
		}
		else
		{
			//我们要将\r...\n...\r\n...全部处理成\n的情况然后放进buf数组中，如果c不等于以上三种情况，那么就将读取的字符一次放进buf数组中。
			if(c == '\r')
			{
				ret = recv(sock, &c, 1, MSG_PEEK);//MSG_PEEK表示只读不取
				if(ret > 0 && c == '\n')
				{
					ret = recv(sock, &c, 1, 0);//这里ret一定会大于0，因为上一次读成功过，并没右取走，所以这里无需在判断
				}
				else
				{
					c = '\n';
				}
			}

			buf[i++] = c;//将读取的字符放进buf数组中
		}
	}

	buf[i] = '\0';
	return i;//返回读取字符的个数
}
