## @file testSeqs.py
#  @author Shengchen Zhou
#  @brief Provides case tests for SeqADT.py and CurveADT.py
#  @data 1/21/2018

from SeqADT import *
from CurveADT import *

# for testing floating point equality after arithmetic
# from Python development documentation: 
#   https://www.python.org/dev/peps/pep-0485/#proposed-implementation
def isClose(a, b, rel_tol = 1e-09, abs_tol = 0.0):
    return abs(a - b) <= max(rel_tol * max(abs(a), abs(b)), abs_tol)

# @brief Tests the add method of the SeqT class
# @details Checks add will raise ValueError and will add value
#         to the right place, and changes the size.
def test_add():
  global testTot, passed
  testTot += 1
  s1 = SeqT()
  try:
    s1.add(3, 0.5)
    print("add test FAILED.")
    return
  except ValueError:
    pass

  try:
    s1.add(-1, 0.5)
    print("add test FAILED.")
    return
  except ValueError:
    pass

  try:
    s1.add(0, 0.3)
    assert s1.get(0) == 0.3
    assert s1.size() == 1
    s1.add(0, 0.2)
    assert s1.get(0) == 0.2
    assert s1.size() == 2
    s1.add(2, 0.1)
    assert s1.get(2) == 0.1
    assert s1.size() == 3
    s1.add(1, 0.5)
    assert s1.get(1) == 0.5
    assert s1.get(3) == 0.1
    assert s1.size() == 4
    passed += 1
    print("add test PASSED")
  except AssertionError:
    print("add test FAILED")

# @brief Tests the rm method of the SeqT class
# @details Checks rm will raise ValueError and will rm value
#         to the right place, and changes the size.
def test_rm():
  global testTot, passed
  testTot += 1
  s1 = SeqT()
  try:
    s1.rm(0)
    print("rm test FAILED")
    return
  except ValueError:
    pass

  try:
    s1.rm(-1)
    print("rm test FAILED")
    return
  except ValueError:
    pass

  s1.add(0, 1.1)
  s1.add(1, 2.2)
  s1.add(2, 3.3)
  s1.add(3, 4.4)
  s1.add(4, 5.5)
  try:
    assert s1.size() == 5
    s1.rm(4)
    assert s1.size() == 4
    s1.rm(1)
    assert s1.size() == 3
    assert s1.get(1) == 3.3
    passed += 1
    print("rm test PASSED")
  except AssertionError:
    print("rm test FAILED")

# @brief Tests the set method of the SeqT class
# @details Checks set will raise ValueError and will set value
#         to the right place, and won't change the size.
def test_set():
  global testTot, passed
  testTot += 1
  s1 = SeqT()
  try:
    s1.set(0, 0.0)
    print("set test FAILED")
    return
  except ValueError:
    pass

  try:
    s1.set(-1, 0.5)
    print("set test FAILED")
    return
  except ValueError:
    pass

  s1.add(0, 1.1)
  s1.add(1, 2.2)
  s1.add(2, 3.3)
  s1.add(3, 4.4)
  s1.add(4, 5.5)
  try:
    assert s1.size() == 5
    assert s1.get(4) == 5.5
    s1.set(4, 6.6)
    assert s1.size() == 5
    assert s1.get(4) == 6.6
    s1.set(0, 0.1)
    assert s1.get(0) == 0.1
    passed += 1
    print("set test PASSED")
  except AssertionError:
    print("set test FAILED")

# @brief Tests the indexInSeq method of the SeqT class
# @details Checks indexInSeq will find the corresponding index
#         of value correctly.
def test_indexInSeq():
  global testTot, passed
  testTot += 1
  s1 = SeqT()
  try:
    assert s1.indexInSeq(5.0) == -1
  except AssertionError:
    print("indexInSeq test FAILED")
    return

  s1.add(0, 1.1)
  s1.add(1, 2.2)
  s1.add(2, 3.3)
  s1.add(3, 4.4)
  s1.add(4, 5.5)
  try:
    assert s1.size() == 5
    assert s1.indexInSeq(5.0) == 3
    assert s1.indexInSeq(4.4) == 2
    assert s1.indexInSeq(6.6) == 4
    passed += 1
    print("indexInSeq test PASSED")
  except AssertionError:
    print("indexInSeq test FAILED")

