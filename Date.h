/*********************************************************************************************************
// Date: 2019/11/11
// Name: Seneca College Teacher
*********************************************************************************************************/

#ifndef SDDS_DATE_H__
#define SDDS_DATE_H__
#include <iostream>
#include "PubRecord.h"

namespace sdds {
   const int NO_ERROR = 0;
   const int CIN_FAILED = 1;
   const int YEAR_ERROR = 2;
   const int MON_ERROR = 3;  
   const int  DAY_ERROR = 4;
   const char DATE_ERROR[5][16] = {
      "No Error",
      "cin Failed",
      "Bad Year Value",
      "Bad Month Value",
      "Bad Day Value"
   };
   const int  MIN_YEAR = 1500;

   class Date {
   private:
      int m_year;
      int m_mon;
      int m_day;
      int m_ErrorCode;
      int m_CUR_YEAR;
      int daysSince0001_1_1()const; // returns number of days passed since the date 0001/1/1
      bool validate();             /* validates the date setting the error code and then returning the result 
                                    true, if valid, and false if invalid.*/
      void errCode(int);           // sets the error code
      int curYear()const;          // returns the current system year
      bool bad()const;             // return true if
      int mdays()const;            // returns the number of days in current month
      void setToToday();           // sets the date to the current date (system date)
   public:
      Date();                      // creates a date with current date
      Date(int year, int mon, int day); /* create a date with assigned values
                                         then validates the date and sets the 
                                         error code accordingly */
      int errCode()const;         // returns the error code or zero if date is valid
      const char* dateStatus()const;  // returns a string corresponding the current status of the date
      int currentYear()const;         // returns the m_CUR_YEAR value;


      // ---------------------- Student code starts below ---------------------- //

      int returnDay() const;
      int returnMonth() const;
      int returnYear() const;



      // reads a date from the console in YYYY/MM/DD format
      std::istream& read(std::istream& is = std::cin);
      // checks the state of the Date object and prints information accordingly
      std::ostream& write(std::ostream& os = std::cout) const;

      // overloads operator == to compare two Date objects and returns true or false accordingly
      bool operator==(const Date& Date_Object) const;
      // overloads operator != to compare two Date objects and returns true or false accordingly
      bool operator!=(const Date& Date_Object) const;
      // overloads operator >= to compare two Date objects and returns true or false accordingly    
      bool operator>=(const Date& Date_Object) const;
      // overloads operator <= to compare two Date objects and returns true or false accordingly
      bool operator<=(const Date& Date_Object) const;
      // overloads operator < to compare two Date objects and returns true or false accordingly
      bool operator<(const Date& Date_Object) const;
      // overloads operator > to compare two Date objects and returns true or false accordingly
      bool operator>(const Date& Date_Object) const;
      // overloads operator - to return the difference in number of days between two Date objects
      int operator-(const Date& Date_Object) const;
      // overloads bool so if a date is casted to bool, it returns true if the date is valid and false otherwise
      operator bool();

   };

   // helper operator overloads
   // overloads cout so it can take a Date object as right operand
   std::ostream& operator<<(std::ostream& os, const Date& Date_Object);
   // overloads cin so it can take a Date object as right operand
   std::istream& operator>>(std::istream& is, Date& Date_Object);

}

#endif