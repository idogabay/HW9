#include "port.h"
#include <cstring>
#include <iostream>
using namespace std;

Port::Port(String pattern): Field(pattern,PORT){

}

/**
* Brief: constructor of port
* Param: String for value
* Return:bool true(if set successful)
*/
bool Port::set_value(String val){
	String temp_val = val.trim();
	String* output;
	size_t size;
	temp_val.split("-",&output,&size);
	this->range[0] = output[0].to_integer();
	this->range[1] = output[1].to_integer();
	delete[] output;
	return true;
}

/**
* Brief: check if string value matches object value
* Param: String valu
* Return:bool true if match
*/

bool Port::match_value(String val) const{
	int port = val.to_integer();
	if(port >= range[0] && port <= range[1])
		return true;
	return false;
}
