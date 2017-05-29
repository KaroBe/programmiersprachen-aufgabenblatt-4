#ifndef BUW_LIST_HPP
#define BUW_LIST_HPP

#include <cstddef>

// List.hpp

//Deklaration des struct List
template <typename T>
class List;

//Definition des struct ListNode
template <typename T>
struct ListNode
{
	//Constructors
	ListNode() : 	m_value(),
					m_prev(nullptr),
					m_next(nullptr)
					{}

	ListNode(T const& v, ListNode* prev, ListNode* next) :
					m_value(v),
					m_prev(prev),
					m_next(next)
					{}

	//Destructor
	~ListNode(){clear();}

	//Member Variables
	T m_value;
	ListNode* m_prev;
	ListNode* m_next;
};

//Definition des struct ListIterator
template <typename T>
struct ListIterator
{
	typedef ListIterator<T> Self;

	typedef T value_pointer;
	typedef T* pointer;
	typedef T& reference;
	typedef ptrdiff_t difference_type;
	typedef std::forward_iterator_tag iterator_category;

	friend class List<T>;

	ListIterator () {}
	ListIterator(ListNode<T>* n) {}
	reference operator*()

private:
	//Pointer auf ListNode m_node, wird mit
	//nullpointer initialisiert
	ListNode<T>* m_node = nullptr;
};

//Definition des struct ConstListIterator
template<typename T>
struct ListConstIterator
{
	friend class List<T>;
	
public:
	//not implemented yet

private:
	ListNode<T>* m_node = nullptr;
};

template<typename T>
class List
{
public:

	//set aliases for data types
	typedef T value_type;

	typedef T* pointer;
	typedef const T* const_pointer;
	
	typedef T& reference;
	typedef const T& const_reference;
	
	typedef ListIterator<T> iterator;
	typedef ListConstIterator<T> const_iterator;

	//fried classes
	friend class ListIterator<T>;
	friend class ListConstIterator<T>;

	//Default-Constructor
	List() : 	m_size{0},
				m_first{nullptr},
				m_last{nullptr}
				{}

	//returns whether list is empty
	bool empty() const
	{
		return m_size == 0;
	};

	//returns number of nodes in list
	std::size_t size() const
	{
		return m_size;
	};

	//pushs element to front of list
	void push_front(value_type value)
	{
		//List empty
		if (m_size == 0)
		{
			//m_first zeigt auf das neue element
			m_first = new ListNode<T>{
				value, 		//T
				nullptr, 	//pointer auf prev
				nullptr 	//pointer auf next
			};

			//m_first und m_last zeigen auf das
			//einzige Element der Liste
			m_last = m_first;
		}

		//List not empty
		else
		{
			//former_first und m_first referenzieren
			//den front node
			ListNode<T>* former_first = m_first;

			//ListNode<T>* m_first referenziert den
			//neuen front node, dessen next der former_
			m_first = new ListNode<T>{
				value, 			//T
				nullptr, 		//pointer auf prev
				former_first 	//pointer auf next
			};

			//prev pointer des 2. elements
			//zeigt jetzt auf das front element
			former_first->m_prev = m_first;
		}

		++ m_size;
	};

	void push_front(std::vector<value_type> const& values)
	{
		for (value_type value : values)
			push_front(value);
	};

	//pushs element to back of list
	void push_back(value_type value)
	{
		//List empty
		if (m_size == 0)
		{
			push_front(value);
		}

		//List not empty
		else
		{
			ListNode<T>* former_last = m_last;

			m_last = new ListNode<T>{
				value, former_last, nullptr};

			former_last->m_next = m_last;
		}

		++ m_size;
	};

	//removes front element of list and returns
	//it's value
	value_type pop_front()
	{
		//List empty
		if (m_size == 0)
		{
			//ERROR???
		}
		//List has one element
		else if (m_size == 1)
		{
			//erstes element zwischenspeichern
			ListNode<T>* former_first = m_first;
			
			m_first = nullptr;
			m_last = nullptr;

			--m_size;
			return former_first->m_value;
			
		}
		//List has multiple elements
		else
		{				
			//erstes element zwischenspeichern
			ListNode<T>* former_first = m_first;
			
			//front zeigt auf das element auf das next
			//des ehm. front auch zeigt
			m_first = former_first->m_next;

			//das prev element von front wird auf nullptr umgebogen
			m_first->m_prev = nullptr;

			/*
			delete former_first;
			former_first = nullptr;
			*/

			-- m_size;
			return former_first->m_value;
		}
	};
	
	//removes front element of list and returns
	//it's value
	value_type pop_back()
	{
		//List empty
		if (m_size == 0)
		{
			//ERROR???
		}
		//List has one element
		else if (m_size == 1)
		{
			return pop_front();	
		}
		//List has multiple elements
		else
		{				
			//erstes element zwischenspeichern
			ListNode<T>* former_last = m_last;
			
			//front zeigt auf das element auf das next
			//des ehm. front auch zeigt
			m_last = former_last->m_prev;

			//das prev element von front wird auf nullptr umgebogen
			m_last->m_next = nullptr;

			/*
			delete former_first;
			former_first = nullptr;
			*/

			-- m_size;
			return former_last->m_value;
		}
	};
	
	//returns value of front element
	value_type front() const
	{
		return m_first->m_value;
	};
	
	//returns value of back element
	value_type back() const
	{
		return m_last->m_value;
	}

	void clear()
	{
		while(!empty())
			pop_front();
	}



private:
	//std::size_t is type returned by sizeof()
	//functions
	//initializes m_size with 0
	std::size_t m_size = 0;

	//pointers to first and last element of list
	ListNode<T>* m_first = nullptr;
	ListNode<T>* m_last = nullptr;
};

#endif //#define BUW_LIST_HPP