/************************************************************************************************************
// Date: 2019/12/10
// Name: Bruno Pinto
************************************************************************************************************/

#ifndef SDDS_PUBRECORD_H__
#define SDDS_PUBRECORD_H__

#include "ReadWriteable.h"

namespace sdds {

   // constant definitions
   const int SDDS_CONSOLE = 1;
   const int SDDS_FILE = 2;

   class PubRecord : public ReadWriteable {
      char* m_name_Of_Publication;
      int m_shelf_No_Of_Publication;
      int m_type_Of_Media;
      
   protected:
      // sets the name of the publication
      void name(const char* name_Of_Publication);
      // returns the name of the publication
      const char* name() const;

   public:
      // pure virtual method to enforce "check in" in derived classes
      virtual void checkIn() = 0;
      // pure virtual method to enforce "check out" in derived classes
      virtual void checkOut() = 0;

      // virtual method that returns a character and does not change the class
      virtual char recID() const = 0;

      // returns day, month and year and does not change the class
      virtual int return_Day() const = 0;
      virtual int return_Month() const = 0;
      virtual int return_Year() const = 0;

      // returns name of publication
      const char* returnName() const;

      // returns if object is empty
      bool isEmpty() const;

      // default constructor
      PubRecord();
      // copy constructor
      PubRecord(const PubRecord& object_To_Copy);
      // dynamically allocate and copy m_name_Of_Publication
      void dynamicAllocationAndCopy(const char* string_To_Copy);
      // sets to safe empty state
      void setToSafeEmptyState();
      // destructor
      virtual ~PubRecord();
      // assignment operator overload
      PubRecord& operator=(const PubRecord& object_To_Copy);
      // sets the type of the media
      void mediaType(int type_Of_Media);
      // returns the type of the media
      int mediaType() const;
      // sets the shelfNo
      void shelfNo(int value);
      // returns the shelf number that stores the publication
      int shelfNo() const;
      // receives a three-digit integer from the console
      void readShelfNo();
      // bool operator overload - compares character to the return value of the recID function. Returns true if it's a match and false otherwise.
      bool operator==(char character) const;
      // bool operator overload - if string is a substring of the name of the class, returns true. Otherwise, false.
      bool operator==(const char* string) const;
      // bool casting overload - returns true if, when casting, PubRecord is empty. Otherwise, false.
      operator bool() const;
   };
}

#endif