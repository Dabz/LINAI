// =====================================================================================
//
//       Filename:  load.h
//
//    Description:
//
//        Version:  1.0
//        Created:  05/27/2010 11:24:41 PM
//       Revision:  none
//       Compiler:  g++
//
//         Author:  GASPARINA Damien (http://lamada.eu), gaspar_d@epita.fr
//        Company:  Epita
//
// =====================================================================================


#ifndef LOAD_H
#define LOAD_H

#include        <iostream>
#include        <fstream>
#include        <iomanip>
#include        <fstream>

#include        <string>

#include        "data.h"

board load_from_file(char* filename);

#endif
