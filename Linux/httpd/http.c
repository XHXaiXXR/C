#include"httpd.h"


int Statup(char* ip, int port)
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0)
	{
		perror("socket");
		exit(2);
	}

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(port);
	local.sin_addr.s_addr = inet_addr(ip);

	int opt = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	if(bind(sock, (struct sockaddr*)&local, sizeof(local)) < 0)
	{
		perror("bind");
		exit(3);
	}

	if(listen(sock, 5) < 0)
	{
		perror("listen");
		exit(4);
	}
	return sock;
}
int SetNonBlocking(int fd)
{
	int old_opt = fcntl(fd, F_GETFL);
	int new_opt = old_opt | O_NONBLOCK;
	fcntl(fd, F_SETFL, new_opt);

	return old_opt;
}
void Addfd(int epollfd, int fd)
{
	struct epoll_event ev;
	ev.events = EPOLLIN | EPOLLET;
	ev.data.fd = fd;
	epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
	
	//由于epoll是高效的ET工作模式，所以必须设置fd为非阻塞的。
	SetNonBlocking(fd);
}
int GetLine(int fd, char buf[], int len)
{
	//按字符读取，一个一个的读
	char c = '\0';
	int index = 0;//buf的下标

	//将\r	\n	\r\n不同的换行符全部换成\n
	while(c != '\n' && index < len-1)
	{
		int num = recv(fd, &c, 1, 0);
		if(num > 0)
		{
			if(c == '\r')
			{
				num = recv(fd, &c, 1, MSG_PEEK);//MSG_PEEK窥探，只读不取
				if(num > 0 && c == '\n')
				{
					num = recv(fd, &c, 1, 0);
				}
				else
				{
					c = '\n';
				}
			}
			buf[index++] = c;
		}
		else
		{
			//什么都没有读到的时候c='\n'然后在while循环中退出
			c = '\n';
		}
	}
	buf[index] = 0;
	return index;//返回读到字符多少个
}
//一个线程处理一个http的请求
void* HandlerRequest(void* arg)
{
	int fd = (int)arg;
	char buf[SIZE];
	int ret = -1;

//	//测试Getline（）函数
//	do
//	{
//		ret = GetLine(fd, buf, sizeof(buf));
//		printf("%s", buf);
//	}while(ret > 0 && strcmp(buf, "\n") != 0);
	
	int nums = -1;//错误码
	char method[SIZE/10];//获取请求方法
	char url[SIZE];	//比如一个请求行是GET /a/b/index.html http/1.0,那么这个url存储的就是/a/b/index.html
	if(GetLine(fd, buf, sizeof(buf)) <= 0)
	{
		//获取请求行，如果进到这个循环中则错误退出
		ret = -1;
		nums = -1;//错误码
		goto end;
	}

	int i = 0;
	int j = 0;//保存buf的下标
	
	//获取请求方法
	while(i < sizeof(method)-1 && j < sizeof(buf) && !isspace(buf[j]))
	{
		method[i++] = buf[j++];
	}
	method[i] = 0;
	printf("method = %s\n", method);

	//过滤掉请求方法和请求资源中间的所有空格
	while(j < sizeof(buf) && !isspace(buf[j]))
	{
		j++;
	}

	i = 0;
	//获取请求资源
	while(i < sizeof(url)-1 && j < sizeof(buf) && !isspace(buf[j]))
	{
		url[i++] = buf[j++];
	}
	url[i] = 0;
	printf("url = %s\n", url);
	
	//这个小型的web服务器只处理GET方法和POST方法，对其他方法均不做处理
	if(strcasecmp(method, "GET")&& strcasecmp(method, "POST"))
	{
		//strcasecmp()函数不分大小写比较
		ret = -2;
		nums = -1;
		goto end;
	}
	
	//这里区分哪些请求要使用cgi的程序，哪些返回默认程序
	//0->非cgi    1->cgi
	//GET方法无参非cgi，GET方法带参和POST方法都是CGI
	int cgi = 0;//默认为非CGI方法
	char* query_string = NULL;//指向GET方法带参以后的参数部分

	if(strcasecmp(method, "POST") == 0)
	{
		//只要是POST方法cgi就等于1
		cgi = 1;
	}
	else
	{
		query_string = url;
		while(*query_string != '\0')
		{
			if(*query_string == '?')
			{
				*query_string = '\0';
				query_string++;//这时候query_string指向？后面的参数部分
				cgi = 1;
				break;
			}
			else
			{
				query_string++;
			}
		}
	}

	char path[SIZE];
	sprintf(path, "wwwroot%s", url);//sprintf()格式化输出到指定的字符串中
	if(path[strlen(path) - 1] == '/')
	{
		//如果path现在只是一个路径的话，给他拼上一个默认页面
		strcat(path, "index.html");//strcat()字符串拼接
	}

	//判断资源路径是否合法
	//Linux下一切皆文件，判断这个路径下的文件是否存在就可以证明这个资源路径是否合法
	struct stat st;
	if(stat(path, &st) != 0)
	{
		//文件不存在
		ret = -3;
		nums = -1;
		goto end;
	}
	else
	{
		//文件一定存在
		if(S_ISDIR(st.st_mode))
		{
			//文件有可能是一个目录
			strcat(path, "/index.html");
		}
		else if( st.st_mode & S_IXUSR || st.st_mode & S_IXGRP || st.st_mode & S_IXOTH)
		{
			//如果是可执行的二进制文件，我们应该把可执行的二进制文件的执行结果返回，所以要执行cgi程序
			cgi = 1;
		}
		else{}
	}

	if(cgi)
	{
		//执行cgi程序
		ExecCgi(fd, path, method, query_string);		
	}
	else
	{
		ClearHead(fd);//清除头部信息，调用函数完了以后请求行，请求报头，还有空行都全部被清除
		EchoWww(fd, path, st.st_size);
	}
end:
	EchoClient(nums);
	close(fd);
	return (void*)ret;//返回退出码
}

