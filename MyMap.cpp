#include <iostream>
#include <string>

template <typename Value>
struct Element
{
    int key;
    Value mappedValue;
    Element<Value>* next = nullptr;
};

template <typename Value>
struct Bucket
{
    Element<Value>* start = nullptr;
};

template <typename Value>
class HashMap
{
    Bucket<Value>* bucketContainer;
    int numberOfBuckets;
    int numberOfEntries;
    double maxLoadFactor;

public:

    // Constructor
    HashMap()
    {
        numberOfBuckets = 5;
        bucketContainer = new Bucket<Value>[numberOfBuckets];
        numberOfEntries = 0;
        maxLoadFactor = 0.75;
    }
    // Destructor 
    ~HashMap() 
    {
        for (int i = 0; i < numberOfBuckets; i++)
        {
            Element<Value>* current = bucketContainer[i].start;
            while (current != nullptr)
            {
                Element<Value>* temp = current->next;
                delete current;
                current = temp;

            }
        }
        delete[] bucketContainer;
    }

    // Hash function
    int hash(const int& key)
    {
        int bucketIndex = key % numberOfBuckets;
        return bucketIndex;
    }

    // Add a new key/value pair
    void add(const int& key, const Value& mappedValue)
    {
        int bucketIndex = hash(key);

        // Check whether the key already exists
        Element<Value>* current = bucketContainer[bucketIndex].start;

        for (; current != nullptr; current = current->next)
        {
            if (current->key == key)
            {
                return;
            }
        }

        // Create the new element
        Element<Value>* bucketMember = new Element<Value>;

        bucketMember->key = key;
        bucketMember->mappedValue = mappedValue;

        // Add the element to the front of the chain
        bucketMember->next = bucketContainer[bucketIndex].start;
        bucketContainer[bucketIndex].start = bucketMember;

        numberOfEntries++;

        // Check the load factor
        double currentLoadFactor =
            static_cast<double>(numberOfEntries) / numberOfBuckets;

        if (currentLoadFactor > maxLoadFactor)
        {
            rehash();
        }
    }

    // Rehash
    void rehash()
    {
        int newNumberOfBuckets = numberOfBuckets * 2;

        Bucket<Value>* newBucketContainer =
            new Bucket<Value>[newNumberOfBuckets];

        for (int i = 0; i < numberOfBuckets; i++)
        {
            Element<Value>* current = bucketContainer[i].start;

            while (current != nullptr)
            {
                int newBucketIndex =
                    current->key % newNumberOfBuckets;

                Element<Value>* temp = current->next;

                current->next =
                    newBucketContainer[newBucketIndex].start;

                newBucketContainer[newBucketIndex].start =
                    current;

                current = temp;
            }
        }

        delete[] bucketContainer;
        bucketContainer = newBucketContainer;
        numberOfBuckets = newNumberOfBuckets;
    }

    Element<Value>* findValue(const int& key)
    {
        int bucketIndex = hash(key);
        Element<Value>* current = bucketContainer[bucketIndex].start;
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

	void remove(const int& key) {

		int bucketIndex = hash(key);
		Element<Value>* current = bucketContainer[bucketIndex].start;
		Element<Value>* previous = nullptr;
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
        for (int i = 0; i < numberOfBuckets; i++)
        {
            Element<Value>* current =
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
    HashMap<std::string> map;
    map.add(12, "A");
    map.add(17, "B");
    map.add(22, "C");
    map.add(21, "D");

    map.printBuckets();

    // Test duplicate rejection
    HashMap<std::string> myMap;
    myMap.add(12, "A");
    myMap.add(12, "NEW");

    myMap.printBuckets();


    // Test find item by key 

    Element<std::string>* result = map.findValue(17);

    if (result != nullptr)
    {
        std::cout << result->mappedValue << '\n';
    }

    if (map.findValue(99) == nullptr)
    {
        std::cout << "Key not found\n";
    }

    // Test remove()
    HashMap<std::string> thirdMap;

    thirdMap.add(32, "A");
    thirdMap.add(22, "B");
    thirdMap.add(12, "C");

    thirdMap.remove(12);
    thirdMap.printBuckets();
    thirdMap.remove(99);
    thirdMap.printBuckets();

}
