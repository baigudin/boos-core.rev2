/** 
 * DOM Element interface.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_API_ELEMENT_HPP_
#define BOOS_API_ELEMENT_HPP_

#include "boos.Types.hpp"
#include "boos.util.String.hpp"

namespace api
{  
  class Element
  {
    typedef ::util::String String;

  public:

    /**
     * Destructor.
     */
    virtual ~Element(){}
    
    /** 
     * Inserts an element as the last child of each element.
     *
     * @param node a name of new element.
     * @return new inserted element.
     */  
    virtual Element* insert(const String& node) = 0;

    /** 
     * Inserts an element as the last child of each element.
     *
     * @param node a new element.
     * @return new inserted element.
     */  
    virtual Element* insert(Element* node) = 0;
    
    /** 
     * Inserts an element as the first child of each element.   
     *
     * @param node a name of new element.
     * @return new inserted element.
     */  
    virtual Element* prepend(const String& node) = 0;

    /** 
     * Inserts an element as the first child of each element.   
     *
     * @param node a new element.
     * @return new inserted element.
     */  
    virtual Element* prepend(Element* node) = 0;
    
    /** 
     * Inserts an element after each element.
     *   
     * @param node a name of new element.
     * @return new inserted element.
     */  
    virtual Element* after(const String& node) = 0;

    /** 
     * Inserts an element after each element.
     *   
     * @param node a new element.
     * @return new inserted element.
     */  
    virtual Element* after(Element* node) = 0;
    
    /** 
     * Inserts an element before each element.
     *   
     * @param node a name of new element.
     * @return new inserted element.
     */   
    virtual Element* before(const String& node) = 0;

    /** 
     * Inserts an element before each element.
     *   
     * @param node a new element.
     * @return new inserted element.
     */   
    virtual Element* before(Element* node) = 0;
    
    /** 
     * Removes each element.
     * 
     * @return removed elements.
     */   
    virtual Element* remove() = 0;
    
    /** 
     * Returns root elements of each element.
     * 
     * @return root elements.
     */
    virtual Element* getRoot() = 0;
    
    /**
     * Returns the number of elements.
     *
     * @return number of elements
     */  
    virtual int32 length() = 0;
    
    /**
     * Returns previous elements.
     *
     * @return previous elements, a NULL value is not returning.
     */  
    virtual Element* prev() = 0;
    
    /**
     * Returns next elements.
     *
     * @return next elements, a NULL value is not returning.
     */  
    virtual Element* next() = 0;
    
    /**
     * Returns child elements.
     *
     * @param number a sequence number of child elements.
     * @return child elements, a NULL value is not returning.
     */  
    virtual Element* child(int32 number) = 0;
    
    /**
     * Returns last child elements.
     *
     * @return last child elements, a NULL value is not returning.
     */  
    virtual Element* last() = 0;
    
    /**
     * Returns parent elements.
     *
     * @return parent elements, a NULL value is not returning.
     */  
    virtual Element* parent() = 0;
    
    /** 
     * Returns a HTML content of the first element.
     *
     * @return content of the first element.
     */     
    virtual String html() = 0;
    
    /** 
     * Sets a HTML content of each element.
     *
     * @param html new HTML string.
     * @return this list.
     */     
    virtual Element* html(const String& html) = 0;       
    
    /**
     * Returns any user data of each element.
     *
     * @return a data of the first element.   
     */  
    virtual String data() = 0;
    
    /**
     * Sets any user data of each element.
     *
     * @param data user data.
     * @return this list.   
     */  
    virtual Element* data(const String& data) = 0;      
    
    /** 
     * Returns a string key.
     *
     * @return a key of the last element.
     */
    virtual String key() = 0;
    
    /** 
     * Sets a string key.
     *
     * @param key a string key.
     * @return this list.
     */
    virtual Element* key(const String& key) = 0;      
    
    /**
     * Returns a children of each element.
     *
     * @return children elements of each element.
     */
    virtual Element* children() = 0;  
    
    /**
     * Removes elements from this list for matched elements by the query.
     *
     * Method removes elements from this list by given query.
     * Requested child elements from query string are not processing.
     *
     * @param query query string.
     * @return new list.
     */
    virtual Element* nott(const String& query) = 0;
    
    /**
     * Filters this list elements by the query.
     *
     * Method returns elements from this list which matching by the query.
     * Requested child elements from query string are not processing.
     *
     * @param query query string.
     * @return new list.
     */  
    virtual Element* filter(const String& query) = 0;
    
    /**
     * Searches parent elements.
     *
     * @param query query string.
     * @return search result.
     */    
    virtual Element* parents(const String& query) = 0;
    
    /**
     * Searches child elements.
     *
     * @param query query string.
     * @return search result.
     */   
    virtual Element* find(const String& query) = 0;
    
    /** 
     * Adds new class attribute value for this list elements.
     *
     * Sets new value for class attribute. 
     * If class attribute is set, the method adds new value of attribute.
     *
     * @param value new class attribute value.
     * @return this list.
     */   
    virtual Element* addClass(const String& value) = 0;
    
    /** 
     * Removes class attribute value for this list elements.
     *
     * @param value class attribute value.
     * @return this list.
     */   
    virtual Element* removeClass(const String& value) = 0;
    
    /**
     * Tests if each element has a given class name.
     *
     * @param name class name.
     * @return true if element has given attribute value.
     */
    virtual bool hasClass(const String& name) = 0;  
    
    /** 
     * Returns attribute value.
     *
     * @param string with attribute name.
     * @return a current value.
     */   
    virtual String attr(const String& name) = 0;
    
    /** 
     * Sets attributes and its values.
     *
     * Sets new value for given attribute. 
     * If attribute is set, the method sets new given value of attribute.   
     *
     * @param name  string with attribute name.
     * @param value given attribute name value. 
     * @return this element.      
     */   
    virtual Element* attr(const String& name, const String& value) = 0;      
    
    /** 
     * Adds new values to an attributes for each element.
     *
     * Sets new value for an attribute. 
     * If given attribute is set, the method adds new value of this attribute.
     *
     * @param name  string with attribute name.
     * @param value given attribute name value. 
     * @return this list.
     */  
    virtual Element* addAttr(const String& name, const String& value) = 0;
    
    /** 
     * Removes attributes for each element.
     *
     * @param name  string with attribute name.
     * @return this list.
     */    
    virtual Element* removeAttr(const String& name) = 0;  
    
    /** 
     * Returns elements array.
     *
     * The method returns an elements array as vector if argument in not given.
     *
     * @return elements array.
     */  
    virtual Element** get() = 0;
    
    /** 
     * Returns an element of this list.
     *
     * If argument greater than or equal zero, method returns an element with given index.
     * If argument less than zero, method counts a index from the end of the list.
     * For example: [-1] returns the last element, [-2] returns the penultimate element, etc.
     *
     * @param index element index of this elements list.
     * @return an element.
     */  
    virtual Element* get(int32 index) = 0;
    
    /**
     * Returns a HTML element name of the first element.
     *
     * @return a current value or this element.
     */  
    virtual String getElementTagName() = 0;
    
    /**
     * Returns an element with the specified ID.
     *
     * @param id ID value.
     * @return searched element.
     */   
    virtual Element* getElementById(const String& id) = 0;
    
    /**
     * Returns child elements with the specified ID of each element.
     *
     * Note: Any valid HTML documents must have only one element with unique identifier.
     *
     * @param id ID value.
     * @return search result.  
     */  
    virtual Element* getElementsById(const String& id) = 0;
    
    /**
     * Returns parent elements with the specified ID of each element.
     *
     * Note: Any valid HTML documents must have only one element with unique identifier.
     *
     * @param id ID value.
     * @return search result.
     */   
    virtual Element* getParentsById(const String& id) = 0;
    
    /**
     * Returns child elements with the specified element name of each element.
     *
     * @param name element name.
     * @return search result.
     */    
    virtual Element* getElementsByTagName(const String& name) = 0;
    
    /**
     * Returns parent elements with the specified element name of each element.
     *
     * @param name element name.
     * @return search result.
     */  
    virtual Element* getParentsByTagName(const String& name) = 0;
    
    /**
     * Returns child elements with the specified class name of each element.
     *
     * @param name class name.
     * @return search result.
     */   
    virtual Element* getElementsByClassName(const String& name) = 0;
    
    /**
     * Returns parent elements with the specified class name of each element.
     *
     * @param name class name.
     * @return search result.
     */   
    virtual Element* getParentsByClassName(const String& name) = 0;
    
    /**
     * Returns child elements with the specified attribute name and its value of each element.
     *
     * @param name  attribute name.
     * @param value attribute value.
     * @return search result.
     */  
    virtual Element* getElementsByAttr(const String& name, const String& value) = 0;
    
    /**
     * Returns parent elements with the specified attribute name and its value of each element.
     *
     * @param name  attribute name.
     * @param value attribute value.
     * @return search result.
     */  
    virtual Element* getParentsByAttr(const String& name, const String& value) = 0;
    
    /**
     * Tests if each element has a given ID value.
     *
     * @param id ID value.
     * @return true if element has given attribute value.
     */   
    virtual bool isElementsId(const String& id) = 0;
    
    /**
     * Tests if each element has a given element name.
     *
     * @param name element name.
     * @return true if element has given attribute value.   
     */ 
    virtual bool isElementsTagName(const String& name) = 0;
    
    /**
     * Tests if each element has a given class name.
     *
     * @param name class name.
     * @return true if element has given attribute value.
     */  
    virtual bool isElementsClassName(const String& name) = 0;
    
    /**
     * Tests if each element has a given attribute name and value.
     *
     * @param name  attribute name.
     * @param value attribute value.
     * @return true if element has given attribute value.
     */   
    virtual bool isElementsAttr(const String& name, const String& value) = 0;

  };
}
#endif // BOOS_API_ELEMENT_HPP_
