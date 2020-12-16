/************************************************************************************************************
// Date: 2019/12/10
// Name: Bruno Pinto
************************************************************************************************************/

#ifndef SDDS_UTILS_H__
#define SDDS_UTILS_H__

namespace sdds {
   // reads an integer from console the integer referenced by "val"
   // argument.
   // if the user enters an invalid integer or values outside of the 
   // boundries set by "min" or "max" , this function flushes the 
   //keyboard, prints the "errorMessage and reads again
   // untill user enters an acceptable integer

   void readUtils(int& val, int min, int max, const char* errorMessage = "");

   // version for long longs

   void readUtils(long long& val, long long min, long long max, const char* ErrorMess);

   // reads a C style string from console up to "len" characters into the
   // the string pointed by the "str" pointer
   // if the user enters more than "len" characters, this function
   // flushes the keyboard, prints the "errorMessage and reads again
   // untill user enters an acceptable string

   void readUtils(char* str, int len, const char* errorMessage = "");
}
#endif // !
