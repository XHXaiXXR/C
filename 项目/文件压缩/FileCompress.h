#pragma once
#include <iostream>
using namespace std;
#include<string>

#include "Huffman.h"

typedef long long LongType;

struct CharInfo
{
	unsigned char _ch;//�����ַ�
	LongType _count;//�����ַ����ֵĴ���
	string _code;//����Huffman����

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
		//��ʼ��ÿ��λ�õ�_dataֵ
		for (int i = 0;i < 256;i++)
		{
			_infos[i]._ch = i;
		}
	}
public:
	//ѹ���ļ�
	void CompressFile(const char* filename)
	{
		FILE* fread = fopen(filename, "rb");//��ֻ����ʽ���ļ�
		if (NULL == fread)
		{
			cout<<"The File Open Fail"<<endl;
			exit(0);
		}

		//ͳ���ļ����ַ����ֵĴ���
		int ch = fgetc(fread);
		while (ch != EOF)//һֱ�����ļ�ĩβ
		{
			_infos[ch]._count++;
			ch = fgetc(fread);
		}

		//����HuffmanTree
		CharInfo invalid;
		HuffmanTree<CharInfo> hufftree(_infos, 256, invalid);
		Node* root = hufftree.GetRoot();

		//��ȡhuffman����
		string code;
		_GetHuffmanCode(root, code);

		//���ļ�ָ���Ƶ��ļ�ͷ
		fseek(fread, 0, SEEK_SET);
		string write(filename);//write = "filename"
		write += ".Compress";//ѹ���ļ�������

		//����һ��ѹ���ļ������ѹ���ļ�����Ϣ
		FILE* fwite = fopen(write.c_str(), "wb");

		ch = fgetc(fread);
		unsigned char data = 0;//ѹ�������Զ����Ƶ���ʽ�洢���ļ���
		int pos = 7;//����bitλ���ƶ�����

		while (ch != EOF)//�����ļ���β
		{
			const char* ptr = _infos[ch]._code.c_str();

			//�������������
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

		//���һ���ַ�����дûд����Ҫ�Ž�ȥ
		fputc(data, fwite);

		//д�����ļ������ڽ�ѹ��
		_WriteConfig(filename);

		fclose(fread);
		fclose(fwite);
		cout<<"ѹ���ɹ�"<<endl;
	}
	//��ѹ���ļ�
	void UnCompressFile(const char* filename)
	{
		//�ļ�������ڣ�Ҫ��Ȼ��ѹʲô
		assert(filename);

		string write(filename);
		//ȥ��ѹ���ļ��ĺ�׺�����������ļ��ĺ�׺��Ȼ���ȡ�����ļ�
		unsigned int index = write.rfind('.', write.size());
		write = write.substr(0, index);
		string writeconfig = write;
		writeconfig += ".config";

		//��ȡ�����ļ����������ļ��������Ϣ��ӵ�RInfo�����С�
		CharInfo RInfo[256];
		_ReadConfigFile(writeconfig.c_str(), RInfo);

		//��ѹ���ļ�
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

		//��ʼ��ѹ��
		FILE* fread = fopen(filename, "rb");
		unsigned char ch = fgetc(fread);

		//���ַ�������������ѭ������
		int pos = 8;
		while (count)
		{
			--pos;
			unsigned char val = 1;

			//��Ҫ��ѹ���ļ�һ���ֽ�һ���ֽڵķ���
			if (ch & (val << pos))
			{
				cur = cur->_right;
			} 
			else
			{
				cur = cur->_left;
			}

			//����Ҷ�ӽ��˵���Ѿ��ҵ�һ���ַ�
			if (cur->_left == NULL && cur->_right == NULL)
			{
				//�������Ҷ�ӽ�㣬��ô��Ҫ����Ӧ���ַ�д����ѹ���ļ���
				fputc(cur->_weight._ch, fwrite);

				//ÿ�ζ�Ҫ��cur��������Ϊ���ڵ�
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
		cout<<"��ѹ���ɹ�"<<endl;
	}
private:
	//��ȡ�����ļ�
	void _ReadConfigFile(const char* configfilename, CharInfo* info)
	{
		FILE* fread = fopen(configfilename, "rb");
		if (NULL == fread)
		{
			cout<<"Read File Fault"<<endl;
			exit(0);
		}

		int ch = fgetc(fread);
		while (ch != EOF)//һֱ��ȡ���ļ���β
		{
			//�ַ����ַ����ֵĴ������ַ�����
			info[ch]._ch = ch;
			unsigned char index = ch;//��¼��ǰ���±꣬һ�����ʹ��

			//��Ϊ������һ��������,����Ҫ������ȡ����ȡ��һ���ַ�
			ch = fgetc(fread);
			ch = fgetc(fread);

			string count;
			while (ch != ',')
			{
				count.push_back(ch);
				ch = fgetc(fread);
			}
			info[index]._count = atoi(count.c_str());//����ȡ���ַ����ֵĴ������롣

			ch = fgetc(fread);
			//���ַ��������δ���
			while (ch != '\n')
			{
				info[index]._code.push_back(ch);
				ch = fgetc(fread);
			}

			ch = fgetc(fread);//��ȡ'\n'�ַ�����һ���ַ�
		}
	}

	//д�����ļ�
	void _WriteConfig(const char* filename)
	{
		//ѹ���ļ�����Ϣ�����ڡ�.config����׺���ļ�����
		string write(filename);
		write += ".config";
		FILE* fwite = fopen(write.c_str(), "wb");//ֻд��ʽ���ļ�

		for (int i = 0;i < 256;i++)
		{
			if (_infos[i]._count)
			{
				//�����ʽΪ���ַ����ַ����ֵĴ����� �ַ����룩
				fputc(_infos[i]._ch, fwite);
				fputc(',', fwite);
				
				//���ַ����ֵĴ�����ʮ�����ַ�����ʽ�����ַ�������
				char arr[126];
				_itoa(_infos[i]._count, arr, 10);
				fputs(arr, fwite);
				fputc(',', fwite);

				fputs(_infos[i]._code.c_str(), fwite);
				fputc('\n', fwite);
			}
		}
		//�ر��ļ�ʵ���Ͼ��Ǳ����ļ�
		fclose(fwite);
	}
	//���������������������ֻ��Ҫ���ʵ�Ҷ�ӽ��
	//��ȡhuffman����
	void _GetHuffmanCode(Node* root, string code)
	{
		if (NULL == root)
		{
			return;
		}

		//������������Ҹ�
		//������0��1
		_GetHuffmanCode(root->_left, code + '0');
		_GetHuffmanCode(root->_right, code + '1');

		if (root->_left == NULL && root->_right == NULL)
		{
			_infos[root->_weight._ch]._code = code;
		}
	}
private:
	CharInfo _infos[256];//����һ��CharInfo���͵����飬���ù�ϣ���ʣ�ÿ��λ�õ�_dataֵ���Ƕ�Ӧ���ַ�
};
