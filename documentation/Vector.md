# Vector


## NOTE: 
- Vectors do NOT automatically resize, they must be MANUALLY resized before insertion and optionally after a deletion
- Vectors may hold ANY datatype without any modification to the library (including structs or unions)

- As an array structure, frequent insertions or deletions anywhere except the back of the vector are computationally costly

## Functions:

- Initialising a vector

  Must be done before usage

```c
Vector vector;
if(vector_initialise(&vector, sizeof(int)) == false) {
  printf("Failed to initialise vector");
}

/*
The code above:
  - Instantiates a Vector named 'vector'
  - Initialises it to hold integers
  - Checks to make sure initialisation was successful
*/
```

- Resizing a vector

  Offsets the amount of items that can be held in the vector

  Can be a negative or positive number - where negative offsets shrink the vector (excess memory automatically freed)


```c
Vector vector;
//Initialisation
if(vector_resize(&vector, 10) == false) {
  printf("Vector resizing failed\n);
}

/*
The code above:
  - Resizes 'vector' to hold a maximum of 10 elements
  - Checks if resizing was successful
*/
```

- Inserting into a vector

  Inserts an item into a vector at any valid index (0 -> end)



```c
Vector vector;
//Initialisation
int data = 10;
if(vector_insert_index(&vector, 0, &data) == false) {

  printf("Insertion failed\n);
}

/*
The code above:
  - Inserts the value '10' into a vector of ints called 'vector'
  - Checks if insertion was successful
*/
```



- Set an index in a vector

  Set the value of an index in a vector

```c
Vector vector;
//Initialisation
int data = 10;
int *value = (int*)(vector_set_index(&vector, 0, &data));

if(value == NULL) {
  printf("Failed to get value\n);
} else {
  printf("element: ",*(value));
}

/*
The code above:
  - Sets the zero index of the vector 'vector' to data (10)
  - Checks if the element was successfuly added
  - If the pointer is valid, it prints the value
*/
```



- Getting an item from a vector at an index

  Get a pointer to some data in the vector at an index

```c
Vector vector;
//Initialisation
int *value = (int*)(vector_get_index(&vector, 0));

if(value == NULL) {
  printf("Failed to get value\n);
} else {
  printf("element: ",*(value));
}

/*
The code above:
  - Gets the integer in 'vector' of index '0'
  - Checks if the pointer returned was NULL (indicating failure)
  - If the pointer is valid, it prints the value
*/
```


- Delete an item at an index in a vector

  Delete an element in a vector


```c
Vector vector;
//Initialisation
if(vector_delete_index(&vector, 0) == false) {
  printf("Failed to remove item from vector\n");
}

/*
The code above:
  - Removes an item from 'vector' at index '0'
  - Checks if the removal was successful
*/
```



- Destroy a vector

  Free all memory associated with a vector


```c
Vector vector;
//Initialisation
if(vector_destroy(&vector) == false) {
  printf("Failed to destroy vector\n");
}

/*
The code above:
  - Attempts to free all memory associated with 'vector'
  - Checks if the removal was successful
*/
```



- Get the end index of a vector

  Get the index of the last element in a vector


```c
Vector vector;
//Initialisation
printf("Length = %zu\n",vector_get_length(&vector));

/*
The code above:
  - Prints the index of the last element in the vector 'vector'
*/
```



- Get the size of a vector

  Get the max number of elements that can fit in a vector


```c
Vector vector;
//Initialisation
printf("Length = %zu\n",vector_get_size(&vector));

/*
The code above:
  - Prints the max capacity of the vector 'vector'
*/
```











































































