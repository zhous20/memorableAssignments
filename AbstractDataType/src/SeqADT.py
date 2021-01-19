## @file SeqADT.py
#  @author Shengchen Zhou
#  @brief Provides the SeqT ADT class for representing sequences
#  @data 1/21/2018

## @brief An ADT that represents a sequence
class SeqT:

  ## @brief SeqT constructor
  #  @details Initializes a SeqT object
  #  @param self An object pointer
  def __init__(self):
    self.__seq = []

  ## @brief Adds value v at index i
  #  @details Value could only be added within the existing sequence or
  #           immediately after the last entry in the existing sequence
  #  @param i The index to be added
  #  @param v The value to be added
  #  @exception ValueError Throws if supplied index is not valid
  def add(self, i, v):
    if i < 0 or i > len(self.__seq):
      raise ValueError("Index is not valid")
    self.__seq.insert(i, v)

  ## @brief Removes value at index i from the sequence
  #  @details index within the existing sequence
  #  @param i The index to be removed
  #  @exception ValueError Throws if supplied index is not valid
  def rm(self, i):
    if i < 0 or i >= self.size():
      raise ValueError("Index is not valid")
    self.__seq.pop(i)

  ## @brief Set the value at index i to be v
  #  @param i The index to be set
  #  @param v The value to be set
  #  @exception ValueError Throws if supplied index is not valid
  def set(self, i, v):
    if i < 0 or i >= self.size():
      raise ValueError("Index is not valid")
    self.__seq[i] = v

  ## @brief Gets value at index i
  #  @param i The index to be added
  #  @exception ValueError Throws if supplied index is not valid
  #  @return The value at index i
  def get(self, i):
    if i < 0 or i >= self.size():
      raise ValueError("Index is not valid")
    return self.__seq[i]

  ## @brief Gets the current size of the sequence
  #  @return The size
  def size(self):
    return len(self.__seq)

  ## @brief Finds the index i that s.get(i) <= v <= s.get(i+1)
  #  @param v The value need to be find
  #  @return Index i
  def indexInSeq(self, v):
    if self.size() <= 0 or self.get(0) > v:
      return -1
    for i in range(self.size() - 1):
      if self.get(i) <= v and v <= self.get(i + 1):
        return i
    return self.size() - 1
