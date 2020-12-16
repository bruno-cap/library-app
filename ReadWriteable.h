/************************************************************************************************************
// Date: 2019/12/10
// Name: Bruno Pinto
************************************************************************************************************/

#ifndef SDDS_READWRITEABLE_H__
#define SDDS_READWRITEABLE_H__
#include <iostream>

namespace sdds {

   class ReadWriteable {
   public:
      // receives and returns references of ostream
      virtual std::ostream& write(std::ostream& os = std::cout) const = 0;
      // receives and returns references of istream
      virtual std::istream& read(std::istream& is = std::cin) = 0;
      // destructor
      virtual ~ReadWriteable();
   };

   // helper overloads
   // overloads the insertion operator
   std::ostream& operator<<(std::ostream& os, const ReadWriteable& toBePrinted);
   // overloads the extraction operator
   std::istream& operator>>(std::istream& is, ReadWriteable& toBeRead);
}

#endif