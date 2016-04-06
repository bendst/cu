/*! @mainpage About
 *
 *      The CU Library contains various helper functions and datastructure.
 *
 *  ### Noteworthy
 *  Most functions for the data structures are defined in [generic.h](generic_8h.html)
 *  as generic function using the c11 _Generic Macro.
 *
 *
 *  ## Usage
 *
 *  Compile the library using Makefile provided,
 *
 *  it will generated a approperiate `cu.h` and a `libcu.a` in `lib` Folder.
 *  
 *  To use the cu library set -lcu Flag in your project.
 *
 *  ~~~{.c}
 *  #include "cu.h"
 *
 *  void deconstruct() {
 *      
 *  }
 *
 *  int main() {
 *      cu_init(deconstruct);
 *
 *      vector_t *v = new(v);
 *      ....
 *  }
 *  ~~~
 *
 *
 *  ## Module
 *  Following modules are provided:
 *  - [dopply linked list](list_8h.html)
 *  - [a continuous vector](vector_8h.html)
 *  - [option type](option_8h.html)
 *  - [various utility function](util_8h.html)
 *  - [generic defines](generic_8h.html)
 *
 *
 */
