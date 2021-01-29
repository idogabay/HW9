/*
 * String.cpp
 *
 *  Created on: 20 Jan 2021
 *      Author: mamat
 */
/*
#include "string.h"
#include <cstring>
#include <iostream>
*/
#include <iostream>
#include <cstring>
#include "ip.h"
#include "string.h"

#define SIZE_AFTER_EQUAL_SPLIT 2
#define SIZE_EMPTY_LINE -1



/**
* Brief: constructor
* Param: empty
* Return: creates string object
*/

String::String() {
	data=NULL;
	length=0;

}

/**
* Brief: constructor
* Param: char *str (as data)
* Return:create string object
*/
String::String(const char *str)
{
if (str==NULL)
{
	this->length=0;
	this->data=NULL;
return;
}
else
{
	size_t len=strlen(str);
	this->length=len;
	this->data=new char[len+1];
	strncpy(this->data, str,len+1);

}
}

/**
* Brief: copy constructor
* Param: string object
* Return:string object identical to given
*/
String::String(const String &str) {
	char* dat=str.data;
	size_t len=str.length;
	if (dat==NULL)
	{
		this->data=NULL;
		this->length=0;
		return;
	}else
	if (len==0)
	{
		this->data=NULL;
		this->length=0;
	}
	else{
		this->length=len;
		data=new char[len+1];
		strcpy(data, str.data);
	}
	//memory leak here
	//delete[] dat;
}
/**
* Brief: destructor
* Param: empty
* Return:delete object (no return)
*/
String::~String() {
	// TODO Auto-generated destructor stub
if (data!=NULL){
	delete[] data;
}}

/**
* Brief: = operator (assign string)
* Param: char *str as data
* Return:String object with given data
*/
String& String::operator=(const char *str)
{
	if (str==NULL)
	{
		this->length=0;
		this->data=NULL;
		return *this;
	}
	if (this->data!=NULL)
	{
		delete[] this->data;
	}

	size_t len=strlen(str);
	if (len==0)
	{
		this->data=NULL;
	}
	else
	{
		this->length=len;
		this->data=new char[len+1];
		strcpy(this->data,str);
	}
	return *this;
}

/**
* Brief: = operator (assign string)
* Param: String object to assign from
* Return:String object with given data
*/
String& String::operator=(const String &rhs)
{
	if (this->data!=NULL)
	{
		delete[] data;
	}


	int len = rhs.length;

	if (len==0)
	{
		this->data = NULL;
		this->length=0;
	}
	else
	{
		this->length=len;
		this->data = new char[length + 1];
		strcpy(this->data, rhs.data);
		}

	return *this;
}

/**
* Brief: compare to given string
* Param: char *str as data
* Return:true if identical strings
*/
bool String::equals(const char *rhs) const
{
	if (this->data==NULL &&rhs==NULL)
	{
		return true;
	}
	if (strlen(rhs)!=unsigned(this->length))
	{
		return false;
	}

	else if (!strcmp(this->data, rhs))
	{
		return false;
	}
	return true;
}

/**
* Brief: compare to given string
* Param: char *str as data
* Return:true if identical strings
*/
bool String::equals(const String &rhs) const
{
	if (this->data==NULL && rhs.data==NULL)
	{
		return true;
	}
	if(this->length != rhs.length)
	{
		return false;
	}

	else if (strcmp(data, rhs.data)!=0)
	{
		return false;
	}
	return true;
}
/**
* Brief: trim spaces from beginning and end of string
* Param: empty
* Return:trimmed string
*/
String String::trim() const
{

	int right=this->length-1;
	int left=0;
	if ((this->data==NULL)||this->length==0)
	{
		return String();
	}

	//go on while there are spaces from at the right edge
	while (this->data[right]==' ')
	{
		right=right-1;
	}
	while (this->data[left]==' ')
	{
		left=left+1;
	}

	if (left>=right+1)
	{
		return String();
	}
	int size=right-left+1;
	char temp[size+1];
	strncpy(temp,&data[left],size);
	temp[size]='\0';
	return String(temp);
}

/**
* Brief: convert string to integer
* Param: empty
* Return:int of string number
*/
int String::to_integer() const
{


	int number=atoi(this->data);
	return number;
}
/**
* Brief: split string tu substrings by delimiteer
* Param: delimiters, output, size
* Return:no return(place in output)
*/
void String::split(const char *delimiters, String **output, size_t *size) const
{
	if ((strcmp(delimiters,"=")==0)&&(output==0x0))
	{
		*size=2;
		return;
	}
	if (this->data==NULL)
	{
		*size=-1;
	}

	int count=1;
	int sub_str=0;
	int num=strlen(delimiters);
int left=0;
	//char temp[this->length + 1] = {0};

	//optional
	//strcpy(temp, this->data);
	//temp[this->length] = '\0';

	for (int i=0; i <(int) length; i++)
	{
		for (int d = 0; d < num; d++)
		{
		//	if (temp[i] == delimiters[d])
			if (data[i]==delimiters[d])
			{
				count++;
			}
		}
	}


	*output = new String[count];


	//copy each substring to output
	for (int i = 0; i <(int) length; i++)
	{
		for (int d = 0; d < num; d++)
		{
			if (data[i] == delimiters[d])
			{
				data[i] = '\0';
				(*output)[sub_str] = String(&data[left]);
				left = i + 1;
				sub_str++;
			}
		}
	}

	//set the last substring
	(*output)[sub_str] = String(&data[left]);
	*size = count;
	return;
	//I think there is a memory leak here
}
