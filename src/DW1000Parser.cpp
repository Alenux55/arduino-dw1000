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
 * @file DW1000Parser.cpp
 * Arduino parser library (source file) for reading and parsing received
 * serial commands.
 *
 * @TODO
 * - 
 */
 
#include "DW1000Parser.h"
 
DW1000ParserClass DW1000Parser;

// Buffer to store incoming commands from serial port
static String DW1000ParserClass::inBuffer;

void DW1000ParserClass::readUntilEol() {
	while (Serial.available() > 0)
		{
		  char received = Serial.read();
		  inBuffer += received;
				
		  // Process message when new line character is received
		  if (received == '\n' or received == '\r')
		  {
			  parseCommand(inBuffer);
			  String inBufferRet = inBuffer;
			  inBuffer = ""; // clear the input buffer
			  /* return inBufferRet; */
		  } 
		}
}

void DW1000ParserClass::parseCommand(String command) {
	if (command.indexOf(PARSER_COMMAND_SET_ANTENNA_DELAY_STR) != -1) 
	{
		// split the string from the last comma to get the antenna delay value
		int lastCommaIndex = command.lastIndexOf(',');
		String antDelayStr = command.substring(lastCommaIndex+1);
		antDelayStr.replace("\n",""); // remove line feed character
		antDelayStr.replace("\r",""); // remove carriage return character
		uint16_t value = antDelayStr.toInt();

		// if the value isn't an integer or value is greater than or equal to the maximum value
		if ((value < 0) or (value >= pow(2,16)) or ((value == 0) and (antDelayStr != "0")))
		{
			Serial.println("ERROR: Please choose an integer antenna delay value between 0 and 65535");
		}
		else
		{
			DW1000.setAntennaDelay(value);
		}		
		
		uint16_t delay = DW1000.getAntennaDelay();
		Serial.println(delay);
	}
	else if (command.indexOf(PARSER_COMMAND_GET_ANTENNA_DELAY_STR) != -1) 
	{
		uint16_t delay = DW1000.getAntennaDelay();
		Serial.println(delay);
	}
	else
	{
		Serial.print("Unknown command: "); Serial.println(command);
	}
}