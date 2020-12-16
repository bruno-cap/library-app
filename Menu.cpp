/*********************************************************************************************************
// Date: 2019/12/10
// Name: Bruno Pinto
*********************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include <cstring>
using namespace std;
#include "Menu.h"

namespace sdds {

   // default constructor
   MenuItem::MenuItem() {
      setToSafeEmptyState();
   }

   // one argument constructor
   MenuItem::MenuItem(const char* description_Of_Menu_Item) {
      m_description = new char[strlen(description_Of_Menu_Item) + 1];
      strcpy(m_description, description_Of_Menu_Item);
   }

   // sets to safe empty state
   void MenuItem::setToSafeEmptyState() {
      m_description = nullptr;
   }

   // destructor
   MenuItem::~MenuItem() {
      delete[] m_description;
   }

   // bool overload to return true if MenuItem is not empty, and false otherwise
   MenuItem::operator bool() const {
      return (m_description != nullptr);
   }

   // const char* overload to return the address of m_description
   MenuItem::operator const char* () const {
      return m_description;
   }

   // checks the state of the Date object and prints information accordingly
   std::ostream& MenuItem::display(std::ostream& os) const {
      return os;
   }

   // returns m_description
   const char* MenuItem::outputTitle() const {
      return m_description;
   }

   // no argument constructor
   Menu::Menu() {
      setToSafeEmptyState();
   }

   // one argument constructor
   Menu::Menu(const char* title_Of_The_Menu): m_title(title_Of_The_Menu) {
      setToSafeEmptyState();
   }

   // sets to safe empty state
   void Menu::setToSafeEmptyState() {
      for (unsigned int i = 0; i < MAX_MENU_ITEMS; i++) {
         m_MenuItem_Array[i] = nullptr;
      }
      m_quant = 0;
   }

   // displays the title of the Menu
   std::ostream& Menu::displayTitle(std::ostream& os) const {
      os << m_title.outputTitle();
      return os;
   }

   // displays the entire Menu
   std::ostream& Menu::displayMenu(std::ostream& os) const {
      // displays m_title if not empty
      if (m_title != nullptr) {
         displayTitle(os) << ":" << endl;
      }

      // displays menu items
      bool endOfArray = false; // control variable that flags when a nullptr is found

      for (unsigned int i = 0; i < MAX_MENU_ITEMS && endOfArray == false; i++) {
         if (m_MenuItem_Array[i] == nullptr) {
            endOfArray = true;
         }
         else {
            os << right << setw(2) <<i + 1 << "- " << m_MenuItem_Array[i]->outputTitle() << endl;
         }
      }
      os << " 0- Exit" << endl;
      os << "> ";
      return os;
   }

   // query function to return the title of the menu
   const char* Menu::returnTitle() const {
      return m_title.outputTitle();
   }

   // overloads << to add a MenuItem to Menu and returns a reference to the Menu object
   Menu& Menu::operator<<(const char* description_Of_Menu_Item) {
      bool keepSearching = true;
      if (m_quant < MAX_MENU_ITEMS) {     // checks if full
         for (unsigned int i = 0; i < MAX_MENU_ITEMS && keepSearching == true; i++) {   // searches empty spot
            if (m_MenuItem_Array[i] == nullptr) {
               m_MenuItem_Array[i] = new MenuItem;
               m_MenuItem_Array[i]->m_description = new char[strlen(description_Of_Menu_Item) + 1];
               strcpy(m_MenuItem_Array[i]->m_description, description_Of_Menu_Item);
               m_quant += 1;
               keepSearching = false;
            }
         }
      }
      return *this;
   }

   // destructor
   Menu::~Menu() {
      for (unsigned int i = 0; i < MAX_MENU_ITEMS; i++) {
         delete m_MenuItem_Array[i];
      }
   }

   // displays the Menu and gets the user selection
   unsigned int Menu::getSelection() const {
      displayMenu();
      unsigned int selection;
      cin >> selection;

      while (cin.fail() || selection > m_quant) {
         cin.clear();
         int checkInput;
         while ((checkInput = getchar()) != '\n' && checkInput != EOF);
         cout << "Invalid Selection, try again: ";
         cin >> selection;
      }

      cin.ignore(1000, '\n');
      return selection;
   }

   // does exactly what getSelection() does
   unsigned int Menu::operator ~() const {
      return getSelection();
   }

   // returns the number of MenuItems allocated in m_MenuItem_Array if casting Menu to 
   // and integer or unsigned integer
   Menu::operator int() {
      return m_quant;
   }
   Menu::operator unsigned int() {
      return m_quant;
   }

   // bool castings to return true if Menu has one or more menu items, otherwise false
   bool Menu::operator !() const {
      return (m_quant < 1);
   }
   Menu::operator bool(){
      return (m_quant >= 1);
   }

   // indexing operator overload to return the const char* cast of the corresponding MenuItem
   // in the array of MenuItem pointers
   const char* Menu::operator[](unsigned int index) const {
      // if the index passed as parameter is greater than the number of MenuItems, loop back to the beginning
      if (index > m_quant) {
         index = 0;
      }
      return m_MenuItem_Array[index]->m_description;
   }


   // helper operator overloads
   // overloads cout so it can take a Menu object as right operand
   std::ostream& operator<<(ostream& os, const Menu& Menu_Object) {
      if (Menu_Object.returnTitle() != nullptr) {
         Menu_Object.displayTitle(os);
      }
      return os;
   }

}