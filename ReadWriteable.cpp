/*********************************************************************************************************
// Date: 2019/12/10
// Name: Bruno Pinto
*********************************************************************************************************/

#include <iostream>
using namespace std;
#include "Utils.h"
#include "ReadWriteable.h"

namespace sdds {

   // destructor
   ReadWriteable::~ReadWriteable() {

   };

   // overloads the insertion operator
   ostream& operator<<(ostream& os, const ReadWriteable& object_As_Right_Operand) {
      return object_As_Right_Operand.write(os);
   };

   // overloads the extraction operator
   istream& operator>>(istream& is, ReadWriteable& object_As_Right_Operand) {
      return object_As_Right_Operand.read(is);
   };

}