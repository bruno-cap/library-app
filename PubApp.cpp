/*********************************************************************************************************
// Date: 2019/12/03
// Name: Seneca College Teacher
*********************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstring>
#include "PubApp.h"
#include "PubRecord.h"
#include "Magazine.h"
#include "Book.h"
using namespace std;
namespace sdds {

   void fs___read(char* str, int len, const char* errorMessage) {
      bool ok;

      do {
         ok = true;
         cin.getline(str, std::streamsize(len) + 1, '\n');
         if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            ok = false;
         }
      } while (!ok && cout << errorMessage);

   }

   void fs___read(int& val, int min, int max, const char* ErrorMess) {
      bool ok;
      char newline;
      do {
         cin >> val;
         newline = cin.get();
         if (cin.fail() || newline != '\n') {
            ok = false;
            cin.clear();
            cin.ignore(1000, '\n');
         }
         else {
            ok = val <= max && val >= min;
         }
      } while (!ok && cout << ErrorMess);

   }


   PubApp::~PubApp() {
      for (int i = 0; i < m_noOfPubs; i++) {
         delete m_pubs[i];
      }
   }
   PubApp::PubApp(const char* fname) :
      m_file(fname, ios::in),
      m_mainMenu("My Little Library"),
      m_sureMenu("Do you really want to exit the program?"),
      m_pubType("What type of Publication?"),
      m_sortMenu("How would you like to sort?"),
      m_pubs{ nullptr }, m_noOfPubs(0)
   {
      char* filename = m_filename;
      while ((*filename++ = *fname++) != 0);
      m_mainMenu << "Add Publication"
         << "Check Out"
         << "Check In"
         << "Search"
         << "List Overdue items"
         << "Print Inventory"
         << "Sort Inventory";
      m_sureMenu << "No, Cancel!";
      m_pubType << "Magazine" << "Book";
      m_sortMenu << "Sort by name" << "Sort by Type and then name";
   }
   bool PubApp::load(void) {
      char ch = 0;
      bool ret = false;
      int i = 0;
      if (m_file.fail()) m_file.clear();
      if (m_file.is_open()) m_file.close();
      m_file.open(m_filename, ios::in);
      if (m_file) {
         ret = true;
         while (ret && m_file && i < MaxNoOfPubs) {
            ch = 'x';
            m_file >> ch;
            if (ch == 'M') {
               m_pubs[i] = new Magazine;
            }
            else if (ch == 'B') {
               m_pubs[i] = new Book;
            }
            else {
               ret = false;
            }
            if (ret) {
               m_pubs[i]->mediaType(SDDS_FILE);
               m_file >> *m_pubs[i++];
            }
         }
      }
      m_noOfPubs = i;
      m_file.close();
      return ret;
   }
   void PubApp::save(void) {
      Menu sure("Save and overwrite the old data?");
      sure << "Yes, overwrite the data file with the current data";
      if (~sure) {
         if (m_file.fail()) m_file.clear();
         if (m_file.is_open()) m_file.close();
         m_file.open(m_filename, ios::out);
         for (int i = 0; i < m_noOfPubs; i++) {
            m_pubs[i]->mediaType(SDDS_FILE);
            m_file << *m_pubs[i];
         }
         m_file.close();
         cout << m_noOfPubs << " Item(s) saved." << endl << endl;
      }

   }
   void PubApp::addPub(void) {
      PubRecord* p = nullptr;
      int sel;
      switch (sel = ~m_pubType) {
      case 1:
         p = new Magazine;
         break;
      case 2:
         p = new Book;
         break;
      }
      if (sel) {
         cin >> *p;
         if (cin) {
            m_pubs[m_noOfPubs++] = p;
         }
         cout << "Publication Added." << endl << endl;
      }
      else {
         cout << "Aborted by user." << endl << endl;
      }
   }
   void PubApp::checkOut(void) {
      int index;
      cout << "Checking Out:" << endl;
      if (search(index, 'B')) {
         m_pubs[index]->mediaType(SDDS_CONSOLE);
         cout << "Checking out:" << endl;
         cout << *m_pubs[index] << endl;
         m_pubs[index]->checkOut();
         cout << endl;
      }
   }
   void PubApp::checkIn(void) {
      int index;
      cout << "Checking In:" << endl;
      if (search(index, 'B')) {
         m_pubs[index]->mediaType(SDDS_CONSOLE);
         cout << "Checking in:" << endl;
         cout << *m_pubs[index] << endl;
         m_pubs[index]->checkIn();
         cout << endl;
      }
   }
   void PubApp::title(void) {
      cout << endl << "Row  Title                                    ISBN or V(I)  Shlf Lent to Ret Date" << endl
         << "--------------------------------------------- -------------  --- -----   ----------" << endl;
   }
   bool PubApp::search(int& index, char rID) {
      char name[41];
      int i = 0;
      int found = 0;
      int foundIndex[MaxNoOfPubs];
      bool res = false;
      cout << "Search for name: ";
      fs___read(name, 40, "Too long!, please enter maximum of 40 characters.");
      cout << "Searching...." << endl;
      title();
      for (i = 0; i < m_noOfPubs && found < 20; i++) {
         if (*m_pubs[i] == name && (!rID || rID == m_pubs[i]->recID())) {
            m_pubs[i]->mediaType(SDDS_CONSOLE);
            cout << setw(3) << right << (found + 1) << "- " << *m_pubs[i] << endl;
            foundIndex[found] = i;
            found++;
         }
      }
      if (found > 0) {
         cout << "  0- Exit" << endl;
         if (found == 20) cout << "There are too many matches..." << endl
            << "Be more specific with the name to narrow down the search" << endl;
         cout << "Select: ";
         fs___read(index, 0, found, "Invalid selection, please try again.");
         res = index > 0;
         index = foundIndex[index - 1];
      }
      else {
         cout << "No matches were found!" << endl;
      }
      cout << endl;
      return res;
   }

   bool PubApp::printInventory(int& index) {
      int i = 0;
      bool res = false;
      title();
      if (m_noOfPubs > 0) {
         for (i = 0; i < m_noOfPubs; i++) {
            m_pubs[i]->mediaType(SDDS_CONSOLE);
            cout << setw(3) << right << (i + 1) << "- " << *m_pubs[i] << endl;
         }
         cout << "  0- Exit" << endl;
         cout << "Select: ";
         fs___read(index, 0, m_noOfPubs, "Invalid selection, please try again.");
         if (index != 0) {
            index -= 1;
            cout << index << endl;
            res = true;
         }
      }
      else {
         cout << "There are no publications in the inventory!" << endl;
      }
      cout << endl;
      return res;
   }

   bool PubApp::listOverdue(int& index) {
      int i = 0;
      int noOverdue = 0;
      bool res = false;
      Date todaysDate;
      title();
      if (m_noOfPubs > 0) {
         for (i = 0; i < m_noOfPubs; i++) {
            // check if publication is a Book and is overdue
            if (m_pubs[i]->recID() == 'B') {
               Date pubDate(m_pubs[i]->return_Year(), m_pubs[i]->return_Month(), m_pubs[i]->return_Day());
               if (pubDate - todaysDate < 0) {
                  m_pubs[i]->mediaType(SDDS_CONSOLE);
                  cout << setw(3) << right << (i + 1) << "- " << *m_pubs[i] << endl;
                  noOverdue += 1;
               }
            }
         }
         if (noOverdue > 0) {
            cout << "  0- Exit" << endl;
            cout << "Select: ";
            fs___read(index, 0, m_noOfPubs, "Invalid selection, please try again.");
            if (index != 0) {
               index -= 1;
               cout << index << endl;
               res = true;
            }
         }
         else {
            cout << "No books are overdue" << endl;
         }
      }
      else {
         cout << "There are no publications in the inventory!" << endl;
      }
      cout << endl;
      return res;
   }


   void PubApp::sortByName(int index) {

      // restart m_pubs to original settings in case previous sorting was applied
      for (int p = 0; p < m_noOfPubs; p++) {
         delete m_pubs[p];
      }
      load();

      int indexArray[MaxNoOfPubs];  // array of indexes that stores the positions items from m_file will be stored in m_pubs
      char ch = 0;
      bool ret = false;
      int i = 0;
      if (m_file.fail()) m_file.clear();
      if (m_file.is_open()) m_file.close();
      m_file.open(m_filename, ios::in);
      int baseIndex, finalIndex, repeatedBefore;

      // go through m_pubs array
      for (int i = 0; i < m_noOfPubs; i++) {
         baseIndex = 0, finalIndex = 0, repeatedBefore = 0;

         // compares current entry with all others to find how many times it was greater than others - that's the baseIndex
         for (int j = 0; j < m_noOfPubs; j++) {
            if (strcmp(m_pubs[i]->returnName(), m_pubs[j]->returnName()) > 0) {
               baseIndex += 1;
            }
         }

         // compares current entry with previous ones to check for repeated entries - that's repeatedBefore
         for (int k = 0; k < i; k++) {
            if (strcmp(m_pubs[i]->returnName(), m_pubs[k]->returnName()) == 0) {
               repeatedBefore += 1;
            }
         }

         // the finalIndex in the temporary array is going to be the baseIndex + repeatedBefore
         finalIndex = baseIndex + repeatedBefore;
         indexArray[i] = finalIndex;
      }

      // read items from file and store in m_pubs according to the indexes stored in indexArray
      if (m_file) {
         ret = true;
         while (ret && m_file && i < m_noOfPubs) {

            ch = 'x';
            m_file >> ch;
            if (ch == 'M') {
               delete m_pubs[indexArray[i]];             // delete previously allocated memory
               m_pubs[indexArray[i]] = new Magazine;
            }
            else if (ch == 'B') {
               delete m_pubs[indexArray[i]];             // delete previously allocated memory
               m_pubs[indexArray[i]] = new Book;
            }
            else {
               ret = false;
            }
            if (ret) {
               m_pubs[indexArray[i]]->mediaType(SDDS_FILE);
               m_file >> *m_pubs[indexArray[i]];
            }
            i++;
         }
      }
      m_file.close();
   }


   void PubApp::sortByTypeAndName(int index) {

      // restart m_pubs to original settings in case previous sorting was applied
      for (int p = 0; p < m_noOfPubs; p++) {
         delete m_pubs[p];
      }
      load();

      int indexArraybyTypeName[MaxNoOfPubs];     // array of indexes that stores the positions items from m_file will be stored in m_pubs
      char ch = 0;
      bool ret = false;
      int i = 0;
      if (m_file.fail()) m_file.clear();
      if (m_file.is_open()) m_file.close();
      m_file.open(m_filename, ios::in);
      int baseIndex, finalIndex, repeatedBefore;


      // find out number of books
      int bookCount = 0;
      for (int l = 0; l < m_noOfPubs; l++) {
         if (m_pubs[l]->recID() == 'B') {
            bookCount++;
         }
      }
      
      for (int i = 0; i < m_noOfPubs; i++) {
         baseIndex = 0; repeatedBefore = 0; finalIndex = 0;

         // compares current entry with all others of the SAME TYPE to find how many times it was greater - that's the baseIndex
         for (int j = 0; j < m_noOfPubs; j++) {
            if (strcmp(m_pubs[i]->returnName(), m_pubs[j]->returnName()) > 0 && m_pubs[i]->recID() == m_pubs[j]->recID()) {
               baseIndex += 1;
            }
         }

         // compares current entry with previous ones of the SAME TYPE to check for repeated entries - that's repeatedBefore
         for (int k = 0; k < i; k++) {
            if (strcmp(m_pubs[i]->returnName(), m_pubs[k]->returnName()) == 0 && m_pubs[i]->recID() == m_pubs[k]->recID()) {
               repeatedBefore += 1;
            }
         }

         // the finalIndex in the temporary array is going to be the baseIndex + repeatedBefore ( + bookCount if it's a magazine -> those are pushed to the end )

         if (m_pubs[i]->recID() == 'M') {
            finalIndex = baseIndex + repeatedBefore + bookCount;
         }
         else {
            finalIndex = baseIndex + repeatedBefore;
         }
         indexArraybyTypeName[i] = finalIndex;
      }

         // read items from file and store in m_pubs according to the indexes stored in indexArraybyTypeName
         if (m_file) {
            ret = true;
            while (ret && m_file && i < m_noOfPubs) {

               ch = 'x';
               m_file >> ch;
               if (ch == 'M') {
                  delete m_pubs[indexArraybyTypeName[i]];               // delete previously allocated memory
                  m_pubs[indexArraybyTypeName[i]] = new Magazine;
               }
               else if (ch == 'B') {
                  delete m_pubs[indexArraybyTypeName[i]];               // delete previously allocated memory
                  m_pubs[indexArraybyTypeName[i]] = new Book;
               }
               else {
                  ret = false;
               }
               if (ret) {
                  m_pubs[indexArraybyTypeName[i]]->mediaType(SDDS_FILE);
                  m_file >> *m_pubs[indexArraybyTypeName[i]];
               }
               i++;
            }
         }
         m_file.close();
   }

   int PubApp::run() {
      int ret = 0;
      int index = 0;
      bool done = false;
      if (!m_file) {
         cout << "file " << m_filename << " does not exist!" << endl;
         done = true;
      }
      else {
         m_file.close();
      }
      load();
      while (!done) {
         switch (~m_mainMenu) {
         case 1:
            addPub();
            break;
         case 2:
            checkOut();
            break;
         case 3:
            checkIn();
            break;
         case 4:
            if (search(index)) {
               m_pubs[index]->mediaType(SDDS_CONSOLE);
               cout << *m_pubs[index];
            }
            break;
         case 5:
            if (listOverdue(index)) {
               m_pubs[index]->mediaType(SDDS_CONSOLE);
               cout << *m_pubs[index];
               cout << endl << endl;
            }
            break;
         case 6:
            if (printInventory(index)) {
               m_pubs[index]->mediaType(SDDS_CONSOLE);
               cout << *m_pubs[index];
               cout << endl << endl;
            }
            break;
         case 7:
            switch (~m_sortMenu) {
            case 1:
               sortByName(index);
               if (printInventory(index)) {
                  m_pubs[index]->mediaType(SDDS_CONSOLE);
                  cout << *m_pubs[index];
                  cout << endl << endl;
               }
               break;
            case 2:
               sortByTypeAndName(index);
               if (printInventory(index)) {
                  m_pubs[index]->mediaType(SDDS_CONSOLE);
                  cout << *m_pubs[index];
                  cout << endl << endl;
               }
               break;
            default:
               break;
            }
            break;

         default:
            if (~m_sureMenu == 0) {
               done = true;
            }
            break;
         }
      }
      save();
      return ret;
   }

}