/*********************************************************************************************************
// Date: 2019/12/03
// Name: Seneca College Teacher
*********************************************************************************************************/

#ifndef SDDS_PUBAPP_H__
#define SDDS_PUBAPP_H__
#include <iostream>
#include <fstream>
#include "PubRecord.h"
#include "Menu.h"
namespace sdds {
   const int MaxNoOfPubs = 1000;
   class PubApp {
      std::fstream m_file;
      Menu m_mainMenu;
      Menu m_sureMenu;
      Menu m_pubType;
      Menu m_sortMenu;
      PubRecord* m_pubs[MaxNoOfPubs];
      int m_noOfPubs;
      char m_filename[256];
      bool load(void);
      void save(void);
      void addPub(void);
      void checkOut(void);
      void checkIn(void);
      void title(void);
      bool search(int& index, char recID = '\0');
      bool listOverdue(int& index);
      bool printInventory(int& index);
      void sortByName(int index);
      void sortByTypeAndName(int index);
   public:
      PubApp(const char* filename);
      int run();
      virtual ~PubApp();
   };

}

#endif
