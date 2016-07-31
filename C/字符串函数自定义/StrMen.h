#pragma once
#include <assert.h>

char* MySrtcpy(char* dest,const char* src)
{
	assert(dest);
	assert(src);
	char* ret = dest;

	while (*src != '\0')
	{
		*dest++ = *src++;
		//dest++;
		//src++;
	}
	*dest = '\0';

	return ret;
}


char* MyStrncpy(char* dest,const char* src,int count)
{
	assert(dest);
	assert(src);
	char* ret = dest;

	while (count && (*src != '\0'))
	{
		*dest++ = *src++;
		count--;
	}
	*dest = '\0';

	return ret;
}

char* MyStrcat(char* dest,const char* src)
{
	assert(dest);
	assert(src);
	char* ret = dest;

	while (*dest != '\0')
	{
		dest++;
	}

	while (*src != '\0')
	{
		*dest++ = *src++;
	}
	*dest = '\0';

	return ret;
}

char* MySrtncat(char* dest,const char* src,int count)
{
	assert(dest);
	assert(src);
	char* ret = dest;

	while (*dest != '\0')
	{
		dest++;
	}

	while ((*src != '\0') && count)
	{
		*dest++ = *src++;
		count--;
	}
	*dest = '\0';

	return ret;
}

int MyStrcmp(const char* dest,const char* src)
{
	assert(dest);
	assert(src);

	while (*dest == *src)
	{
		dest++;
		src++;
	}

	int ret = (((unsigned int)*dest) - ((unsigned int)*src));

	if (ret > 0)
	{
		ret = 1;
	}
	else if (ret < 0)
	{
		ret = -1;
	} 
	else
	{
		ret = 0;
	}

	return ret;
}

int MyStrncmp(const char* dest,const char* src,int count)
{
	assert(dest);
	assert(src);

	while ((*dest == *src) && (count))
	{
		count--;
		if (count == 0)
		{
			//若是n都比较完了，那么指针就不要向后偏移了
			break;
		}
		dest++;
		src++;
	}

	return (((unsigned int)*dest)-((unsigned int)*src));
}

char* MyStrstr(const char* str1,const char* str2)
{
	assert(str1);
	assert(str2);

	const char* new_str1 = NULL;
	const char* new_str2 = NULL;

	while (*str1 != '\0')
	{
		new_str1 = str1;
		new_str2 = str2;

		while ((*new_str1) && (*new_str2) && (*new_str1 == *new_str2))
		{
			new_str1++;
			new_str2++;
		}

		if (*new_str2 == '\0')
		{
			return (char* )str1;
		}

		str1++;
	}

	return NULL;
}

char* MyStrchr(const char* str,const char c)
{
	assert(str);

	while (*str != '\0')
	{
		if (*str == c)
		{
			return (char *)str;
		}
		str++;
	}

	return NULL;
}

int MyStrlen(const char* str)
{
	assert(str);
	int count = 0;

	while (*str != '\0')
	{
		count++;
		str++;
	}
	return count;
}

int MyStrlen_OP(const char* str)
{
	assert(str);
	const char* str_end = str;
	const char* str_start = str;

	while (*str_end != '\0')
	{
		str_end++;
	}

	return (str_end - str_start);
}