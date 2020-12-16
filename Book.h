/************************************************************************************************************
// Date: 2019/12/10
// Name: Bruno Pinto
************************************************************************************************************/

#ifndef SDDS_BOOK_H__
#define SDDS_BOOK_H__

#include "PubRecord.h"
#include "Date.h"

namespace sdds {
   class Book : public PubRecord {
   public:
      long long m_ISBN;
      int m_shipId;
      Date m_dueDate;
   public:
      // default constructor
      Book();
      // copy constructor
      Book(const Book& book_Object);
      // assignment operator overload
      Book& operator=(const Book& book_Object);
      // returns the character 'B'
      char recID() const;
      // returns the member id and cannot modify the Book object
      int memberID() const;
      // returns the day and cannot modify the Book object
      int return_Day() const;
      // returns the month and cannot modify the Book object
      int return_Month() const;
      // returns the year and cannot modify the Book object
      int return_Year() const;
      // sets m_shipId = 0 and prints the Book on the console
      virtual void checkIn();
      // checks out the Book and lends to a member
      virtual void checkOut();
      // receives and returns references of istream
      std::istream& read(std::istream& is = std::cin);
      // receives and returns references of ostream
      std::ostream& write(std::ostream& os = std::cout) const;
      // destructor
      virtual ~Book();
   };

}

#endif