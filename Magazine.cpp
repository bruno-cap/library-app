/*********************************************************************************************************
// Date: 2019/12/10
// Name: Bruno Pinto
*********************************************************************************************************/

#include <iostream>
#include <iomanip>
using namespace std;
#include "Utils.h"
#include "Magazine.h"

namespace sdds {

   // default constructor
   Magazine::Magazine(): PubRecord(), m_volume(0), m_issueNo(0) {
   }

   // copy constructor
   Magazine::Magazine(const Magazine& magazine_Object) : PubRecord(magazine_Object), 
      m_volume(magazine_Object.m_volume), m_issueNo(magazine_Object.m_issueNo) {
   }

   // assignment operator overload
   Magazine& Magazine::operator=(const Magazine& magazine_Object) {
      PubRecord::operator=(magazine_Object);
      m_volume = magazine_Object.m_volume;
      m_issueNo = magazine_Object.m_issueNo;
      return *this;
   }

   // returns the character 'M'
   char Magazine::recID() const {
      return 'M';
   }

   // prints "Magazines cannot be checked in or out!"
   void Magazine::checkIn() {
      cout << "Magazines cannot be checked in or out!" << endl;
   }

   // prints "Magazines cannot be checked in or out!"
   void Magazine::checkOut() {
      cout << "Magazines cannot be checked in or out!" << endl;
   }

   // returns m_dueDate and cannot modify the Book object
   int Magazine::return_Day() const {
      cout << "Magazines cannot be checked in or out!" << endl;
      return 0;
   }
   // returns m_dueDate and cannot modify the Book object
   int Magazine::return_Month() const {
      cout << "Magazines cannot be checked in or out!" << endl;
      return 0;
   }
   // returns m_dueDate and cannot modify the Book object
   int Magazine::return_Year() const {
      cout << "Magazines cannot be checked in or out!" << endl;
      return 0;
   }

   // receives and returns references of istream
   std::istream& Magazine::read(std::istream& is) {
      char tempName[100];
      int tempVolume = 0;
      int tempIssue = 0;

      if (mediaType() == 1) {
         cout << "Magazine Name: ";
         readUtils(tempName, 40, "Magazine name too long, Enter again: ");
         name(tempName);

         cout << "Volume: ";
         readUtils(tempVolume, 1, 99, "Invalid Volume number, Enter again: ");
         m_volume = tempVolume;

         cout << "Issue: ";
         readUtils(tempIssue, 1, 99, "Invalid Issue number, Enter again: ");
         m_issueNo = tempIssue;

         cout << "Shelf Number: ";
         readShelfNo();

      }
      else {

         int tempShelf;

         is.getline(tempName, 40, '\t');
         is >> tempVolume;
         is.ignore(1);       // ignore '\t'
         is >> tempIssue;
         is.ignore(1);       // ignore '\t'
         is >> tempShelf;
         is.ignore(1);       // ignore '\n'

         // if is doesn't fail, copies temporary variables to member variables
         if(!is.fail()) {
            name(tempName);
            m_volume = tempVolume;
            m_issueNo = tempIssue;
            shelfNo(tempShelf);
         }
      }
      return is;
   }

   // receives and returns references of ostream
   std::ostream& Magazine::write(std::ostream& os) const {
      if (mediaType() == 1) {
         os << setw(41) << left << name();
         os << "       ";
         os << setw(2) << right << setfill('0') << m_volume << "(";
         os << setw(2) << right << setfill('0') << m_issueNo << ")";
         os << "  ";
         os << setfill(' ');
         os << shelfNo();
      }
      else {
         os << recID() << name() << "\t" << m_volume << "\t" << m_issueNo << "\t" << shelfNo() << endl;
      }

      return os;
   }

   // destructor
   Magazine::~Magazine() {

   }

}