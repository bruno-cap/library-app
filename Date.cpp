/*********************************************************************************************************
// Date: 2019/11/11
// Name: Seneca College Teacher
*********************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
using namespace std;
#include "Date.h"

namespace sdds {
   bool Date::validate() {
      errCode(NO_ERROR);
      if (m_year < MIN_YEAR || m_year > m_CUR_YEAR) {
         errCode(YEAR_ERROR);
      }
      else if (m_mon < 1 || m_mon > 12) {
         errCode(MON_ERROR);
      }
      else if (m_day < 1 || m_day > mdays()) {
         errCode(DAY_ERROR);
      }
      return !bad();
   }
   int Date::mdays()const {
      int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
      int mon = m_mon >= 1 && m_mon <= 12 ? m_mon : 13;
      mon--;
      return days[mon] + int((mon == 1) * ((m_year % 4 == 0) && (m_year % 100 != 0)) || (m_year % 400 == 0));
   }
   int Date::curYear()const {
      time_t t = time(NULL);
      tm lt = *localtime(&t);
      return lt.tm_year + 1900;
   }
   void Date::setToToday() {
      time_t t = time(NULL);
      tm lt = *localtime(&t);
      m_day = lt.tm_mday;
      m_mon = lt.tm_mon + 1;
      m_year = lt.tm_year + 1900;
      errCode(NO_ERROR);
   }
   int Date::daysSince0001_1_1()const { // Rata Die day since 0001/01/01 
      int ty = m_year;
      int tm = m_mon;
      if (tm < 3) {
         ty--;
         tm += 12;
      }
      return 365 * ty + ty / 4 - ty / 100 + ty / 400 + (153 * tm - 457) / 5 + m_day - 306;
   }
   Date::Date() :m_CUR_YEAR(curYear()) {
      setToToday();
   }
   Date::Date(int year, int mon, int day) : m_CUR_YEAR(curYear()) {
      m_year = year;
      m_mon = mon;
      m_day = day;
      validate();
   }
   const char* Date::dateStatus()const {
      return DATE_ERROR[errCode()];
   }
   int Date::currentYear()const {
      return m_CUR_YEAR;
   }
   void Date::errCode(int readErrorCode) {
      m_ErrorCode = readErrorCode;
   }
   int Date::errCode()const {
      return m_ErrorCode;
   }
   bool Date::bad()const {
      return m_ErrorCode != 0;
   }


   // ---------------------- Student code starts below ---------------------- //

   int Date::returnDay() const {
      return m_day;
   }
   int Date::returnMonth() const {
      return m_mon;
   }
   int Date::returnYear() const {
      return m_year;
   }



   // reads a date from the console in YYYY/MM/DD format
   std::istream& Date::read(std::istream& is) {
      errCode(NO_ERROR);
      // reads year
      int tempYear;
      is >> tempYear;
      is.ignore(1); // ignores a single character to bypass separator
      // reads month
      int tempMon;
      is >> tempMon;
      is.ignore(1); // ignores a single character to bypass separator
      // reads day
      int tempDay;
      is >> tempDay;

      if (is.fail() == true) {
         errCode(CIN_FAILED);
         is.clear();
      }
      else {
         // assigns the temporary variables to the current object and validate them
         *this = Date(tempYear, tempMon, tempDay);
      }

      // flush the keyboard
      is.ignore(1000, '\n');

      return is;
   }

   // checks the state of the Date object and prints information accordingly
   std::ostream& Date::write(std::ostream& os) const {
      if (bad()) {
          os << dateStatus();
      }
      else {
         os << m_year << "/" << setfill('0') << setw(2) << m_mon << "/" << setfill('0') << setw(2) << m_day << setfill(' ');
      }

      return os;
   }

   // overloads operator == to compare two Date objects and returns true or false accordingly
   bool Date::operator==(const Date& Date_Object) const {
      return (daysSince0001_1_1() == Date_Object.daysSince0001_1_1());
   }

   // overloads operator != to compare two Date objects and returns true or false accordingly
   bool Date::operator!=(const Date& Date_Object) const {
      return (daysSince0001_1_1() != Date_Object.daysSince0001_1_1());
   }

   // overloads operator >= to compare two Date objects and returns true or false accordingly    
   bool Date::operator>=(const Date& Date_Object) const {
      return (daysSince0001_1_1() >= Date_Object.daysSince0001_1_1());
   }

   // overloads operator <= to compare two Date objects and returns true or false accordingly
   bool Date::operator<=(const Date& Date_Object) const {
      return (daysSince0001_1_1() <= Date_Object.daysSince0001_1_1());
   }

   // overloads operator < to compare two Date objects and returns true or false accordingly
   bool Date::operator<(const Date& Date_Object) const {
      return (daysSince0001_1_1() < Date_Object.daysSince0001_1_1());
   }

   // overloads operator > to compare two Date objects and returns true or false accordingly
   bool Date::operator>(const Date& Date_Object) const {
      return (daysSince0001_1_1() > Date_Object.daysSince0001_1_1());
   }

   // overloads operator - to return the difference in number of days between two Date objects
   int Date::operator-(const Date& Date_Object) const {
      return (daysSince0001_1_1() - Date_Object.daysSince0001_1_1());
   }

   // overloads bool so if a date is casted to bool, it returns true if the date is valid and false otherwise
   Date::operator bool() {
      return validate();
   }

   // helper operator overloads
   // overloads cout so it can take a Date object as right operand
   std::ostream& operator<<(std::ostream& os, const Date& Date_Object) {
      return Date_Object.write(os);
   }

   // overloads cin so it can take a Date object as right operand
   std::istream& operator>>(std::istream& is, Date& Date_Object) {
      return Date_Object.read(is);
   }

}
