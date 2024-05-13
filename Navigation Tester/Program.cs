using Navigation_Tester.Common;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Navigation_Tester
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("App started");
            Loader.Load();
            Console.WriteLine("App Completed");
            Console.Read();
        }
    }
}
