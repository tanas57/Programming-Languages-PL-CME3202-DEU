using System;
using System.Collections.Generic;
public class Test
{
	public static void Main()
	{
		// your code goes here
		LinkedList<object> linked = new LinkedList<object>();
		linked.AddLast(10);
        linked.AddLast(7.5);
        
        foreach (var item in linked)
        {
            Console.WriteLine(item);
        }
        
        linked.AddLast("Programming languages");
        
        foreach (var item in linked)
        {
            Console.WriteLine(item);
        }
	}
}
