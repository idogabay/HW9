/*
 * String.cpp
 *
 *  Created on: 20 Jan 2021
 *      Author: mamat
 */

#include <cstring>
#include <iostream>
#include "field.h"
#include "ip.h"
#include "port.h"

using namespace std;

 /**
 * Brief: constructor of Field
 * Param: String (as pattern)
 * Return:Creates Field object
 */
/////////////////note - need to insert a clean
///////////////// string w/o spaces
Field::Field(const String pattern){
	this->pattern = pattern;
	this->type = GENERIC;
}

/**
* Brief: constructor of Field
* Param: String (as pattern), type
* Return:Creates Field object
*/
Field::Field(String pattern, field_type type){
	this->pattern = pattern;
	this->type = type;
}

/**
* Brief: destructor of Field
* Param: empty
* Return:deletes field
*/
Field::~Field(){
}

/**
* Brief: Return field type
* Param:empty
* Return: field_type
*/
field_type Field::get_type() const{
	//std::cout << this->pattern, this->type << std::endl;
	return this->type;
}

/**
* Brief: set value of field object
* Param: String (as value)
* Return:bool if successful
*/
bool Field::set_value(String val){
	if(this->type == IP){
		return (Ip*)this->set_value(val);
	}
	if(this->type == PORT){
		return (Port*)this->set_value(val);
	}
	return false;
}
/**
* Brief: check if string has given value
* Param: String (as value)
* Return:bool if identical or not
*/
bool Field::match_value(String val) const{
	if(this->type == IP){
		return ((Ip*)this)->match_value(val);
	}
	if(type == PORT){
		return ((Port*)this)->match_value(val);
	}
	return false;
}



/**
* Brief: check if packet matches law of field
* Param: String as packet
* Return:true if match
*/
bool Field::match(String packet){
	String *output;
	size_t size;
	packet.split(",", &output,&size);
	String *temp_output;
	size_t temp_size;
	String content;
	bool flag=false;
	for(int i=0;i<(int)size;i++){
		output[i]=output[i].trim();
		output[i].split("=",&temp_output,&temp_size);
		String trim_temp = temp_output[0].trim();
		if(trim_temp.equals(this->pattern)){
			flag=true;
			break;
		}
	}
	bool result=false;
	if(flag==true){
	String temp1 = temp_output[1].trim();
	result = match_value(temp1);
	}

	delete[] temp_output;
	delete[] output;
	return result;

}

