## @file SeqADT.py
#  @title SeqADT
#  @author Alexie McDonald
#  @date 2018-01-12

## @brief An Abstract Data Type that represents a Sequence
#  @details A sequence ADT contains methods involving the sequence's elements (add, remove, set, get, size, check for value).
class SeqT:
    ## @brief Sequence Constructor
    #  @details Initializes a SeqT object with an empty state array
    #  @return A SeqT object that has an empty state.
    def __init__(self):
        self.__state = []
    ## @brief Add an element to the SeqT object's state array
    #  @details Checks if the index, i, is valid for the array. Index i is valid if it's within the bounds of [0,len(state)], as well as if it's at the end of the array or within the existing array elements.
    #  @param i The desired index where the float v will be added
    #  @param v The float to be added to the index at place i
    def add(self, i, v):
        if (i == len(self.__state)):
            self.__state.append(v);
        elif (i < len(self.__state) and i > 0):
            self.__state.insert(i, v);
        else:
              print ("Invalid index")
    ## @brief Remove an element from the SeqT object's state array
    #  @details Removes the element at index i from the SeqT object's state array granted index i is within the bounds of [0,len(state)]
    #  @param i The desired index in the SeqT object's state where the value will be removed
    def rm(self, i):
        if (i >= 0 and i < len(self.__state)):
            del self.__state[i]
    ## @brief Set an element in the SeqT object's state array to a new value
    #  @details Checks if the index, i, is within the bounds of [0,len(state)], then changes the value at that index to v.
    #  @param i The desired index where the float v, will placed
    #  @param v The float to be added to the index at place i
    def set(self, i, v):
        if (i < len(self.__state)):
            self.__state[i] = v
    ## @brief Gets the value of the SeqT object's state array at index i
    #  @details Checks if the index is within the bounds of [0,len(state)], then if so, it returns the value of the object's state at that index.
    #  @param i The desired index in the object's state array where the value will be fetched
    #  @return The value of the object's state array at index i
    def get(self, i):
        if (i >= 0 and i < len(self.__state)):
            return self.__state[i]
        else:
            return -1
    ## @brief Gets the length of the SeqT object's state array
    #  @details Returns the number of elements currently contained within the object's state array
    #  @return The length of the SeqT object's state array
    def size(self):
        return len(self.__state)
    ## @brief Gets the index of v in the SeqT object's state array
    #  @details Searches the object's state array for element v, and if it's in the array, it returns it's index
    #  @return The index of element v in the object's state array. If not found, returns -1
    def indexInSeq(self, v):
        try:
            return self.__state.index(v);
        except ValueError:
            return -1
    
            
