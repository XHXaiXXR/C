#define _CRT_SECURE_NO_WARNINGS 1

#pragma once  //保证头文件被多次包含的时候只出现一次
#pragma warning (disable: 4996)
#include<assert.h>
#include<errno.h>

typedef enum State
{
	C_BEGIN,
	C_END,
}State;

void Convert(FILE* fIn,FILE* fOut)
{
	char first,second;
	State tag = C_END;
	assert(fIn);
	assert(fOut);
	do
	{
		first = fgetc(fIn); // 读文件
		switch(first)
		{
		case '/':
            second = fgetc(fIn);
			if(second == '*')
			{
				if(tag == C_END)
				{
					fputc('/',fOut);
					fputc('/',fOut);

					tag = C_BEGIN;
				}
				else
				{
					fputc('/',fOut);
					fputc('*',fOut);
				}
			}
			else
			{
				fputc(first,fOut);
				fputc(second,fOut);
			}
			break;
		case '\n':
			//多行注释问题
			fputc('\n',fOut);
			if(tag == C_BEGIN)
			{
				fputc('/',fOut);
				fputc('/',fOut);
			}
			break;
		case '*':
			second = fgetc(fIn);
			if(second == '/')
			{
				//换行问题
				char next = fgetc(fIn);
				if(next == '/')
				{
					fputc('\n',fOut);
					fseek(fIn,-1,SEEK_CUR);//fseek使文件指针倒退一个字符
				}
				else if(next != '\n' && next != EOF)
				{
					fputc('\n',fOut);
					fputc(next,fOut);
				}
				else
				{
					fputc('\n',fOut);
				}
				tag = C_END;
			}
			else
			{
				fputc(first,fOut);
				fputc(second,fOut);

			}
			break;
		default:
			fputc(first,fOut);
			break;
		}
	}while(first != EOF);//EOF是文件的结束
}


void AnnoyatinConvert(const char* inputFile,
	                  const char* outputFile)
{
	FILE* fIn,*fOut;
	fIn = fopen(inputFile,"r");
	if(fIn == NULL)
	{
		printf("打开文件%s失败,errno: %d\n",inputFile,errno);
		return;
	}

	fOut = fopen(outputFile,"w");
	if(fOut == NULL)
	{
		fclose(fIn);
		printf("打开文件%s失败,errno: %d\n",outputFile,errno);
		return;
	}

	Convert(fIn,fOut);

	fclose(fIn);
	fclose(fOut);

}