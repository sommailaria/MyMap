#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <functional>

template <typename Key, typename Value>
struct Element
{
    Key key;
    Value mappedValue;
    Element<Key,Value>* next = nullptr;
};

template <typename Key, typename Value>
struct Bucket
{
    Element<Key,Value>* start = nullptr;
    
};

template <typename Key, typename Value>
class HashMap
{
    std::vector<Bucket<Key,Value>> bucketContainer;
    int numberOfEntries;
    double maxLoadFactor;

public:

    // Constructor
    HashMap()
    {
        bucketContainer.resize(5);
        numberOfEntries = 0;
        maxLoadFactor = 0.75;
    }
    // Destructor 
    ~HashMap() 
    {
        for (std::size_t i = 0; i < bucketContainer.size(); i++)
        {
            Element<Key,Value>* current = bucketContainer[i].start;
            while (current != nullptr)
            {
                Element<Key,Value>* temp = current->next;
                delete current;
                current = temp;

            }
        }
        
    }

    // Hash function
   std::size_t hash(const Key& key)
    {
       std::hash<Key> hasher;
       std::size_t hashValue = hasher(key);
       std::size_t bucketIndex = hashValue % bucketContainer.size();

        return bucketIndex;
    }

    // Add a new key/value pair
    void add(const Key& key, const Value& mappedValue)
    {
        std::size_t bucketIndex = hash(key);

        // Check whether the key already exists
        Element<Key,Value>* current = bucketContainer[bucketIndex].start;

        for (; current != nullptr; current = current->next)
        {
            if (current->key == key)
            {
                return;
            }
        }

        // Create the new element
        Element<Key,Value>* bucketMember = new Element<Key,Value>;

        bucketMember->key = key;
        bucketMember->mappedValue = mappedValue;

        // Add the element to the front of the chain
        bucketMember->next = bucketContainer[bucketIndex].start;
        bucketContainer[bucketIndex].start = bucketMember;

        numberOfEntries++;

        // Check the load factor
        double currentLoadFactor =
            static_cast<double>(numberOfEntries) / bucketContainer.size();

        if (currentLoadFactor > maxLoadFactor)
        {
            rehash();
        }
    }

    // Rehash
    void rehash()
    {
        std::size_t newNumberOfBuckets = bucketContainer.size() * 2;
        std::vector<Bucket<Key,Value>> newBucketContainer;
        newBucketContainer.resize(newNumberOfBuckets);

        for (std::size_t i = 0; i < bucketContainer.size(); i++)
        {
            Element<Key, Value>* current = bucketContainer[i].start;

            while (current != nullptr)
            {
                std::hash<Key> hasher;
                std::size_t hashValue = hasher(current->key);
                std::size_t newBucketIndex = hashValue % newNumberOfBuckets;
                Element<Key, Value>* temp = current->next;
                current->next = newBucketContainer[newBucketIndex].start;
                newBucketContainer[newBucketIndex].start = current;
                current = temp;
            }
        }

        bucketContainer = std::move(newBucketContainer);
       
    }

    Element<Key,Value>* findValue(const Key& key)
    {
        std::size_t bucketIndex = hash(key);
        Element<Key,Value>* current = bucketContainer[bucketIndex].start;
        while (current != nullptr)
        {
            if (current->key == key)
            {
                return current;
            }
            current = current->next;
        }
        return nullptr;
        
    }

	void remove(const Key& key) {

        std::size_t bucketIndex = hash(key);
		Element<Key,Value>* current = bucketContainer[bucketIndex].start;
		Element<Key,Value>* previous = nullptr;
		while (current != nullptr)
		{
			if (current->key == key)
			{
				if (previous == nullptr)
				{
					bucketContainer[bucketIndex].start = current->next;
				}
				else
				{
					previous->next = current->next;

				}

				delete current;
				numberOfEntries--;
				return;
			}

			previous = current;
			current = current->next;

		}


	} 

    // Print the contents of each bucket
    void printBuckets()
    {
        for (std::size_t i = 0; i < bucketContainer.size(); i++)
        {
            Element<Key,Value>* current =
                bucketContainer[i].start;

            std::cout << "Bucket " << i << ": ";

            while (current != nullptr)
            {
                std::cout << current->key << " " << current->mappedValue << " ";
                current = current->next;
            }

            std::cout << '\n';
        }
    }
};

int main() {
    // Testing rehash with a collision
    HashMap<int, std::string> map;
    map.add(12, "A");
    map.add(17, "B");
    map.add(22, "C");
    map.add(21, "D");

    map.printBuckets();

    // Test duplicate rejection
    HashMap<int,std::string> myMap;
    myMap.add(12, "A");
    myMap.add(12, "NEW");

    myMap.printBuckets();


    // Test find item by key 

    Element<int, std::string>* result = map.findValue(17);

    if (result != nullptr)
    {
        std::cout << result->mappedValue << '\n';
    }

    if (map.findValue(99) == nullptr)
    {
        std::cout << "Key not found\n";
    }

    // Test remove()
    HashMap<int,std::string> thirdMap;

    thirdMap.add(32, "A");
    thirdMap.add(22, "B");
    thirdMap.add(12, "C");

    thirdMap.remove(12);
    thirdMap.printBuckets();
    thirdMap.remove(99);
    thirdMap.printBuckets();

    // Testing new key setup 
    HashMap<std::string, int> studentGraduations;
    studentGraduations.add("Anna", 2022);
    studentGraduations.add("Marco", 2025);
    studentGraduations.add("Vittoria", 2023);
    studentGraduations.add("Anna", 2024);
    studentGraduations.add("Luca", 2023);
    studentGraduations.printBuckets();

    // Testing retrieve by Value 

    Element<std::string, int>* query = studentGraduations.findValue("Marco");
    if (query != nullptr)
    {
        std::cout << query->mappedValue << '\n';
    }

    if (studentGraduations.findValue("Giulia") == nullptr)
    {
        std::cout << "Key not found\n";
    }

   
   




}
