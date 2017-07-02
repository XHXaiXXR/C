#pragma once
#include <iostream>
using namespace std;
#include<string>

#include "Huffman.h"

typedef long long LongType;

struct CharInfo
{
	unsigned char _ch;//保存字符
	LongType _count;//保存字符出现的次数
	string _code;//保存Huffman编码

	CharInfo(const LongType& count = 0)
		:_count(count)
	{}

	CharInfo operator+(CharInfo& ch)
	{
		return CharInfo(_count + ch._count);
	}

	bool operator<(CharInfo& ch)
	{
		return _count < ch._count;
	}
};

class HuffmanFileCompress
{
	typedef HuffmanTreeNode<CharInfo> Node;
public:
	HuffmanFileCompress()
	{
		//初始化每个位置的_data值
		for (int i = 0;i < 256;i++)
		{
			_infos[i]._ch = i;
		}
	}
public:
	//压缩文件
	void CompressFile(const char* filename)
	{
		FILE* fread = fopen(filename, "rb");//已只读形式打开文件
		if (NULL == fread)
		{
			cout<<"The File Open Fail"<<endl;
			exit(0);
		}

		//统计文件中字符出现的次数
		int ch = fgetc(fread);
		while (ch != EOF)//一直读到文件末尾
		{
			_infos[ch]._count++;
			ch = fgetc(fread);
		}

		//构建HuffmanTree
		CharInfo invalid;
		HuffmanTree<CharInfo> hufftree(_infos, 256, invalid);
		Node* root = hufftree.GetRoot();

		//获取huffman编码
		string code;
		_GetHuffmanCode(root, code);

		//将文件指针移到文件头
		fseek(fread, 0, SEEK_SET);
		string write(filename);//write = "filename"
		write += ".Compress";//压缩文件的名字

		//创建一个压缩文件，存放压缩文件的信息
		FILE* fwite = fopen(write.c_str(), "wb");

		ch = fgetc(fread);
		unsigned char data = 0;//压缩数据以二进制的形式存储在文件中
		int pos = 7;//控制bit位的移动次数

		while (ch != EOF)//读到文件结尾
		{
			const char* ptr = _infos[ch]._code.c_str();

			//遍历保存结点编码
			while (*ptr)
			{
				if (pos >= 0)
				{
					data = data | ((*ptr - '0')<< pos);
					--pos;
				}
				if (pos < 0)
				{
					fputc(data, fwite);
					pos = 7;
					data = 0;
				}

				ptr++;
			}
			ch = fgetc(fread);
		}

		//最后一个字符不管写没写满都要放进去
		fputc(data, fwite);

		//写配置文件，用于解压缩
		_WriteConfig(filename);

		fclose(fread);
		fclose(fwite);
		cout<<"压缩成功"<<endl;
	}
	//解压缩文件
	void UnCompressFile(const char* filename)
	{
		//文件必须存在，要不然解压什么
		assert(filename);

		string write(filename);
		//去掉压缩文件的后缀，加上配置文件的后缀，然后读取配置文件
		unsigned int index = write.rfind('.', write.size());
		write = write.substr(0, index);
		string writeconfig = write;
		writeconfig += ".config";

		//读取配置文件，将配置文件里面的信息添加到RInfo数组中。
		CharInfo RInfo[256];
		_ReadConfigFile(writeconfig.c_str(), RInfo);

		//解压缩文件
		write += ".UnCompress";
		FILE* fwrite = fopen(write.c_str(), "wb");

		CharInfo invalid;
		HuffmanTree<CharInfo> hft(RInfo, 256, invalid);
		Node* root = hft.GetRoot();
		if (NULL == root)
		{
			return ;
		}
		Node* cur = root;
		LongType count = (root->_weight)._count;

		//开始解压缩
		FILE* fread = fopen(filename, "rb");
		unsigned char ch = fgetc(fread);

		//用字符的总数来控制循环条件
		int pos = 8;
		while (count)
		{
			--pos;
			unsigned char val = 1;

			//需要对压缩文件一个字节一个字节的访问
			if (ch & (val << pos))
			{
				cur = cur->_right;
			} 
			else
			{
				cur = cur->_left;
			}

			//读到叶子结点说明已经找到一个字符
			if (cur->_left == NULL && cur->_right == NULL)
			{
				//如果读到叶子结点，那么就要把相应的字符写进解压缩文件中
				fputc(cur->_weight._ch, fwrite);

				//每次都要将cur重新设置为根节点
				cur = root;
				if (--count == 0)
				{
					break;
				}
			}

			if (pos == 0)
			{
				pos = 8;
				ch = fgetc(fread);
			}
		}

		fclose(fread);
		fclose(fwrite);
		cout<<"解压缩成功"<<endl;
	}
private:
	//读取配置文件
	void _ReadConfigFile(const char* configfilename, CharInfo* info)
	{
		FILE* fread = fopen(configfilename, "rb");
		if (NULL == fread)
		{
			cout<<"Read File Fault"<<endl;
			exit(0);
		}

		int ch = fgetc(fread);
		while (ch != EOF)//一直读取到文件结尾
		{
			//字符，字符出现的次数，字符编码
			info[ch]._ch = ch;
			unsigned char index = ch;//记录当前的下标，一遍后面使用

			//因为这里是一个“，”,所以要将他读取并读取下一个字符
			ch = fgetc(fread);
			ch = fgetc(fread);

			string count;
			while (ch != ',')
			{
				count.push_back(ch);
				ch = fgetc(fread);
			}
			info[index]._count = atoi(count.c_str());//将获取的字符出现的次数存入。

			ch = fgetc(fread);
			//将字符编码依次存入
			while (ch != '\n')
			{
				info[index]._code.push_back(ch);
				ch = fgetc(fread);
			}

			ch = fgetc(fread);//读取'\n'字符的下一个字符
		}
	}

	//写配置文件
	void _WriteConfig(const char* filename)
	{
		//压缩文件的信息保存在“.config”后缀的文件当中
		string write(filename);
		write += ".config";
		FILE* fwite = fopen(write.c_str(), "wb");//只写形式打开文件

		for (int i = 0;i < 256;i++)
		{
			if (_infos[i]._count)
			{
				//存放形式为（字符，字符出现的次数， 字符编码）
				fputc(_infos[i]._ch, fwite);
				fputc(',', fwite);
				
				//将字符出现的次数以十进制字符的形式存入字符数组中
				char arr[126];
				_itoa(_infos[i]._count, arr, 10);
				fputs(arr, fwite);
				fputc(',', fwite);

				fputs(_infos[i]._code.c_str(), fwite);
				fputc('\n', fwite);
			}
		}
		//关闭文件实际上就是保存文件
		fclose(fwite);
	}
	//后序遍历哈夫曼树，我们只需要访问到叶子结点
	//获取huffman编码
	void _GetHuffmanCode(Node* root, string code)
	{
		if (NULL == root)
		{
			return;
		}

		//后序遍历，左右根
		//编码左0右1
		_GetHuffmanCode(root->_left, code + '0');
		_GetHuffmanCode(root->_right, code + '1');

		if (root->_left == NULL && root->_right == NULL)
		{
			_infos[root->_weight._ch]._code = code;
		}
	}
private:
	CharInfo _infos[256];//创建一个CharInfo类型的数组，利用哈希性质，每个位置的_data值都是对应的字符
};
