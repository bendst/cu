#ifndef CU_GENERIC_H_
#define CU_GENERIC_H_ 

/**
 * @file generic.h
 * @brief Provides generic functions for the data structures
 */

#define cu_push(x, y) _Generic((x), \
                            vector_t * : vector_push((vector_t *)x, y), \
                            list_t * : list_push_back((list_t *)x, y) \
                            )

#define cu_new(x) _Generic((x), \
                        vector_t * : vector_new(), \
                        list_t * : list_new()\
                        )

#define cu_clear(x, fn) _Generic((x), \
                              vector_t * : vector_clear((vector_t *)x, fn), \
                              list_t * : list_clear((list_t *)x, fn) \
                              )

#define cu_del(x) _Generic((x), \
                        vector_t * : vector_del((vector_t *)x), \
                        list_t * : list_del((list_t *)x) \
                        )

#define cu_clear_del(x, fn) _Generic((x), \
                                  vector_t * : vector_clear_del((vector_t *)x, fn), \
                                  list_t * : list_clear_del((list_t *)x, fn) \
                                  )
#define cu_len(x) _Generic((x), \
                        vector_t * : vector_len((vector_t *)x), \
                        list_t * : list_len((list_t *)x) \
                        )

#define cu_foreach(x, fn) _Generic((x), \
                                vector_t * : vector_foreach((vector_t *)x, fn), \
                                list_t * : list_foreach((list_t *)x, fn) \
                                )

#define cu_is_empty(x) _Generic((x), \
                             vector_t * : vector_is_empty((vector_t *)x), \
                             list_t * : list_is_empty((list_t *)x) \
                             )

#define cu_find(x, key, pred) _Generic((x), \
                                    vector_t * : vector_find((vector_t *)x, key, pred), \
                                    list_t * : list_find((list_t *)x, key, pred) \
                                    )

#define cu_insert(x, index, data) _Generic((x), \
                                        vector_t * : vector_insert((vector_t *)x, index, data), \
                                        list_t * : list_insert((list_t *) x, index, data) \
                                        )

#define cu_contains(x, key, pred) _Generic((x), \
                                        vector_t * : vector_contains((vector_t *)x, key, pred), \
                                        list_t * : list_contains((list_t *)x, key, pred) \
                                        )


#endif /* ifndef CU_GENERIC_H_ */
