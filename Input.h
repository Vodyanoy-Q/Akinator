#ifndef _INPUT_H_
#define _INPUT_H_

ERROR InputMatch(int* ret_val, const char* error_message, const char** match_data, const int data_size);
ERROR InputAnswer(char** str, const char* error_message);

#endif //_INPUT_H_