void ExecCgi(int fd, const char* path, const char* method, const char*query_string)
{
	int content_lenght = -1;//用于存放POST方法Content-Lenght的长度（参数的长度）

	//POST和GET方法均要清空头部信息，POST在清空头部信息的时候还要获取参数的长度
	if(strcasecmp(method, "GET") == 0)
	{
		ClearHead(fd);
	}
	else
	{
		//POST方法
		char buf[SIZE];
		int ret = -1;
		do{
			ret = GetLine(fd, buf, sizeof(buf));

			if(strncasecmp(buf, "Content-Lenght: ", 16) == 0)
			{
				content_lenght = atoi(buf+16);//提取POST方法的参数的长度
			}
		}while(ret > 0 && strcmp(buf, "\n"));

		if(content_lenght <= 0)
		{
			return;
		}
	}
	
	//将响应行，空行写回去
	const char* statusline = "HTTP/1.0 200 OK\r\n";//响应行
	const char* blankline = "\r\n";//空行
	send(fd, statusline, strlen(statusline), 0);
	send(fd, blankline, strlen(blankline), 0);
	
	//为父子进程之间创建管道进行通信
	int input[2];
	int output[2];
	if(pipe(input) < 0)
	{
		return;
	}
	if(pipe(output) < 0)
	{
		return;
	}

	pid_t id = fork();
	if(id == 0)
	{
		//子进程
		close(input[1]);
		close(output[0]);

		dup2(input[0], 0);//将标准输入重定向到input[0]中
		dup2(output[1], 1);//将标准输出重定向到output[1]中

		char method_env[SIZE/10];
		char query_string_env[SIZE];
		char content_lenght_env[SIZE];
		//putenv()函数可以设置环境变量，环境变量是可以被子进程继承的
		sprintf(method_env, "METHOD = %s", method);
		putenv(method_env);
		
		if(strcasecmp(method, "GET") == 0)
		{
			sprintf(query_string_env, "QUERY_STRING = %s", query_string);
			putenv(query_string_env);
		}
		else
		{
			sprintf(content_lenght_env, "CONTENT_LENGHT = %s", content_lenght);
			putenv(content_lenght_env);
		}

		execl(path, path, NULL);//第一个参数表示资源路径在哪里，第二个参数表示命令行应该怎么执行他
		//execl函数程序替换成功没有返回值，一旦返回，必定失败
		exit(1);
	}
	else if(id > 0)
	{
		//父进程
		close(input[0]);
		close(output[1]);

		char c = '\0';
		if(strcasecmp(method, "POST") == 0)
		{
			//如果是POST方法，我们需要将参数传给子进程，让子进程来处理
			int i = 0;
			for(;i < content_lenght;i++)
			{
				recv(fd, &c, 1, 0);
				write(input[1], &c, 1);
			}
		}

		//子进程处理响应，并将结果写回父进程，父进程需要从管道中取读取数据
		while(read(output[0], &c, 1) > 0)
		{
			send(fd, &c, 1, 0);
		}

		waitpid(id, NULL, 0);

		close(input[1]);
		close(output[0]);
	}
	else
	{
		perror("fork");
		return;
	}
}

void ClearHead(int fd)
{
	char buf[SIZE];
	int ret = -1;
	do{
		ret = GetLine(fd, buf, sizeof(buf));
	}while(ret > 0 && strcmp(buf, "\n") != 0);
}

void EchoWww(int fd, char* path, int size)
{
	int newfd = open(path, O_RDONLY);
	if(newfd < 0)
	{
		return ;
	}

	const char* statusline = "HTTP/1.0 200 OK\r\n";//响应行
	const char* blankline = "\r\n";//空行
	send(fd, statusline, strlen(statusline), 0);
	send(fd, blankline, strlen(blankline), 0);
	
	sendfile(fd, newfd, NULL, size);//sendfile()将一个文件的内容直接拷贝到另一个文件中，没有缓冲区拷贝数据

	close(newfd);
}

void EchoClient(int nums)
{}

