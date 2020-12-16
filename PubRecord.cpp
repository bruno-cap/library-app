/*********************************************************************************************************
// Date: 2019/12/10
// Name: Bruno Pinto
*********************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;
#include "PubRecord.h"
#include "Utils.h"

namespace sdds {

   // sets the name of the publication
   void PubRecord::name(const char* name_Of_Publication) {
      delete[] m_name_Of_Publication;
      dynamicAllocationAndCopy(name_Of_Publication);
   }

   // returns the name of the publication
   const char* PubRecord::name() const {
      return m_name_Of_Publication;
   }

   // returns if object is empty
   bool PubRecord::isEmpty() const {
      return (m_name_Of_Publication == nullptr);
   }

   // default constructor
   PubRecord::PubRecord() {
      setToSafeEmptyState();
   }

   // sets to safe empty state
   void PubRecord::setToSafeEmptyState() {
      m_name_Of_Publication = nullptr;
      m_shelf_No_Of_Publication = 0;
      m_type_Of_Media = 0;
   }

   // copy constructor
   PubRecord::PubRecord(const PubRecord& object_To_Copy) {

      // if object is not empty, proceed with copy. otherwise, sets to safe empty state
      if (object_To_Copy.m_name_Of_Publication != nullptr) {

         // shallow copy m_shelf_No_Of_Publication and m_type_Of_Media
         m_shelf_No_Of_Publication = object_To_Copy.m_shelf_No_Of_Publication;
         m_type_Of_Media = object_To_Copy.m_type_Of_Media;

         // deep copy m_name_Of_Publication
         dynamicAllocationAndCopy(object_To_Copy.m_name_Of_Publication);
      }
      else {
         setToSafeEmptyState();
      }
   }

   // dynamically allocate and copy m_name_Of_Publication
   void PubRecord::dynamicAllocationAndCopy(const char* string_To_Copy) {
      m_name_Of_Publication = new char[strlen(string_To_Copy) + 1];
      strcpy(m_name_Of_Publication, string_To_Copy);
   }

   // destructor
   PubRecord::~PubRecord() {
      delete[] m_name_Of_Publication;
   }

   // assignment operator overload
   PubRecord& PubRecord::operator=(const PubRecord& object_To_Copy) {

      // deallocate m_name_Of_Publication
      delete[] m_name_Of_Publication;

      // shallow copy m_shelf_No_Of_Publication and m_type_Of_Media
      m_shelf_No_Of_Publication = object_To_Copy.m_shelf_No_Of_Publication;
      m_type_Of_Media = object_To_Copy.m_type_Of_Media;

      // deep copy m_name_Of_Publication
      dynamicAllocationAndCopy(object_To_Copy.m_name_Of_Publication);

      return *this;
   }

   // sets the type of the media
   void PubRecord::mediaType(int type_Of_Media) {
      m_type_Of_Media = type_Of_Media;
   }

   // returns the type of the media
   int PubRecord::mediaType() const {
      return (m_type_Of_Media == 0 ? 1 : m_type_Of_Media);
   }

   // returns name of publication
   const char* PubRecord::returnName() const {
      return m_name_Of_Publication;
   }



   // sets the shelfNo
   void PubRecord::shelfNo(int value) {
      m_shelf_No_Of_Publication = value;
   }

   // returns the shelf number that stores the publication
   int PubRecord::shelfNo() const {
      return m_shelf_No_Of_Publication;
   }

   // receives a three-digit integer from the console
   void PubRecord::readShelfNo() {
      int shelf_No_Input;
      readUtils(shelf_No_Input, 100, 999, "Invalid Shelf Number, Enter again: ");
      m_shelf_No_Of_Publication = shelf_No_Input;
   }

   // bool operator overload - compares character to the return value of the recID function. Returns true if it's a match and false otherwise.
   bool PubRecord::operator==(char character) const {
      return (character == recID());
   }

   // bool operator overload - if string is a substring of the name of the class, returns true. Otherwise, false.
   bool PubRecord::operator==(const char* string) const {
      return (strstr(m_name_Of_Publication, string) != nullptr);
   }

   // bool casting overload - returns true if, when casting, PubRecord is empty. Otherwise, false.
   PubRecord::operator bool() const {
      return (m_name_Of_Publication != nullptr && m_name_Of_Publication[0] != '\0');
   }

}