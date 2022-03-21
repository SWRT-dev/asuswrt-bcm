#!/usr/bin/env python 
# -*- Mode: python -*-
#======================================================================
# FILE: Property.py
# CREATOR: eric 
#
# DESCRIPTION:
#   
#
#  $Id: Property.py,v 1.13 2002-10-24 13:44:30 acampi Exp $
#  $Locker:  $
#
# (C) COPYRIGHT 2001, Eric Busboom <eric@softwarestudio.org>
# (C) COPYRIGHT 2001, Patrick Lewis <plewis@inetarena.com>  
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of either: 
#
#    The LGPL as published by the Free Software Foundation, version
#    2.1, available at: http://www.fsf.org/copyleft/lesser.html
#
#  Or:
#
#    The Mozilla Public License Version 1.0. You may obtain a copy of
#    the License at http://www.mozilla.org/MPL/
#======================================================================

from LibicalWrap import *
import re
import base64
from string import index, upper, split
from types import StringType

#def icalerror_supress(arg): 
#    pass

#def icalerror_restore(a,b):
#    pass

def error_type():
    error = icalerror_perror()
    return error[:index(error,':')]

def test_enum(prop,enum):

    vkind = icalvalue_string_to_kind(prop)
    e = icalproperty_kind_and_string_to_enum(vkind, enum)

    if e != 0:
        return 1
    
    return None


class Property(object):
    """ Represent any iCalendar Property.

    Usage:
    Property(dict)

    Where:
    dict is a dictionary with keys of 'name', 'value_type', and 'value'.
    In addition, parameter:parameter value entries may be included.
    """

    class ConstructorFailedError(Exception):
        "Failed to construct a property"

    class UpdateFailedError(Exception):
        "Failed to update the value of a property"
        

    def __init__(self, type = None, ref = None):


        #~ assert(ref == None or isinstance(ref,StringType))
        #~ assert(type == None or isinstance(type,StringType))

        self._ref = None
        
        if ref != None:
            self._ref = ref
        elif type != None:
            kind  = icalproperty_string_to_kind(type)
            self._ref = icalproperty_new(kind)

	    if type.find("X-") == 0:
                icalproperty_set_x_name(self._ref, type)

        if self._ref == None or self._ref == 'NULL':
            raise Property.ConstructorFailedError("Failed to construct Property: %s (%s)"%(type, ref))
            
        self._deleted = 0;

        # Initialize all of the required keys


    def __del__(self):

        self._deleted = 1;

        if not self._deleted and \
           self.ref() and \
           icalproperty_get_parent(self.ref()) == 'NULL':
            
            icalproperty_free(self.ref())
            
    def name(self,v=None):
        """ Return the name of the property """
        return icalproperty_get_property_name(self._ref)

    def ref(self,v=None):
        """ Return the internal reference to the libical icalproperty """
        if(v != None):

            if not self._deleted and self._ref and \
               icalproperty_get_parent(self._ref) == 'NULL':
                
                icalproperty_free(self._ref)

            self._ref = v

        return self._ref


    def value(self,v=None, kind = None):
        """ Return the RFC2445 representation of the value """

        if(v != None):
            
            if kind != None:
                # Get the default kind of value for this property 
                default_kind = icalvalue_kind_to_string(
                    icalproperty_kind_to_value_kind(
                        icalproperty_string_to_kind(self.name())))

                if(kind != default_kind):
                    self.__setitem__('VALUE',kind)
                vt = kind
            elif self.__getitem__('VALUE'):
                vt = self.__getitem__('VALUE')
                print "###########", self
            else:
                vt = 'NO' # Use the kind of the existing value


            icalerror_clear_errno()

            #e1=icalerror_supress("MALFORMEDDATA")
            if (self.name() == None or self.name().find("X-") == 0) and type(v) is StringType:
                v = icallangbind_quote_as_ical(v)

            if isinstance(v, unicode):
                v = v.encode('utf8')

            icalproperty_set_value_from_string(self._ref,str(v),vt)
            #icalerror_restore("MALFORMEDDATA",e1)

            if error_type() != "NO":
                raise Property.UpdateFailedError(error_type())

            s = icalproperty_get_value_as_string(self._ref)

        return icalproperty_get_value_as_string(self._ref)

    def parameters(self):
        """
	Return a list of parameters
        """

        params = [] 

	p = icallangbind_get_first_parameter(self._ref) 
	
	while p != None:
		kv = split(icalparameter_as_ical_string(p),'=',2)
		params.append(kv[0])
		p = icallangbind_get_next_parameter(self._ref)

	return params

    def as_ical_string(self):
        "Return the property in iCalendar text format."
        return icalproperty_as_ical_string(self._ref)

    def __getitem__(self,key):
        """ Return property values by name """
        key = upper(key)
        str = icalproperty_get_parameter_as_string(self._ref,key)
        
        if(str == 'NULL'): return None

        return str

    def __setitem__(self,key,value):
        """ Set Property Values by Name """
        key = upper(key)

        icalproperty_set_parameter_from_string(self._ref,key,value)

        return self.__getitem__(key)

    def __delitem__(self,key):
        """ Remove Property Values by Name """
        key = upper(key)

	if self.__getitem__(key):
		icalproperty_remove_parameter_by_name(self._ref,key)

    def __str__(self):

        str = self.as_ical_string()
        return re.sub('\r?\n ?','',str)

    def __cmp__(self, other):
        s_str = str(self)
        o_str = str(other)

        return cmp(s_str,o_str)


class RecurrenceSet: 
    """
    Represents a set of event occurrences. This
    class controls a component's RRULE, EXRULE, RDATE and EXDATE
    properties and can produce from them a set of occurrences. 
    """

    def __init__(self):
        pass

    def include(self, **params): 
        """ 
        Include a date or rule to the set. 

        Use date= or pass in a
        Time instance to include a date. Included dates will add an
        RDATE property or will remove an EXDATE property of the same
        date.

        Use rule= or pass in a string to include a rule. Included
        rules with either add a RRULE property or remove an EXRULE
        property.

        """
        pass

    def exclude(self, **params): 
        """ 
        Exclude date or rule to the set. 

        Use date= or pass in a Time instance to exclude a
        date. Excluded dates will add an EXDATE property or will remove
        an RDATE property of the same date.

        Use rule= or pass in a string to exclude a rule. Excluded
        rules with either add an EXRULE property or remove an RRULE
        property.

        """
        pass
        
    def occurrences(self, count=None):
        """
        Return 'count' occurrences as a tuple of Time instances.
        """
        pass


