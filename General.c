#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "General.h"
//#define _CRT_SECURE_NO_WARNINGS - this is update in our project in visual

char* getStrExactName(const char* msg)
{
	char* str;
	char temp[MAX_STR_LEN];
	printf("%s\t", msg);
	myGets(temp, MAX_STR_LEN);

	str = getDynStr(temp);
	return str;

}
char* getDynStr(char* str)
{
	char* theStr;
	theStr = (char*)malloc((strlen(str) + 1) * sizeof(char));
	if (!theStr)
		return NULL;

	strcpy(theStr, str);
	return theStr;
}
char* myGetsF(char* buffer, int size, FILE* source)
{
	char* ok;
	if (buffer != NULL && size > 0)
	{
		do {
			ok = fgets(buffer, size, source);
		} while (ok && ((strlen(buffer) <= 1) && (isspace(buffer[0]))));
		if (ok)
		{
			char* back = buffer + strlen(buffer);
			//trim end spaces
			while ((buffer < back) && (isspace(*--back)));
			*(back + 1) = '\0';
			return buffer;
		}
		buffer[0] = '\0';
	}
	return NULL;
}
char* myGets(char* buffer, int size)
{
	char* ok;
	if (buffer != NULL && size > 0)
	{
		do { //skip only '\n' strings
			ok = fgets(buffer, size, stdin);
		} while (ok && ((strlen(buffer) <= 1) && (isspace(buffer[0]))));
		if (ok)
		{
			char* back = buffer + strlen(buffer);
			//trim end spaces
			while ((buffer < back) && (isspace(*--back)));
			*(back + 1) = '\0';
			return buffer;
		}
		buffer[0] = '\0';
	}
	return NULL;
}
char* myGetsFile(char* buffer, int size, FILE* fp)
{
	if (buffer == NULL || size <= 0 || fp == NULL)
	{
		return NULL;  // Invalid input
	}

	char* result = NULL;
	while (fgets(buffer, size, fp) != NULL)
	{  // Read a line
		// Check if the line is not just empty or whitespace
		char* end = buffer + strlen(buffer) - 1;  // Point to the end of the string
		if (end >= buffer && *end == '\n')
		{
			*end = '\0';  // Remove newline character
			end--;  // Move back to the new end
		}

		// Check if the line is not just empty or whitespace
		char* start = buffer;
		while (isspace((unsigned char)*start)) start++;  // Skip leading whitespace
		if (*start == '\0') {
			continue;  // Skip this line if it's empty or contains only whitespace
		}

		// Trim trailing spaces
		while (end > start && isspace((unsigned char)*end)) end--;
		*(end + 1) = '\0';  // Null-terminate after the last non-whitespace character

		result = buffer;  // Found a valid line
		break;  // Break the loop after finding the first valid line
	}

	if (result == NULL)
	{
		if (!buffer)
			return NULL;
		buffer[0] = '\0';  // Ensure buffer is null-terminated if no valid line was read
	}

	return result;  // Return the buffer if a line was read, NULL otherwise
}


