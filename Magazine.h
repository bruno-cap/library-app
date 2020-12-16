/************************************************************************************************************
// Date: 2019/12/10
// Name: Bruno Pinto
************************************************************************************************************/

#ifndef SDDS_MAGAZINE_H__
#define SDDS_MAGAZINE_H__

#include "PubRecord.h"

namespace sdds {

   class Magazine : public PubRecord {
      int m_volume;
      int m_issueNo;
   public:
      // default constructor
      Magazine();
      // copy constructor
      Magazine(const Magazine& magazine_Object);
      // assignment operator overload
      Magazine& operator=(const Magazine& magazine_Object);
      // returns the character 'M'
      char recID() const;
      // prints "Magazines cannot be checked in or out!"
      virtual void checkIn();
      // prints "Magazines cannot be checked in or out!"
      virtual void checkOut();
      // receives and returns references of istream
      std::istream& read(std::istream& is = std::cin);
      // receives and returns references of ostream
      std::ostream& write(std::ostream& os = std::cout) const;
      // destructor
      virtual ~Magazine();
      // prints Magazines cannot be checked in or out!
      int return_Day() const;
      // prints Magazines cannot be checked in or out!
      int return_Month() const;
      // prints Magazines cannot be checked in or out!
      int return_Year() const;
   };
}

#endif