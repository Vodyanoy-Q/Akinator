#ifndef _ASSERT_H_
#define _ASSERT_H_


#define MY_ASSERT(addres, error) if(addres == NULL)                                                              \
                                 {                                                                               \
                                     printf(RED "ERROR: %d\n" RESET_COLOR, error);                               \
                                     printf(RED "%s:%d in func %s\n" RESET_COLOR, __FILE__, __LINE__, __func__); \
                                     return error;                                                               \
                                 }                                                                               \

#define _FOPEN(addres, name, arg) addres = fopen(name, arg);                                                        \
                                                                                                                    \
                                  if(addres == NULL)                                                                \
                                  {                                                                                 \
                                      printf(RED "ERROR OPEN FILE\n" RESET_COLOR);                                  \
                                      printf(RED "ERROR CODE: %d\n" RESET_COLOR, OPEN_FILE_ERROR);                  \
                                      printf(YELLOW "FILE NAME: %s\n" RESET_COLOR, name);                           \
                                      printf(YELLOW "OPEN ARG: %s\n" RESET_COLOR, arg);                             \
                                      printf(YELLOW "LINE: %d\n" RESET_COLOR, __LINE__);                            \
                                      printf(YELLOW "FUNC: %s\n" RESET_COLOR, __func__);                            \
                                      printf(YELLOW "FILE: %s\n" RESET_COLOR, __FILE__);                            \
                                                                                                                    \
                                      return OPEN_FILE_ERROR;                                                       \
                                  }                                                                                 \

#define _FCLOSE(addres) if(fclose(addres) != NO_ERROR)                                                     \
                        {                                                                                  \
                            printf(RED "ERROR CODE: %d\n" RESET_COLOR, CLOSE_FILE_ERROR);                  \
                            printf(YELLOW "LINE: %d\n" RESET_COLOR, __LINE__);                             \
                            printf(YELLOW "FUNC: %s\n" RESET_COLOR, __func__);                             \
                            printf(YELLOW "FILE: %s\n" RESET_COLOR, __FILE__);                             \
                                                                                                           \
                            return CLOSE_FILE_ERROR;                                                       \
                        }                                                                                  \

#define _CHECK_ERROR(func) error = func;                                               \
                           if (error != NO_ERROR)                                      \
                           {                                                           \
                               printf(RED "ERROR CODE: %d\n" RESET_COLOR, error);      \
                               printf(YELLOW "FUNC: %s\n" RESET_COLOR, __func__);      \
                               printf(YELLOW "FILE: %s\n" RESET_COLOR, __FILE__);      \
                               return error;                                           \
                           }                                                           \

#endif // _ASSERT_H_
