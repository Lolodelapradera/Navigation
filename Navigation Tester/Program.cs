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
            uint mapId = 0;
            var moveToTargetPosition = new Vector3(-8831.653f, -97.78971f, 84.78954f);
            var playerPosition = new Vector3(-8949.95f, -132.493f, 83.5312f);

            var results = Loader.CalculatePath(mapId, playerPosition, moveToTargetPosition);
            foreach ( var result in results )
            {
                Console.WriteLine("results: " + result.ToString());
            }
           


            Console.WriteLine("App Completed");
            Console.Read();
        }
    }
}
