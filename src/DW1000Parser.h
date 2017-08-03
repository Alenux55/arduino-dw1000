/*
 * Copyright (c) 2015 by Thomas Trojer <thomas@trojer.net> and Leopold Sayous <leosayous@gmail.com>
 * Decawave DW1000 library for arduino.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @file DW1000Parser.h
 * Arduino parser library (header file) for reading and parsing received
 * serial commands.
 *
 * @TODO
 * - 
 */
 
#include "DW1000.h"
#include <string.h>
 
class DW1000ParserClass {
public:
	//variables
	// Buffer to store incoming commands from serial port
	static String inBuffer;

/* 	typedef enum _PARSER_COMMAND{
		PARSER_COMMAND_SET_ANTENNA_DELAY
	}PARSER_COMMAND; */
	
	// Available serial commands
	#define PARSER_COMMAND_SET_ANTENNA_DELAY_STR "set,antDelay,"
	#define PARSER_COMMAND_GET_ANTENNA_DELAY_STR "get,antDelay,"
	
/* 	#define SET_KEY(key) strcpy(keys[key], key##_STR); keyLengths[key] = strlen(key##_STR);
	
	#define ADD_PARSER_KEYS()\
		SET_KEY(PARSER_COMMAND_SET_ANTENNA_DELAY);\	
	
	#define PARSER_COMMAND_MAX_LENGTH 15 */
	
	//functions
	/** 
	Reads data sent through the serial connection until a CR or LF character is received
	*/
	static void readUntilEol();
	static void parseCommand(String command);
};

extern DW1000ParserClass DW1000Parser;