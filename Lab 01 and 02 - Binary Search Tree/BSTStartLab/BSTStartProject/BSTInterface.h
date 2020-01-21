
#include <iostream>
#include <ostream>


template <typename KeyComparable , typename Value > 
class BSTInterface
{
	// only allow pointer types for the value
	static_assert(std::is_pointer<Value>::value, "Expected a pointer");
 private:
	
 public:
	 BSTInterface() {};
	 BSTInterface(const BSTInterface & rhs) {};
	 BSTInterface(BSTInterface && rhs) {};
	 virtual ~BSTInterface() {};
		
	virtual const Value findMin() const = 0;
	virtual const Value findMax() const = 0;
	virtual bool contains(const KeyComparable & key) const = 0;
	virtual bool find(const KeyComparable & key, Value & itemFound) const = 0;
	virtual bool isEmpty() const = 0;
	virtual void printTree(std::ostream & out = cout) const = 0;		
	virtual void makeEmpty() = 0;
	virtual bool insert(Value item , KeyComparable key) = 0;
	virtual void remove(const KeyComparable & key) = 0;
		
		
		
 
};