/*********************************************************************************************************
// Date: 2019/12/10
// Name: Bruno Pinto
*********************************************************************************************************/

#include <iostream>
#include <iomanip>
using namespace std;
#include "Book.h"
#include "Utils.h"

namespace sdds {

   // default constructor
   Book::Book() : PubRecord(), m_ISBN(0), m_shipId(0), m_dueDate() {
   }

   // copy constructor
   Book::Book(const Book& book_Object) : PubRecord(book_Object), m_ISBN(book_Object.m_ISBN), m_shipId(0), m_dueDate() {
   }

   // assignment operator overload
   Book& Book::operator=(const Book& book_Object) {
      PubRecord::operator=(book_Object);
      m_ISBN = book_Object.m_ISBN;
      m_shipId = 0;
      this->m_dueDate = Date();
      return *this;
   }

   // returns the character 'B'
   char Book::recID() const {
      return 'B';
   }

   // returns the member id and cannot modify the Book object
   int Book::memberID() const {
      return m_shipId;
   }

   // returns m_dueDate and cannot modify the Book object
   int Book::return_Day() const {
      return m_dueDate.returnDay();
   }
   // returns m_dueDate and cannot modify the Book object
   int Book::return_Month() const {
      return m_dueDate.returnMonth();
   }
   // returns m_dueDate and cannot modify the Book object
   int Book::return_Year() const {
      return m_dueDate.returnYear();
   }

   // sets m_shipId = 0 and prints the Book on the console
   void Book::checkIn() {
      m_shipId = 0;
      write() << " checked in!" << endl;
   }

   // checks out the Book and lends to a member
   void Book::checkOut() {
      int tempMemberID;
      bool keepGoing = true;
      Date tempDate;
      Date todaysDate;

      cout << "Enter Member id: ";
      readUtils(tempMemberID, 10000, 99999, "Invalid Member ID, Enter again: ");
      while (keepGoing) {
         cout << "Enter return date: ";
         cin >> tempDate;
         if (cin.fail()) {
            cout << tempDate << "." << endl;
         }
         else if (tempDate <= todaysDate) {
            cout << "Please enter a future date." << endl;
         }
         else if ((tempDate - todaysDate > 30)) {
            cout << "The return date must be earlier than 30 days away from today." << endl;
         }
         else {
            keepGoing = false;
         }
      }
      m_shipId = tempMemberID;
      m_dueDate = tempDate;
   }

   // receives and returns references of istream
   std::istream& Book::read(std::istream& is) {
      char tempName[100];
      long long tempISBN = 0;

      if (mediaType() == 1) {
         m_shipId = 0;

         cout << "Book Name: ";
         readUtils(tempName, 40, "Book name too long, Enter again: ");
         name(tempName);

         cout << "ISBN: ";
         readUtils(tempISBN, 1000000000000LL, 9999999999999LL, "Invalid ISBN, Enter again: ");
         m_ISBN = tempISBN;

         cout << "Shelf Number: ";
         readShelfNo();
      } 
      else {
         int tempShelf = 0;
         int tempShipId = 0;
         Date tempDate;

         is.getline(tempName, 40, '\t');

         is >> tempISBN;

         is.ignore(1);     // ignore '\t'
         is >> tempShelf;

         is.ignore(1);     // ignore '\t'
         is >> tempShipId;

         if (tempShipId != 0) {
            is.ignore(1);
            is >> tempDate;
            // is.ignore() wasn't used here because Date::Read() will already flush the keyboard
         }
         else {
            is.ignore(1);     // ignore '\n'
         }

         if (!is.fail()) {
            name(tempName);
            m_ISBN = tempISBN;
            shelfNo(tempShelf);
            m_shipId = tempShipId;

            if (tempShipId != 0) {
               m_dueDate = tempDate;
            }
         }
      }
      return is;
   }

   // receives and returns references of ostream
   std::ostream& Book::write(std::ostream& os) const {
      if (mediaType() == 1) {
         os << setw(41) << left << name();
         os << setw(13) << setprecision(0) << fixed << m_ISBN;
         os << "  ";
         os << shelfNo();

         if (m_shipId != 0) {
            os << " " << m_shipId << "   " << m_dueDate;
         }

      }
      else {
         os << recID() << name() << "\t" << setw(13) << setprecision(0) << fixed << m_ISBN << "\t" << shelfNo() << "\t" << m_shipId;

         if (m_shipId != 0) {
            os << "\t" << m_dueDate;
         }

         os << endl;
      }

      return os;
   }

   // destructor
   Book::~Book() {

   }

}
