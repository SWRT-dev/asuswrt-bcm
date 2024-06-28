/*
 * $Id: json_object.h,v 1.8 2004/08/07 04:21:27 mclark Exp $
 *
 * Copyright Metaparadigm Pte. Ltd. 2004.
 * Michael Clark <michael@metaparadigm.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public (LGPL)
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details: http://www.gnu.org/
 *
 */

#ifndef _json_object_h_
#define _json_object_h_

#define JSON_OBJECT_DEF_HASH_ENTIRES 16

#undef FALSE
#define FALSE ((boolean)0)

#undef TRUE
#define TRUE ((boolean)1)

extern char *json_number_chars;
extern char *json_hex_chars;

/* forward structure definitions */

typedef int boolean;
struct printbuf;
struct lh_table;
struct array_list;
struct json_object;

/* supported object types */

enum json_type {
  json_type_null,
  json_type_boolean,
  json_type_double,
  json_type_int,
  json_type_object,
  json_type_array,
  json_type_string,
};

/* reference counting functions */

/**
 * Increment the reference count of json_object
 * @param this the json_object instance
 */
extern struct json_object* json_object_get(struct json_object *this);

/**
 * Decrement the reference count of json_object and free if it reaches zero
 * @param this the json_object instance
 */
extern void json_object_put(struct json_object *this);


/**
 * Check if the json_object is of a given type
 * @param this the json_object instance
 * @param type one of:
     json_type_boolean,
     json_type_double,
     json_type_int,
     json_type_object,
     json_type_array,
     json_type_string,
 */
extern int json_object_is_type(struct json_object *this, enum json_type type);

/**
 * Get the type of the json_object
 * @param this the json_object instance
 * @returns type being one of:
     json_type_boolean,
     json_type_double,
     json_type_int,
     json_type_object,
     json_type_array,
     json_type_string,
 */
extern enum json_type json_object_get_type(struct json_object *this);


/** Stringify object to json format
 * @param this the json_object instance
 * @returns a string in JSON format
 */
extern char* json_object_to_json_string(struct json_object *this);


/* object type methods */

/** Create a new empty object
 * @returns a json_object of type json_type_object
 */
extern struct json_object* json_object_new_object();

/** Get the hashtable of a json_object of type json_type_object
 * @param this the json_object instance
 * @returns a linkhash
 */
extern struct lh_table* json_object_get_object(struct json_object *this);

/** Add an object field to a json_object of type json_type_object
 *
 * The reference count will *not* be incremented. This is to make adding
 * fields to objects in code more compact. If you want to retain a reference
 * to an added object you must wrap the passed object with json_object_get
 *
 * @param this the json_object instance
 * @param key the object field name (a private copy will be duplicated)
 * @param val a json_object or NULL member to associate with the given field
 */
extern void json_object_object_add(struct json_object* this, char *key,
				   struct json_object *val);

/** Get the json_object associate with a given object field
 * @param this the json_object instance
 * @param key the object field name
 * @returns the json_object associated with the given field name
 */
extern struct json_object* json_object_object_get(struct json_object* this,
						  char *key);

/** Delete the given json_object field
 *
 * The reference count will be decremented for the deleted object
 *
 * @param this the json_object instance
 * @param key the object field name
 */
extern void json_object_object_del(struct json_object* this, char *key);

/** Iterate through all keys and values of an object
 * @param this the json_object instance
 * @param key the local name for the char* key variable defined in the body
 * @param val the local name for the json_object* object variable defined in the body
 */
#define json_object_object_foreach(obj,key,val) \
char *key=0; struct json_object *val=0; \
for(struct lh_entry *entry = json_object_get_object(obj)->head; ({ if(entry) { key = (char*)entry->k; val = (struct json_object*)entry->v; } ; entry; }); entry = entry->next )


/* Array type methods */

/** Create a new empty json_object of type json_type_array
 * @returns a json_object of type json_type_array
 */
extern struct json_object* json_object_new_array();

/** Get the arraylist of a json_object of type json_type_array
 * @param this the json_object instance
 * @returns an arraylist
 */
