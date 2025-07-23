#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ustr.h"
#include "pset1.h"

/*
Initializes a new UStr with contents
*/
UStr new_ustr(char* contents) {
	int32_t bytes = strlen(contents);
	int32_t codepoints = utf8_strlen(contents);
	uint8_t all_ascii = bytes == codepoints;
	char* contents_copy = malloc(bytes + 1);
	strcpy(contents_copy, contents);
	UStr s = {
		codepoints,
		bytes,
		all_ascii,
		contents_copy
	};
	return s;
}

/*
Returns length of string
*/
int32_t len(UStr s) {
	return s.codepoints;
}

/*
Returns a substring of str, starting at index start (inclusive) 
and ending at index end (exclusive).

Returns an empty string on invalid range.
*/
UStr substring(UStr s, int32_t start, int32_t end) {
	if(start < 0 || end >= len(s)){
		UStr return_ustr = new_ustr("");
		return return_ustr;
	}
	int byte_count = 0;
   	int codepoint_count = 0;
	while(codepoint_count < start){
		int codepoint_length = utf8_codepoint_size(s.contents[byte_count]);
		byte_count += codepoint_length;
		codepoint_count++;
	}
	int byte_start = byte_count;
	while(codepoint_count < end){
                int codepoint_length = utf8_codepoint_size(s.contents[byte_count]);
                byte_count += codepoint_length;
                codepoint_count++;
        }
	int byte_end = byte_count;
	int byte_len = byte_end - byte_start;
	char *substr = malloc(byte_len+1);
	strncpy(substr,s.contents + byte_start,byte_len);
	substr[byte_len] = '\0';
	UStr return_ustr = new_ustr(substr);
	free(substr);
	return return_ustr;
}

/*
Given 2 strings s1 and s2, returns a string that is the result of 
concatenating s1 and s2. 
*/
UStr concat(UStr s1, UStr s2) {
	int byte_count_s1 = 0;
	int codepoint_count_s1 = 0;
        while(codepoint_count_s1 < len(s1)){
                int codepoint_length = utf8_codepoint_size(s1.contents[byte_count_s1]);
                byte_count_s1 += codepoint_length;
                codepoint_count_s1++;
        }
        int byte_count_s2 = 0;
	int codepoint_count_s2 = 0;
        while(codepoint_count_s2 < len(s2)){
                int codepoint_length = utf8_codepoint_size(s2.contents[byte_count_s2]);
                byte_count_s2 += codepoint_length;
                codepoint_count_s2++;
        }
	char *joined = malloc(byte_count_s1 + byte_count_s2 + 1);
	strncpy(joined,s1.contents,byte_count_s1);
	strncpy(joined + byte_count_s1,s2.contents, byte_count_s2);
	joined[byte_count_s1+byte_count_s2] = '\0';
	UStr return_ustr = new_ustr(joined);
	free(joined);
	return return_ustr;
}

/*
Given a string s and an index, return a string with the character at index 
removed from the original string. 

Returns the original string if index is out of bounds.
*/
UStr removeAt(UStr s, int32_t index) {
	int s_len = len(s);
	if(index < 0 || index >= s_len){
		UStr copy = new_ustr(s.contents);
		return copy;
	}
	char *removed = malloc(s_len);
	for(int i = 0; i < index; i++){
		removed[i] = s.contents[i];
	}
	for(int i = index; i < s_len - 1; i++){
		removed[i] = s.contents[i+1];
	}
	removed[s_len - 1] = '\0';
	UStr return_ustr = new_ustr(removed);
	free(removed);
	return return_ustr;
}

/*
Given a string s, return s reversed. 

Example: reverse("apples🍎 and bananas🍌") = "🍌sananab dna 🍎selppa")
*/
UStr reverse(UStr s) {
	

}


void print_ustr(UStr s) {
	printf("%s [codepoints: %d | bytes: %d]", s.contents, s.codepoints, s.bytes);
}

void free_ustr(UStr s) {
	if (s.contents != NULL) {
		free(s.contents);
		s.contents = NULL;
	}
}

