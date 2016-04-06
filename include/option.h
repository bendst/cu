#ifndef CU_OPTION_H_
#define  CU_OPTION_H_

#include <stdbool.h>

/** 
 * @file option.h
 * @brief Datatype for wrapping pointer in a safer way 
 */

/** @brief option_t wraps a pointer und does checks whether it is null.
 *
 *
 * The structure contains pointer to functions for unwrapping the data 
 * and doing checks on it. 
 * 
 */
typedef struct option_t {
    enum  {
        none,
        some,
    } _options;
    void *data;
    void *(*unwrap)(const struct option_t *);
    void *(*expect)(const struct option_t *, const char *msg);
    void *(*unwrap_or)(const struct option_t *, void *);
    bool (*is_some)(const struct option_t *);
    bool (*is_none)(const struct option_t *);
} option_t;



/** @brief Create a new option_t for given pointer
 *
 *  ~~~{.c}
 *  int *data = malloc(20);
 *  option_t opt = option(data);
 *  ~~~
 *
 *  @param data expects a pointer 
 *  @return returns a pointer struct which wraps the pointer
 */
option_t option(void *data);



/** @brief Unwrap the option_t and retrieve the underlying pointer.
 *
 *  In case that the underlying data is NULL, abort() is called.
 *
 *  ~~~{.c}
 *  int *data = malloc(20);
 *  option_t opt = option(data);
 *  void *my_data = opt.unwrap(&opt);
 *  ~~~
 *  
 *  @param self reference to option
 *  @return get the underlying data of the option
 */
void *unwrap(option_t *self);



/** @brief Unwraps the option_t and retrieve the underlying pointer.
 *
 *  In case of an error see unwrap(), the passed error msg is printed and abort is called.
 *
 *  ~~~{.c}
 *  int *data = malloc(20);
 *  option_t opt = option(data);
 *  void *my_data = opt.expect(&opt, "Data was NULL");
 *  ~~~
 * 
 *  @param self reference to the option
 *  @param msg message to print to stderr 
 *  @return retrieve the underlying pointer
 */
void *expect(option_t *self, const char *msg);


/** @brief Unwraps the option_t and retrieve the underlying pointer.
 *
 * ~~~{.c}
 *  int *data = malloc(20);
 *  int default[20] = {}; 
 *
 *  option_t opt = option(data);
 *  void *my_data = opt.unwrap_or(&opt, default);
 * ~~~
 * 
 * @param self reference to the option_t
 * @param default_val default value to return
 * @result retrieve the underlying pointer
 */
void *unwrap_or(option_t *self, void *default_val);


/** @brief Check if the underlying data contains a valid pointer
 *
 * ~~~{.c}
 *  int *data = malloc(20);
 *
 *  option_t opt = option(data);
 *  bool is = opt.is_some(&opt); // with a high probability is 1
 * ~~~
 *
 * @param self reference to the option_t
 * @result true in case that the underlying pointer is not NULL
 */
bool is_some(option_t *self);

/** @brief Check if the underlying data is a invalid pointer
 *
 *
 * ~~~{.c}
 *  option_t opt = option(NULL);
 *  bool is = opt.is_none(&opt); // returns false
 * ~~~
 *
 * @param self reference to the option_t
 * @result Is false in case that the pointer passed is NULL
 */
bool is_none(option_t *self);
#endif // CU_OPTION_H_