extern struct array_list* json_object_get_array(struct json_object *this);

/** Get the length of a json_object of type json_type_array
 * @param this the json_object instance
 * @returns an int
 */
extern int json_object_array_length(struct json_object *this);

/** Add an element to the end of a json_object of type json_type_array
 *
 * The reference count will *not* be incremented. This is to make adding
 * fields to objects in code more compact. If you want to retain a reference
 * to an added object you must wrap the passed object with json_object_get
 *
 * @param this the json_object instance
 * @param val the json_object to be added
 */
extern int json_object_array_add(struct json_object *this,
				 struct json_object *val);

/** Insert or replace an element at a specified index in an array (a json_object of type json_type_array)
 *
 * The reference count will *not* be incremented. This is to make adding
 * fields to objects in code more compact. If you want to retain a reference
 * to an added object you must wrap the passed object with json_object_get
 *
 * The reference count of a replaced object will be decremented.
 *
 * The array size will be automatically be expanded to the size of the
 * index if the index is larger than the current size.
 *
 * @param this the json_object instance
 * @param idx the index to insert the element at
 * @param val the json_object to be added
 */
extern int json_object_array_put_idx(struct json_object *this, int idx,
				     struct json_object *val);

/** Get the element at specificed index of the array (a json_object of type json_type_array)
 * @param this the json_object instance
 * @param idx the index to get the element at
 * @returns the json_object at the specified index (or NULL)
 */
extern struct json_object* json_object_array_get_idx(struct json_object *this,
						     int idx);

/* boolean type methods */

/** Create a new empty json_object of type json_type_boolean
 * @param b a boolean TRUE or FALSE (0 or 1)
 * @returns a json_object of type json_type_boolean
 */
extern struct json_object* json_object_new_boolean(boolean b);

/** Get the boolean value of a json_object
 *
 * The type is coerced to a boolean if the passed object is not a boolean.
 * integer and double objects will return FALSE if there value is zero
 * or TRUE otherwise. If the passed object is a string it will return
 * TRUE if it has a non zero length. If any other object type is passed
 * TRUE will be returned if the object is not NULL.
 *
 * @param this the json_object instance
 * @returns a boolean
 */
extern boolean json_object_get_boolean(struct json_object *this);


/* int type methods */

/** Create a new empty json_object of type json_type_int
 * @param i the integer
 * @returns a json_object of type json_type_int
 */
extern struct json_object* json_object_new_int(int i);

/** Get the int value of a json_object
 *
 * The type is coerced to a int if the passed object is not a int.
 * double objects will return their integer conversion. Strings will be
 * parsed as an integer. If no conversion exists then 0 is returned.
 *
 * @param this the json_object instance
 * @returns an int
 */
extern int json_object_get_int(struct json_object *this);


/* double type methods */

/** Create a new empty json_object of type json_type_double
 * @param d the double
 * @returns a json_object of type json_type_double
 */
extern struct json_object* json_object_new_double(double d);

/** Get the double value of a json_object
 *
 * The type is coerced to a double if the passed object is not a double.
 * integer objects will return their dboule conversion. Strings will be
 * parsed as a double. If no conversion exists then 0.0 is returned.
 *
 * @param this the json_object instance
 * @returns an double
 */
extern double json_object_get_double(struct json_object *this);


/* string type methods */

/** Create a new empty json_object of type json_type_string
 *
 * A copy of the string is made and the memory is managed by the json_object
 *
 * @param s the string
 * @returns a json_object of type json_type_string
 */
extern struct json_object* json_object_new_string(char *s);

extern struct json_object* json_object_new_string_len(char *s, int len);

/** Get the string value of a json_object
 *
 * If the passed object is not of type json_type_string then the JSON
 * representation of the object is returned.
 *
 * The returned string memory is managed by the json_object and will
 * be freed when the reference count of the json_object drops to zero.
 *
 * @param this the json_object instance
 * @returns a string
 */
extern char* json_object_get_string(struct json_object *this);

#endif
