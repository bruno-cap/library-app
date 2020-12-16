/************************************************************************************************************
// Date: 2019/12/10
// Name: Bruno Pinto
************************************************************************************************************/

#ifndef SDDS_MENU_H__
#define SDDS_MENU_H__

namespace sdds {

   const unsigned int MAX_MENU_ITEMS = 20;

   class Menu;

   class MenuItem {
   private:
      friend Menu;
      char* m_description;
      // no argument constructor
      MenuItem();
      // one argument constructor
      MenuItem(const char* description_Of_MenuItem);
      // sets to safe empty state
      void setToSafeEmptyState();
      // copy constructor preventing copy
      MenuItem(const MenuItem& MenuItem_Object) = delete;
      // assignmet overload with prevention
      MenuItem& operator=(const MenuItem& MenuItem_Object) = delete;
      // destructor
      virtual ~MenuItem();
      // bool overload to return true if MenuItem is not empty, and false otherwise
      operator bool() const;
      // const char* overload to return the address of m_description
      operator const char*() const;
      // checks the state of the Date object and prints information accordingly
      std::ostream& display(std::ostream& os = std::cout) const;
      // outputs m_description
      const char* outputTitle() const;
   };

   class Menu {
      MenuItem m_title;
      MenuItem *m_MenuItem_Array[MAX_MENU_ITEMS];
      unsigned int m_quant;
   public:
      // no argument constructor
      Menu();
      // one argument constructor
      Menu(const char* title_Of_The_Menu);
      // sets to safe empty state
      void setToSafeEmptyState();
      // destructor
      virtual ~Menu();
      // displays the title of the Menu
      std::ostream& displayTitle(std::ostream& os = std::cout) const;
      // displays the entire Menu
      std::ostream& displayMenu(std::ostream& os = std::cout) const;
      // query function to return the title of the menu
      const char* returnTitle() const;
      // overloads << to add a MenuItem to Menu and returns a reference to the Menu object
      Menu& operator<<(const char* description_Of_Menu_Item) ;
      // displays the Menu and gets the user selection
      unsigned int getSelection() const;
      // does exactly what getSelection() does
      unsigned int operator ~() const;
      // returns the number of MenuItems allocated in m_MenuItem_Array if casting Menu to 
      // and integer or unsigned integer
      operator int();
      operator unsigned int();
      // bool castings to return true if Menu has one or more menu items, otherwise false
      operator bool();
      bool operator !() const;
      // indexing operator overload to return the const char* cast of the corresponding MenuItem
      // in the array of MenuItem pointers
      const char* operator[](unsigned int index) const;
   };

   // helper operator overloads
   // overloads cout so it can take a Menu object as right operand
   std::ostream& operator<<(std::ostream& os, const Menu& Menu_Object);
}

#endif