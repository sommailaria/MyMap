# Custom Hash Map — C++

## Overview

A custom hash map implemented in C++ to explore the internal structure of hash-based associative containers.

Developed as a hands-on learning project, the implementation focuses on hashing, collision resolution, dynamic resizing, and memory management without relying on `std::unordered_map`.

## Features

- **Templated key-value storage:** Supports different key and value types through `HashMap<Key, Value>`.
- **Hash-based indexing:** Uses `std::hash<Key>` to calculate bucket indices.
- **Collision resolution:** Implements separate chaining using singly linked lists.
- **Dynamic rehashing:** Doubles the number of buckets when the load factor exceeds 0.75.
- **Insertion:** Adds new key-value pairs and prevents duplicate keys.
- **Lookup:** Searches for elements by key, returning a pointer to the matching element or `nullptr` if no match exists.
- **Removal:** Removes entries while correctly updating linked-list pointers.
- **Memory management:** Explicitly allocates and releases dynamically created nodes.
- **Bucket inspection:** Provides a method to display the internal distribution of elements.

## Technical Concepts

- C++ templates
- Hash tables and hash functions
- Collision resolution through separate chaining
- Singly linked lists
- Dynamic memory management
- Load factors and rehashing
- Pointers and resource ownership
- Algorithmic complexity

## Testing

The implementation includes tests covering:

- Insertion of key-value pairs
- Hash collisions and automatic rehashing
- Duplicate key rejection
- Lookup of existing and missing keys
- Removal of existing and missing entries
- Different key and value types, including integer and string keys

## Learning Objectives

This project was developed to understand how hash-based data structures store, organize, and retrieve elements efficiently.

Implementing collision handling, node allocation, and automatic rehashing provided practical experience with pointer manipulation, memory ownership, and the performance considerations involved in building associative containers.

## Limitations

This is an educational implementation rather than a complete replacement for `std::unordered_map`. It does not implement the full standard container interface and currently uses a simplified approach to memory and ownership management.
