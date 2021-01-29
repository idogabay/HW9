#include "ip.h"
#include <cstring>
#include <iostream>
#include <cmath>
#define TOTAL_BITS 32
#define SEGMENTS 4


 /**
 * Brief: constructor of Ip
 * Param: String (as pattern)
 * Return:Creates Ip object
 */
Ip::Ip(String pattern): Field(pattern,IP){

}
/**
* Brief: converts ip string to integer
* Param: String (as pattern)
* Return:int
*/
unsigned int ip_to_int(String ip){
	String* output;
	size_t size;
	ip.split(".", &output, &size);

	unsigned int val = 0;
	unsigned int temp_val=0;
	for (int i=0;i<4; i++){
		temp_val = output[i].to_integer();
		val = val<<8;
		val = val+temp_val;
	}
	delete [] output;
	//delete size;
	return val;

}

/**
* Brief: set value of ip
* Param: String
* Return:bool if sucessful set or not
*/
bool Ip::set_value(String val){
	val = val.trim();
	String* output;
//	this->low;// = 0;
	//this->high;// = 0;
	size_t size;
	val.split("/",&output,&size);
	if(size != 2){
		delete[] output;
		return false;
	}
	String ip = output[0].trim();
	String mask = output[1].trim();
	unsigned int ip_val= ip_to_int(output[0]);
	int mask_bits = TOTAL_BITS-output[1].to_integer();
	//std::cout<< ip_val<<std::endl;
	if(mask_bits == TOTAL_BITS){
		this->low=0;
		this->high=0xFFFFFFFF;
		delete[] output;
		return true;
	}
	this->low= (ip_val >> mask_bits)<<mask_bits;
	this->high= (ip_val >> mask_bits);
	unsigned int temp_high = this->high;
	for (int i=0;i<mask_bits;i++){
		temp_high = temp_high<<1;
		temp_high++;

	}
	this->high = temp_high;
	delete[] output;
	return true;
}


/**
* Brief: check if string value matches object value
* Param: String valu
* Return:bool true if match
*/
bool Ip::match_value(String val) const{

	unsigned int ip = ip_to_int(val);

	if(ip >= this->low && ip <= this->high){
		return true;
	}
	return false;
}
