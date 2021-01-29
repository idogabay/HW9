/*
 * main.cpp
 *
 *  Created on: 20 Jan 2021
 *      Author: mamat
 */
#include <iostream>
#include <cstring>
#include <cstdbool>
#include "ip.h"
#include "port.h"
#include "input.h"
#include "field.h"
#include "string.h"
using namespace std;

extern int check_args(int,char**);
extern void parse_input(Field&);

int main(int argc, char **argv)
{
	if (check_args(argc, argv)!=0)
	{
		return 1;
	}
	String rule(argv[1]);
	String *splitted;
	size_t splitted_size=0;
	rule.split("=",&splitted,&splitted_size);

	if (splitted==NULL)
	{
		delete[] splitted;
		return 0;
	}

	splitted[0]=splitted[0].trim();
	String type_ip_src("src-ip");
	String type_port_src("src-port");
	String type_ip_dst("dst-ip");
	String type_port_dst("dst-port");

	bool b_ip1=(splitted[0].equals(type_ip_src));
	bool b_ip2=(splitted[0].equals(type_ip_dst));
	bool b_port1=(splitted[0].equals(type_port_src));
	bool b_port2=(splitted[0].equals(type_port_dst));

	if(b_ip1==true||b_ip2==true){

		Ip ip_rule(splitted[0]);

		splitted[1]=splitted[1].trim();

		ip_rule.set_value(splitted[1]);

		parse_input(ip_rule);

	}else if(b_port1==true||b_port2==true)
	{
			Port port_rule(splitted[0]);
			splitted[1]=splitted[1].trim();
			port_rule.set_value(splitted[1]);
			parse_input(port_rule);
	}
	delete[] splitted;

}
