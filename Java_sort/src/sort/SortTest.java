package sort;

import static org.junit.Assert.*;

import org.junit.AssumptionViolatedException;
import org.junit.Before;
import org.junit.Test;
import java.io.*;
import org.apache.commons.lang3.time.StopWatch;

public class SortTest 
{
  private Job[][] jobs = new Job[7][];
  
	@Before
	public void setUp() throws Exception 
	{
    jobs[0] = new Job[16];
    jobs[1] = new Job[64];
    jobs[2] = new Job[256];
    jobs[3] = new Job[1024];
    jobs[4] = new Job[4096];
    jobs[5] = new Job[16384];
    jobs[6] = new Job[65536];
    BufferedReader in = null;
    try 
    {
      in = new BufferedReader(new FileReader("data/a1_in.txt"));
      for(int i = 0; i < 7; ++i)
      {
    	  String line = in.readLine();
        String[] jobstring = line.split("},");
        for(int j = 0; j < jobstring.length; ++j)
        {
          String[] strs = jobstring[j].split(",");
          String id = strs[0].substring(1,strs[0].length());
          int t;
          if(j == jobstring.length - 1)
          {
            t = Integer.parseInt(strs[1].substring(0,strs[1].length()-1));
          }
          else
          {
            t = Integer.parseInt(strs[1]);
          }
          //System.out.println("i: " + i + " id: " + id + ", " + t);
          jobs[i][j] = new Job(id,t);
        }
      }
    } catch(IOException e)
    {
      e.printStackTrace();
    } finally
    {
      in.close();
    }
	}

  

  /**
   * test insert sort
   */
	@Test
	public void testSortInsert() 
  {
		for(int i = 0; i < 7; ++i)
    {
		StopWatch sw = new StopWatch();
      System.out.println("start sortInsert: " + (i+1));
      sw.start();
      Insertion.sortInsert(jobs[i]);
      sw.stop();
      System.out.println("end sortInsert times: " + sw.getNanoTime() + " nanosceonds.");
      for(int j = 0; j < jobs[i].length - 1; ++j)
      {
        assertTrue(jobs[i][j].compareTo(jobs[i][j]) <= 0);
      }
    }
	}

  /**
   * test insert sort with comparable
   */
	@Test
	public void testInsertComparable() 
  {
		for(int i = 0; i < 7; ++i)
    {
	    StopWatch sw = new StopWatch();
      System.out.println("start sortComparable: " + (i+1));
      sw.start();
      Insertion.sortComparable(jobs[i],jobs[i].length);
      sw.stop();
      System.out.println("end sortComparable times: " + sw.getNanoTime() + " nanosceonds.");
      for(int j = 0; j < jobs[i].length - 1; ++j)
      {
        assertTrue(jobs[i][j].compareTo(jobs[i][j]) <= 0);
      }
    }
	}
	
  /**
   * test insert sort with binary search
   */
	@Test
	public void testInsertBinary() 
  {
		for(int i = 0; i < 7; ++i)
    {
      StopWatch sw = new StopWatch();
      System.out.println("start sortBinary: " + (i+1));
      sw.start();
      Insertion.sortBinary(jobs[i],jobs[i].length);
      sw.stop();
      System.out.println("end sortBinary times: " + sw.getNanoTime() + " nanosceonds.");
      for(int j = 0; j < jobs[i].length - 1; ++j)
      {
        assertTrue(jobs[i][j].compareTo(jobs[i][j]) <= 0);
      }
    }
	}
	
  /**
   * test merge sort
   */
	@Test
	public void testMerge() 
  {
		for(int i = 0; i < 7; ++i)
    {
      StopWatch sw = new StopWatch();
      System.out.println("start sortMerge: " + (i+1));
      sw.start();
      Merge.sortMerge(jobs[i],jobs[i].length);
      sw.stop();
      System.out.println("end sortMerge times: " + sw.getNanoTime() + " nanosceonds.");
      for(int j = 0; j < jobs[i].length - 1; ++j)
      {
        assertTrue(jobs[i][j].compareTo(jobs[i][j]) <= 0);
      }
    }
	}
	
  /**
   * test heap sort
   */
	@Test
	public void testHeapSort() 
  {
		for(int i = 0; i < 7; ++i)
    {
      StopWatch sw = new StopWatch();
      System.out.println("start sortHeap: " + (i+1));
      sw.start();
      Heap.sortHeap(jobs[i],jobs[i].length);
      sw.stop();
      System.out.println("end sortHeap times: " + sw.getNanoTime() + " nanosceonds.");
      for(int j = 0; j < jobs[i].length - 1; ++j)
      {
        assertTrue(jobs[i][j].compareTo(jobs[i][j]) <= 0);
      }
    }
	}
}