# @brief Tests the linVal method of the CurveT class
# @details Checks linVal will do the right caculation with linear interpolation.
def test_linVal():
  global testTot, passed
  testTot += 1
  filename = "curve.txt"
  with open(filename, "w") as f:
    f.write("1.0, 3.0\n")
    f.write("2.0, 4.0\n")
    f.write("3.0, 5.0\n")
    f.write("4.0, 6.0\n")
    f.close()
  try:
    c1 = CurveT(filename)
    assert c1.linVal(1.5) == 3.5
    assert c1.linVal(2.5) == 4.5
    passed += 1
    print("linVal test PASSED")
  except Exception:
    print("linVal test FAILED")

# @brief Tests the quadVal method of the CurveT class
# @details Checks quadVal will do the right caculation with quadratic interpolation.
def test_quadVal():
  global testTot, passed
  testTot += 1
  filename = "curve.txt"
  with open(filename, "w") as f:
    f.write("-1.0, 0.0\n")
    f.write("0.0, 4.0\n")
    f.write("1.0, 0.0\n")
    f.close()
  try:
    c1 = CurveT(filename)
    assert c1.quadVal(0.0) == 4.0
    assert c1.quadVal(-3.0) == -32.0
    assert c1.quadVal(3.0) == -32.0
    passed += 1
    print("quadVal test PASSED")
  except Exception:
    print("quadVal test FAILED")

# @brief Tests the npolyVal method of the CurveT class
# @details Checks npolyVal will do the right caculation with 2 degree interpolation.
def test_npolyVal1():
  global testTot, passed
  testTot += 1
  filename = "curve.txt"
  with open(filename, "w") as f:
    f.write("-1.0, 0.0\n")
    f.write("0.0, 4.0\n")
    f.write("1.0, 0.0\n")
    f.close()

  try:
    c1 = CurveT(filename)
    assert isClose(c1.npolyVal(2, 0.0), 4.0)
    assert isClose(c1.npolyVal(2, -3.0), -32.0)
    assert isClose(c1.npolyVal(2, 3.0), -32.0)
    passed += 1
    print("npolyVal test PASSED")
  except Exception:
    print("npolyVal test FAILED")

# @brief Tests the npolyVal method of the CurveT class
# @details Checks npolyVal will do the right caculation with different degree interpolation.
def test_npolyVal2():
  global testTot, passed
  testTot += 1
  filename = "curve.txt"
  with open(filename, "w") as f:
    f.write("-1.0, 0.0\n")
    f.write("0.0, 4.0\n")
    f.write("1.0, 0.0\n")
    f.write("3.0, 6.0\n")
    f.write("5.0, 7.0\n")
    f.write("10.0, 55.0\n")
    f.write("15.0, 25.0\n")
    f.close()

  try:
    c1 = CurveT(filename)
    assert isClose(c1.npolyVal(6, 0.0), 4.0)
    assert isClose(c1.npolyVal(6, -3.0), -213.342285714)
    assert isClose(c1.npolyVal(6, 3.0), 6.0)
    assert isClose(c1.npolyVal(5, 3.0), 4.59152210266)
    passed += 1
    print("npolyVal test PASSED")
  except Exception:
    print("npolyVal test FAILED")

testTot, passed = 0, 0

test_add()
test_rm()
test_set()
test_indexInSeq()
test_linVal()
test_quadVal()
test_npolyVal1()
test_npolyVal2()

print('\n%d of %d tests passed.' % (passed, testTot))
